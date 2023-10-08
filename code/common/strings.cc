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
    // Make a null-terminated copy of the input string because
    // 1) string_views are not guaranteed to be null-terminated
    // 2) The input argument to iconv is mutable
    auto input_copy        = std::string(sjis);
    char* ptr_in           = reinterpret_cast<char*>(input_copy.data());
    size_t bytes_remaining = input_copy.size();

    // Set up the output variable
    // SHIFT-JIS is 1 byte minimum, UTF8 is 6 bytes maximum: worst case scenario,
    // out string is 6x larger than input string.
    // However: if we can guarantee that all characters are ascii/kana/non-extension kanji,
    // we can do better and assume a worst-case size of 3x input size due to the byte range
    // these characters are encoded to within UTF-8.
    size_t buf_out_size = bytes_remaining*6;
    std::string buf_out;
    buf_out.resize(buf_out_size);
    char*  ptr_out= buf_out.data();

    // Do the conversion
    // *Could* do this in a while loop "while(bytes_remaining > 0)", but
    // not sure if it's really better than paying the memory cost for
    // reserving a large buffer and converting all in one call.
    // //IGNORE will drop any unconvertable glyphs
    auto descriptor = iconv_open("UTF-8//IGNORE", "SHIFT-JIS");
    iconv(descriptor, &ptr_in, &bytes_remaining, &ptr_out, &buf_out_size);
    int close_state = iconv_close(descriptor);
    if (close_state != 0)
        return std::nullopt;

    // Create an output string with any junk after the buf_out ends trimmed off
    std::string out{buf_out.data()};
    return out;
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


  void xplat_strcpy_s(char* dest, size_t dest_size, const char* src)
  {
    #if defined(_MSC_VER)
      strcpy_s(dest, dest_size, src);
    #else
      // No safety check on strlen...
      size_t srclen = strlen(src);

      if ((srclen + 1) > dest_size)
      {
        common::debug::panic("Destination buffer in xplat_strcpy_s is too small");
      }

      for (size_t i=0; i < srclen; ++i)
        dest[i] = src[i];
      
      std::fill(&dest[srclen], &dest[dest_size], 0);
    #endif
  }

  void local_panic_alias(const std::string& str)
  {
    // Exists to prevent circular dependencies in templates
    common::debug::panic(str);
  }

}
