#include "common/log.h"

#include "dc2/convviewlp.h"
#include "dc2/mg_lib.h"

set_log_channel("convviewlp");

// 01F64AA0
static mgCMemory DataBuffer{};
// 01F64AD0
static mgCMemory Stack_ReadBuff{};
