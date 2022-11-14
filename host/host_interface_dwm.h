#pragma once
#include <wil/resource.h>
#include <memory>
#include <string_view>

namespace host
{
  class dwm_interface
  {
  public:
    using ptr = std::unique_ptr<dwm_interface>;

    // create a windows host interface
    static bool create(std::string_view name);
  public:
    dwm_interface();
    ~dwm_interface();

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

    bool m_message_pump_quit_requested{ false };
  };
}

extern host::dwm_interface::ptr g_host_interface;
