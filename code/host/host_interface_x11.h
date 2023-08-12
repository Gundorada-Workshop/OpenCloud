#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>

#include <memory>
#include <string_view>

#include "common/types.h"
#include "common/bits.h"
#include "common/window_handle.h"

#include "host/host_interface_base.h"
#include "host/pad_handler.h"

namespace host
{
  class x11_interface final : public host_interface_base
  {
  public:
    x11_interface();
    ~x11_interface();

    // create an xlib host interface
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

    // get the window handle
    common::native_window_handle_type window_handle() override;

  private:
    Display* m_display = nullptr;
    sint     m_screen;
    Window   m_window_handle;
  };
}
