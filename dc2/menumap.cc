#include "common/log.h"
#include "menumap.h"
#include "mg_lib.h"

set_log_channel("menumap");

// 01F0C9E0
static mgCMemory WorldMapStack{};
// 01F0CA10
static mgCMemory SphidaStack{};