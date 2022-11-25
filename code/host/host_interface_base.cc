#include "common/log.h"

#include "host/host_interface_base.h"

set_log_channel("host");

std::unique_ptr<host::host_interface_base> g_host_interface{ nullptr };

namespace host
{
  host_interface_base::host_interface_base() = default;
  host_interface_base::~host_interface_base() = default;

  vec2 host_interface_base::sample_pad_left_stick_xy()
  {
    std::lock_guard<std::mutex> lk(m_pad_handler_mutex);

    const auto axis = m_pad_handler->right_stick_axis();

    return { axis.x, axis.y };
  }

  vec2 host_interface_base::sample_pad_right_stick_xy()
  {
    std::lock_guard<std::mutex> lk(m_pad_handler_mutex);

    const auto axis = m_pad_handler->left_stick_axis();

    return { axis.x, axis.y };
  }

  void host_interface_base::start_game_frame()
  {
    log_trace("Starting in-game frame");

    // critical section
    {
      std::lock_guard<std::mutex> lk(m_pad_handler_mutex);

      m_game_button_buffer[m_game_button_buffer_index ^= 1] = m_pad_handler->current_buttons();
    }
  }
}
