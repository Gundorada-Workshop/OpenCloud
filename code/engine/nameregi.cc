#include "common/log.h"

#include "engine/nameregi.h"
#include "engine/mg/mg_lib.h"

set_log_channel("nameregi");

// 01F5DD70
static mgCMemory NameRegiStack{};