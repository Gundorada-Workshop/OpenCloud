#include "common/platform.h"
#include "common/file.h"
#include "common/strings.h"

#if PLATFORM_OS_WINDOWS
#include "Windows.h"
#else
#include <cstdio>
#include <sys/stat.h>
#include <unistd.h>
#endif

#if PLATFORM_OS_WINDOWS
#define ftello64 _ftelli64
#define fseeko64 _fseeki64
#endif

namespace common::file
{
    common::result<std::FILE*, errno_t> open_native(std::string_view path, std::string_view mode)
  {
    std::FILE* file{ nullptr };

    #if PLATFORM_OS_WINDOWS
      const auto wfilename = common::strings::utf8_to_wstring_or_panic(path);
      const auto wmode     = common::strings::utf8_to_wstring_or_panic(mode);

      const errno_t res = _wfopen_s(&file, wfilename.c_str(), wmode.c_str());

      if (res != 0) UNLIKELY
      {
        return common::unexpected{ res };
      }

      return file;
    #else
      file = std::fopen(path.data(), "r");

      if (file == nullptr) UNLIKELY
      {
        return common::unexpected{ errno };
      }

      return file;
    #endif
  }

  common::result<managed_ptr, errno_t> open_managed(std::string_view path, std::string_view mode)
  {
    auto res = open_native(path, mode);

    if (res.failed()) UNLIKELY
    {
      return common::unexpected{ res.error() };
    }

    return managed_ptr{ res.value() };
  }

  common::result<u64, errno_t> tell64(std::FILE* file)
  {
    assert_panic(file);

    const auto res = ftello64(file);

    if (res == -1) UNLIKELY
    {
      return common::unexpected{ errno };
    }

    return res;
  }

  common::result<u64, errno_t> size64(std::FILE* file)
  {
    const auto pos = tell64(file);

    if (pos.failed()) UNLIKELY
    {
      return common::unexpected{ pos.error() };
    }

    {
      const auto res = seek64(file, SEEK_END, 0);

      if (res.failed()) UNLIKELY
      {
        return common::unexpected{ res.error() };
      }
    }

    const auto size = tell64(file);

    if (size.failed()) UNLIKELY
    {
      return common::unexpected{ size.error() };
    }

    {
      const auto res = seek64(file, SEEK_SET, pos.value());

      if (res.failed()) UNLIKELY
      {
        return common::unexpected{ res.error() };
      }
    }

    return size.value();
  }

  common::result<u64, errno_t> size64(std::string_view path)
  {
    const auto res = open_native(path, "r");

    if (res.failed()) UNLIKELY
    {
      return common::unexpected{ res.error() };
    }

    auto size = size64(res.value());

    fclose(res.value());

    return size;
  }

  common::result<bool, errno_t> seek64(std::FILE* file, u64 offset, u64 whence)
  {
    assert_panic(file);

    const auto res = fseeko64(file, offset, static_cast<int>(whence));

    if (res == -1) UNLIKELY
    {
      return common::unexpected{ errno };
    }

    return true;
  }

  common::result<std::vector<u8>, errno_t> read_all_binary(std::FILE* file)
  {
    const auto size = size64(file);

    if (size.failed()) UNLIKELY
    {
      return common::unexpected{ size.error() };
    }

    // don't try for an empty file
    if (size.value() == 0) UNLIKELY
    {
      return std::vector<u8>{ };
    }

    std::vector<u8> data{ };
    data.resize(size.value());

    const auto res = seek64(file, SEEK_SET, 0);

    if (res.failed()) UNLIKELY
    {
        return common::unexpected{ res.error() };
    }

    const auto read_size = fread(data.data(), 1, data.size(), file);

    // EOF should not be possible
    if (read_size != data.size()) UNLIKELY
    {
      return common::unexpected{ errno };
    }

    return data;
  }

  common::result<std::vector<u8>, errno_t> read_all_binary(std::string_view path)
  {
    const auto file = open_native(path, "rb");

    if (file.failed()) UNLIKELY
    {
      return common::unexpected{ file.error() };
    }

    auto res = read_all_binary(file.value());

    fclose(file.value());

    return res;
  }
}