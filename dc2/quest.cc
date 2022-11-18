#include "common/log.h"

#include "dc2/quest.h"

set_log_channel("quest");

// 0031aa30
void CQuestData::Initialize()
{
  log_trace("CQuestData::Initialize()");

  memset(this, 0, sizeof(this));
}