// SPDX-License-Identifier: MIT

#pragma once

#include <optional>
#include <concepts>
#include <string>
#include <string_view>

#include <fmt/core.h>
#include <fmt/chrono.h>

#include "common/types.h"
#include "common/macros.h"

FILE_WARNING_PUSH;
// fmt lib throws a bunch of this warning
FILE_WARNING_DISABLE(WARNING_ID_CONDITIONAL_EXPRESSION_IS_CONSTANT)

namespace common::strings
{
  template<typename type>
  concept is_char_type = requires
  {
    requires(std::same_as<type, char> || std::same_as<type, wchar_t>);
  };

  #if defined(_WIN32)
  std::optional<std::string>  wstring_to_utf8(std::wstring_view wide);
  std::optional<std::wstring> utf8_to_wstring(std::string_view utf8);
  #endif
  std::optional<std::string> sjis_to_utf8(std::string_view sjis);

  #if defined(_WIN32)
  std::string wstring_to_utf8_or_none(std::wstring_view wide);
  std::string wstring_to_utf8_or_panic(std::wstring_view wide);

  std::wstring utf8_to_wstring_or_none(std::string_view utf8);
  std::wstring utf8_to_wstring_or_panic(std::string_view utf8);
  #endif

  std::string sjis_to_utf8_or_none(std::string_view sjis);
  std::string sjis_to_utf8_or_panic(std::string_view sjis);

  // format a string
  // note: fmtstr must be constexpr
  template<typename ...Args>
  ALWAYS_INLINE std::string format(fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    return fmt::format(fmtstr, std::forward<Args>(args)...);
  }

  // convert string to lowercase
  template<typename type>
  requires(is_char_type<type>)
  ALWAYS_INLINE constexpr std::basic_string<type> lowercase(std::basic_string_view<type> s)
  {
    std::basic_string<type> out{ s };

    std::transform(out.begin(), out.end(), out.begin(), [&](type ch) {
        return std::tolower(ch);
    });

    return out;
  }

  // convert string to uppercase
  template<typename type>
  requires(is_char_type<type>)
  ALWAYS_INLINE constexpr std::basic_string<type> uppercase(std::basic_string_view<type> s)
  {
    std::basic_string<type> out{ s };

    std::transform(out.begin(), out.end(), out.begin(), [&](type ch) {
        return std::toupper(ch);
    });

    return out;
  }
}

FILE_WARNING_POP;
