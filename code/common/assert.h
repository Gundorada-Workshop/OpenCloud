#pragma once
#include <string_view>

#include "common/fmt.h"

namespace common
{
  // cause an assert with a message
  // cant use assert() because windows
  void rassert(std::string_view msg);

  // assert with format message
  template<typename ...Args>
  void assert_format(fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    const std::string msg = common::format(fmtstr, std::forward<Args>(args)...);

    rassert(msg);
  }
}

// runtime assert
// we can't use assert() because windows
#define runtime_assert(cnd) \
  do                        \
  {                         \
    if (!(cnd))             \
      common::rassert(#cnd); \
  } while (0)

// compile-time assert
#define compile_assert(cnd) static_assert(cnd)

// compile-time assert for checking a type is the expect size
#define compile_assert_type_size(type, expected_size) \
  static_assert(sizeof(type) == expected_size) 

// assert for checking pointers for non-null
// use when the application can recover (does a null ptr check)
// otherwise use panic_assert_ptr
#define assert_ptr(ptr)                             \
  do                                                \
  {                                                 \
    if (ptr == nullptr)                             \
    {                                               \
      common::assert_format("{} is nullptr", #ptr); \
    }                                               \
  } while(0)

// runtime assert with formatting
// use to display a message with the assert
#define assert_msg(cnd, msg)                      \
  do                                              \
  {                                               \
    if (!(cnd))                                   \
      common::assert_format("{}: {}", #cnd, msg); \
  } while (0)

#if defined(_DEBUG) || defined(_FDEBUG)
  // debug assert
  // only enabled in debug builds
  #define debug_assert(cnd) runtime_assert(cnd)

  // debug assert with formatting
  // only enabled in debug builds
  #define debug_assert_msg(cnd, msg) assert_msg(cnd, msg)
#else
  // disabled in non-debug builds
  #define debug_assert(cnd) do { } while (0)

  // disabled in non-debug builds
  #define debug_assert_msg(cnd, msg) do { } while (0)
#endif