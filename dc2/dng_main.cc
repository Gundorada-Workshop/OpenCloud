#include <array>
#include "common/log.h"
#include "dng_main.h"
#include "mg_math.h"

set_log_channel("dng_main");

CAutoMapGen AutoMapGen;

// 001D4C40
void CMiniMapSymbol::DrawSymbol(glm::vec4& pos, EMiniMapSymbol::EMiniMapSymbol symbol_type)
{
  // 0033D8A0
  static std::array<MINIMAP_SYMBOL_DATA, EMiniMapSymbol::COUNT + 1> symbol_table
  {
    EMiniMapSymbol::SphidaShotGuide, {255, 0,   0},   10, 10, false, true,
    EMiniMapSymbol::TreasureBox,     {96,  64,  0},   10, 10, false, true,
    EMiniMapSymbol::RandomCircle,    {255, 255, 0},   10, 10, false, true,
    EMiniMapSymbol::GeoStone,        {255, 0,   180}, 10, 10, false, true,
    EMiniMapSymbol::SphidaRedGoal,   {255, 0,   0},   14, 14, false, false,
    EMiniMapSymbol::SphidaBlueGoal,  {0,   64,  255}, 14, 14, false, false,
    EMiniMapSymbol::SphidaRedBall,   {255, 0,   0},   10, 10, true,  false,
    EMiniMapSymbol::SphidaBlueBall,  {0,   0,   255}, 10, 10, true,  false,
    EMiniMapSymbol::Monster,         {255, 0,   0},   10, 10, true,  true,
    EMiniMapSymbol::TERMINATOR,      {0,   0,   0},   0,  0,  false, false,
  };

  log_trace("CMiniMapSymbol::DrawSymbol({}, {})", fmt::ptr(&pos), symbol_type);

  todo;
}

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