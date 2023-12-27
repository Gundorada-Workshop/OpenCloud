#pragma once
#include "common/macros.h"
#include "common/types.h"
#include "common/bits.h"
#include "common/strings.h"
#include "common/dictionary.h"

namespace script
{
  // the opcode for the instruction
  enum class opcode : u32
  {
    end               = 0,
    push_stack        = 1,
    push_pointer      = 2,
    push              = 3,
    pop               = 4,
    deference_pointer = 5,
    add               = 6,
    sub               = 7,
    mul               = 8,
    div               = 9,
    mod               = 10,
    neg               = 11,
    int_to_float      = 12,
    float_to_int      = 13,
    compare           = 14,
    return_           = 15,
    jump              = 16,
    branch_false      = 17,
    branch_true       = 18,
    call              = 19,
    print             = 20,
    extended_function = 21,
    unknown_0         = 22,
    yield             = 23,
    and_              = 24,
    or_               = 25,
    not_              = 26,
    exit              = 27,
    unknown_1         = 28,
    sin               = 29,
    cos               = 30,
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
    integer         = 1,
    floating_point  = 2,
    string          = 3,
    count
  };

  // the comparison function for comparison operations
  // for some reason these start at 40
  enum class comparison_function : u32
  {
    equal              = 40,
    not_equal          = 41,
    less_than          = 42,
    less_than_equal    = 43,
    greater_than       = 44,
    greater_than_equal = 45,
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
      { opcode::end,               instruction_encoding_type::empty },
      { opcode::push_stack,        instruction_encoding_type::load_store_relative },
      { opcode::push_pointer,      instruction_encoding_type::load_store_relative },
      { opcode::push,              instruction_encoding_type::load_store_immediate },
      { opcode::pop,               instruction_encoding_type::empty },
      { opcode::deference_pointer, instruction_encoding_type::empty },
      { opcode::add,               instruction_encoding_type::empty },
      { opcode::sub,               instruction_encoding_type::empty },
      { opcode::mul,               instruction_encoding_type::empty },
      { opcode::div,               instruction_encoding_type::empty },
      { opcode::mod,               instruction_encoding_type::empty },
      { opcode::neg,               instruction_encoding_type::empty },
      { opcode::int_to_float,      instruction_encoding_type::empty },
      { opcode::float_to_int,      instruction_encoding_type::empty },
      { opcode::compare,           instruction_encoding_type::comparison },
      { opcode::return_,           instruction_encoding_type::empty },
      { opcode::jump,              instruction_encoding_type::jump },
      { opcode::branch_false,      instruction_encoding_type::conditional_branch },
      { opcode::branch_true,       instruction_encoding_type::conditional_branch },
      { opcode::call,              instruction_encoding_type::jump },
      { opcode::print,             instruction_encoding_type::single_integer_argument },
      { opcode::extended_function, instruction_encoding_type::single_integer_argument },
      { opcode::unknown_0,         instruction_encoding_type::empty },
      { opcode::yield,             instruction_encoding_type::empty },
      { opcode::and_,              instruction_encoding_type::empty },
      { opcode::or_,               instruction_encoding_type::empty },
      { opcode::not_,              instruction_encoding_type::empty },
      { opcode::exit,              instruction_encoding_type::empty },
      { opcode::unknown_1,         instruction_encoding_type::empty },
      { opcode::sin,               instruction_encoding_type::empty },
      { opcode::cos,               instruction_encoding_type::empty }
    };

    return table.find_or(op, instruction_encoding_type::invalid);
  }

  constexpr std::string_view opcode_to_string(const opcode op)
  {
    constexpr usize count = common::to_underlying(opcode::count);

    constexpr common::dictionary<opcode, std::string_view, count> table =
    {
      { opcode::end,               "end" },
      { opcode::push_stack,        "psh" },
      { opcode::push_pointer,      "psh" },
      { opcode::push,              "psh" },
      { opcode::pop,               "pop" },
      { opcode::deference_pointer, "drf" },
      { opcode::add,               "add" },
      { opcode::sub,               "sub" },
      { opcode::mul,               "mul" },
      { opcode::div,               "div" },
      { opcode::mod,               "mod" },
      { opcode::neg,               "neg" },
      { opcode::int_to_float,      "itf" },
      { opcode::float_to_int,      "fti" },
      { opcode::compare,           "cmp" },
      { opcode::return_,           "ret" },
      { opcode::jump,              "jmp" },
      { opcode::branch_false,      "brf" },
      { opcode::branch_true,       "brt" },
      { opcode::call,              "cal" },
      { opcode::print,             "prt" },
      { opcode::extended_function, "ext" },
      { opcode::unknown_0,         "unk" },
      { opcode::yield,             "yld" },
      { opcode::and_,              "and" },
      { opcode::or_,               "lor" },
      { opcode::not_,              "not" },
      { opcode::exit,              "trm" },
      { opcode::unknown_1,         "unk" },
      { opcode::sin,               "sin" },
      { opcode::cos,               "cos" }
    };

    return table.find_or(op, "inv");
  }

  constexpr std::string_view value_data_type_to_string(value_data_type type)
  {
    constexpr usize count = common::to_underlying(value_data_type::count);

    constexpr common::dictionary<value_data_type, std::string_view, count> table =
    {
      { value_data_type::floating_point, "flt" },
      { value_data_type::integer,        "int" },
      { value_data_type::string,         "str" }
    };

    return table.find_or(type, "inv");
  }

  constexpr std::string_view comparison_function_to_string(comparison_function fnc)
  {
    constexpr usize count = common::to_underlying(comparison_function::count);

    constexpr common::dictionary<comparison_function, std::string_view, count> table =
    {
      { comparison_function::equal,              "eq" },
      { comparison_function::not_equal,          "ne" },
      { comparison_function::greater_than_equal, "ge" },
      { comparison_function::greater_than,       "gt" },
      { comparison_function::less_than_equal,    "le" },
      { comparison_function::less_than,          "lt" }
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
  struct value_data_type_traits<value_data_type::floating_point>
  {
    using type = f32;
  };

  union value_data
  {
    value_data_type_traits<value_data_type::integer>::type        int_;
    value_data_type_traits<value_data_type::floating_point>::type flt_;
    value_data_type_traits<value_data_type::string>::type         str_;
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
struct fmt::formatter<script::opcode> : formatter<string_view>
{
  auto format(script::opcode op, format_context& ctx) const -> decltype(ctx.out())
  {
    const std::string_view opcode_name = script::opcode_to_string(op);

    return fmt::formatter<string_view>::format(opcode_name, ctx);
  }
};

template<>
struct fmt::formatter<script::value_data_type> : formatter<string_view>
{
  auto format(script::value_data_type vt, format_context& ctx) const -> decltype(ctx.out())
  {
    const std::string_view value_type_name = script::value_data_type_to_string(vt);

    return formatter<string_view>::format(value_type_name, ctx);
  }
};

template<>
struct fmt::formatter<script::comparison_function> : formatter<string_view>
{
  auto format(script::comparison_function op, format_context& ctx) const -> decltype(ctx.out())
  {
    const std::string_view compare_function_name = script::comparison_function_to_string(op);

    return formatter<string_view>::format(compare_function_name, ctx);
  }
};

template<>
struct fmt::formatter<script::address_mode> : formatter<string_view>
{
  auto format(script::address_mode mode, format_context& ctx) const -> decltype(ctx.out())
  {
    const std::string_view address_mode_name = script::address_mode_to_string(mode);

    return formatter<string_view>::format(address_mode_name, ctx);
  }
};

template<>
struct fmt::formatter<script::test_flag_mode> : formatter<string_view>
{
  auto format(script::test_flag_mode mode, format_context& ctx) const -> decltype(ctx.out())
  {
    const std::string_view mode_name = script::test_flag_to_string(mode);

    return formatter<string_view>::format(mode_name, ctx);
  }
};

template<>
struct fmt::formatter<script::instruction::jump_type> : formatter<string_view>
{
  auto format(const script::instruction::jump_type& data, format_context& ctx) const -> decltype(ctx.out())
  {
    return fmt::format_to(ctx.out(), "loc_{:06x}", data.address);
  }
};

template<>
struct fmt::formatter<script::instruction::integer_type> : formatter<string_view>
{
  auto format(const script::instruction::integer_type& data, format_context& ctx) const -> decltype(ctx.out())
  {
    return fmt::format_to(ctx.out(), "{}", data.value);
  }
};

template<>
struct fmt::formatter<script::instruction::branch_type> : formatter<string_view>
{
  auto format(const script::instruction::branch_type& data, format_context& ctx) const -> decltype(ctx.out())
  {
    return fmt::format_to(ctx.out(), "loc_{:06x} {}", data.address, data.restore_flag);
  }
};

template<>
struct fmt::formatter<script::instruction::comparison_type> : formatter<string_view>
{
  auto format(const script::instruction::comparison_type& data, format_context& ctx) const -> decltype(ctx.out())
  {
    return fmt::format_to(ctx.out(), "{}", data.function);
  }
};

template<>
struct fmt::formatter<script::instruction::load_store_relative_type> : formatter<string_view>
{
  auto format(const script::instruction::load_store_relative_type& data, format_context& ctx) const -> decltype(ctx.out())
  {
    return fmt::format_to(ctx.out(), "{}[{:#x}]", data.mode, data.address);
  }
};

template<>
struct fmt::formatter<script::instruction::load_store_immediate_type> : formatter<string_view>
{
  auto format(const script::instruction::load_store_immediate_type& data, format_context& ctx) const -> decltype(ctx.out())
  {
    switch (data.type)
    {
    case script::value_data_type::floating_point:
      return fmt::format_to(ctx.out(), "{} {}", data.type, data.data.flt_);
    case script::value_data_type::string:
      return fmt::format_to(ctx.out(), "{} {:#06x}", data.type, data.data.int_);
    default:
      break;
    }

    return fmt::format_to(ctx.out(), "{} {}", data.type, data.data.int_);
  }
};

template<>
struct fmt::formatter<script::instruction> : formatter<string_view>
{
  auto format(const script::instruction& inst, format_context& ctx) const
  {
    const auto encoding = script::encoding_type_for_opcode(inst.opcode);

    switch (encoding)
    {
    case script::instruction_encoding_type::jump:
      if (inst.opcode == script::opcode::call)
        return fmt::format_to(ctx.out(), "{} fun_{:06x}", inst.opcode, inst.jump.address);

      return fmt::format_to(ctx.out(), "{} {}", inst.opcode, inst.jump);
    case script::instruction_encoding_type::single_integer_argument:
      return fmt::format_to(ctx.out(), "{} {}", inst.opcode, inst.single_integer);
    case script::instruction_encoding_type::conditional_branch:
      return fmt::format_to(ctx.out(), "{} {}", inst.opcode, inst.conditional_branch);
    case script::instruction_encoding_type::comparison:
      return fmt::format_to(ctx.out(), "{} {}", inst.opcode, inst.comparison); 
    case script::instruction_encoding_type::load_store_relative:
      if(inst.opcode == script::opcode::push_pointer)
        return fmt::format_to(ctx.out(), "{} ptr {}", inst.opcode, inst.load_store_relative);

      return fmt::format_to(ctx.out(), "{} {}", inst.opcode, inst.load_store_relative);
    case script::instruction_encoding_type::load_store_immediate:
      return fmt::format_to(ctx.out(), "{} {}", inst.opcode, inst.load_store_immediate);
    default:
      break;
    }

    return fmt::format_to(ctx.out(), "{}", inst.opcode);   
  }
};
