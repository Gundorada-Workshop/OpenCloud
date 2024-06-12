// SPDX-License-Identifier: MIT

#pragma once

namespace common
{
  enum class platform
  {
    windows,
    linux_x11
  };

  constexpr platform platform_type()
  {
    #if defined(_WIN32)
      return platform::windows;
    #elif defined(__linux__)
      return platform::linux_x11;
    #else
      static_assert(false, "Undefined target platform");
    #endif
  }
}