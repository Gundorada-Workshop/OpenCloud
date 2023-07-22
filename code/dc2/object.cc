#include "common/log.h"

#include "dc2/mg/mg_lib.h"
#include "dc2/object.h"

set_log_channel("object");

// 00160B50
unkptr CObject::Draw()
{
  log_trace("CObject::{}()", __func__);

  return nullptr;
}

// 00160B60
unkptr CObject::DrawDirect()
{
  log_trace("CObject::{}()", __func__);

  return nullptr;
}

void CObject::Initialize()
{
  log_trace("CObject::Initialize()");
  log_warn("Initialize should not be called (unless the game actually uses this as a virtual method on unknown type)");
  new (this) CObject();
}

// 00169DB0
bool CObject::PreDraw()
{
  log_trace("CObject::{}()", __func__);

  return m_visible && !m_unk_field_68;
}

// 00169C10
f32 CObject::GetCameraDist()
{
  log_trace("CObject::{}()", __func__);

  return 0.0f;
  //return mgGetDistFromCamera(m_position);
}

// 00169AC0
bool CObject::FarClip(float distance, float* alpha_result)
{
  log_trace("CObject::{}({}, {})", __func__, distance, fmt::ptr(alpha_result));

  *alpha_result = 1.0f;

  bool is_visible = true;
  float fade_delta = m_fade_delta;

  if (m_far_dist > 0.0f && distance > m_far_dist)
  {
    // Object is too far from the camera; make it fade out.
    is_visible = false;
  }

  if (m_near_dist > 0.0f && distance < m_near_dist)
  {
    // Object is too close to the camera; make it fade out.
    is_visible = false;
    // Twice as fast for objects which are too close.
    fade_delta *= 2.0f;
  }

  if (!m_visible)
  {
    // Not going to show invisible objects, unsurprisingly.
    is_visible = false;
  }

  if (m_unk_field_68)
  {
    is_visible = false;
  }

  if (m_alpha < 0.0f)
  {
    // 00169B78
    m_alpha = is_visible ? 1.0f : 0.0f;
  }

  if (!m_fade_flag)
  {
    // If we don't want a fade, we either want to be
    // max alpha or no alpha
    return is_visible;
  }

  if (is_visible)
  {
    // 00169BA0
    // Fade the object in until we reach max alpha.
    m_alpha = std::min(m_alpha + fade_delta, 1.0f);
  }
  else
  {
    // 00169BCC
    // Fade the object out until we reach min alpha.
    m_alpha = std::max(m_alpha - fade_delta, 0.0f);
    is_visible = m_alpha > 0.0f;
  }

  *alpha_result = m_alpha;
  return is_visible;
}

// 00169D10
void CObject::DrawStep()
{
  log_trace("CObject::{}()", __func__);

  f32 fp;
  FarClip(GetCameraDist(), &fp);
}

// 00169D60
float CObject::GetAlpha()
{
  log_trace("CObject::{}()", __func__);

  if (m_fade_flag)
  {
    return m_alpha;
  }

  if (CheckDraw())
  {
    return 1.0f;
  }
  else
  {
    return 0.0f;
  }
}
// 00160B70
void CObject::Show(bool visible)
{
  log_trace("CObject::{}({})", __func__, visible);

  m_visible = visible;
}
// 0015F110
bool CObject::GetShow()
{
  log_trace("CObject::{}()", __func__);

  return m_visible;
}
// 00160B80
void CObject::SetFarDist(float far_dist)
{
  log_trace("CObject::{}({})", __func__, far_dist);

  m_far_dist = far_dist;
}

// 00160B90
float CObject::GetFarDist()
{
  log_trace("CObject::{}()", __func__);

  return m_far_dist;
}

// 00160BA0
void CObject::SetNearDist(float near_dist)
{
  log_trace("CObject::{}({})", __func__, near_dist);

  m_near_dist = near_dist;
}

// 00160BB0
float CObject::GetNearDist()
{
  log_trace("CObject::{}()", __func__);

  return m_near_dist;
}

// 00169C20
bool CObject::CheckDraw()
{
  log_trace("CObject::{}()", __func__);

  if (m_fade_flag)
  {
    return m_alpha != 0.0f;
  }

  if (!m_visible || m_unk_field_68)
  {
    return false;
  }

  f32 camera_dist = GetCameraDist();

  if (m_far_dist > 0.0f && camera_dist > m_far_dist)
  {
    return false;
  }

  if (m_near_dist > 0.0f && camera_dist < m_near_dist)
  {
    return false;
  }

  return true;
}

// 00160BC0
void CObject::Copy(MAYBE_UNUSED CObject& other, MAYBE_UNUSED mgCMemory* mem)
{
  log_trace("CObject::{}({}, {})", __func__, fmt::ptr(&other), fmt::ptr(mem));

  todo;
}

void CObjectFrame::Initialize()
{
  log_trace("CObjectFrame::Initialize()");
  log_warn("Initialize should not be called (unless the game actually uses this as a virtual method on unknown type)");
  new (this) CObjectFrame();
}

// 00169FD0
unkptr CObjectFrame::Draw()
{
  log_trace("CObjectFrame::Draw()");

  if (PreDraw())
  {
    mgDraw(m_frame);
  }
  
  return nullptr;
}

// 0016A010
unkptr CObjectFrame::DrawDirect()
{
  log_trace("CObjectFrame::DrawDirect()");

  if (PreDraw())
  {
    mgDrawDirect(m_frame);
  }

  return nullptr;
}

// 00169F30
bool CObjectFrame::PreDraw()
{
  log_trace("CObjectFrame::PreDraw()");

  todo;
  return false;
}

// 00169F00
f32 CObjectFrame::GetCameraDist()
{
  log_trace("CObjectFrame::GetCameraDist()");

  todo;
  return INFINITY;
}

// 00169EF0
void CObjectFrame::DrawStep()
{
  log_trace("CObjectFrame::DrawStep()");

  CObject::DrawStep();
}

// 00169E80
void CObjectFrame::UpdatePosition()
{
  log_trace("CObjectFrame::UpdatePosition()");

  //if (m_frame == nullptr)
  //{
  //  return;
  //}

  //m_frame->SetPosition(m_position);
  //m_frame->SetRotation(m_rotation);
  //m_frame->SetScale(m_scale);
}

// 0016A050
void CObjectFrame::Copy(MAYBE_UNUSED CObjectFrame& other, MAYBE_UNUSED mgCMemory* mem)
{
  log_trace("CObject::{}({}, {})", __func__, fmt::ptr(&other), fmt::ptr(mem));

  todo;
}