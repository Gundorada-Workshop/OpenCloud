#pragma once
#include <wil/resource.h>
#include <memory>
#include <string_view>

#include "common/types.h"
#include "common/bits.h"

#include "host/host_interface_base.h"
#include "host/pad_handler.h"

namespace host
{
  class dwm_interface final : public host_interface_base
  {
  public:
    dwm_interface();
    ~dwm_interface();

    // create a windows host interface
    static bool create(std::string_view name);

  public:
    // create the render window
    bool create_render_window() override;

    // destroy the render window
    void destroy_render_window() override;

    // run the message pump
    sint run_message_pump() override;

    // create an error dialog
    void present_user_error_dialog(std::string_view msg) override;

    // resize the render window
    void handle_render_window_resize(u32 width, u32 height) override;

  private:
    // win32 message pump
    static LRESULT CALLBACK winproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

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

  private:
    // native window handle
    wil::unique_hwnd m_window_handle{ };

    // native module instance
    HINSTANCE m_module_base{ NULL };
  };
}
