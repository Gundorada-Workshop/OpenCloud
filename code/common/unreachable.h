#pragma once
#include "common/platform.h"
#include "common/macros.h"
#include "common/panic.h"

// based on C++23 std::unreachable
// Note about __assume(0) and case from MSDN:
// 
// "For the default case optimization to work, 
// the __assume(0) statement must be the first
// statement in the body of the default case."
namespace common
{
  NO_RETURN inline void unreachable()
  {
  #if !defined(_DEBUG)
    #if PLATFORM_COMPILER_MSVC
      __assume(0);
    #else
      __builtin_unreachable();
    #endif
  #else
    common::panic("The application executed code that was expected to be unreachable");
  #endif
  }
}