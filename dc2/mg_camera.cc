#include <array>
#include "common/log.h"
#include "mg_camera.h"
#include "mg_math.h"

set_log_channel("mg_camera");

// 00376C00
bool mgCCamera::StopCamera = false;

// 00131630
mgCCamera::mgCCamera(float speed)
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
}

// 00131110
void mgCCamera::Step(int steps)
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

  for (int i = 0; i < steps; ++i)
  {
    if (m_position_speed <= 1.0f && m_rotation_speed <= 1.0f)
    {
      // We snap to our new target in one frame, we're done here.
      m_position = m_next_position;
      m_reference = m_next_reference;
      break;
    }

    for (int j = 0; j < 3; ++j)
    {
      // Adjust our position
      // NOTE: no std::max for pos_speed in original game
      float pos_speed = std::max(m_position_speed, 1.0f);
      m_position[j] += (m_next_position[j] - m_position[j]) / pos_speed;

      // Adjust our direction
      float rot_speed = std::max(m_rotation_speed, 1.0f);
      m_reference[j] += (m_next_reference[j] - m_reference[j]) / pos_speed;

      // Check to see if are close enough to stop adjusting this component
      // Position
      if (std::fabsf(m_position[j] - m_next_position[j]) < m_step_epsilon)
      {
        m_position[j] = m_next_position[j];
      }

      // Direction
      if (std::fabsf(m_reference[j] - m_next_reference[j]) < m_step_epsilon)
      {
        m_reference[j] = m_next_reference[j];
      }
    }
  }

  // Record our pitch and yaw (these probably aren't pitch and yaw?)
  glm::vec3 direction = GetDir();

  glm::vec3 direction_normal = glm::normalize(glm::vec3{ direction.x, 0.0f, direction.z });
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
glm::mat4 mgCCamera::GetCameraMatrix() const
{
  log_trace("mgCCamera::GetCameraMatrix()");

  // FIXME: Check if this is correct
  return glm::lookAt(
    m_position,
    m_reference,
    glm::vec3(0, 1, 0)
  );
}

// 00131B50
int mgCCamera::Iam() const
{
  log_trace("mgCCamera::Iam()");

  return 0;
}

// 00131A90
mgCCameraFollow::mgCCameraFollow(
  float follow_distance,
  float height,
  float angle,
  float speed
) : mgCCamera(speed)
{
  log_trace(
    "mgCCameraFollow::mgCCameraFollow({}, {}, {}, {})",
    follow_distance,
    height,
    angle,
    speed
  );

  m_follow_next = glm::vec3(0.0f);
  m_angle_soon = angle;
  m_angle = angle;
  m_distance = follow_distance;
  m_height = height;
  m_follow_offset = glm::vec3(0.0f);
  m_following = true;
}

// 00131740
void mgCCameraFollow::Step(int steps)
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
    if (m_angle_soon > DEGREES_TO_RADIANS(360.0f))
    {
      m_angle_soon -= DEGREES_TO_RADIANS(360.0f);
    }
    if (m_angle_soon < 0)
    {
      m_angle_soon += DEGREES_TO_RADIANS(360.0f);
    }

    for (int i = 0; i < steps; ++i)
    {
      if (m_following)
      {
        m_angle = mgAngleInterpolate(
          m_angle,
          m_angle_soon,
          std::max(m_position_speed / 2.0f, 1.0f),
          true
        );

        if (m_position_speed < 1.1f)
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
int mgCCameraFollow::Iam() const
{
  log_trace("mgCCameraFollow::{}()", __func__);

  return 1;
}

// 00131680
glm::vec3 mgCCameraFollow::GetFollowNextPos() const
{
  log_trace("mgCCameraFollow::{}()", __func__);
  
  return glm::vec3(
    m_follow_next.x + (m_distance * sinf(m_angle)),
    m_follow_next.y + m_height,
    m_follow_next.z + (m_distance * cosf(m_angle))
  );
}