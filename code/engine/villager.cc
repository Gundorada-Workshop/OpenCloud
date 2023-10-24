#include "common/log.h"
#include "common/constants.h"

#include "engine/villager.h"

set_log_channel("villager");

using namespace common;

// 002CD110
void CVillagerData::Initialize()
{
  log_trace("CVillagerData::Initialize()");

  m_unk_field_0 = -1;
  m_unk_field_4 = -1;
  m_unk_field_8 = -1;
  m_unk_field_C = 0;
  m_unk_field_10 = 0;
  m_unk_field_14 = 0;
  m_unk_field_18 = 0;
  m_unk_field_1C = 0;
  m_unk_field_20 = 0;
  m_unk_field_24 = 0;
  m_unk_field_28 = 0;
  m_unk_field_2C = 0;
  m_unk_field_30 = 0;
  m_unk_field_34 = 0;
  m_unk_field_38 = 0;
  m_unk_field_3C = 0;
  m_unk_field_40 = 0;
  //m_unk_field_50 = constants::vec4_zero;
  //m_unk_field_60 = constants::vec4_zero;
}

// 002CD220
void CVillagerMngr::Initialize()
{
  log_trace("CVillagerMngr::Initialize()");

  m_n_villager_data = m_villager_data.size();

  for (auto& villager_data : m_villager_data)
  {
    villager_data.Initialize();
  }

  m_unk_field_0 = 0;
}