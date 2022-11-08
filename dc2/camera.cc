#include "glm/glm.hpp"
#include "common/log.h"
#include "camera.h"
#include "mg_math.h"

set_log_channel("camera");

// 002EBE80
CCameraControl::CCameraControl() : mgCCameraFollow(40.0f, 30.0f, 0.0f, 8.0f)
{
  // 2EBF04 compiler code end (ignore branch slot)
  log_trace("CCameraControl::CCameraControl()");

  m_controlling = false;
  m_n_active_param = 0;
  CameraCtrlParam& param = GetActiveParam();
  param.m_unk_field_0 = 100.0f;
  param.m_unk_field_4 = 160.0f;
  param.m_unk_field_8 = 18.0f;
  param.m_unk_field_C = 10.0f;
  param.m_unk_field_14 = 40.0f;
  param.m_unk_field_18 = -15.0f;
  param.m_unk_field_1C = 20.0f;
  param.m_unk_field_20 = -15.0f;
  param.m_unk_field_10 = -15.0f;
  param.m_unk_field_24 = 25.0f;
  m_unk_field_1E0 = 0;
  param.m_unk_field_28 = 0;

  InitStatus();
  m_active_param = CameraCtrlParam(GetActiveParam());
}

// 002EC0D0
void CCameraControl::Stay()
{
  log_trace("CCameraControl::Stay()");

  if (m_controlling)
  {
    mgCCamera::Stay();
  }
  else
  {
    mgCCameraFollow::Stay();
  }
}
// 002EC110
void CCameraControl::Step(int steps)
{
  log_trace("CCameraControl::Step({})", steps);

  if (!m_controlling)
  {
    mgCCameraFollow::Step(steps);
    return;
  }

  if (steps < 0 && m_unk_field_C8)
  {
    SetRotate(m_unk_field_CC);
  }

  mgCCamera::Step(steps);
  glm::vec3 difference = m_next_reference - m_next_position;
  m_distance = glm::distance(glm::vec3(0.0f), difference);
  m_height = -difference.y;
  m_angle_soon = atan2f(-difference.x, -difference.z);

  difference = m_reference - m_position;
  m_angle = atan2f(-difference.x, -difference.z);
}

// 002EC030
void CCameraControl::ControlOn()
{
  log_trace("CCameraControl::ControlOn()");

  if (m_controlling)
  {
    return;
  }

  m_next_reference = m_reference;
  m_next_position = m_position;

  CameraCtrlParam& param = GetActiveParam();

  param.m_unk_field_10 = std::clamp(
    m_next_position.y - m_next_reference.y,
    param.m_unk_field_18,
    param.m_unk_field_14
  );

  m_controlling = true;
}

// 002EC1F0
void CCameraControl::MoveCamera(const CPadControl* pad_control, const glm::vec3& v, CCPoly* c_poly, usize i)
{
  log_trace("CCameraControl::{}({}, {}, {}, {})", __func__, fmt::ptr(&pad_control), fmt::ptr(&v), fmt::ptr(c_poly), i);

  todo;
}

// 002EC370
void CCameraControl::MoveCamera(const Control& control, const glm::vec3& v, CCPoly* c_poly, usize i)
{
  log_trace("CCameraControl::{}({}, {}, {}, {})", __func__, fmt::ptr(&control), fmt::ptr(&v), fmt::ptr(c_poly), i);

  if (!m_controlling)
  {
    return;
  }

  CameraCtrlParam& active_param = GetActiveParam();
  
  glm::vec3 follow;
  glm::vec3 follow_offset;
  glm::vec3 next_difference;
  glm::vec3 next_difference_normal;
  glm::vec3 var_10 = glm::vec3(0);

  GetFollow(follow);
  GetFollowOffset(follow_offset);
  m_next_reference = follow + follow_offset;

  next_difference = m_next_reference - m_next_position;
  next_difference.y = 0.0f;
  glm::normalize(next_difference_normal);
  float dist = glm::distance(next_difference, glm::vec3(0));

  if (dist > 0.0f)
  {
    next_difference.z = 1.0f;
    next_difference_normal.z = 1.0f;
  }

  if (dist < active_param.m_unk_field_0)
  {
    var_10 = next_difference_normal * (dist - active_param.m_unk_field_0);
  }

  if (dist > active_param.m_unk_field_4)
  {
    var_10 = next_difference_normal * (dist - active_param.m_unk_field_4);
  }

  float f = control.x * active_param.m_unk_field_0 / std::min(dist, active_param.m_unk_field_0);
  if (f != 0.0f)
  {
    Rotate(f);
  }

  active_param.m_unk_field_10 = std::max(
    active_param.m_unk_field_10 + control.y,
    active_param.m_unk_field_18
  );

  active_param.m_unk_field_10 = std::min(
    active_param.m_unk_field_10,
    active_param.m_unk_field_14
  );

  if (control.y == 0.0f)
  {
    if (active_param.m_unk_field_10 > active_param.m_unk_field_20)
    {
      active_param.m_unk_field_10 += \
        (active_param.m_unk_field_20 - active_param.m_unk_field_10) / 20.0f;
    }

    if (active_param.m_unk_field_10 < active_param.m_unk_field_1C)
    {
      active_param.m_unk_field_10 += \
        (active_param.m_unk_field_1C - active_param.m_unk_field_10) / 20.0f;
    }
  }

  // TODO clean this up
  // 2EC588
  float f0;
  float f1;
  float f2;
  float f4 = active_param.m_unk_field_C - active_param.m_unk_field_8;
  f1 = dist - active_param.m_unk_field_0;
  f2 = active_param.m_unk_field_4 - active_param.m_unk_field_0;
  f1 /= f2;
  f0 = active_param.m_unk_field_C - f4;
  f0 *= f1;
  f0 += f4;
  var_10.y = f0;

  m_next_position.y = m_next_reference.y + active_param.m_unk_field_10;

  if (control.m_unk_field_8 && (m_rot_camera_cancel & 0x40) == 0)
  {
    RotBack(v.y - DEGREES_TO_RADIANS(180.0f));
  }

  if (m_unk_field_C8)
  {
    float f6 = mgAngleInterpolate(GetAngle(), m_unk_field_CC, 1.0f, false);
    SetRotate(f6);

    if (mgAngleCmp(f6, m_unk_field_CC, 0.1f) == 0)
    {
      m_unk_field_C8 = false;
    }
  }

  if (active_param.m_unk_field_28)
  {
    CheckGround(c_poly, i);

    if (f != 0.f && (m_rot_camera_cancel & 0x80) != 0)
    {
      CheckCollision(c_poly, i);
    }
    else
    {
      CheckCollision(c_poly, i);
      AutoMove(c_poly, i);
    }
  }
}

// 002EC710
void CCameraControl::Rotate(float delta)
{
  log_trace("CCameraControl::{}({})", __func__, delta);

  glm::vec4 var_50;
  glm::mat4 var_40 = glm::mat4(1.0f);

  var_50 = glm::vec4(m_next_position - m_next_reference, 1.0f);
  delta = mgAngleLimit(delta);
  glm::rotate(var_40, delta, glm::vec3(0, 1, 0));
  var_50 = var_40 * var_50;
  m_next_position = m_next_reference + glm::vec3(var_50);
}

// 002EC790
void CCameraControl::SetRotate(float rot)
{
  log_trace("CCameraControl::{}({})", __func__, rot);

  glm::vec4 var_50 = glm::vec4(0.0f);
  glm::mat4 var_40 = glm::mat4(1.0f);

  var_50.z = glm::distance(
    glm::vec3(m_next_reference.x, 0.0f, m_next_reference.z),
    glm::vec3(m_next_position.x, 0.0f, m_next_position.z)
  );
  var_50.y = m_next_position.y - m_next_reference.y;

  glm::rotate(var_40, mgAngleLimit(rot), glm::vec3(0, 1, 0));
  var_50 = var_40 * var_50;
  m_next_position = m_next_reference + glm::vec3(var_50);
}

// 002EC830
void CCameraControl::SetHeight(float height)
{
  log_trace("CCameraControl::{}({})", __func__, height);

  if (!m_controlling)
  {
    mgCCameraFollow::SetHeight(height);
  }

  GetActiveParam().m_unk_field_10 = height;
  m_next_position.y = m_next_reference.y + height;
}

// 002EC910
void CCameraControl::CheckCollision(CCPoly* c_poly, usize i)
{
  log_trace("CCameraControl::{}({})", __func__, fmt::ptr(c_poly), i);

  todo;
}

// 002ECB60
void CCameraControl::AutoMove(CCPoly* c_poly, usize i)
{
  log_trace("CCameraControl::{}({})", __func__, fmt::ptr(c_poly), i);

  todo;
}

// 002ECE70
void CCameraControl::CheckGround(CCPoly* c_poly, usize i)
{
  log_trace("CCameraControl::{}({})", __func__, fmt::ptr(c_poly), i);

  todo;
}

// 002ED250
void CCameraControl::GetCameraMatrix(glm::mat4& dest)
{
  log_trace("CCameraControl::{}({})", __func__, fmt::ptr(&dest));
}

void CCameraControl::CopyParam(CCameraControl& other)
{

}

// 002ED3D0
int CCameraControl::Iam()
{
  log_trace("CCameraControl::{}()", __func__);

  return 1000;
}