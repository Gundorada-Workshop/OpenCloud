#include "common/log.h"
#include "common/rectangle.h"

#include "dc2/editmenu.h"
#include "dc2/mg_lib.h"

set_log_channel("editmenu");

// 01EC92E0
mgCMemory MenuGeoramaStack{ };

// 01EC95E0
irect potti0{ irect::from_extent(372, 190, 16, 16) };

// 01EC95F0
irect potti1{ irect::from_extent(356, 190, 16, 16) };
