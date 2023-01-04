#include "common/log.h"
#include "common/strings.h"
#include "common/dynamic_library.h"

#include "host/host_interface_dwm.h"
#include "host/xinput_pad_handler.h"

set_log_channel("dwm");

using namespace common;

namespace host
{
  dwm_interface::dwm_interface() = default;
  dwm_interface::~dwm_interface() = default;

  LRESULT CALLBACK dwm_interface::winproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
  {
    switch (msg)
    {
    case WM_SIZE:
      g_host_interface->handle_render_window_resize(LOWORD(lparam), HIWORD(lparam));
      break;
    case WM_CLOSE:
    case WM_QUIT:
      g_host_interface->request_message_pump_quit();
      break;
    default:
      return DefWindowProcW(hwnd, msg, wparam, lparam);
    }

    return 0;
  }

  bool dwm_interface::create(std::string_view name)
  {
    log_debug("Creating DWM interface");

    auto host_interface = std::make_unique<dwm_interface>();

    host_interface->set_window_title(name);
    host_interface->set_module(GetModuleHandleW(nullptr));

    if (!host_interface->register_window_class(name))
    {
      log_error("Failed to register window class");

      return false;
    }

    host_interface->m_pad_handler = xinput_pad_handler::create();

    g_host_interface = std::move(host_interface);

    return true;
  }

  bool dwm_interface::register_window_class(std::string_view class_name)
  {
    log_debug("Registering window class");

    const auto wide_class_name = strings::utf8_to_wstring_or_panic(class_name);

    const WNDCLASSEXW window_class_descriptor =
    {
      .cbSize = sizeof(WNDCLASSEXW),
      .style = 0,
      .lpfnWndProc = &dwm_interface::winproc,
      .cbClsExtra = 0,
      .cbWndExtra = 0,
      .hInstance = m_module_base,
      .hIcon = NULL,
      .hCursor = LoadCursorW(NULL, IDC_ARROW),
      .hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1),
      .lpszMenuName = NULL,
      .lpszClassName = wide_class_name.c_str(),
      .hIconSm = NULL
    };

    if (!RegisterClassExW(&window_class_descriptor))
      return false;

    return true;
  }

  bool dwm_interface::create_render_window()
  {
    log_debug("Creating render window");

    constexpr DWORD window_style = WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_SIZEBOX;
    constexpr DWORD window_style_ex = WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE;

    const auto wide_window_name = strings::utf8_to_wstring_or_panic(m_window_title);

    auto window_handle = CreateWindowExW(window_style_ex, wide_window_name.c_str(), wide_window_name.c_str(),
      window_style, CW_USEDEFAULT, CW_USEDEFAULT, 640, 448, nullptr, nullptr, m_module_base, nullptr);

    if (!window_handle)
    {
      present_user_error_dialog("Failed to create render window");

      return false;
    }

    m_window_handle.reset(window_handle);

    // show window/update window should set the window extent by sending a resize/paint event
    // so there's no need to set it here
    ShowWindow(m_window_handle.get(), SW_SHOW);

    if (!UpdateWindow(m_window_handle.get()))
    {
      present_user_error_dialog("Failed to update window");

      return false;
    }

    log_debug("Render window created");

    return true;
  }

  void dwm_interface::destroy_render_window()
  {
    m_window_handle.reset();
  }

  sint dwm_interface::run_message_pump()
  {
    log_debug("Starting Windows message pump");

    while (!m_message_pump_quit_requested)
    {
      m_pad_handler->poll();

      MSG msg;
      if (!GetMessageW(&msg, nullptr, 0, 0))
        continue;

      TranslateMessage(&msg);
      DispatchMessageW(&msg);
    }

    return EXIT_SUCCESS;
  }

  void dwm_interface::present_user_error_dialog(std::string_view message)
  {
    const auto wide_message = strings::utf8_to_wstring_or_panic(message);

    MessageBoxW(m_window_handle.get(), wide_message.c_str(), L"Error", MB_ICONERROR | MB_OK);
  }

  void dwm_interface::handle_render_window_resize(u32 width, u32 height)
  {
    m_window_extent = graph::urect::from_extent(width, height);

    log_debug("Window resize event: {}", m_window_extent);
  }

  common::native_window_handle_type dwm_interface::window_handle()
  {
    common::native_window_handle_type handle =
    {
      .window_handle = m_window_handle.get()
    };

    return handle;
  }
}
