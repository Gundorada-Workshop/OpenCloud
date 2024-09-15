#pragma once
#include <string_view>

#include "common/macros.h"
#include "common/fmt.h"

namespace common
{
  // panic the application
  // stops everything and dumps a backtrace
  NO_RETURN void panic(std::string_view msg);

  // same as panic, but with string formatting
  template<typename ...Args>
  NO_RETURN void panic_format(fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    const std::string msg = common::format(fmtstr, std::forward<Args>(args)...);

    panic(msg);
  }
}

#define panic_msg(...)                        \
  do                                          \
  {                                           \
    common::panic_format(__VA_ARGS__);        \
  } while (0)

#define assert_panic(cnd)                       \
  do                                            \
  {                                             \
    if (!(cnd)) UNLIKELY                        \
    {                                           \
      common::panic_format("{}", #cnd);         \
    }                                           \
  } while (0)

#define assert_panic_ptr(ptr)                      \
  do                                               \
  {                                                \
    if(ptr == nullptr) UNLIKELY                    \
    {                                              \
      common::panic_format("{} is nullptr", #ptr); \
    }                                              \
  } while(0)