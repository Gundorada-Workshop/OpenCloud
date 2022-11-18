#include "common/log.h"

#include "dc2/menusave.h"

set_log_channel("menusave");

// 002F12D0
CMenuSystemData::CMenuSystemData()
{
  log_trace("CMenuSystemData::CMenuSystemData()");

  MenuSystemDataInit();
}

// 002f1300
void CMenuSystemData::MenuSystemDataInit()
{
  log_trace("CMenuSystemData::MenuSystemDataInit()");

  memset(this, 0, sizeof(this));
}

