#include <array>

#include "common/log.h"
#include "common/macros.h" // MAYBE_UNUSED

#include "engine/editeff.h"
#include "engine/mg/mg_lib.h"

set_log_channel("editeff");

// 01F59370
static std::array<CStarEffect, 3> _StarEffect{ };

// 01F59670
MAYBE_UNUSED static mgCMemory CurPartsBuff{ };
