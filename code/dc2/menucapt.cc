#include "common/log.h"
#include "common/types.h"

#include "dc2/menucapt.h"
#include "dc2/mg/mg_lib.h"

set_log_channel("menucapt");

// 01F0A370
static mgCMemory MenuChapterStack{};
