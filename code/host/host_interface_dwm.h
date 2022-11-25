#pragma once
#include <wil/resource.h>
#include <memory>
#include <string_view>

#include "common/types.h"
#include "common/bits.h"

#include "host/pad_handler.h"

namespace host
{
  class dwm_interface
  {
  public:
    dwm_interface();
    ~dwm_interface();

    // create a windows host interface
    static bool create(std::string_view name);

  public:
    // create the render window
    bool create_render_window();

    // destroy the render window
    void destroy_render_window();

    // run the message pump
    int run_message_pump();

    // create an error dialog
    void error_dialog(std::string_view msg);

    // resize the render window
    void handle_resize(u32 width, u32 height);

    // start a new in-game frame
    void start_game_frame();

    // sample the left stick axis
    vec2 sample_pad_left_stick_xy();

    // sample the right stick axis
    vec2 sample_pad_right_stick_xy();

  public:
    // get the window name
    inline void set_window_name(std::string_view name)
    {
      m_window_title = name;
    }

    // set the window handle
    inline std::string_view get_title() const
    {
      return m_window_title;
    }

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

  private:
    // window loop
    static LRESULT CALLBACK winproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

  private:
    // register the window
    bool register_window_class(std::string_view class_name);

  private:
    // get the window handle
    inline HANDLE get_window_handle() const
    {
      return m_window_handle.get();
    }

    // set the hinstance
    inline void set_module(HINSTANCE module_handle)
    {
      m_module_base = module_handle;
    }

    // get the hinstance
    inline HINSTANCE get_module() const
    {
      return m_module_base;
    }

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

  private:
    std::string m_window_title{ };

    // native window handle
    wil::unique_hwnd m_window_handle{ };

    // native module instance
    HINSTANCE m_module_base{ NULL };

    // mutex for input
    std::mutex m_pad_handler_mutex{ };

    // handle to the pad
    std::unique_ptr<pad_handler> m_pad_handler{ nullptr };

    // buffer of buttons
    std::array<pad_handler::buttons, 2> m_game_button_buffer{ };

    // index into the button double buffer
    usize m_game_button_buffer_index{ 0 };

    // should we exit?
    std::atomic<bool> m_message_pump_quit_requested{ false };
  };
}

extern std::unique_ptr<host::dwm_interface> g_host_interface;
