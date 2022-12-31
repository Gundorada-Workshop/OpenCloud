#pragma once
#include "common/macros.h"
#include "common/types.h"
#include "common/bits.h"
#include "common/strings.h"

namespace script::rs
{
  // the opcode for the instruction
  enum class opcode : u32
  {
    _end        = 0,
    _push_stack = 1,
    _push_ptr   = 2,
    _push       = 3,
    _pop        = 4,
    _deref      = 5,
    _add        = 6,
    _sub        = 7,
    _mul        = 8,
    _div        = 9,
    _mod        = 10,
    _neg        = 11,
    _itof       = 12,
    _ftoi       = 13,
    _cmp        = 14,
    _ret        = 15,
    _jmp        = 16,
    _bf         = 17,
    _bt         = 18,
    _call       = 19,
    _print      = 20,
    _ext        = 21,
    _unk0       = 22,
    _yld        = 23,
    _and        = 24,
    _or         = 25,
    _not        = 26,
    _exit       = 27,
    _unk1       = 28,
    _sin        = 29,
    _cos        = 30,
    count
  };

  // the instruction encoding
  enum class instruction_encoding_type : u32
  {
    invalid,
    empty,
    single_integer_argument,
    load_store_relative,
    load_store_immediate,
    comparison,
    jump,
    conditional_branch,
    count
  };

  // the value type
  enum class value_data_type : u32
  {
    invalid,
    _int = 1,
    _flt = 2,
    _str = 3,
    count
  };

  // the comparison function for comparison operations
  // for some reason these start at 40
  enum class comparision_function : u32
  {
    _eq = 40,
    _ne = 41,
    _lt = 42,
    _le = 43,
    _gt = 44,
    _ge = 45,
    count
  };

  // the address mode for push instructions
  // why is this a bitfield? no idea.
  enum class address_mode : u32
  {
    frame_relative      = 1 << 0,
    frame_offset        = 1 << 1,
    data_offset         = 1 << 2,
    frame_relative_flt  = 1 << 3,
    frame_offset_flt    = 1 << 4,
    data_offset_flt     = 1 << 5,
    global_relative     = 1 << 6,
    unk0                = 1 << 7,
    unk1                = 1 << 8,
    global_relative_flt = 1 << 9,
    count               = 10
  };

  enum class test_flag_mode
  {
    discard,
    preserve,
    count
  };

  constexpr instruction_encoding_type encoding_type_for_opcode(opcode op)
  {
    switch (op)
    {
    case opcode::_end:
    case opcode::_pop:
    case opcode::_deref:
    case opcode::_add:
    case opcode::_sub:
    case opcode::_mul:
    case opcode::_div:
    case opcode::_mod:
    case opcode::_neg:
    case opcode::_itof:
    case opcode::_ftoi:
    case opcode::_ret:
    case opcode::_yld:
    case opcode::_and:
    case opcode::_or:
    case opcode::_not:
    case opcode::_exit:
    case opcode::_unk0:
    case opcode::_unk1:
    case opcode::_sin:
    case opcode::_cos:
      return instruction_encoding_type::empty;
    case opcode::_print:
    case opcode::_ext:
      return instruction_encoding_type::single_integer_argument;
    case opcode::_push_stack:
    case opcode::_push_ptr:
      return instruction_encoding_type::load_store_relative;
    case opcode::_call:
    case opcode::_jmp:
      return instruction_encoding_type::jump;
    case opcode::_bf:
    case opcode::_bt:
      return instruction_encoding_type::conditional_branch;
    case opcode::_push:
      return instruction_encoding_type::load_store_immediate;
    case opcode::_cmp:
      return instruction_encoding_type::comparison;
    }

    return instruction_encoding_type::invalid;
  }

  // almost all values are ints (including str and ptr)
  template<value_data_type data_type>
  struct value_data_type_traits
  {
    using type = u32;
  };

  // special case for float
  template<>
  struct value_data_type_traits<value_data_type::_flt>
  {
    using type = f32;
  };

  union value_data
  {
    value_data_type_traits<value_data_type::_int>::type _int;
    value_data_type_traits<value_data_type::_flt>::type _flt;
    value_data_type_traits<value_data_type::_str>::type _str;
  };

  template<instruction_encoding_type encoding>
  struct instruction_data
  {
  };

  template<>
  struct instruction_data<instruction_encoding_type::load_store_relative>
  {
    u32 address;
    address_mode mode;
  };

  template<>
  struct instruction_data<instruction_encoding_type::load_store_immediate>
  {
    value_data_type type;
    value_data data;
  };

  template<>
  struct instruction_data<instruction_encoding_type::comparison>
  {
    comparision_function function;
  };

  template<>
  struct instruction_data<instruction_encoding_type::conditional_branch>
  {
    u32 address;
    test_flag_mode restore_flag;
  };

  template<>
  struct instruction_data<instruction_encoding_type::jump>
  {
    u32 address;
  };

  template<>
  struct instruction_data<instruction_encoding_type::single_integer_argument>
  {
    u32 value;
  };

  #pragma pack(push, 1)
  struct instruction
  {
    using empty_type      = instruction_data<instruction_encoding_type::empty>;
    using jump_type       = instruction_data<instruction_encoding_type::jump>;
    using integer_type    = instruction_data<instruction_encoding_type::single_integer_argument>;
    using branch_type     = instruction_data<instruction_encoding_type::conditional_branch>;
    using comparison_type = instruction_data<instruction_encoding_type::comparison>;

    using load_store_relative_type  = instruction_data<instruction_encoding_type::load_store_relative>;
    using load_store_immediate_type = instruction_data<instruction_encoding_type::load_store_immediate>;

    opcode opcode;

    union
    {
      std::array<u32, 2> raw;

      empty_type      empty;
      jump_type       jump;
      integer_type    single_integer;
      branch_type     conditional_branch;
      comparison_type comparison;

      load_store_relative_type  load_store_relative;
      load_store_immediate_type load_store_immediate;
    };
  };
  #pragma pack(pop)
}

template<>
struct fmt::formatter<script::rs::opcode> : formatter<string_view>
{
  auto format(script::rs::opcode op, format_context& ctx) const -> decltype(ctx.out())
  {
    using enum script::rs::opcode;

    std::array<string_view, std::to_underlying(count)> table =
    {
      "end",
      "psh", // stack
      "psh", // ptr
      "psh",
      "pop",
      "drf",
      "add",
      "sub",
      "mul",
      "div",
      "mod",
      "neg",
      "itf",
      "fti",
      "cmp",
      "ret",
      "jmp",
      "brf",
      "brt",
      "cal",
      "prt",
      "ext",
      "nop",
      "yld",
      "and",
      "lor",
      "not",
      "trm",
      "unk",
      "sin",
      "cos"
    };

    if (op >= count)
      ctx.on_error("Invalid op");

    return fmt::formatter<string_view>::format(table[std::to_underlying(op)], ctx);
  }
};

template<>
struct fmt::formatter<script::rs::value_data_type> : formatter<string_view>
{
  auto format(script::rs::value_data_type vt, format_context& ctx) const -> decltype(ctx.out())
  {
    using enum script::rs::value_data_type;

    constexpr std::array<string_view, std::to_underlying(count)> table =
    {
      "inv",
      "int",
      "flt",
      "str"
    };

    if (vt >= count)
      ctx.on_error("Invalid value type");

    return formatter<string_view>::format(table[std::to_underlying(vt)], ctx);
  }
};

template<>
struct fmt::formatter<script::rs::comparision_function> : formatter<string_view>
{
  auto format(script::rs::comparision_function op, format_context& ctx) const -> decltype(ctx.out())
  {
    using enum script::rs::comparision_function;

    constexpr std::array<string_view, std::to_underlying(count)> table =
    {
      "eq",
      "ne",
      "lt",
      "le",
      "gt",
      "ge"
    };

    if (op >= count || op < _eq)
      ctx.on_error("Invalid comparison op");

    return formatter<string_view>::format(table[std::to_underlying(op)], ctx);
  }
};

template<>
struct fmt::formatter<script::rs::address_mode> : formatter<string_view>
{
  auto format(script::rs::address_mode mode, format_context& ctx) const -> decltype(ctx.out())
  {
    using enum script::rs::address_mode;

    constexpr std::array<string_view, std::to_underlying(count)> table =
    {
      "spo",
      "sf0",
      "spr",
      "sfr",
      "dpo",
      "dfo",
      "gpr",
      "unk",
      "unk",
      "gpf"
    };

    const auto v = std::to_underlying(mode);

    if (v < std::to_underlying(frame_relative))
      ctx.on_error("Invalid address mode");

    const auto i = common::bits::lsb_index(v);

    if (i >= table.size())
      ctx.on_error("Address mode out of bounds");

    return formatter<string_view>::format(table[i], ctx);
  }
};

template<>
struct fmt::formatter<script::rs::test_flag_mode> : formatter<string_view>
{
  auto format(script::rs::test_flag_mode mode, format_context& ctx) const -> decltype(ctx.out())
  {
    using namespace script::rs;

    constexpr std::array<string_view, std::to_underlying(test_flag_mode::count)> table =
    {
      "discard",
      "restore"
    };

    if (mode >= test_flag_mode::count)
      ctx.on_error("Invalid test flag mode");

    return formatter<string_view>::format(table[std::to_underlying(mode)], ctx);
  }
};

template<>
struct fmt::formatter<script::rs::instruction::jump_type> : formatter<string_view>
{
  auto format(const script::rs::instruction::jump_type& data, format_context& ctx) const -> decltype(ctx.out())
  {
    return fmt::format_to(ctx.out(), "loc_{:06x}", data.address);
  }
};

template<>
struct fmt::formatter<script::rs::instruction::integer_type> : formatter<string_view>
{
  auto format(const script::rs::instruction::integer_type& data, format_context& ctx) const -> decltype(ctx.out())
  {
    return fmt::format_to(ctx.out(), "{}", data.value);
  }
};

template<>
struct fmt::formatter<script::rs::instruction::branch_type> : formatter<string_view>
{
  auto format(const script::rs::instruction::branch_type& data, format_context& ctx) const -> decltype(ctx.out())
  {
    return fmt::format_to(ctx.out(), "loc_{:06x} {}", data.address, data.restore_flag);
  }
};

template<>
struct fmt::formatter<script::rs::instruction::comparison_type> : formatter<string_view>
{
  auto format(const script::rs::instruction::comparison_type& data, format_context& ctx) const -> decltype(ctx.out())
  {
    return fmt::format_to(ctx.out(), "{}", data.function);
  }
};

template<>
struct fmt::formatter<script::rs::instruction::load_store_relative_type> : formatter<string_view>
{
  auto format(const script::rs::instruction::load_store_relative_type& data, format_context& ctx) const -> decltype(ctx.out())
  {
    return fmt::format_to(ctx.out(), "{}[{:#x}]", data.mode, data.address);
  }
};

template<>
struct fmt::formatter<script::rs::instruction::load_store_immediate_type> : formatter<string_view>
{
  auto format(const script::rs::instruction::load_store_immediate_type& data, format_context& ctx) const -> decltype(ctx.out())
  {
    using namespace script::rs;

    switch (data.type)
    {
    case value_data_type::_flt:
      return fmt::format_to(ctx.out(), "{} {}", data.type, data.data._flt);
    case value_data_type::_str:
      return fmt::format_to(ctx.out(), "{} {:#06x}", data.type, data.data._int);
    }

    return fmt::format_to(ctx.out(), "{} {}", data.type, data.data._int);
  }
};

template<>
struct fmt::formatter<script::rs::instruction> : formatter<string_view>
{
  auto format(const script::rs::instruction& inst, format_context& ctx) const
  {
    using namespace script::rs;

    const auto encoding = encoding_type_for_opcode(inst.opcode);

    switch (encoding)
    {
    case instruction_encoding_type::jump:
      if (inst.opcode == opcode::_call)
        return fmt::format_to(ctx.out(), "{} fun_{:06x}", inst.opcode, inst.jump.address);

      return fmt::format_to(ctx.out(), "{} {}", inst.opcode, inst.jump);
    case instruction_encoding_type::single_integer_argument:
      return fmt::format_to(ctx.out(), "{} {}", inst.opcode, inst.single_integer);
    case instruction_encoding_type::conditional_branch:
      return fmt::format_to(ctx.out(), "{} {}", inst.opcode, inst.conditional_branch);
    case instruction_encoding_type::comparison:
      return fmt::format_to(ctx.out(), "{} {}", inst.opcode, inst.comparison); 
    case instruction_encoding_type::load_store_relative:
      if(inst.opcode == opcode::_push_ptr)
        return fmt::format_to(ctx.out(), "{} ptr {}", inst.opcode, inst.load_store_relative);

      return fmt::format_to(ctx.out(), "{} {}", inst.opcode, inst.load_store_relative);
    case instruction_encoding_type::load_store_immediate:
      return fmt::format_to(ctx.out(), "{} {}", inst.opcode, inst.load_store_immediate);
    }

    return fmt::format_to(ctx.out(), "{}", inst.opcode);   
  }
};
