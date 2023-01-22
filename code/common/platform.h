#pragma once

namespace common
{
  enum class platform
  {
    windows,
    linuxplatform // plain 'linux' is a g++ predefined macro
  };

  constexpr platform platform_type()
  {
    #if defined(_WIN32)
      return platform::windows;
    #elif defined(__linux__)
      return platform::linuxplatform;
    #else
      static_assert(false, "Undefined target platform");
    #endif
  }
}