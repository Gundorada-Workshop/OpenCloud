#pragma once
#include "types.h"
#include "strings.h"

namespace common::debug
{
  // print a stack trace to the console
  void print_trace(uint depth);

  // cause an assert break if cond == false
  void runtime_assert(std::string_view msg);

  // panic the application
  // stops everything and dumps a backtrace
  void panic(std::string_view msg);

  // format assert
  template<typename ...Args>
  void runtime_assert_format(fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    const std::string msg = common::strings::format(fmtstr, std::forward<Args>(args)...);

    runtime_assert(msg);
  }

  // same as panic, but with string formatting
  template<typename ...Args>
  void panic_format(fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    const std::string msg = common::strings::format(fmtstr, std::forward<Args>(args)...);

    panic(msg);
  }
}

// panic the application
#define panicf(...)                           \
  do                                          \
  {                                           \
    common::debug::panic_format(__VA_ARGS__); \
  } while (0)

// mark code unreachable
#define unreachable_code \
  do                                                     \
  {                                                      \
    common::debug::panic("UNREACHABLE"); \
  } while (0)

// mark code unimplemented
#define unimplemented_code                                \
  do                                                      \
  {                                                       \
    common::debug::panic("UNIMPLEMENTED"); \
  } while (0)

// assert (live)
#define assert(cnd)                        \
  do                                       \
  {                                        \
    if (!cnd)                              \
      common::debug::runtime_assert(#cnd); \
  } while (0)

// assert (live) with message
#define assert_msg(cnd, msg)                                     \
  do                                                             \
  {                                                              \
    if (!cnd)                                                    \
      common::debug::runtime_assert_format("{}: {}", #cnd, msg); \
  } while (0)

// mark something todo
#define todo_msg(msg)                                     \
  do                                                      \
  {                                                       \
    common::debug::runtime_assert_format("TODO: {}", msg); \
  } while(0)

#define todo                               \
  do                                       \
  {                                        \
    common::debug::runtime_assert("TODO"); \
  } while (0)

#define unimplemented_var(expr)                                           \
  do                                                                      \
  {                                                                       \
    common::debug::runtime_assert_format("UNIMPLEMENTED VAR: {}", #expr); \
  } while (0)

#define unimplemented_member(type, pos) \
  type m_unk_field_##pos{ };

#if defined(_DEBUG) || defined(_FDEBUG)

#define debug_assert(cnd) assert(cnd)
#define debug_assert_msg(cnd, msg) assert_msg(cnd, msg)

#else

#define debug_assert(cnd) do { } while (0)
#define debug_assert_msg(cnd, msg) do { } while (0)

#endif
