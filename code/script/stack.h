#pragma once
#include "common/types.h"
#include "common/debug.h"
#include "common/strings.h"

namespace script::rs
{
  struct stack_data;

  enum class stack_data_type : u32
  {
    _int,
    _flt,
    _str,
    _ptr
  };

  template<stack_data_type type>
  struct stack_data_type_traits;

  template<>
  struct stack_data_type_traits<stack_data_type::_int>
  {
    using type = s32;
  };

  template<>
  struct stack_data_type_traits<stack_data_type::_flt>
  {
    using type = f32;
  };

  template<>
  struct stack_data_type_traits<stack_data_type::_str>
  {
    using type = char*;
  };

  template<>
  struct stack_data_type_traits<stack_data_type::_ptr>
  {
    using type = stack_data*;
  };

  struct stack_data
  {
    template<stack_data_type type>
    using traits = stack_data_type_traits<type>;

    static stack_data from(f32 val)
    {
      const stack_data out =
      {
        .type = stack_data_type::_flt,
        ._flt = val
      };

      return out;
    }

    static stack_data from(s32 val)
    {
      const stack_data out =
      {
        .type = stack_data_type::_int,
        ._int = val
      };

      return out;
    }

    stack_data_type type;
    union
    {
      u64 _raw;

      traits<stack_data_type::_int>::type _int;
      traits<stack_data_type::_flt>::type _flt;
      traits<stack_data_type::_str>::type _str;
      traits<stack_data_type::_ptr>::type _ptr;
    };
  };

  template<stack_data_type type>
  constexpr bool check_type(const stack_data& data)
  {
    return data.type == type;
  }

  constexpr bool check_type_int(const stack_data& data)
  {
    return check_type<stack_data_type::_int>(data);
  }

  constexpr bool check_type_flt(const stack_data& data)
  {
    return check_type<stack_data_type::_flt>(data);
  }

  constexpr bool check_type_number(const stack_data& data)
  {
    return check_type_int(data) || check_type_flt(data);
  }

  constexpr bool check_type_str(const stack_data& data)
  {
    return check_type<stack_data_type::_str>(data);
  }

  constexpr bool check_type_ptr(const stack_data& data)
  {
    return check_type<stack_data_type::_ptr>(data);
  }

  constexpr bool check_type_ptr_to_int(const stack_data& data)
  {
    if (!check_type_ptr(data))
      return false;

    return check_type<stack_data_type::_int>(*data._ptr);
  }

  constexpr bool check_type_ptr_to_flt(const stack_data& data)
  {
    if (!check_type_ptr(data))
      return false;

    return check_type<stack_data_type::_flt>(*data._ptr);
  }

  template<stack_data_type type, typename traits = stack_data_type_traits<type>>
  ALWAYS_INLINE traits::type extract_stack_value(const stack_data& stack)
  {
    using enum stack_data_type;

    switch (stack.type)
    {
    case _int:
      return static_cast<traits::type>(stack._int);
    case _flt:
      return static_cast<traits::type>(stack._flt);
    }

    unreachable_code;
  }

  ALWAYS_INLINE s32 extract_int(const stack_data& stack)
  {
    return extract_stack_value<stack_data_type::_int>(stack);
  }

  ALWAYS_INLINE f32 extract_flt(const stack_data& stack)
  {
    return extract_stack_value<stack_data_type::_flt>(stack);
  }
}

template<>
struct fmt::formatter<script::rs::stack_data> : formatter<string_view>
{
  template<script::rs::stack_data_type type>
  using fmt_traits = script::rs::stack_data_type_traits<type>;

  auto format(const script::rs::stack_data& data, format_context& ctx) const -> decltype(ctx.out())
  {
    using enum script::rs::stack_data_type;

    switch (data.type)
    {
    case _int:
      return fmt::format_to(ctx.out(), "{}", data._int);
    case _flt:
      return fmt::format_to(ctx.out(), "{}", data._flt);
    case _str:
      return fmt::format_to(ctx.out(), "{}", data._str);
    case _ptr:
      return fmt::format_to(ctx.out(), "{}", fmt::ptr(data._ptr));
    }

    unreachable_code;
  }
};