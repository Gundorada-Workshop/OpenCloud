#pragma once
#include <variant>

#include "common/macros.h"

namespace common
{
  // note: C++23 has std::expected which is similar to this
  // should probably be replaced at a later date
  // this implementation is inspired by Rust's std::result and C++ std::optional

  template<typename result_type, typename error_type>
  class result final
  {
    using result_ptr_type = result_type*;
    using result_ref_type = result_type&;

    using result_const_ptr_type = const result_type*;
    using result_const_ref_type = const result_type&;
 
  public:
    static_assert(!std::is_same_v<result_type, error_type>, "Result type and error type must not be the same");

    ALWAYS_INLINE result(result&& other)
      : m_value{ std::move(other.m_value) }
    {
    }

    ALWAYS_INLINE result(result_const_ref_type res)
      : m_value{ res }
    {
    }

    ALWAYS_INLINE result(const error_type& err)
      : m_value{ err }
    {
    }

    ALWAYS_INLINE result(result_type&& res)
      : m_value{ std::move(res) }
    {
    }

    ALWAYS_INLINE result(error_type&& err)
      : m_value{ std::move(err) }
    {
    }

    // success result?
    ALWAYS_INLINE auto succeeded() const -> bool
    {
      return std::holds_alternative<result_type>(m_value);
    }

    // error result?
    ALWAYS_INLINE auto failed() const -> bool
    {
      return std::holds_alternative<error_type>(m_value);
    }

    // success result
    ALWAYS_INLINE auto value() const -> result_type
    {
      return std::get<result_type>(m_value);
    }

    // error result
    ALWAYS_INLINE auto error() const -> error_type
    {
      return std::get<error_type>(m_value);
    }

    // overload boolean operator like an optional
    // can be called regardless of result type
    ALWAYS_INLINE explicit operator bool() const
    {
      return std::holds_alternative<result_type>(m_value);
    }

    // overload to do *result like an optional
    // only call if no error type is held
    ALWAYS_INLINE auto operator*() const -> result_const_ref_type
    {
      return std::get<result_type>(m_value);
    }

    // overload to do *result like an optional
    // only call if no error type is held
    ALWAYS_INLINE auto operator*() -> result_ref_type
    {
      return std::get<result_type>(m_value);
    }

    // overload to do result->member like an optional
    // only call if no error type is held
    ALWAYS_INLINE auto operator->() const -> result_const_ptr_type
    {
      return &std::get<result_type>(m_value);
    }

    // overload to do result->member like an optional
    // only call if no error type is held
    ALWAYS_INLINE auto operator->() -> result_ptr_type
    {
      return &std::get<result_type>(m_value);
    }

  private:
    std::variant<result_type, error_type> m_value;
  };
}