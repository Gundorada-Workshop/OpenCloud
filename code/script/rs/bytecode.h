#pragma once
#include "common/macros.h"
#include "common/types.h"
#include "common/bits.h"
#include "common/strings.h"
#include "common/dictionary.h"

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
  enum class comparison_function : u32
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
    constexpr usize count = common::to_underlying(opcode::count);

    constexpr common::dictionary<opcode, instruction_encoding_type, count> table =
    {
      { opcode::_end,        instruction_encoding_type::empty },
      { opcode::_push_stack, instruction_encoding_type::load_store_relative },
      { opcode::_push_ptr,   instruction_encoding_type::load_store_relative },
      { opcode::_push,       instruction_encoding_type::load_store_immediate },
      { opcode::_pop,        instruction_encoding_type::empty },
      { opcode::_deref,      instruction_encoding_type::empty },
      { opcode::_add,        instruction_encoding_type::empty },
      { opcode::_sub,        instruction_encoding_type::empty },
      { opcode::_mul,        instruction_encoding_type::empty },
      { opcode::_div,        instruction_encoding_type::empty },
      { opcode::_mod,        instruction_encoding_type::empty },
      { opcode::_neg,        instruction_encoding_type::empty },
      { opcode::_itof,       instruction_encoding_type::empty },
      { opcode::_ftoi,       instruction_encoding_type::empty },
      { opcode::_cmp,        instruction_encoding_type::comparison },
      { opcode::_ret,        instruction_encoding_type::empty },
      { opcode::_jmp,        instruction_encoding_type::jump },
      { opcode::_bf,         instruction_encoding_type::conditional_branch },
      { opcode::_bt,         instruction_encoding_type::conditional_branch },
      { opcode::_call,       instruction_encoding_type::jump },
      { opcode::_print,      instruction_encoding_type::single_integer_argument },
      { opcode::_ext,        instruction_encoding_type::single_integer_argument },
      { opcode::_unk0,       instruction_encoding_type::empty },
      { opcode::_yld,        instruction_encoding_type::empty },
      { opcode::_and,        instruction_encoding_type::empty },
      { opcode::_or,         instruction_encoding_type::empty },
      { opcode::_not,        instruction_encoding_type::empty },
      { opcode::_exit,       instruction_encoding_type::empty },
      { opcode::_unk1,       instruction_encoding_type::empty },
      { opcode::_sin,        instruction_encoding_type::empty },
      { opcode::_cos,        instruction_encoding_type::empty }
    };

    return table.find_or(op, instruction_encoding_type::invalid);
  }

  constexpr std::string_view opcode_to_string(const opcode op)
  {
    constexpr usize count = common::to_underlying(opcode::count);

    constexpr common::dictionary<opcode, std::string_view, count> table =
    {
      { opcode::_end,        "end" },
      { opcode::_push_stack, "psh" },
      { opcode::_push_ptr,   "psh" },
      { opcode::_push,       "psh" },
      { opcode::_pop,        "pop" },
      { opcode::_deref,      "drf" },
      { opcode::_add,        "add" },
      { opcode::_sub,        "sub" },
      { opcode::_mul,        "mul" },
      { opcode::_div,        "div" },
      { opcode::_mod,        "mod" },
      { opcode::_neg,        "neg" },
      { opcode::_itof,       "itf" },
      { opcode::_ftoi,       "fti" },
      { opcode::_cmp,        "cmp" },
      { opcode::_ret,        "ret" },
      { opcode::_jmp,        "jmp" },
      { opcode::_bf,         "brf" },
      { opcode::_bt,         "brt" },
      { opcode::_call,       "cal" },
      { opcode::_print,      "prt" },
      { opcode::_ext,        "ext" },
      { opcode::_unk0,       "unk" },
      { opcode::_yld,        "yld" },
      { opcode::_and,        "and" },
      { opcode::_or,         "lor" },
      { opcode::_not,        "not" },
      { opcode::_exit,       "trm" },
      { opcode::_unk1,       "unk" },
      { opcode::_sin,        "sin" },
      { opcode::_cos,        "cos" }
    };

    return table.find_or(op, "inv");
  }

  constexpr std::string_view value_data_type_to_string(value_data_type type)
  {
    constexpr usize count = common::to_underlying(value_data_type::count);

    constexpr common::dictionary<value_data_type, std::string_view, count> table =
    {
      { value_data_type::_flt, "flt" },
      { value_data_type::_int, "int" },
      { value_data_type::_str, "str" }
    };

    return table.find_or(type, "inv");
  }

  constexpr std::string_view comparison_function_to_string(comparison_function fnc)
  {
    constexpr usize count = common::to_underlying(comparison_function::count);

    constexpr common::dictionary<comparison_function, std::string_view, count> table =
    {
      { comparison_function::_eq, "eq" },
      { comparison_function::_ne, "ne" },
      { comparison_function::_ge, "ge" },
      { comparison_function::_gt, "gt" },
      { comparison_function::_le, "le" },
      { comparison_function::_lt, "lt" }
    };

    return table.find_or(fnc, "inv");
  }

  constexpr std::string_view address_mode_to_string(address_mode mode)
  {
    constexpr usize count = common::to_underlying(address_mode::count);

    constexpr common::dictionary<address_mode, std::string_view, count> table =
    {
      { address_mode::frame_relative,      "fr" },
      { address_mode::frame_offset,        "fo" },
      { address_mode::global_relative,     "gr" },
      { address_mode::data_offset,         "do" },
      { address_mode::frame_relative_flt,  "fr" },
      { address_mode::frame_offset_flt,    "fo" },
      { address_mode::global_relative_flt, "gr" },
      { address_mode::data_offset_flt,     "do" },
      { address_mode::unk0,                "uk" },
      { address_mode::unk1,                "uk" }
    };

    return table.find_or(mode, "unk");
  }

  constexpr std::string_view test_flag_to_string(test_flag_mode mode)
  {
    constexpr usize count = common::to_underlying(test_flag_mode::count);

    constexpr common::dictionary<test_flag_mode, std::string_view, count> table =
    {
      { test_flag_mode::discard,  "discard" },
      { test_flag_mode::preserve, "preserve" }
    };

    return table.find_or(mode, "invalid");
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
    comparison_function function;
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
    using namespace script::rs;

    const std::string_view opcode_name = opcode_to_string(op);

    return fmt::formatter<string_view>::format(opcode_name, ctx);
  }
};

template<>
struct fmt::formatter<script::rs::value_data_type> : formatter<string_view>
{
  auto format(script::rs::value_data_type vt, format_context& ctx) const -> decltype(ctx.out())
  {
    using namespace script::rs;

    const std::string_view value_type_name = value_data_type_to_string(vt);

    return formatter<string_view>::format(value_type_name, ctx);
  }
};

template<>
struct fmt::formatter<script::rs::comparison_function> : formatter<string_view>
{
  auto format(script::rs::comparison_function op, format_context& ctx) const -> decltype(ctx.out())
  {
    using namespace script::rs;

    const std::string_view compare_function_name = comparison_function_to_string(op);

    return formatter<string_view>::format(compare_function_name, ctx);
  }
};

template<>
struct fmt::formatter<script::rs::address_mode> : formatter<string_view>
{
  auto format(script::rs::address_mode mode, format_context& ctx) const -> decltype(ctx.out())
  {
    using namespace script::rs;

    const std::string_view address_mode_name = address_mode_to_string(mode);

    return formatter<string_view>::format(address_mode_name, ctx);
  }
};

template<>
struct fmt::formatter<script::rs::test_flag_mode> : formatter<string_view>
{
  auto format(script::rs::test_flag_mode mode, format_context& ctx) const -> decltype(ctx.out())
  {
    using namespace script::rs;

    const std::string_view mode_name = test_flag_to_string(mode);

    return formatter<string_view>::format(mode_name, ctx);
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
