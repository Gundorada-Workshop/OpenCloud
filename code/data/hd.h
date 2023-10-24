#pragma once
#include <algorithm>
#include "common/types.h"
#include "common/strings.h"
#include "common/file_helpers.h"

#include "data/iso/stream.h"

namespace hdx
{
  #pragma pack(push, 1)
  struct hd2_file_descriptor
  {
    // offset in the file of the location of the name
    u32 name_location;

    // I don't know what these are for, padding maybe?
    u32 unk0;
    u32 unk1;
    u32 unk2;

    // position in the file
    u32 offset;

    // size of the file at pos
    u32 size;

    // ISO9660 LBA
    u32 logical_block_offset;

    // ISO9660 extent
    u32 logical_block_size;
  };

  struct hd3_file_descriptor
  {
    // offset in the file of the location of the name
    u32 name_location;

    // size of the file at pos
    u32 size;

    // ISO9660 LBA
    u32 logical_block_offset;

    // ISO9660 extent
    u32 logical_block_size;
  };

  union file_descriptor
  {
    hd3_file_descriptor hd3;
    hd2_file_descriptor hd2;
  };
  #pragma pack(pop)

  static_assert(sizeof(hd2_file_descriptor) == 32);
  static_assert(sizeof(hd3_file_descriptor) == 16);

  static_assert(sizeof(file_descriptor) == sizeof(hd2_file_descriptor));

  struct hdx_file_entry
  {
    std::string relative_path{ };

    // the location of the start of the data in the ISO
    u64 logical_block_data_offset{ 0 };

    // the size of the data in the ISO (aligned up)
    u64 total_byte_count{ 0 };
  };

  using hdx_file_entry_list = std::vector<hdx_file_entry>;

  namespace constants
  {
    static constexpr usize hd3_size = sizeof(hd3_file_descriptor);
    static constexpr usize hd2_size = sizeof(hd2_file_descriptor);
  }
}
