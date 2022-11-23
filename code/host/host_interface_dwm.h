#pragma once
#include <wil/resource.h>
#include <memory>
#include <string_view>

#include "common/types.h"
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

  public:
    inline void set_window_name(std::string_view name)
    {
      m_window_title = name;
    }

    inline std::string_view get_title() const
    {
      return m_window_title;
    }

    inline HANDLE get_window_handle() const
    {
      return m_window_handle.get();
    }

    inline void set_module(HINSTANCE module_handle)
    {
      m_module_base = module_handle;
    }

    inline HINSTANCE get_module() const
    {
      return m_module_base;
    }

    inline void quit_message_pump()
    {
      m_message_pump_quit_requested = true;
    }

    // check if a button is being pressed
    inline bool pad_button_down(pad_handler::buttons btn)
    {
      return (m_pad_handler->changed_buttons() & btn) == btn;
    }

    // check if a button has been released
    inline bool pad_button_up(pad_handler::buttons btn)
    {
      return (m_pad_handler->changed_buttons() & (~btn)) == btn;
    }

    inline bool pad_button_pressed(pad_handler::buttons btn)
    {
      return (m_pad_handler->current_buttons() & btn) == btn;
    }

    inline bool pad_button_unpressed(pad_handler::buttons btn)
    {
      return (m_pad_handler->current_buttons() & (~btn)) == btn;
    }

    inline std::pair<f32, f32> pad_right_thumb_xy()
    {
      const auto axis = m_pad_handler->right_stick_axis();

      return { axis.x, axis.y };
    }

    inline std::pair<f32, f32> pad_left_thumb_xy()
    {
      const auto axis = m_pad_handler->left_stick_axis();

      return { axis.x, axis.y };
    }

    inline f32 pad_right_thumb_x()
    {
      const auto [x, y] = pad_right_thumb_xy();

      return x;
    }

    inline f32 pad_right_thumb_y()
    {
      const auto [x, y] = pad_right_thumb_xy();

      return y;
    }

    inline f32 pad_left_thumb_x()
    {
      const auto [x, y] = pad_left_thumb_xy();

      return x;
    }

    inline f32 pad_left_thumb_y()
    {
      const auto [x, y] = pad_left_thumb_xy();

      return y;
    }
  private:
    // window loop
    static LRESULT CALLBACK winproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

  private:
    // register the window
    bool register_window_class(std::string_view class_name);

  private:
    std::string m_window_title{ };

    // native window handle
    wil::unique_hwnd m_window_handle{ };

    // native module instance
    HINSTANCE m_module_base{ NULL };

    std::unique_ptr<pad_handler> m_pad_handler{ nullptr };

    bool m_message_pump_quit_requested{ false };
  };
}

extern std::unique_ptr<host::dwm_interface> g_host_interface;
