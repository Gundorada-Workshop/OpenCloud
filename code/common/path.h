#pragma once
#include <cstdio>
#include <memory>

#include "common/types.h"
#include "common/strings.h"
#include "common/result.h"

namespace common::path
{
  // returns the file name (with ext)
  std::string_view filename(std::string_view path);

  // returns the file name (without ext)
  std::string_view basename(std::string_view path);

  // returns the ext(s)
  std::string_view ext(std::string_view path);

  // get the directory of a file
  std::string_view parent_directory(std::string_view path);

  // append to path
  std::string append(std::string_view path, std::string_view item);

  // append a path to another path
  void append_to_path(std::string& path, std::string_view item);

  // converts a path to the native
  std::string native_path(std::string_view path);

  // create a directory
  // if directory already exists returns true
  bool create_directory(std::string_view path);

  // same as create directory
  // but attempts to create all directories in the path
  bool create_directories(std::string_view path);

  // get the path to the executable
  std::string get_executable_path();

  // get the application directory
  std::string get_application_directory();

  // get the data directory
  std::string get_data_directory();

  // get the current working directory
  std::optional<std::string> get_working_directory();

  // set the working directory
  bool set_working_directory(std::string_view path);

  // formats a path string and combines it with the data directory path
  // note: fmtpath must be constexpr
  template<typename ...Args>
  std::string resolve_data_path(fmt::format_string<Args...> fmtpath, Args&&... args)
  {
    return path::append(path::get_data_directory(), common::format(fmtpath, std::forward<Args>(args)...));
  }
}
