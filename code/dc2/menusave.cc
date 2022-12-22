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

void CSaveData::ForceBootTour(sint i, bool b)
{
  log_trace("CSaveData::{}({}, {})", __func__, i, b);

  todo;
}

// 002F6AE0
ETourType CSaveData::CheckNowTourType()
{
  log_trace("CSaveData::{}()", __func__);

  todo;
  return ETourType(-1);
}

// 002F73F0
void CSaveDataDungeon::SetFloorID(sint floor)
{
  log_trace("CSaveDataDungeon::{}({})", __func__, floor);

  auto index = static_cast<s32>(m_now_dungeon_id);

  m_old_floors[index] = m_now_floors[index];
  m_now_floors[index] = floor;

  log_info("CSaveDataDungeon::{}: [{}] FLOOR :::    {} ----->> {} ", __func__, index, m_old_floors[index], m_now_floors[index]);
}