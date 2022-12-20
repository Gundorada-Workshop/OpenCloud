#if defined(_WIN32)
#include <Windows.h>
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

  std::optional<std::string> sjis_to_utf8(std::string_view sjis)
  {
    static constexpr UINT CP_SJIS = 932;

    if (sjis.empty())
      return "";

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
  }

  std::string sjis_to_utf8_or_none(std::string_view sjis)
  {
    auto utf8_string = sjis_to_utf8(sjis);

    if (!utf8_string)
      return { };

    return *utf8_string;
  }

  std::string sjis_to_utf8_or_panic(std::string_view sjis)
  {
    auto utf8_string = sjis_to_utf8(sjis);

    if (!utf8_string)
      common::debug::panic("Failed to convert sjis string to utf8");

    return *utf8_string;
  }
#endif
}
