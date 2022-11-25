#pragma once
#include "common/types.h"
#include "common/bits.h"

#include "host/pad_handler.h"

namespace host
{
  class host_interface_base
  {
  public:
    host_interface_base();
    virtual ~host_interface_base();

    // create the host window
    virtual bool create_render_window() = 0;

    // destroy the render window
    virtual void destroy_render_window() = 0;

    // run the host message loop
    virtual sint run_message_pump() = 0;

    // handle a resize event from the window pump
    virtual void handle_render_window_resize(u32 width, u32 height) = 0;

    // present the user with an error in a host specific way
    virtual void present_user_error_dialog(std::string_view message) = 0;

  public:
    // sample the left stick axis
    vec2 sample_pad_left_stick_xy();

    // sample the right stick axis
    vec2 sample_pad_right_stick_xy();

    // start a new in-game frame
    void start_game_frame();

  public:
    // request the message pump exit
    inline void request_message_pump_quit()
    {
      m_message_pump_quit_requested = true;
    }

    // check if the message pump was requested to exit
    inline bool message_pump_quit_requested() const
    {
      return m_message_pump_quit_requested;
    }

    // check if any buttons started being pressed this frame
    inline bool pad_button_any_down(pad_handler::buttons btn)
    {
      return common::bits::to_bool(delta_frame_buttons() & btn);
    }

    // check if any buttons started being released this frame
    inline bool pad_button_any_up(pad_handler::buttons btn)
    {
      return common::bits::to_bool(delta_frame_buttons() & (~btn));
    }

    // check if all buttons started being pressed this frame
    inline bool pad_button_all_down(pad_handler::buttons btn)
    {
      return (delta_frame_buttons() & btn) == btn;
    }

    // check if all buttons started being released this frame
    inline bool pad_button_all_up(pad_handler::buttons btn)
    {
      return (delta_frame_buttons() & (~btn)) == btn;
    }

    // check if any button is pressed this frame
    inline bool pad_button_any_pressed(pad_handler::buttons btn)
    {
      return common::bits::to_bool(current_frame_buttons() & btn);
    }

    // check if any button is not pressed this frame
    inline bool pad_button_any_unpressed(pad_handler::buttons btn)
    {
      return common::bits::to_bool(current_frame_buttons() & (~btn));
    }

    // check if all buttons are pressed this frame
    inline bool pad_button_all_pressed(pad_handler::buttons btn)
    {
      return (current_frame_buttons() & btn) == btn;
    }

    // check if all buttons are not pressed this frame
    inline bool pad_button_all_unpressed(pad_handler::buttons btn)
    {
      return (current_frame_buttons() & (~btn)) == btn;
    }

    // sample the left stick x value
    inline f32 sample_pad_left_stick_x()
    {
      const auto axis = sample_pad_left_stick_xy();

      return axis.x;
    }

    // sample the left stick y value
    inline f32 sample_pad_left_stick_y()
    {
      const auto axis = sample_pad_left_stick_xy();

      return axis.y;
    }

    // sample the right stick x value
    inline f32 sample_pad_right_stick_x()
    {
      const auto axis = sample_pad_right_stick_xy();

      return axis.x;
    }

    // sample the right stick y value
    inline f32 sample_pad_right_stick_y()
    {
      const auto axis = sample_pad_right_stick_xy();

      return axis.y;
    }

  protected:
    inline pad_handler::buttons current_frame_buttons()
    {
      return m_game_button_buffer[m_game_button_buffer_index];
    }

    inline pad_handler::buttons previous_frame_buttons()
    {
      return m_game_button_buffer[m_game_button_buffer_index ^ 1];
    }

    inline pad_handler::buttons delta_frame_buttons()
    {
      return current_frame_buttons() ^ previous_frame_buttons();
    }

    inline void set_window_title(std::string_view name)
    {
      m_window_title = std::string{ name };
    }

  protected:
    // name of the window
    std::string m_window_title{ };

    // should we exit?
    std::atomic<bool> m_message_pump_quit_requested{ false };

    // mutex for input
    std::mutex m_pad_handler_mutex{ };

    // handle to the pad
    std::unique_ptr<pad_handler> m_pad_handler{ nullptr };

    // buffer of buttons
    std::array<pad_handler::buttons, 2> m_game_button_buffer{ };

    // index into the button double buffer
    usize m_game_button_buffer_index{ 0 };
  };
}

extern std::unique_ptr<host::host_interface_base> g_host_interface;