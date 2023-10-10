#include "common/log.h"

#include "graph/rectangle.h"

#include "engine/editmenu.h"
#include "engine/mg/mg_lib.h"

set_log_channel("editmenu");

// 01EC92E0
mgCMemory MenuGeoramaStack{ };

// 01EC95E0
graph::irect potti0{ graph::irect::from_extent(372, 190, 16, 16) };

// 01EC95F0
graph::irect potti1{ graph::irect::from_extent(356, 190, 16, 16) };
