#include "host/pad_handler.h"

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
  void pad_handler::register_button_action(const std::string_view& action_name, buttons button, std::function<void(bool pressed)> callback)
  {
    m_button_actions[action_name.data()] = {
      .m_value = (button & m_buttons) != buttons::none,
      .m_input_key = button,
      .m_callback = callback
    };
  }

  // Register a button action which corresponds to inputs
  void pad_handler::register_button_action(const std::string_view& action_name, const std::vector<buttons>& input_buttons, std::function<void(bool pressed)> callback)
  {
    // We OR all buttons into one, so we can check if any are pressed when updating actions.
    buttons input_button = buttons::none;
    for (buttons button : input_buttons)
    {
      input_button |= button;
    }

    register_button_action(action_name, input_button, callback);
  }

  // TODO:
  //void register_analog_action(const std::string_view& action, ... axis);

  // Set a callback for a button action
  void pad_handler::set_button_action_callback(const std::string_view& action_name, std::function<void(bool pressed)> callback)
  {
    auto it = m_button_actions.find(action_name.data());
    if (it == m_button_actions.end())
    {
      log_warn("pad_handler::{}: Attempted to set a callback for action {}, but that action has not been registered!", __func__, action_name);
      return;
    }

    auto& action = (*it).second;
    action.m_callback = callback;
  }

  // Set a callback for an analog action
  void pad_handler::set_analog_action_callback(const std::string_view& action_name, std::function<void(f32 axis)> callback)
  {
    auto it = m_analog_actions.find(action_name.data());
    if (it == m_analog_actions.end())
    {
      log_warn("pad_handler::{}: Attempted to set a callback for action {}, but that action has not been registered!", __func__, action_name);
      return;
    }

    auto& action = (*it).second;
    action.m_callback = callback;
  }

  // Check the value of a button action
  bool pad_handler::check_button_action(const std::string_view& action_name)
  {
    auto it = m_button_actions.find(action_name.data());
    if (it == m_button_actions.end())
    {
      log_warn("pad_handler::{}: Attempted to check value for action {}, but action has not been registered!", __func__, action_name);
      return false;
    }

    auto& action = (*it).second;
    return action.m_value;
  }

  // Check the value of an analog action
  f32 pad_handler::check_analog_action(const std::string_view& action_name)
  {
    auto it = m_analog_actions.find(action_name.data());
    if (it == m_analog_actions.end())
    {
      log_warn("pad_handler::{}: Attempted to check value for action {}, but action has not been registered!", __func__, action_name);
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

    // TODO: Update analog
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
