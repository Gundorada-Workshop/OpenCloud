#pragma once
#include <variant>

#include "common/macros.h"

namespace common
{
  // note: C++23 has std::expected which is similar to this
  // should probably be replaced at a later date
  // this implementation is inspired by Rust's std::result and C++ std::optional

  template<typename type>
  struct unexpected
  {
    type value{ };
  };

  template<typename result_type, typename error_type>
  class result final
  {
    using failure_wrapper_type = unexpected<error_type>;

    using underlying_type = std::variant<result_type , failure_wrapper_type>;
 
  public:
    ALWAYS_INLINE result(result&& other)
      : m_value{ std::move(other.m_value) }
    {
    }

    ALWAYS_INLINE result(const result_type& res)
      : m_value{ res }
    {
    }

    ALWAYS_INLINE result(const error_type& err)
      : m_value{failure_wrapper_type{ err }}
    {
    }

    ALWAYS_INLINE result(result_type&& res)
      : m_value{ std::move(res) }
    {
    }

    ALWAYS_INLINE result(error_type&& err)
      : m_value{failure_wrapper_type{ std::move(err) }}
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
      return std::holds_alternative<failure_wrapper_type>(m_value);
    }

    // success result
    ALWAYS_INLINE auto value() const -> result_type
    {
      return std::get<result_type>(m_value);
    }

    // error result
    ALWAYS_INLINE auto error() const -> error_type
    {
      return std::get<failure_wrapper_type>(m_value).value;
    }

    // overload boolean operator like an optional
    // can be called regardless of result type
    ALWAYS_INLINE explicit operator bool() const
    {
      return std::holds_alternative<result_type>(m_value);
    }

    // overload to do *result like an optional
    // only call if no error type is held
    ALWAYS_INLINE auto operator*() const -> const result_type&
    {
      return std::get<result_type>(m_value);
    }

    // overload to do *result like an optional
    // only call if no error type is held
    ALWAYS_INLINE auto operator*() -> result_type&
    {
      return std::get<result_type>(m_value);
    }

    // overload to do result->member like an optional
    // only call if no error type is held
    ALWAYS_INLINE auto operator->() const -> const result_type*
    {
      return &std::get<result_type>(m_value);
    }

    // overload to do result->member like an optional
    // only call if no error type is held
    ALWAYS_INLINE auto operator->() -> result_type*
    {
      return &std::get<result_type>(m_value);
    }

  private:
    underlying_type m_value;
  };
}