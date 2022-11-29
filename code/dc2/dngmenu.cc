#include "common/log.h"

#include "dc2/dngmenu.h"
#include "dc2/mg/mg_lib.h"

set_log_channel("dngmenu");

// 00368640
static irect dng_light_circle{ irect::from_extent(388, 304, 124, 80) };

// 00368650
static irect dngfreemap_num{ irect::from_extent(0, 0, 12, 18) };

// 01EC8DE0
static rect treemap_root_put{ 0, 0, 0, 0 };

// 01EC8DF0
static irect Floor_Info{ irect::from_extent(0, 238, 256, 18) };

// 01EC8E00
static mgCMemory MenuTreeMapStack{ };

// 001EA760
CDngFreeMap::CDngFreeMap()
{
  log_trace("CDngFreeMap::CDngFreeMap()");

  m_unk_field_8 = true;
  m_unk_field_9 = 0;
  m_unk_field_A = 0;
  m_unk_field_4 = 0;
  m_unk_field_0 = 0;
  m_unk_field_C = 0;

  m_unk_field_20 = rect::from_extent(120, 138, 420, 286);

  for (auto& rect : m_unk_field_40)
  {
    rect = rect::from_extent(0, 0, 0, 0);
  }

  m_unk_field_30 = 0;
  m_unk_field_C2 = -1;
  m_unk_field_C0 = -1;
  m_unk_field_10 = 0;
  m_unk_field_104 = 0;
  m_unk_field_100 = 0;
  m_unk_field_108 = 200.0f;
  m_unk_field_10C = 200.0f;
  m_unk_field_CC = 0;

  InitializeTexture();

  m_unk_field_F0 = 128.0f;
  m_unk_field_C4 = 0;
  m_unk_field_C8 = 0;
  m_unk_field_E8 = 0;
  m_unk_field_E4 = 0;
  m_unk_field_EC = 0;
  m_unk_field_FC = -1;
  m_unk_field_F4 = -1;
  m_unk_field_F8 = 0;
}

// 001EA830
void CDngFreeMap::InitializeTexture()
{
  log_trace("CDngFreeMap::InitializeTexture()");

  m_unk_field_D8 = 0;
  m_unk_field_DC = 0;
  m_unk_field_E0 = 0;
  m_unk_field_D4 = 0;
  m_unk_field_D0 = -1;
}