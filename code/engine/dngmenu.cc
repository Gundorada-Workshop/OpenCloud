#include "common/log.h"

#include "graph/rectangle.h"

#include "engine/dngmenu.h"
#include "engine/mg/mg_lib.h"

set_log_channel("dngmenu");

// 00368640
static graph::irect dng_light_circle{ graph::irect::from_extent(388, 304, 124, 80) };

// 00368650
static graph::irect dngfreemap_num{ graph::irect::from_extent(0, 0, 12, 18) };

// 01EC8DE0
static graph::rect treemap_root_put{ 0, 0, 0, 0 };

// 01EC8DF0
static graph::irect Floor_Info{ graph::irect::from_extent(0, 238, 256, 18) };

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

// 001EE790
void CDngFreeMap::FadeIn(s32 duration)
{
  log_trace("CDngFreeMap::{}({})", __func__, duration);

  m_fade_status = EDngFreeMapFadeStatus::FadeIn;
  m_fade_duration = duration;
  m_fade_alpha = 128.0f; // Max alpha FIXME: set correct value for PC

  if (duration != 0)
  {
    m_fade_alpha /= static_cast<f32>(duration);
  }

  m_unk_field_F0 = 0;
}

// 001EE7D0
void CDngFreeMap::FadeOut(s32 duration)
{
  log_trace("CDngFreeMap::{}({})", __func__, duration);
  m_fade_status = EDngFreeMapFadeStatus::FadeOut;
  m_fade_duration = duration;
  m_fade_alpha = -128.0f; // Min alpha FIXME: set correct value for PC

  if (duration != 0)
  {
    m_fade_alpha /= static_cast<f32>(duration);
  }
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