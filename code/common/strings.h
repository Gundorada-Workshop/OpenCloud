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

  // Cross-platform bounds-checked strcpy
  void xplat_strcpy_s(char* dest, size_t dest_size, const char* src);
  
  // Alias for common::debug::panic so that it can be used in templates with minimal
  // source disruption
  void local_panic_alias(const std::string&);

  // Non-overflowing str->std::array<char> converter 
  template<size_t N>
  ALWAYS_INLINE void safe_str_to_array(std::array<char, N>& dest, const std::string& src)
  {
    #if defined(_MSC_VER)
      strcpy_s(dest.data(), N, src.c_str());
    #else
      // Inefficient, but should work...
      const auto& truncated_string = src.substr(0, N-1); // Room for null terminator required?
      std::fill(dest.begin(), dest.end(), 0);
      std::copy(src.begin(), src.end(), dest.data());
    #endif
  }

  // Bounds-checked concatenation for two std::array<char>s
  template<size_t N, size_t M>
  ALWAYS_INLINE void safe_arraycat(std::array<char, N>& dest, const std::array<char, M>& src)
  {
    #if defined(_MSC_VER)
      strcat_s(dest.data(), N, src.data());
    #else
      // No safety check on strlen...
      size_t dest_size = strlen(dest.data());
      size_t src_size  = strlen(src.data());

      if (dest_size + src_size + 1 > N)
      {
        local_panic_alias("Buffer overflow in safe_arraycat");
      }

      std::fill(dest.begin() + dest_size, dest.end(), 0);
      std::copy(src.begin(), src.end(), &dest[dest_size]);
    #endif
  }

}

FILE_WARNING_POP;
