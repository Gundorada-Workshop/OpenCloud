#include "common/log.h"

#include "dc2/mainloop3.h"
#include "dc2/mg/mg_lib.h"

set_log_channel("mainloop3");

// 01F647D0
static mgCMemory buf0{};
// 01F64800
static mgCMemory buf1{};
// 01F64830
static mgCMemory dbuf0{};
// 01F64860
static mgCMemory dbuf1{};
// 01F64890
static mgCMemory Stack{};
