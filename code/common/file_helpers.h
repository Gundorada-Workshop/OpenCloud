#pragma once
#include <cstdio>
#include "common/types.h"
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

  // open a file using the native method
  bool open_native(std::FILE** file, std::string_view path, std::string_view mode);

  // tell a file (64 bit)
  u64 tell64(std::FILE* file);

  // seek to position (64 bit)
  bool seek64(std::FILE* file, u64 offset, u64 whence);

  // create a directory
  // if directory already exists returns true
  bool create_directory(std::string_view path);

  // same as create directory
  // but attempts to create all directories in the path
  bool create_directories(std::string_view path);

  // set the application directory
  // should be called with an argv from main
  void set_application_directory(std::string_view path);

  // get the application directory
  std::string_view get_application_directory();

  // get the data directory
  std::string get_data_directory();

  // get the current working directory
  std::string get_working_directory();
}
