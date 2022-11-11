#include "common/debug.h"
#include "common/log.h"
#include "event_edit.h"
#include "event_func.h"

set_log_channel("event_edit");

// 01F04200
CCameraPas g_cmr_pas;
// 01F04B50
CCharaPas g_chara_pas;
// 01F05000
_UNKNOWN g_info;

namespace event_edit
{
  // 003747C0
  void SInit()
  {
    log_trace("SInit()");

    new (&g_cmr_pas) CCameraPas();
    new (&g_chara_pas) CCharaPas();
  }
}