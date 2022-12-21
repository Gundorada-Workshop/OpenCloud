#pragma once
#include "common/types.h"

namespace pak
{
  struct entry_header
  {
    char name[64];
    u32 header_byte_count;
    u32 entry_byte_count;
    u32 unk0;
    u32 unk1;
  };

  struct entry
  {
    std::string name;
    usize file_byte_offset;
    usize file_byte_count;
  };

  using entry_list = std::vector<entry>;
}