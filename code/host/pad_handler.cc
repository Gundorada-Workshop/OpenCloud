#include "host/pad_handler.h"

namespace host
{
  pad_handler::pad_handler() = default;
  pad_handler::~pad_handler() = default;

  pad_handler::buttons pad_handler::current_buttons()
  {
    std::lock_guard<std::mutex> lk(m_input_mutex);

    return m_button_buffers[m_current_button_buffer];
  }

  pad_handler::buttons pad_handler::previous_buttons()
  {
    std::lock_guard<std::mutex> lk(m_input_mutex);

    return m_button_buffers[m_current_button_buffer ^ 1];
  }

  pad_handler::buttons pad_handler::changed_buttons()
  {
    buttons current_button_state{ };
    buttons previous_button_state{ };

    {
      std::lock_guard<std::mutex> lk(m_input_mutex);

      current_button_state = m_button_buffers[m_current_button_buffer];
      previous_button_state = m_button_buffers[m_current_button_buffer ^ 1];
    }

    return current_button_state ^ previous_button_state;
  }

  pad_handler::axis pad_handler::right_stick_axis()
  {
    std::lock_guard<std::mutex> lk(m_input_mutex);

    return m_right_stick_axis;
  }

  pad_handler::axis pad_handler::left_stick_axis()
  {
    std::lock_guard<std::mutex> lk(m_input_mutex);

    return m_left_stick_axis;
  }

  pad_handler::axis pad_handler::trigger_axis()
  {
    std::lock_guard<std::mutex> lk(m_input_mutex);

    return m_trigger_axis;
  }
}
