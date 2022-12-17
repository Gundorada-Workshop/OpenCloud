#include "common/log.h"
#include "common/math.h"
#include "common/constants.h"

#include "dc2/camera.h"
#include "dc2/mg/mg_math.h"

set_log_channel("camera");

using namespace common;

// 002EBE80
CCameraControl::CCameraControl()
  : mgCCameraFollow(40.0f, 30.0f, 0.0f, 8.0f)
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
void CCameraControl::Step(sint steps)
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
  vec3 difference = m_next_reference - m_next_position;

  m_distance = math::vector_distance(constants::vec3_zero, difference);

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
void CCameraControl::MoveCamera(MAYBE_UNUSED const CPadControl* pad_control, MAYBE_UNUSED const vec3& v, MAYBE_UNUSED CCPoly* c_poly, MAYBE_UNUSED usize i)
{
  log_trace("CCameraControl::{}({}, {}, {}, {})", __func__, fmt::ptr(&pad_control), fmt::ptr(&v), fmt::ptr(c_poly), i);

  todo;
}

// 002EC370
void CCameraControl::MoveCamera(MAYBE_UNUSED const Control& control, MAYBE_UNUSED const vec3& v, MAYBE_UNUSED CCPoly* c_poly, MAYBE_UNUSED usize i)
{
  log_trace("CCameraControl::{}({}, {}, {}, {})", __func__, fmt::ptr(&control), fmt::ptr(&v), fmt::ptr(c_poly), i);

  if (!m_controlling)
  {
    return;
  }

  CameraCtrlParam& active_param = GetActiveParam();
  
  vec3 next_difference;
  vec3 next_difference_normal;
  vec3 var_10 = constants::vec3_zero;

  m_next_reference = GetFollow() + GetFollowOffset();

  next_difference = m_next_reference - m_next_position;
  next_difference.y = 0.0f;

  next_difference_normal = math::vector_normalize(next_difference);
  f32 dist = math::vector_distance(next_difference, constants::vec3_zero);

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

  f32 f = control.x * active_param.m_unk_field_0 / std::min(dist, active_param.m_unk_field_0);
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
  f32 f0;
  f32 f1;
  f32 f2;
  f32 f4 = active_param.m_unk_field_C - active_param.m_unk_field_8;
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
    RotBack(v.y - math::deg_to_rad(180.0f));
  }

  if (m_unk_field_C8)
  {
    f32 f6 = mgAngleInterpolate(GetAngle(), m_unk_field_CC, 1.0f, false);
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
void CCameraControl::Rotate(f32 delta)
{
  log_trace("CCameraControl::{}({})", __func__, delta);

  vec4 var_50;
  matrix4 var_40 = matrix4(1.0f);

  var_50 = vec4(m_next_position - m_next_reference, 1.0f);
  delta = mgAngleLimit(delta);

  // TODO: replace
  glm::rotate(var_40, delta, vec3(0, 1, 0));

  var_50 = var_40 * var_50;
  m_next_position = m_next_reference + vec3(var_50);
}

// 002EC790
void CCameraControl::SetRotate(f32 rot)
{
  log_trace("CCameraControl::{}({})", __func__, rot);

  vec4 var_50 = vec4(0.0f);
  matrix4 var_40 = matrix4(1.0f);

  var_50.z = math::vector_distance(
    vec3(m_next_reference.x, 0.0f, m_next_reference.z),
    vec3(m_next_position.x, 0.0f, m_next_position.z)
  );
  var_50.y = m_next_position.y - m_next_reference.y;

  // TODO: replace
  glm::rotate(var_40, mgAngleLimit(rot), vec3(0, 1, 0));

  var_50 = var_40 * var_50;
  m_next_position = m_next_reference + vec3(var_50);
}

// 002EC830
void CCameraControl::SetHeight(f32 height)
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
void CCameraControl::CheckCollision(MAYBE_UNUSED CCPoly* c_poly, MAYBE_UNUSED usize i)
{
  log_trace("CCameraControl::{}({})", __func__, fmt::ptr(c_poly), i);

  todo;
}

// 002ECB60
void CCameraControl::AutoMove(MAYBE_UNUSED CCPoly* c_poly, MAYBE_UNUSED usize i)
{
  log_trace("CCameraControl::{}({})", __func__, fmt::ptr(c_poly), i);

  todo;
}

// 002ECE70
void CCameraControl::CheckGround(MAYBE_UNUSED CCPoly* c_poly, MAYBE_UNUSED usize i)
{
  log_trace("CCameraControl::{}({})", __func__, fmt::ptr(c_poly), i);

  todo;
}

// 002ED250
matrix4 CCameraControl::GetCameraMatrix()
{
  log_trace("CCameraControl::{}()", __func__);

  todo;

  return matrix4{ 1.0f };
}

void CCameraControl::CopyParam(MAYBE_UNUSED CCameraControl& other)
{

}

// 002ED3D0
sint CCameraControl::Iam()
{
  log_trace("CCameraControl::{}()", __func__);

  return 1000;
}