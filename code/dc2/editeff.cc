#include <array>

#include "common/log.h"

#include "dc2/editeff.h"
#include "dc2/mg_lib.h"

set_log_channel("editeff");

// 01F59370
static std::array<CStarEffect, 3> _StarEffect{ };

// 01F59670
static mgCMemory CurPartsBuff{ };
