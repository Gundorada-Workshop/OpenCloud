#include "common/clock.h"
#include "common/constants.h"
#include "common/debug.h"
#include "common/log.h"

#include "dc2/rain.h"

set_log_channel("rain");

// 00281300
static f32 f_rand(f32 min, f32 max)
{
  log_trace("{}({}, {})", __func__, min, max);

  return (f32(rand()) / f32(common::constants::s32_max)) * (max - min) + min;
}

// 00281350
static s32 i_rand(s32 min, s32 max)
{
  log_trace("{}({}, {})", __func__, min, max);

  return s32(f_rand(f32(min), f32(max)));
}

inline static f32 frame_step(f32 scale = 1.0f)
{
  return scale * (GAME_DT * GAME_FPS);
}

// 002813A0
MAYBE_UNUSED static f32 RandXYinViewArea(f32 f1, f32 f2, f32 f3, f32* x_dest, f32* y_dest)
{
  log_trace("{}({}, {}, {}, {}, {})", __func__, f1, f2, f3, fmt::ptr(x_dest), fmt::ptr(y_dest));

  todo;
  return -1;
}

// 00281510
s32 CRipple::Birth(const vec3& position)
{
  log_trace("CRipple::{}({})", __func__, position);

  if (m_birthed)
  {
    return 0;
  }

  // If this ripple is now active
  m_birthed = true;

  // Position of the ripple
  m_position = position;

  // Size of the ripple
  m_scale = f_rand(8.0f, 12.0f);

  // Current anim frame / How many animation frames this ripple has
  m_frame = 0;
  m_frame_max = static_cast<f32>(i_rand(20, 40));
  
  return static_cast<s32>(m_frame_max);
}

// 00281590
CRipple::StepResult CRipple::Step()
{
  log_trace("CRipple::{}()", __func__);

  using enum CRipple::StepResult;

  if (!m_birthed)
  {
    return NotBirthed;
  }

  m_frame += frame_step();
  if (m_frame >= m_frame_max)
  {
    m_birthed = false;
    return Finished;
  }

  return Playing;
}

// 002815E0
void CRipple::Draw()
{
  log_trace("CRipple::{}()", __func__);

  todo;
}

// 002819E0
bool CParticle::Birth(const vec3& v1, const vec3& v2)
{
  log_trace("CParticle::{}({}, {})", __func__, v1, v2);

  if (m_birthed)
  {
    return false;
  }

  m_unk_field_30 = { 0.0f, -1.0f, 0.0f };
  m_unk_field_20 = v2;
  m_unk_field_10 = v1;
  m_unk_field_40 = v1.y;
  return true;
}

// 00281A60
CParticle::StepResult CParticle::Step()
{
  log_trace("CParticle::{}()", __func__);

  using enum CParticle::StepResult;

  if (!m_birthed)
  {
    return NotBirthed;
  }

  if (m_unk_field_10.y < m_unk_field_40)
  {
    m_birthed = false;
    return Finished;
  }

  // TODO: due to lack of understanding, this might not be the correct way to account for framerate
  m_unk_field_20.x += frame_step(m_unk_field_30.x);
  m_unk_field_20.y += frame_step(m_unk_field_30.y);
  m_unk_field_20.z += frame_step(m_unk_field_30.z);

  m_unk_field_10.x += frame_step(m_unk_field_20.x);
  m_unk_field_10.y += frame_step(m_unk_field_20.y);
  m_unk_field_10.z += frame_step(m_unk_field_20.z);

  return Playing;
}

// 00281B10
void CParticle::Draw()
{
  log_trace("CParticle::{}()", __func__);

  todo;
}

// 00282180
void CRain::SetCharNo(sint char_no)
{
  log_trace("CRain::{}({})", __func__, char_no);

  m_char_no = char_no;

  if (char_no == -1)
  {
    return;
  }

  for (CParticle particle : m_particles)
  {
    new (&particle) CParticle;
  }
}

// 002821F0
void ParticleBirth(const vec3& v, sint i)
{
  log_trace("CRain::{}({}, {})", __func__, v, i);

  todo;
}

// 002822D0
void CRain::Stop()
{
  log_trace("CRain::{}()", __func__);

  m_unk_field_0 = false;
}

// 002822E0
void CRain::Start()
{
  log_trace("CRain::{}()", __func__);

  todo;
}

// 002823E0
void CRain::Step()
{
  log_trace("CRain::{}()", __func__);

  todo;
}

// 002827D0
MAYBE_UNUSED static void DrawScreenRain()
{
  log_trace("{}()", __func__);

  todo;
}

// 002829E0
void CRain::Draw()
{
  log_trace("CRain::{}()", __func__);

  todo;
}