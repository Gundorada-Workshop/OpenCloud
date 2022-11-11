#include "common/log.h"
#include "nameregi.h"
#include "mg_lib.h"

set_log_channel("nameregi");

// 01F5DD70
static mgCMemory NameRegiStack{};