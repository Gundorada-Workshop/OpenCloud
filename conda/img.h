#pragma once
#include <vector>

#include "common/types.h"

namespace im3
{
  #pragma pack(push, 1)
  struct header
  {
    char magic[4];
    u32 unk;
    u32 image_count;
    u32 pad0;
  };

  struct entry_header
  {
    char name[32];
    u32 header_byte_count;
    u32 image_data_byte_offset;
    u32 unk1;
    u32 unk2;
    u32 unk3;
    u32 image_byte_count;
    u32 unk4;
    u32 unk5;
  };
  #pragma pack(pop)

  struct entry
  {
    std::string name;
    usize file_byte_offset;
    usize file_byte_count;
  };

  static_assert(sizeof(entry_header) == 64);
}
