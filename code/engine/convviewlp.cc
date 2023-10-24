#include "common/log.h"

#include "engine/convviewlp.h"
#include "engine/mg/mg_lib.h"

set_log_channel("convviewlp");

// 01F64AA0
static mgCMemory DataBuffer{};
// 01F64AD0
static mgCMemory Stack_ReadBuff{};
