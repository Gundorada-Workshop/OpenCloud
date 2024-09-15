#pragma once
#include <string>

#include <fmt/core.h>
#include <fmt/chrono.h>

#include "common/macros.h"

FILE_WARNING_PUSH;
// fmt lib throws a bunch of this warning
FILE_WARNING_DISABLE(WARNING_ID_CONDITIONAL_EXPRESSION_IS_CONSTANT)

namespace common
{
  // format a string
  // note: fmtstr must be constexpr
  template<typename ...Args>
  ALWAYS_INLINE std::string format(fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    return fmt::format(fmtstr, std::forward<Args>(args)...);
  }
}

FILE_WARNING_POP;