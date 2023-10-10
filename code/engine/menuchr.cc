#include <array>

#include "common/log.h"

#include "engine/menuchr.h"
#include "engine/mg/mg_lib.h"

set_log_channel("menuchr");

// 01F0CAC0
static std::array<mgCMemory, 7> MenuActionCharaBuffer{};
// 01F0CC50
static mgCMemory MenuChangeMemory{};
// 01F0CC80
static mgCMemory MenuChangeNpcMemory{};
// 01F0CCB0
static mgCMemory ChrChangeInitTextureStack{};
// 01F0CEA0
static mgCMemory MenuMonChangeLoadStack{};
// 01F0CED0
static mgCMemory MenuMosBuildStack{};
// 01F0CF00
static mgCMemory MenuMosLoadStack{};
// 01F0D010
static mgCMemory SwordEffectStack{};
// 01F0D170
static mgCMemory MosBookStack{};