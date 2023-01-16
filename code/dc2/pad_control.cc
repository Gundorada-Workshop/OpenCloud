#include "common/debug.h"
#include "common/log.h"

#include "dc2/pad_control.h"

#include "host/host_interface_dwm.h"

set_log_channel("pad_control");

// 002ED3E0
// Clears all recorded actions
void CPadControl::Reset()
{
  log_trace("CPadControl::{}()", __func__);

  m_buttons.clear();
  m_analog.clear();
}

// 002ED460
// Registers up to two buttons for a particular action
// TODO: Accept a vector for an arbitrary number of buttons
void CPadControl::RegisterBtn(const std::string_view& action_name, host::pad_handler::buttons btn1, host::pad_handler::buttons btn2)
{
  log_trace("CPadControl::{}({}, {:#X}, {:#X})", __func__, action_name, std::to_underlying(btn1), std::to_underlying(btn2));

  m_buttons[action_name.data()] = {
    .m_value = false,
    .m_input_key = btn1 | btn2
  };
}

// 002ED4A0
// Registers an axis for a particular aciton
void CPadControl::RegisterAnalog(const std::string_view& action_name, EPadAxis axis)
{
  log_trace("CPadControl::{}({}, {})", __func__, action_name, std::to_underlying(axis));

  m_analog[action_name.data()] = {
    .m_value = 0.0f,
    .m_input_axis = axis
  };
}

// 002ED4E0
// Checks the button value for a particular action
bool CPadControl::Btn(const std::string_view& action_name)
{
  log_trace("CPadControl::{}({})", __func__, action_name);

  if (!m_buttons.contains(action_name.data()))
  {
    return false;
  }

  return m_buttons[action_name.data()].m_value;
}

// 002ED520
// Checks the analog value for a particular action
f32 CPadControl::Analog(const std::string_view& action_name)
{
  log_trace("CPadControl::{}({})", __func__, action_name);

  if (!m_analog.contains(action_name.data()))
  {
    return 0.0f;
  }

  return m_analog[action_name.data()].m_value;
}

// 002ED550
// Updates each action's button pressed/analog value
void CPadControl::Update()
{
  log_trace("CPadControl::{}()", __func__);

  for (auto& button : m_buttons)
  {
    // Update recorded values for buttons
    button.second.m_value = g_host_interface->pad_button_any_pressed(button.second.m_input_key);
  }

  // TODO: Check analog values
  todo;
}