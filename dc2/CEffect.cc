#include "string.h"
#include "common/log.h"
#include "CEffect.h"

set_log_channel("CEffect");

// 001847C0
void CFireRaster::Initialize()
{
  log_trace("CFireRaster::Initialize()");

  for (auto& unk_var : m_unk_field_70)
  {
    memset(&unk_var, 0, sizeof(unk_var));
  }
}