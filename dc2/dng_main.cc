#include "common/log.h"
#include "dng_main.h"

set_log_channel("dng_main");

// 002F8CC0
void CDngFloorManager::Initialize()
{
  log_trace("CDngFloorManager::Initialize()");

  m_map_id = 0;
  m_unk_field_4 = 0;
  m_unk_field_8 = 0;
  m_unk_field_C = 0;
  m_unk_field_E = 0;
}