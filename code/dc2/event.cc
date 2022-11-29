#include "common/log.h"

#include "dc2/event.h"
#include "dc2/run_script.h"

set_log_channel("event");

static CRunScript EventScript{ };

// 002554C0
void SkipEventStart()
{
  log_trace("{}()", __func__);

  todo;
}