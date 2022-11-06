#include "common/log.h"
#include "dng_main.h"
#include "mg_math.h"

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

// 001CB3E0
void CLockOnModel::Draw_()
{
  log_trace("CLockOnModel::Draw_()");

  todo;
}

// 001CB860
void CLockOnModel::Step()
{
  log_trace("CLockOnModel::Step()");

  // NOTE: DEGREES_TO_RADIANS(4.0f) == 0x3D8EFA35
  m_unk_field_88 += DEGREES_TO_RADIANS(4.0f);

  if (m_unk_field_88 > M_PI_F)
  {
    m_unk_field_88 -= (M_PI_F * 2);
  }
}

// 001CBD20
void CLockOnModel::Initialize(CScene* scene)
{
  log_trace("CLockOnModel::Initialize({})", fmt::ptr(scene));

  m_scene = scene;
  m_unk_field_8C = 0;
}

// 001CB7B0
void CLockOnModel::DrawMes(int i)
{
  log_trace("CLockOnModel::DrawMes({})", i);

  todo;
}