﻿#include "common/file_helpers.h"
#include "common/debug.h"

#if defined(_WIN32)
#include "Windows.h"
#endif

namespace common::file_helpers
{
  static std::string s_application_directory{ };

  static consteval const char native_path_seperator()
  {
#if defined(_WIN32)
    return '\\';
#else
    return '/';
#endif
  }

  static std::string_view::size_type last_seperator_position(std::string_view path)
  {
    return path.find_last_of("\\/");
  }

  static std::string_view::size_type first_seperator_position(std::string_view path)
  {
    return path.find_first_of("\\/");
  }

  static bool is_path_seperator(char ch)
  {
    return ch == '\\' || ch == '/';
  }

  static bool has_trailing_seperator(std::string_view path)
  {
    return last_seperator_position(path) == path.length() - 1;
  }

  static bool has_leading_seperator(std::string_view path)
  {
    return first_seperator_position(path) == 0;
  }

  // must be converted to native path first
  static void remove_trailing_seperators(std::string& path)
  {
    if (path.empty())
    {
      return;
    }

    while (has_trailing_seperator(path))
    {
      path.pop_back();
    }
  }

  static void to_native_path(std::string& path)
  {
    for (auto& ch : path)
    {
      if (is_path_seperator(ch) && ch != native_path_seperator())
      {
        // swap with the native separator
        ch = native_path_seperator();
      }
    }
  }

  std::string_view filename(std::string_view path)
  {
    auto last_sep = last_seperator_position(path);

    if (last_sep == std::string_view::npos)
    {
      return {};
    }

    return path.substr(++last_sep, path.size());
  }

  std::string_view basename(std::string_view path)
  {
    const auto file_name = filename(path);
    const auto first_period = file_name.find_first_of(".");

    if (first_period == std::string_view::npos)
    {
      return {};
    }

    return file_name.substr(0, first_period);
  }

  std::string_view ext(std::string_view path)
  {
    const auto file_name = filename(path);
    auto first_period = file_name.find_first_of(".");

    if (first_period == std::string_view::npos)
    {
      return {};
    }

    return file_name.substr(++first_period, file_name.size());
  }

  std::string_view parent_directory(std::string_view path)
  {
    const auto last_sep_pos = last_seperator_position(path);

    if (last_sep_pos == std::string_view::npos)
    {
      return {};
    }

    return path.substr(0, last_sep_pos);
  }

  std::string append(std::string_view path, std::string_view item)
  {
    std::string out{ path };

    append_to_path(out, item);

    return out;
  }

  void append_to_path(std::string& path, std::string_view item)
  {
    remove_trailing_seperators(path);

    if (!has_leading_seperator(item))
    {
      path.append({ native_path_seperator() });
    }

    path.append(native_path(item));
  }

  std::string native_path(std::string_view path)
  {
    std::string out{ path };

    to_native_path(out);

    return out;
  }

  bool open_native(std::FILE** file, std::string_view path, std::string_view mode)
  {
    if (!file)
      panicf("File is null opening {} with mode {}", path, mode);

#if defined(_WIN32)
    const auto wfilename = common::strings::to_wstring(path);
    const auto wmode = common::strings::to_wstring(mode);

    if (!wfilename)
      return false;

    if (_wfopen_s(file, wfilename->c_str(), wmode->c_str()) != 0)
      return false;

    return true;
#else
    return false;
#endif
  }

  u64 tell64(std::FILE* file)
  {
    if (!file)
      panicf("File is null");

#if defined(_WIN32)
    return _ftelli64(file);
#else
    return 0;
#endif
  }

  bool seek64(std::FILE* file, u64 offset, u64 whence)
  {
    if (!file)
      panicf("File is null seeking to {} from {}", offset, whence);

#if defined(_WIN32)
    return _fseeki64(file, offset, static_cast<int>(whence)) == 0;
#else
    return false;
#endif
  }

  bool create_directory(std::string_view path)
  {
#if defined(_WIN32)
    const auto wdir = common::strings::to_wstring(path);
    if (!wdir)
      panicf("Failed to convert directory path to UTF16: ", path);

    const auto res = CreateDirectoryW(wdir->c_str(), NULL);

    if (!res)
    {
      const auto err = GetLastError();

      if (err != ERROR_ALREADY_EXISTS)
        return false;
    }

    return true;
#else
    return false;
#endif
  }

  void set_application_directory(std::string_view path)
  {
    assert_msg(s_application_directory.empty(), "Application directory already set");

    s_application_directory = std::string{ path };
  }

  std::string_view get_application_directory()
  {
    assert_msg(!s_application_directory.empty(), "Application directory needs to be set before calling get_parent_directory()");

    return s_application_directory;
  }

  std::string get_working_directory()
  {
#if defined(_WIN32)
    TCHAR dir[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, dir);

    auto working_dir = common::strings::to_utf8(dir);

    if (!working_dir)
      panicf("Failed to convert working directory path to UTF8");

    return *working_dir;
#endif
  }
}