#pragma once
#include "common/types.h"
#include "common/debug.h"
#include "common/strings.h"

namespace script
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

  template<typename type, usize max_element_count>
  class stack
  {
  public:
    stack() = default;
    ~stack() = default;

  public:
    // push an item on to the stack
    // returns the index of the pushed item
    ALWAYS_INLINE usize push(type&& val);

    // pop an item off the stack
    // returns the item popped off
    ALWAYS_INLINE type pop();

    // reset the stack
    ALWAYS_INLINE void reset();

    // get the most recently pushed item in the stack
    ALWAYS_INLINE type poke() const;

    // get the number of elements in the stack
    constexpr usize count() const;

    // get the size of the stack in bytes
    constexpr usize size() const;

    // get the max number of elements the stack can hold
    constexpr usize max_count() const;

    // get the max number of bytes the stack can hold
    constexpr usize max_size() const;

    // check if the stack is empty
    ALWAYS_INLINE bool empty() const;

  private:
    // increment the stack pointer
    ALWAYS_INLINE void increment_stack_offset();

    // decrement the stack pointer
    ALWAYS_INLINE void decrement_stack_offset();

    // insert a value at a given index
    ALWAYS_INLINE void insert_value_at_index(type&& val, usize index);

    // get an item at a given index
    ALWAYS_INLINE type item_at_index(usize index) const;

    // get the current index into the stack
    ALWAYS_INLINE usize current_index() const;

    // get the next index in the stack
    ALWAYS_INLINE usize next_index() const;

  private:
    std::array<type, max_element_count> m_stack{ };

    usize m_current_index{ 0 };
  };

  template<typename type, usize max_element_count>
  ALWAYS_INLINE auto stack<type, max_element_count>::push(type&& val) -> usize
  {
    const usize index = next_index();

    insert_value_at_index(std::move(val), index);
    increment_stack_offset();

    return index;
  }

  template<typename type, usize max_element_count>
  ALWAYS_INLINE auto stack<type, max_element_count>::pop() -> type
  {
    type item = poke();

    decrement_stack_offset();

    return item;
  }

  template<typename type, usize max_element_count>
  ALWAYS_INLINE auto stack<type, max_element_count>::poke() const -> type
  {
    const usize index = current_index();
    const type item = item_at_index(index);

    return item;
  }

  template<typename type, usize max_element_count>
  ALWAYS_INLINE void stack<type, max_element_count>::reset()
  {
    m_current_index = 0;
  }

  template<typename type, usize max_element_count>
  constexpr usize stack<type, max_element_count>::count() const
  {
    return current_index();
  }

  template<typename type, usize max_element_count>
  constexpr usize stack<type, max_element_count>::size() const
  {
    return current_index() * sizeof(type);
  }

  template<typename type, usize max_element_count>
  constexpr usize stack<type, max_element_count>::max_count() const
  {
    return max_element_count;
  }

  template<typename type, usize max_element_count>
  constexpr usize stack<type, max_element_count>::max_size() const
  {
    return max_element_count * sizeof(type);
  }

  template<typename type, usize max_element_count>
  ALWAYS_INLINE usize stack<type, max_element_count>::current_index() const
  {
    return m_current_index;
  }

  template<typename type, usize max_element_count>
  ALWAYS_INLINE usize stack<type, max_element_count>::next_index() const
  {
    return m_current_index + 1;
  }

  template<typename type, usize max_element_count>
  ALWAYS_INLINE bool stack<type, max_element_count>::empty() const
  {
    return m_current_index != 0;
  }

  template<typename type, usize max_element_count>
  ALWAYS_INLINE void stack<type, max_element_count>::increment_stack_offset()
  {
    m_current_index += 1;
  }

  template<typename type, usize max_element_count>
  ALWAYS_INLINE void stack<type, max_element_count>::decrement_stack_offset()
  {
    m_current_index -= 1;
  }

  template<typename type, usize max_element_count>
  ALWAYS_INLINE void stack<type, max_element_count>::insert_value_at_index(type&& val, usize index)
  {
    m_stack[index] = std::move(val);
  }

  template<typename type, usize max_element_count>
  ALWAYS_INLINE type stack<type, max_element_count>::item_at_index(usize index) const
  {
    return m_stack[index];
  }
}

template<>
struct fmt::formatter<script::stack_data> : formatter<string_view>
{
  template<script::stack_data_type type>
  using fmt_traits = script::stack_data_type_traits<type>;

  auto format(const script::stack_data& data, format_context& ctx) const -> decltype(ctx.out())
  {
    using enum script::stack_data_type;

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