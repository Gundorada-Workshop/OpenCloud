#include <array>
#include "common/log.h"
#include "villager.h"
#include "vlgr_info.h"

set_log_channel("vlgr_info");

// 01F62BD0
static std::array<CVillagerPlace, 0x200> VlgrPlace{};