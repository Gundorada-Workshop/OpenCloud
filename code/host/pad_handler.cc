#include "host/pad_handler.h"

#include "common/helpers.h"
#include "common/log.h"

set_log_channel("pad_handler");

namespace host
{
  // Clear all input actions
  void pad_handler::clear_actions()
  {
    m_analog_actions.clear();
    m_button_actions.clear();
  }

  // Register a button action which corresponds to an input
  void pad_handler::register_button_action(const button_action btn_action, buttons button, std::function<void(bool pressed)> callback)
  {
    m_button_actions[btn_action] = {
      .m_value = (button & m_buttons) != buttons::none,
      .m_input_key = button,
      .m_callback = callback
    };
  }

  // Register a button action which corresponds to inputs
  void pad_handler::register_button_action(const button_action btn_action, const std::vector<buttons>& input_buttons, std::function<void(bool pressed)> callback)
  {
    // We OR all buttons into one, so we can check if any are pressed when updating actions.
    buttons input_button = buttons::none;
    for (buttons button : input_buttons)
    {
      input_button |= button;
    }

    register_button_action(btn_action, input_button, callback);
  }

  // Register an analog action which corresponds to an input
  void pad_handler::register_analog_action(const analog_action ana_action, analog analog_axis, std::function<void(f32 axis)> callback)
  {
    axis axis_xy;
    f32 axis_val;

    // Poll the current analog value
    switch (analog_axis)
    {
      case analog::left_x:
      case analog::left_y:
        axis_xy = left_stick_axis();
        if (analog_axis == analog::left_x)
        {
          axis_val = axis_xy.x;
        }
        else
        {
          axis_val = axis_xy.y;
        }
        break;
      case analog::right_x:
      case analog::right_y:
        axis_xy = right_stick_axis();
        if (analog_axis == analog::right_x)
        {
          axis_val = axis_xy.x;
        }
        else
        {
          axis_val = axis_xy.y;
        }
        break;
      default:
        panicf("Unrecognized analog value {}", common::to_underlying(analog_axis));
        return;
    }

    m_analog_actions[ana_action] = {
      .m_value = axis_val,
      .m_input_key = analog_axis,
      .m_callback = callback
    };
  }

  // Set a callback for a button action
  void pad_handler::set_button_action_callback(const button_action btn_action, std::function<void(bool pressed)> callback)
  {
    auto it = m_button_actions.find(btn_action);
    if (it == m_button_actions.end())
    {
      log_warn("pad_handler::{}: Attempted to set a callback for action {}, but that action has not been registered!", __func__, common::to_underlying(btn_action));
      return;
    }

    auto& action = (*it).second;
    action.m_callback = callback;
  }

  // Set a callback for an analog action
  void pad_handler::set_analog_action_callback(const analog_action ana_action, std::function<void(f32 axis)> callback)
  {
    auto it = m_analog_actions.find(ana_action);
    if (it == m_analog_actions.end())
    {
      log_warn("pad_handler::{}: Attempted to set a callback for action {}, but that action has not been registered!", __func__, common::to_underlying(ana_action));
      return;
    }

    auto& action = (*it).second;
    action.m_callback = callback;
  }

  // Check the value of a button action
  bool pad_handler::check_button_action(const button_action btn_action)
  {
    auto it = m_button_actions.find(btn_action);
    if (it == m_button_actions.end())
    {
      log_warn("pad_handler::{}: Attempted to check value for action {}, but action has not been registered!", __func__, common::to_underlying(btn_action));
      return false;
    }

    auto& action = (*it).second;
    return action.m_value;
  }

  // Check the value of an analog action
  f32 pad_handler::check_analog_action(const analog_action ana_action)
  {
    auto it = m_analog_actions.find(ana_action);
    if (it == m_analog_actions.end())
    {
      log_warn("pad_handler::{}: Attempted to check value for action {}, but action has not been registered!", __func__, common::to_underlying(ana_action));
      return 0.0f;
    }

    auto& action = (*it).second;
    return action.m_value;
  }

  // Updates the values of actions
  void pad_handler::update_actions()
  {
    // Update buttons
    for (auto& kv : m_button_actions)
    {
      auto& action = kv.second;
      bool pressed = (action.m_input_key & m_buttons) != buttons::none;

      if (action.m_value != pressed && action.m_callback != nullptr)
      {
        // Pressed state has changed, defer callback
        m_button_action_callbacks.push_back(
        {
          .m_value = pressed,
          .m_callback = action.m_callback
        });
      }

      action.m_value = pressed;
    }

    // Update analog
    auto left_axis = left_stick_axis();
    auto right_axis = right_stick_axis();

    for (auto& kv : m_analog_actions)
    {
      auto& action = kv.second;

      switch (action.m_input_key)
      {
        case analog::left_x:
          action.m_value = left_axis.x;
          break;
        case analog::left_y:
          action.m_value = left_axis.y;
          break;
        case analog::right_x:
          action.m_value = right_axis.x;
          break;
        case analog::right_y:
          action.m_value = right_axis.y;
      }

      // Currently we defer a callback to execute every frame for analog actions
      if (action.m_callback != nullptr)
      {
        m_analog_action_callbacks.push_back(
        {
          .m_value = action.m_value,
          .m_callback = action.m_callback
        });
      }
    }
  }

  void pad_handler::do_action_callbacks()
  {
    for (const auto& action_callback : m_button_action_callbacks)
    {
      action_callback.m_callback(action_callback.m_value);
    }

    for (const auto& action_callback : m_analog_action_callbacks)
    {
      action_callback.m_callback(action_callback.m_value);
    }

    m_button_action_callbacks.clear();
    m_analog_action_callbacks.clear();
  }
}
