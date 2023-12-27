#include "common/log.h"
#include "common/macros.h" // MAYBE_UNUSED

#include "engine/convviewlp.h"
#include "engine/mg/mg_lib.h"

set_log_channel("convviewlp");

// 01F64AA0
MAYBE_UNUSED static mgCMemory DataBuffer{};
// 01F64AD0
MAYBE_UNUSED static mgCMemory Stack_ReadBuff{};
