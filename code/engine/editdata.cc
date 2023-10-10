#include <array>
#include <string>

#include "common/log.h"
#include "common/constants.h"

#include "engine/editdata.h"

set_log_channel("editdata")

// 01F06300
std::array<EditAnalyzeSrc, 5> AnalyzeSrc{ };

// 00194550
CEditData::CEditData()
{
  log_trace("CEditData::CEditData()");

  memset(&m_unk_field_C, 0, sizeof(m_unk_field_C));
  memset(&m_unk_field_2A40, 0, sizeof(m_unk_field_2A40));
  memset(&m_unk_field_5040, 0, sizeof(m_unk_field_5040));
  
  Initialize();
}
// 002a89c0
void CEditData::Initialize()
{
  log_trace("CEditData::Initialize()");

  memset(this, 0, sizeof(this));
  InitPlaceData();
  memset(&m_unk_field_5040, 0, sizeof(m_unk_field_5040));
}
// 002a8a10
void CEditData::InitPlaceData()
{
  log_trace("CEditData::InitPlaceData()");

  m_unk_field_4 = 0;
  m_n_unk_field_C = m_unk_field_C.size();
  memset(&m_unk_field_C, 0, sizeof(m_unk_field_C));

  m_n_unk_field_2A40 = m_unk_field_2A40.size();
  memset(&m_unk_field_2A40, 0, sizeof(m_unk_field_2A40));

  for (usize i = 0; i < m_unk_field_2C40.size(); ++i)
  {
    m_unk_field_2C40[i] = -1;
  }

  for (usize i = 0; i < m_unk_field_4C40.size(); ++i)
  {
    m_unk_field_4C40[i] = common::constants::u8_max;
  }
}