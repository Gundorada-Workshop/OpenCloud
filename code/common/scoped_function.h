#pragma once
#include <functional>

namespace common
{
  // simple RAII class calls a function when it falls out of scope
  // good for cleaning up stuff that isn't RAII
  class scoped_function
  {
  public:
    // remove the default constructor, must be called with a function
    scoped_function() = delete;

    scoped_function(std::function<void()> function)
    {
      m_function = std::move(function);
    }

    ~scoped_function()
    {
      if (m_function)
        m_function();
    }

  private:
    std::function<void()> m_function{};
  };
}
