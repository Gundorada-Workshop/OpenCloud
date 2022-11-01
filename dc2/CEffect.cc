#include "string.h"
#include "common/log.h"
#include "CEffect.h"

set_log_channel("CEffect");

// 0017D750
void CFadeInOut::Initialize()
{
  log_trace("CFadeInOut::Initialize()");

  m_unk_field_0 = 0.0f;
  m_unk_field_4 = 0.0f;
  m_unk_field_8 = 0.0f;
  m_unk_field_C = 0.0f;
  m_unk_field_10 = 0;
  m_unk_field_14 = false;
  m_unk_field_18 = 0.0f;
  m_unk_field_1C = 0;
  m_unk_field_20 = false;
  m_unk_field_24 = 0.0f;
  m_unk_field_28 = nullptr;
  m_unk_field_2C = 0;
}

// 001847C0
void CFireRaster::Initialize()
{
  log_trace("CFireRaster::Initialize()");

  for (auto& unk_var : m_unk_field_70)
  {
    memset(&unk_var, 0, sizeof(unk_var));
  }
}