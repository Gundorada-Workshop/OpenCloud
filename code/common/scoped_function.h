// SPDX-License-Identifier: MIT

#pragma once
#include <concepts>
#include <optional>
#include <functional>

#include "common/macros.h"

namespace common
{
  // simple RAII class calls a function when it falls out of scope
  // good for cleaning up stuff that isn't RAII
  template<typename callable_type>
  requires std::invocable<callable_type>
  class scoped_function final
  {
  public:
    // remove the default constructor, must be called with a function
    scoped_function() = delete;

    // no copying
    scoped_function(const scoped_function&) = delete;
    void operator=(const scoped_function&) = delete;

    // construct with callable
    ALWAYS_INLINE scoped_function(callable_type&& function)
      : m_callable{ std::forward<callable_type>(function) }
    {
    }

    // calls execute
    ALWAYS_INLINE ~scoped_function()
    {
      execute();
    }

    // invoke the callable
    ALWAYS_INLINE void execute()
    {
      // possible reset
      if (!m_callable)
        return;

      std::invoke(m_callable.value());

      reset();
    }

    // remove the callable
    ALWAYS_INLINE void reset()
    {
      m_callable.reset();
    }

  private:
    // callable
    // could be a thread, a lambda, whatever
    std::optional<callable_type> m_callable{ };
  };
}
