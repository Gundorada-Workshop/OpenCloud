#pragma once

namespace common
{
  enum class platform
  {
    windows
  };

  constexpr platform platform_type()
  {
    return platform::windows;
  }
}