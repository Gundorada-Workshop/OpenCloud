#pragma once
#include <unordered_map>

#include "common/data_stream.h"

#include "script/bytecode.h"

namespace script::rs
{
  #pragma pack(push, 1)
  struct func_data_entry
  {
    // start of the function code
    u32 code_start_byte_offset;

    // name of the function
    u32 name_byte_offset;
    
    // size of the stack
    u32 stack_byte_count;

    // number of arguments
    u32 argument_count;

    unk32 unk0;
    unk32 unk1;
    unk32 unk2;
    unk32 unk3;
    unk32 unk4;
    unk32 unk5;
    unk32 unk6;
    unk32 unk7;
    unk32 unk8;
    unk32 unk9;
  };

  static_assert(sizeof(func_data_entry) == 0x38);

  struct func_table_entry
  {
    u32 id;
    u32 function_data_byte_offset;
  };

  struct header
  {
    char magic[4];
    unk32 unk0;
    u32 data_start_byte_offset;
    u32 header_byte_count;
    u32 function_count;
    unk32 unk1;
    u32 global_variable_count;
    unk32 unk2;
    unk32 unk3;
    unk32 unk4;
    unk32 unk5;
    unk32 unk6;
    unk32 unk7;
    unk32 unk8;
    unk32 unk9;
    unk32 unk10;
  };

  static_assert(sizeof(header) == 0x40);
  #pragma pack(pop)
}