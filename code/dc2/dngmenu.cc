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

  InitializeTexture();
}

// 001EA830
void CDngFreeMap::InitializeTexture()
{
  log_trace("CDngFreeMap::InitializeTexture()");

  m_unk_field_D8 = nullptr;
  m_unk_field_DC = nullptr;
  m_unk_field_E0 = nullptr;
  m_unk_field_D4 = nullptr;
  m_texb = -1;
}

// 001EE840
// "SetKomaMove"
void CDngFreeMap::SetPieceMove(s16 i)
{
  log_trace("CDngFreeMap::{}({})", __func__, i);

  m_unk_field_EC = i;
  m_unk_field_E8 = m_unk_field_E4;

  if (m_unk_field_E8 != nullptr)
  {
    m_unk_field_E8 = m_unk_field_E8->m_next;
  }
}