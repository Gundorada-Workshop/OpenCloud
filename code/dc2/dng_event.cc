#include <cmath>

#include "common/clock.h"
#include "common/log.h"

#include "dc2/dng_event.h"
#include "dc2/dng_main.h"
#include "dc2/mapjump.h"
#include "dc2/mg_lib.h"

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

  m_height_offset_sine += common::deg_to_rad(3.0f) * GAME_DT * GAME_FPS;

  if (m_height_offset_sine > common::deg_to_rad(180.0f))
  {
    // Mantain a continuous bound from -pi to +pi
    m_height_offset_sine -= common::deg_to_rad(360.0f);
  }
}

// 0028BD50
void CRandomCircle::Draw(glm::vec4* v)
{
  log_trace("CRandomCircle::{}()", __func__);

  for (int i = 0; i < m_unk_field_0.size(); ++i)
  {
    if (!m_unk_field_30[i])
    {
      continue;
    }

    if (glm::distance(*v, m_unk_field_0[i]) >= 1000.0f)
    {
      continue;
    }

    m_character.SetPosition(m_unk_field_0[i]);
    m_character.SetRotation(0.0f, 0.0f, 0.0f);
    m_character.DrawDirect();
  }
}

// 0028BE40
void CRandomCircle::Step()
{
  log_trace("CRandomCircle::{}()", __func__);

  m_character.Step();
}

// 0028BE60
void CRandomCircle::DrawSymbol(CMiniMapSymbol* mini_map_symbol)
{
  log_trace("CRandomCircle::{}({})", __func__, fmt::ptr(mini_map_symbol));

  for (int i = 0; i < m_unk_field_0.size(); ++i)
  {
    if (m_unk_field_30[i])
    {
      mini_map_symbol->DrawSymbol(m_unk_field_0[i], EMiniMapSymbol::RandomCircle);
    }
  }
}

// 0028BEF0
bool CRandomCircle::CheckArea(glm::vec4* v, float f)
{
  log_trace("CRandomCircle::{}({}, {})", __func__, fmt::ptr(v), f);

  for (int i = 0; i < m_unk_field_0.size(); ++i)
  {
    if (!m_unk_field_30[i])
    {
      continue;
    }

    if (glm::distance(m_unk_field_0[i], *v) < f)
    {
      return false;
    }
  }

  return true;
}

// 0028BFA0
bool CRandomCircle::GetPosition(glm::vec4* dest, ssize i)
{
  log_trace("CRandomCircle::{}({}, {})", __func__, fmt::ptr(dest), i);

  if (i == -1)
  {
    if (m_unk_field_3C == -1)
    {
      return false;
    }
    *dest = m_unk_field_0[m_unk_field_3C];
    return true;
  }
  else
  {
    if (i < 0 || m_unk_field_0.size() <= i)
    {
      return false;
    }
    *dest = m_unk_field_0[i];
    return true;
  }
}

// 0028C020
ssize CRandomCircle::CheckEvent(glm::vec4* v)
{
  log_trace("CRandomCircle::{}(({}, {}, {}))", __func__, v->x, v->y, v->z);

  for (int i = 0; i < m_unk_field_30.size(); ++i)
  {
    if (!m_unk_field_30[i])
    {
      continue;
    }

    if (glm::distance(m_unk_field_0[i], *v) <= 20.0f)
    {
      m_unk_field_3C = i;
      return i;
    }
  }

  m_unk_field_3C = -1;
  return -1;
}

// 0028C0D0
ssize CRandomCircle::SetCircle(glm::vec4* v)
{
  log_trace("CRandomCircle::{}(({}, {}, {}))", __func__, v->x, v->y, v->z);

  for (int i = 0; i < m_unk_field_30.size(); ++i)
  {
    if (!m_unk_field_30[i])
    {
      m_unk_field_0[i] = *v;
      m_unk_field_30[i] = true;
      return i;
    }
  }
  return -1;
}

// 0028C160
void CRandomCircle::Clear()
{
  log_trace("CRandomCircle::{}()", __func__);

  for (bool& b : m_unk_field_30)
  {
    b = false;
  }
  m_unk_field_3C = -1;
}
