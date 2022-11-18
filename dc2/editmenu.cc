#include "common/log.h"

#include "dc2/editmenu.h"
#include "dc2/mg_lib.h"

set_log_channel("editmenu");

// 01EC92E0
mgCMemory MenuGeoramaStack{};
// 01EC95E0
mgRect<int> potti0{ 372, 190, 16, 16 };
// 01EC95F0
mgRect<int> potti1{ 356, 190, 16, 16 };
