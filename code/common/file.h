#pragma once
#include <cstdio>
#include <memory>
#include <vector>
#include <string_view>

#include "common/result.h"

namespace common::file
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

  // open a file using the native method
  common::result<std::FILE*, ::errno_t> open_native(std::string_view path, std::string_view mode);

  // open a file but wrap it in a smart ptr
  common::result<managed_ptr, ::errno_t> open_managed(std::string_view path, std::string_view mode);

  // tell a file (64 bit)
  common::result<u64, ::errno_t> tell64(std::FILE* file);

  // get file size (64 bit)
  common::result<u64, ::errno_t> size64(std::FILE* file);

  // get file size (64 bit) given a path
  // short hand for opening, getting the size, closing
  common::result<u64, ::errno_t> size64(std::string_view path);

  // seek to position (64 bit)
  common::result<bool, ::errno_t> seek64(std::FILE* file, u64 offset, u64 whence);

  // read entire file contents as binary
  common::result<std::vector<u8>, ::errno_t> read_all_binary(std::FILE* file);

  // read entire file contents as binary
  // short hand for opening, reading, closing
  common::result<std::vector<u8>, ::errno_t> read_all_binary(std::string_view path);
}