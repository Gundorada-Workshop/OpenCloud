#include "common/log.h"
#include "common/strings.h"
#include "common/dynamic_library.h"

#include "host/host_interface_x11.h"
#include "host/linux_pad_handler.h"

set_log_channel("x11");

using namespace common;

namespace host
{
  x11_interface::x11_interface()
  {
    // Acquire XServer display
    m_display = XOpenDisplay(NULL);
    if (m_display == NULL) {
        common::debug::panic("Cannot open display");
    }
  };
  x11_interface::~x11_interface()
  {
    XCloseDisplay(m_display);
  };

  bool x11_interface::create(std::string_view name)
  {
    log_debug("Creating X11 interface");

    auto host_interface = std::make_unique<x11_interface>();

    host_interface->set_window_title(name);
    host_interface->m_pad_handler = linux_pad_handler::create();

    g_host_interface = std::move(host_interface);

    return true;
  }

  bool x11_interface::create_render_window()
  {
    log_debug("Creating render window");

    m_screen = DefaultScreen(m_display);
    m_window_handle = XCreateSimpleWindow(m_display, RootWindow(m_display, m_screen), 10, 10, 100, 100, 1,
                                          BlackPixel(m_display, m_screen), WhitePixel(m_display, m_screen));
    XStoreName(m_display, m_window_handle, m_window_title.c_str());
    XSelectInput(m_display, m_window_handle, ExposureMask | KeyPressMask);
    XMapWindow(m_display, m_window_handle);

    // Get rid of this later, it's just here for testing.
    // Render window won't pop up without something like this.
    XEvent e;
    const char* msg = "test!";
    XNextEvent(m_display, &e);
    if (e.type == Expose) {
        XFillRectangle(m_display, m_window_handle, DefaultGC(m_display, m_screen), 20, 20, 10, 10);
        XDrawString(m_display, m_window_handle, DefaultGC(m_display, m_screen), 10, 50, msg, strlen(msg));
    }

    log_debug("Render window created");

    return true;
  }

  void x11_interface::destroy_render_window()
  {
    XDestroyWindow(m_display, m_window_handle);
  }

  sint x11_interface::run_message_pump()
  {
    log_debug("Starting Linux X11 message pump");
    log_info("Starting Linux X11 message pump");

    while (!m_message_pump_quit_requested)
    {
      //if (m_pad_handler != nullptr)
      m_pad_handler->poll();

    }

    log_info("Ending Linux X11 message pump");
    return EXIT_SUCCESS;
  }

  void x11_interface::present_user_error_dialog(std::string_view message)
  {
    log_info("ATTEMPTED TO CREATE USER DIALOG");
  }

  void x11_interface::handle_render_window_resize(u32 width, u32 height)
  {
    m_window_extent = graph::urect::from_extent(width, height);

    log_debug("Window resize event: {}", m_window_extent);
  }

  common::native_window_handle_type x11_interface::window_handle()
  {
    common::native_window_handle_type handle =
    {
      .connection = m_display,
      .handle     = &m_window_handle
    };

    return handle;
  }
}
