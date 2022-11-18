#include "common/log.h"

#include "dc2/nameregi.h"
#include "dc2/mg_lib.h"

set_log_channel("nameregi");

// 01F5DD70
static mgCMemory NameRegiStack{};