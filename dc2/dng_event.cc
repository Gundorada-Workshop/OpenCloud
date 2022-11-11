#include <cmath>
#include "common/clock.h"
#include "common/log.h"
#include "dng_event.h"
#include "dng_main.h"
#include "mapjump.h"
#include "mg_lib.h"

set_log_channel("dng_event");

// 01F052C0
static MapJumpInfo MainMapInfo{};

void CGeoStone::Initialize()
{
  log_trace("CGeoStone::Initialize()");
  log_warn("Initialize should not be called (unless the game actually uses this as a virtual method on unknown type)");
  new (this) CGeoStone();
}

// 0028BCA0
bool CGeoStone::CheckEvent(glm::vec4& position)
{
  log_trace("CGeoStone::{}({})", __func__, fmt::ptr(&position));

  if (!m_flag)
  {
    return false;
  }

  glm::vec4 stone_position = GetPosition();
  return glm::distance(stone_position, position) <= 30.0f;
}

// 0028BA80
void CGeoStone::GeoDraw(glm::vec4& position)
{
  log_trace("CGeoStone::{}({})", __func__, fmt::ptr(&position));

  if (!m_flag)
  {
    return;
  }

  glm::vec4 orig_pos = GetPosition();
  glm::vec4 draw_pos{ orig_pos };

  if (glm::distance(draw_pos, position) < 1000.0f || !m_unk_field_668)
  {
    if (m_unk_field_668)
    {
      // Before drawing, adjust the y position of the stone.
      // This gives the illusion of the stone floating up and down over time.
      draw_pos.y = draw_pos.y + (sinf(m_height_offset_sine) * 3.0f);
    }

    SetPosition(draw_pos);
    DrawDirect();
  }

  // Restore the stone's original position
  SetPosition(orig_pos);
}

// 0028BB70
void CGeoStone::DrawMiniMapSymbol(CMiniMapSymbol* mini_map_symbol)
{
  log_trace("CGeoStone::{}({})", __func__, fmt::ptr(mini_map_symbol));

  if (!m_flag)
  {
    glm::vec4 stone_position = GetPosition();
    mini_map_symbol->DrawSymbol(stone_position, EMiniMapSymbol::GeoStone);
  }
}

// 0028BBC0
void CGeoStone::SetFlag(bool flag)
{
  log_trace("CGeoStone::{}({})", __func__, flag);

  m_flag = flag;
  if (!m_flag)
  {
    return;
  }

  if (AutoMapGen.m_map_parts == nullptr)
  {
    return;
  }

  AutoMapGen.m_map_parts->SetPosition(glm::vec4{ 0.0f, -99999.0f, 0.0f, 1.0f });
}

// 0028BC20
void CGeoStone::GeoStep()
{
  log_trace("CGeoStone::{}()", __func__);

  if (!m_flag)
  {
    return;
  }

  CCharacter2::Step();

  m_height_offset_sine += DEGREES_TO_RADIANS(3.0f) * GAME_DT * GAME_FPS;

  if (m_height_offset_sine > DEGREES_TO_RADIANS(180.0f))
  {
    // Mantain a continuous bound from -pi to +pi
    m_height_offset_sine -= DEGREES_TO_RADIANS(360.0f);
  }
}