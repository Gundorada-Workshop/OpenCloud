#include <array>

#include "common/clock.h"
#include "common/log.h"

#include "dc2/mg/mg_camera.h"
#include "dc2/mg/mg_math.h"

set_log_channel("mg_camera");

// 00376C00
bool mgCCamera::StopCamera = false;

// 00131630
mgCCamera::mgCCamera(f32 speed)
{
  log_trace("mgCCamera::mgCCamera({})", speed);

  if (speed <= 0.0f)
  {
    speed = 1.0f;
  }

  m_position_speed = speed;
  m_rotation_speed = speed;
  m_unk_field_44 = 0;
  m_roll = 0.0f;

  // how close a pos/dir component has to get to next pos/dir in order
  // to snap to the final position.
  m_step_epsilon = 0.1f;
  m_stopped = false;

  // additional members
  SetPos(0, 0, 0);
  SetNextPos(0, 0, 0);
  SetRef(0, 0, 0);
  SetNextRef(0, 0, 0);
  m_angleH = 0.0f;
  m_angleV = 0.0f;
}

// 00131110
void mgCCamera::Step(sint steps)
{
  log_trace("mgCCamera::Step({})", steps);

  if (m_stopped || StopCamera)
  {
    return;
  }

  if (m_position_speed <= 0.0f)
  {
    m_position_speed = 1.0f;
  }

  if (m_rotation_speed <= 0.0f)
  {
    m_rotation_speed = 1.0f;
  }

  if (steps < 0)
  {
    // Instantly go to next
    m_position = m_next_position;
    m_reference = m_next_reference;
  }

  for (sint i = 0; i < steps; ++i)
  {
    f32 one_frame = GAME_DT * GAME_FPS;
    if (m_position_speed <= one_frame && m_rotation_speed <= one_frame)
    {
      // We snap to our new target in one frame, we're done here.
      m_position = m_next_position;
      m_reference = m_next_reference;
      break;
    }

    for (usize j = 0; j < 3; ++j)
    {
      // Adjust our position
      // NOTE: no std::max for pos_speed in original game
      f32 pos_speed = std::max(m_position_speed, 1.0f);
      m_position[j] += (m_next_position[j] - m_position[j]) / pos_speed * one_frame;

      // Adjust our direction
      f32 rot_speed = std::max(m_rotation_speed, 1.0f);
      m_reference[j] += (m_next_reference[j] - m_reference[j]) / pos_speed * one_frame;

      // Check to see if are close enough to stop adjusting this component
      f32 step_epsilon = m_step_epsilon * one_frame;
      // Position
      if (std::fabsf(m_position[j] - m_next_position[j]) < step_epsilon)
      {
        m_position[j] = m_next_position[j];
      }

      // Direction
      if (std::fabsf(m_reference[j] - m_next_reference[j]) < step_epsilon)
      {
        m_reference[j] = m_next_reference[j];
      }
    }
  }

  // Record our pitch and yaw (these probably aren't pitch and yaw?)
  vec3 direction = GetDir();

  vec3 direction_normal = glm::normalize(vec3{ direction.x, 0.0f, direction.z });
  m_angleH = atan2f(direction_normal.x, direction_normal.z);
  m_angleV = -atan2f(direction.y, sqrtf(powf(direction.x, 2) + powf(direction.z, 2)));
}

// 00131B30
void mgCCamera::Suspend()
{
  log_trace("mgCCamera::Suspend()");

  m_stopped = true;
}

// 00131B40
void mgCCamera::Resume()
{
  log_trace("mgCCamera::Resume()");

  m_stopped = false;
}

// 001313A0
void mgCCamera::Stay()
{
  log_trace("mgCCamera::Stay()");

  m_next_position = m_position;
  m_next_reference = m_reference;
}

// 001314D0
matrix4 mgCCamera::GetCameraMatrix() const
{
  log_trace("mgCCamera::GetCameraMatrix()");

  // FIXME: Check if this is correct
  return glm::lookAt(
    m_position,
    m_reference,
    vec3(0, 1, 0)
  );
}

// 00131B50
sint mgCCamera::Iam() const
{
  log_trace("mgCCamera::Iam()");

  return 0;
}

// 00131A90
mgCCameraFollow::mgCCameraFollow(
  f32 follow_distance,
  f32 height,
  f32 angle,
  f32 speed
) : mgCCamera(speed)
{
  log_trace(
    "mgCCameraFollow::mgCCameraFollow({}, {}, {}, {})",
    follow_distance,
    height,
    angle,
    speed
  );

  m_follow_next = vec3(0.0f);
  m_angle_soon = angle;
  m_angle = angle;
  m_distance = follow_distance;
  m_height = height;
  m_follow_offset = vec3(0.0f);
  m_following = true;
}

// 00131740
void mgCCameraFollow::Step(sint steps)
{
  log_trace("mgCCameraFollow::{}({})", __func__, steps);

  if (m_stopped || StopCamera)
  {
    return;
  }

  m_follow_next = m_follow + m_follow_offset;

  if (steps < -1)
  {
    // Instantly go to next
    if (m_following)
    { 
      m_angle = m_angle_soon;
      SetNextPos(GetFollowNextPos());
      SetNextRef(m_follow_next);
    }
    mgCCamera::Step(steps);
  }
  else
  {
    // Clamp m_angle_soon to [0, 360.0] degrees in radians
    if (m_angle_soon > common::deg_to_rad(360.0f))
    {
      m_angle_soon -= common::deg_to_rad(360.0f);
    }
    if (m_angle_soon < 0)
    {
      m_angle_soon += common::deg_to_rad(360.0f);
    }

    for (sint i = 0; i < steps; ++i)
    {
      if (m_following)
      {
        f32 position_speed = m_position_speed / (GAME_DT * GAME_FPS);
        m_angle = mgAngleInterpolate(
          m_angle,
          m_angle_soon,
          std::max(position_speed / 2.0f, 1.0f),
          true
        );

        if (position_speed < 1.1f)
        {
          m_angle = m_angle_soon;
        }

        SetNextPos(GetFollowNextPos());
        SetNextRef(m_follow_next);
      }
      mgCCamera::Step();
    }

    if (m_following)
    {
      m_angle_soon = m_angleH;
      m_angle = m_angleH;
    }
  }
}

// 00131950
void mgCCameraFollow::Stay()
{
  log_trace("mgCCameraFollow::{}()", __func__);

  mgCCamera::Stay();

  if (m_following)
  {
    m_follow_next = m_next_reference;
    m_angle_soon = m_angle;
  }
}

// 00131B20
sint mgCCameraFollow::Iam() const
{
  log_trace("mgCCameraFollow::{}()", __func__);

  return 1;
}

// 00131680
vec3 mgCCameraFollow::GetFollowNextPos() const
{
  log_trace("mgCCameraFollow::{}()", __func__);
  
  return vec3(
    m_follow_next.x + (m_distance * sinf(m_angle)),
    m_follow_next.y + m_height,
    m_follow_next.z + (m_distance * cosf(m_angle))
  );
}