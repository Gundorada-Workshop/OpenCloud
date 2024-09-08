#pragma once
#include <cstdio>
#include <memory>

#include "common/types.h"
#include "common/strings.h"
#include "common/result.h"

namespace common::file_helpers
{
  struct managed_ptr_deleter
  {
    ALWAYS_INLINE void operator()(std::FILE* file)
    {
      if (!file)
      {
        return;
      }

      std::fclose(file);
    }
  };

  using managed_ptr = std::unique_ptr<std::FILE, managed_ptr_deleter>;

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

  // open a file using the native method
  common::result<std::FILE*, errno_t> open_native(std::string_view path, std::string_view mode);

  // open a file but wrap it in a smart ptr
  common::result<managed_ptr, errno_t> open_managed(std::string_view path, std::string_view mode);

  // tell a file (64 bit)
  common::result<u64, errno_t> tell64(std::FILE* file);

  // get file size (64 bit)
  common::result<u64, errno_t> size64(std::FILE* file);

  // get file size (64 bit) given a path
  // short hand for opening, getting the size, closing
  common::result<u64, errno_t> size64(std::string_view path);

  // seek to position (64 bit)
  common::result<bool, errno_t> seek64(std::FILE* file, u64 offset, u64 whence);

  // read entire file contents as binary
  common::result<std::vector<u8>, errno_t> read_all_binary(std::FILE* file);

  // read entire file contents as binary
  // short hand for opening, reading, closing
  common::result<std::vector<u8>, errno_t> read_all_binary(std::string_view path);

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
    return append(file_helpers::get_data_directory(), strings::format(fmtpath, std::forward<Args>(args)...));
  }
}
