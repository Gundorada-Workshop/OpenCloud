#include "common/log.h"
#include "mg_tanime.h"

set_log_channel("mg_tanime");

// 00380E70
static mgCTexAnimeData nowTexData;

namespace mg_tanime
{
  // 00373410
  void SInit()
  {
    log_trace("SInit()");

    nowTexData = mgCTexAnimeData();
  }
}

// 0013BCD0
mgCTexAnimeData::mgCTexAnimeData()
{
  log_trace("mgCTexAnimeData::mgCTexAnimeData()");

  Initialize();
}

// 0013BD00
void mgCTexAnimeData::Initialize()
{
  log_trace("mgCTexAnimeData::Initialize()");

  m_unk_field_0 = -1;
  m_unk_field_1 = 0;
  m_unk_field_28 = 0;
  m_unk_field_3 = 0;
  m_unk_field_8 = 0;
  m_unk_field_4 = 0;
  m_unk_field_12 = 0;
  m_unk_field_10 = 0;
  m_unk_field_E = 0;
  m_unk_field_C = 0;
  m_unk_field_16 = 0;
  m_unk_field_14 = 0;
  m_unk_field_22 = 0;
  m_unk_field_20 = 0;
  m_unk_field_1E = 0;
  m_unk_field_1C = 0;
  m_unk_field_24 = 0;
  m_unk_field_2 = -1;
  m_unk_field_2C = 1;
  m_unk_field_2D = 4;
  m_unk_field_2E = -1;
  m_unk_field_2F = 0;
  m_unk_field_2A = 4;
  m_unk_field_33 = 0x80;
  m_unk_field_32 = 0x80;
  m_unk_field_31 = 0x80;
  m_unk_field_30 = 0x80;
}