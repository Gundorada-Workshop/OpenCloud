#include "common/log.h"
#include "mg_camera.h"

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

  // Record our pitch and yaw
  glm::vec3 direction;
  GetDir(direction);

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
void mgCCamera::GetCameraMatrix(glm::mat4& dest) const
{
  log_trace("mgCCamera::GetCameraMatrix({})", fmt::ptr(&dest));

  // FIXME: Check if this is correct
  dest = glm::lookAt(
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