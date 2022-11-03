#pragma once
#include "common/strings.h"

namespace common::file_helpers
{
  // returns the file name (with ext)
  std::string_view filename(std::string_view path);

  // returns the file name (without ext)
  std::string_view basename(std::string_view path);

  // returns the ext(s)
  std::string_view ext(std::string_view path);

  // get the directory of a file
  std::string_view parent_directory(std::string_view path);

  std::string append(std::string_view path, std::string_view item);

  // append a path to another path
  void append_to_path(std::string& path, std::string_view item);

  // converts a path to the native
  std::string native_path(std::string_view path);
}
