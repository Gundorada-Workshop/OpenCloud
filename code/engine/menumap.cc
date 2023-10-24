#include "common/log.h"

#include "engine/menumap.h"
#include "engine/mg/mg_lib.h"

set_log_channel("menumap");

// 01F0C9E0
static mgCMemory WorldMapStack{};
// 01F0CA10
static mgCMemory SphidaStack{};