#pragma once
#include <Windows.h>
#include "common/platform.h"

namespace common
{
  template<enum platform>
  struct window_handle_t;

  template<>
  struct window_handle_t<platform::windows>
  {
    HWND window_handle{ nullptr };
  };

  using native_window_handle_type = window_handle_t<platform_type()>;
}