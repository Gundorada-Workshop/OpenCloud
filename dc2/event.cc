#include "common/log.h"
#include "common/types.h"
#include "event.h"
#include "run_script.h"

set_log_channel("event");

static CRunScript EventScript;

namespace event
{
  // 00374580
  void SInit()
  {
    log_trace("SInit()");

    new (&EventScript) CRunScript();
  }
}

// 002554C0
void SkipEventStart()
{
  log_trace("{}()", __func__);

  todo;
}