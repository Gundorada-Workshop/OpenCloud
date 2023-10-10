#include <array>

#include "common/log.h"

#include "engine/villager.h"
#include "engine/vlgr_info.h"

set_log_channel("vlgr_info");

// 01F62BD0
static std::array<CVillagerPlace, 0x200> VlgrPlace{};