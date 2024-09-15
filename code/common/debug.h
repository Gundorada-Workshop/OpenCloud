#pragma once
#include <array>

#include "common/types.h"
#include "common/macros.h"
#include "common/strings.h"
#include "common/assert.h"
#include "common/panic.h"

// mark code unimplemented
#define unimplemented_code          \
  do                                \
  {                                 \
    common::panic("UNIMPLEMENTED"); \
  } while (0)

// mark something todo
#define todo_msg(msg)                       \
  do                                        \
  {                                         \
    common::assert_format("TODO: {}", msg); \
  } while(0)

// mark something todo
#define todo                \
  do                        \
  {                         \
    common::rassert("TODO"); \
  } while (0)

// mark a variable as unimplemented
#define unimplemented_var(expr)                            \
  do                                                       \
  {                                                        \
    common::assert_format("UNIMPLEMENTED VAR: {}", #expr); \
  } while (0)


