#include "common/debug.h"
#include "common/log.h"
#include "dc2io.h"

set_log_channel("dc2io");

// 00149370
bool LoadFile2(const char* file_name, void* file_buf, usize* read_bytes, int mode)
{
  log_trace("{}({}, {}, {}, {})", __func__, fmt::ptr(file_name), fmt::ptr(file_buf), fmt::ptr(read_bytes), mode);

  todo;
  return false;
}