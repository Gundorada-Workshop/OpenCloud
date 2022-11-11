#include "common/log.h"
#include "mg_lib.h"
#include "movieviewlp.h"

set_log_channel("movieviewlp");

// 01F0D300
static mgCMemory DataBuffer{};
// 01F0D330
static mgCMemory Stack_ReadBuff{};