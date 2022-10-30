#pragma once
#include <optional>
#include <string>
#include <string_view>

#include <fmt/core.h>

#include "types.h"

namespace common::strings
{
#if defined(_WIN32)
  std::optional<std::string>  to_utf8(std::wstring_view wide);
  std::optional<std::wstring> to_wstring(std::string_view utf8);
#endif // _WIN32

  // format a string
  // note: fmtstr must be constexpr
  template<typename ...Args>
  std::string format(fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    return fmt::format(fmtstr, std::forward<Args>(args)...);
  }
}
