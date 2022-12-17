#pragma once
#include <optional>
#include <string>
#include <string_view>

#include <fmt/core.h>
#include <fmt/chrono.h>

#include "common/types.h"
#include "common/macros.h"

FILE_DISABLE_WARNING(WARNING_ID_CONDITIONAL_EXPRESSION_IS_CONSTANT);

namespace common::strings
{
#if defined(_WIN32)
  std::optional<std::string>  wstring_to_utf8(std::wstring_view wide);
  std::optional<std::wstring> utf8_to_wstring(std::string_view utf8);
  std::optional<std::string> sjis_to_utf8(std::string_view sjis);
#endif // _WIN32

  // format a string
  // note: fmtstr must be constexpr
  template<typename ...Args>
  std::string format(fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    return fmt::format(fmtstr, std::forward<Args>(args)...);
  }

  // convert string to lowercase
  static inline std::string lowercase(std::string_view s)
  {
    std::string out{ s };

    std::transform(out.begin(), out.end(), out.begin(), [&](char ch) {
        return std::tolower(ch);
    });

    return out;
  }

  // convert string to uppercase
  static inline std::string upercase(std::string_view s)
  {
    std::string out{ s };

    std::transform(out.begin(), out.end(), out.begin(), [&](char ch) {
        return std::toupper(ch);
    });

    return out;
  }
}
