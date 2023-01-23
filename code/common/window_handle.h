#pragma once
#if defined(_WIN32)
  #include <Windows.h>
#elif defined(__linux__)
#else
  static_assert(false, "Not implemented");
#endif

#include "common/platform.h"


namespace common
{
  template<enum platform>
  struct window_handle_t;

  #if defined(_WIN32)
  template<>
  struct window_handle_t<platform::windows>
  {
    HWND window_handle{ nullptr };
  };
  #elif defined(__linux__)
  template<>
  struct window_handle_t<platform::linux_x11>
  {
    void* connection; // Display from e.g. XOpenDisplay(NULL)
    void* handle;     // Window from e.g. XCreateSimpleWindow(...)
  };
  #endif

  using native_window_handle_type = window_handle_t<platform_type()>;
}
