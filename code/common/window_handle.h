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
  struct window_handle_t<platform::linuxplatform>
  {
    // Don't know the type to go in here yet
    //HWND window_handle{ nullptr };
  };
  #endif

  using native_window_handle_type = window_handle_t<platform_type()>;
}
