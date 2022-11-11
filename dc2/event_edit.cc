#include "common/debug.h"
#include "common/log.h"
#include "event_edit.h"
#include "event_func.h"

set_log_channel("event_edit");

// 01F04200
CCameraPas g_cmr_pas{};
// 01F04B50
CCharaPas g_chara_pas{};
// 01F05000
_UNKNOWN g_info{};