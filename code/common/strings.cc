#if defined(_WIN32)
  #include <Windows.h>
#elif defined(__linux__)
  #include <cstdlib>
  #include <iconv.h>
  #include <wchar.h>
#endif

#include "common/strings.h"
#include "common/debug.h"

namespace common::strings
{
  #if defined(_WIN32)
  std::optional<std::string> wstring_to_utf8(std::wstring_view wide)
  {
    if (wide.empty())
      return "";

    auto size = WideCharToMultiByte(CP_UTF8, 0, wide.data(),
      static_cast<int>(wide.size()), nullptr, 0, 0, nullptr);

    if (size < 1)
      return std::nullopt;

    std::string out;
    out.resize(static_cast<usize>(size));

    size = WideCharToMultiByte(CP_UTF8, 0, wide.data(),
      static_cast<int>(wide.size()), out.data(), static_cast<int>(out.size()), 0, nullptr);

    if (size < 1)
      return std::nullopt;

    return out;
  }

  std::optional<std::wstring> utf8_to_wstring(std::string_view utf8)
  {
    if (utf8.empty())
      return L"";

    auto size = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), static_cast<int>(utf8.size()), nullptr, 0);

    if (size < 1)
      return std::nullopt;

    std::wstring out;
    out.resize(static_cast<usize>(size));

    size = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), static_cast<int>(utf8.size()),
      out.data(), static_cast<int>(out.size()));

    if (size < 1)
      return std::nullopt;

    return out;
  }
  #endif

  std::optional<std::string> sjis_to_utf8(std::string_view sjis)
  {
    if (sjis.empty())
      return "";

    #if defined(_WIN32)
    static constexpr UINT CP_SJIS = 932;
    auto size = MultiByteToWideChar(CP_SJIS, 0, sjis.data(), static_cast<int>(sjis.size()), nullptr, 0);
    if (size < 1)
      return std::nullopt;

    std::wstring out;
    out.resize(static_cast<usize>(size));

    size = MultiByteToWideChar(CP_SJIS, 0, sjis.data(), static_cast<int>(sjis.size()),
      out.data(), static_cast<int>(out.size()));

    if (size < 1)
      return std::nullopt;

    return wstring_to_utf8(out);
    #elif defined(__linux__)
    // Make a copy of the input string in case iconv alters it
    // +1 to make room for a null-terminator we'll add on the end
    size_t buf_in_size = sjis.size() + 1;
    char in_buf[buf_in_size];
    std::strncpy(in_buf, sjis.data(), sjis.size());
    // Ensure it's null-terminated: string_view doesn't guarantee null-termination
    in_buf[sjis.size()] = '\0';

    // Create pointers to be fed into iconv
    char* ptr_in = static_cast<char*>(in_buf);
    size_t buf_out_size = buf_in_size*6; // UTF8 can be a maximum of 6 bytes/symbol, SHIFT-JIS can be a minimum of 1 byte/symbol
    char buf_out[buf_out_size];
    char* ptr_out = static_cast<char*>(buf_out);

    // shift-jis char* to utf-8 char*
    // //IGNORE flag will drop anything that can't be utf8-encoded
    auto descriptor = iconv_open("UTF-8//IGNORE", "SHIFT-JIS");
    iconv(descriptor, &ptr_in, &buf_in_size, &ptr_out, &buf_out_size);
    iconv_close(descriptor);

    return std::string(buf_out);
    #endif

  }



  #if defined(_WIN32)
  std::string wstring_to_utf8_or_none(std::wstring_view wide)
  {
    const auto utf8 = wstring_to_utf8(wide);

    return utf8.value_or("");
  }

  std::string wstring_to_utf8_or_panic(std::wstring_view wide)
  {
    auto utf8 = wstring_to_utf8(wide);

    if (!utf8)
      common::debug::panic("Failed to convert wide string to utf8 string");

    return utf8.value();
  }

  std::wstring utf8_to_wstring_or_none(std::string_view utf8)
  {
    const auto wide = utf8_to_wstring(utf8);

    return wide.value_or(L"");
  }

  std::wstring utf8_to_wstring_or_panic(std::string_view utf8)
  {
    const auto wide = utf8_to_wstring(utf8);

    if(!wide)
      common::debug::panic("Failed to convert utf8 string to wide string");

    return wide.value();
  }
  #endif

  std::string sjis_to_utf8_or_none(std::string_view sjis)
  {
    const auto utf8_string = sjis_to_utf8(sjis);

    return utf8_string.value_or("");
  }

  std::string sjis_to_utf8_or_panic(std::string_view sjis)
  {
    auto utf8 = sjis_to_utf8(sjis);

    if (!utf8)
      common::debug::panic("Failed to convert sjis string to utf8 string");

    return utf8.value();
  }
}
