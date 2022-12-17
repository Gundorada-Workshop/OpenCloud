#include "common/debug.h"
#include "common/log.h"

#include "dc2/io.h"

set_log_channel("dc2io");

// 00149370
bool LoadFile2(MAYBE_UNUSED const char* file_name, MAYBE_UNUSED void* file_buf, MAYBE_UNUSED usize* read_bytes, MAYBE_UNUSED int mode)
{
  log_trace("{}({}, {}, {}, {})", __func__, fmt::ptr(file_name), fmt::ptr(file_buf), fmt::ptr(read_bytes), mode);

  todo;
  return false;
}