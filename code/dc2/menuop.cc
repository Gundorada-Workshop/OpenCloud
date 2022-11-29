#include "common/log.h"

#include "dc2/menuop.h"
#include "dc2/mg/mg_lib.h"

set_log_channel("menuop");

// 01F0D200
static mgCMemory StaticMenuLocalStack{};
// 01F0D230
static mgCMemory StaticMenuLocalStack2{};
// 01F0D260
static mgCMemory SaveMenuStack{};