#include "common/debug.h"
#include "common/log.h"

#include "dc2/event_edit.h"
#include "dc2/event_func.h"

set_log_channel("event_edit");

// 01F04200
CCameraPas g_cmr_pas{ };
// 01F04B50
CCharaPas g_chara_pas{ };
// 01F05000
unk g_info{ };