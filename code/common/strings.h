#pragma once

#include <optional>
#include <concepts>
#include <string>
#include <string_view>

#include "common/types.h"
#include "common/panic.h"
#include "common/macros.h"
#include "common/platform.h"

namespace common::strings
{
  template<typename type>
  concept is_char_type = requires
  {
    requires(std::same_as<type, char> || std::same_as<type, wchar_t>);
  };

  #if PLATFORM_OS_WINDOWS
  // convert a wide utf16 string to narrow utf8
  // use at windows api boundary
  std::optional<std::string>  wstring_to_utf8(std::wstring_view wide);

  // convert a narrow utf8 string to wide utf16
  // use at windows api boundary
  std::optional<std::wstring> utf8_to_wstring(std::string_view utf8);

  // converts a wide utf16 string to a narrow utf8 string
  // if the string cannot be converted returns an empty string
  std::string wstring_to_utf8_or_none(std::wstring_view wide);

  // converts a wide utf16 string to a narrow utf8 string
  // if the string cannot be converted panics the application
  std::string wstring_to_utf8_or_panic(std::wstring_view wide);

  // convert a narrow utf8 string to wide utf16
  // if the string cannot be converted returns an empty string
  std::wstring utf8_to_wstring_or_none(std::string_view utf8);

  // convert a narrow utf8 string to wide utf16
  // if the string cannot be converted panics the application
  std::wstring utf8_to_wstring_or_panic(std::string_view utf8);
  #endif

  // converts a narrow shift-jis string to a narrow utf8
  std::optional<std::string> sjis_to_utf8(std::string_view sjis);

  // converts a narrow shift-jis string to a narrow utf8
  // the the string cannot be converted returns an empty string
  std::string sjis_to_utf8_or_none(std::string_view sjis);

  // converts a narrow shift-jis string to a narrow utf8
  // if the string cannot be converted panics the application
  std::string sjis_to_utf8_or_panic(std::string_view sjis);

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
        common::panic("Buffer overflow in safe_arraycat");
      }

      std::fill(dest.begin() + dest_size, dest.end(), 0);
      std::copy(src.begin(), src.end(), &dest[dest_size]);
    #endif
  }
}
