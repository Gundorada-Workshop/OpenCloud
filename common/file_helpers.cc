#include "common/file_helpers.h"

namespace common::file_helpers
{
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
}