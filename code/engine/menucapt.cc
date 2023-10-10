#include "common/log.h"
#include "common/types.h"

#include "engine/menucapt.h"
#include "engine/mg/mg_lib.h"

set_log_channel("menucapt");

// 01F0A370
static mgCMemory MenuChapterStack{};
