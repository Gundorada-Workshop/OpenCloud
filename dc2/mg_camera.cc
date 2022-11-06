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

// 001313E0
inline void mgCCamera::SetPos(float x, float y, float z)
{
  log_trace("mgCCamera::{}({}, {}, {})", __func__, x, y, z);

  SetPos(glm::vec3(x, y, z));
}

// 00131410
inline void mgCCamera::SetPos(const glm::vec3& pos)
{
  log_trace("mgCCamera::{}({})", __func__, fmt::ptr(&pos));

  m_position = pos;
}

// 00131420
inline void mgCCamera::SetNextPos(float x, float y, float z)
{
  log_trace("mgCCamera::{}({}, {}, {})", __func__, x, y, z);

  SetNextPos(glm::vec3(x, y, z));
}

// 00131430
inline void mgCCamera::SetNextPos(const glm::vec3& next_pos)
{
  log_trace("mgCCamera::{}({})", __func__, fmt::ptr(&next_pos));

  m_next_position = next_pos;
}

// 00131440
inline void mgCCamera::SetRef(float h, float p, float r)
{
  log_trace("mgCCamera::{}({}, {}, {})", __func__, h, p, r);

  SetRef(glm::vec3(h, p, r));
}

// 00131460
inline void mgCCamera::SetRef(const glm::vec3& ref)
{
  log_trace("mgCCamera::{}({})", __func__, fmt::ptr(&ref));

  m_reference = ref;
}

// 00131470
inline void mgCCamera::SetNextRef(float h, float p, float r)
{
  log_trace("mgCCamera::{}({}, {}, {})", __func__, h, p, r);

  SetNextRef(glm::vec3(h, p, r));
}

// 00131480
inline void mgCCamera::SetNextRef(const glm::vec3& next_ref)
{
  log_trace("mgCCamera::{}({})", __func__, fmt::ptr(&next_ref));

  m_reference = next_ref;
}

// 00131490
inline void mgCCamera::GetDir(glm::vec3& dest) const
{
  log_trace("mgCCamera::GetDir({})", fmt::ptr(&dest));

  dest = m_reference - m_position;
}

// 001315C0
inline void mgCCamera::SetRoll(float roll)
{
  log_trace("mgCCamera::{}({})", __func__, roll);

  m_roll = roll;
}

// 001315D0
inline void mgCCamera::GetPos(glm::vec3& dest) const
{
  log_trace("mgCCamera::{}({})", __func__, fmt::ptr(&dest));

  dest = m_position;
}

// 001315E0
inline void mgCCamera::GetRef(glm::vec3& dest) const
{
  log_trace("mgCCamera::{}({})", __func__, fmt::ptr(&dest));

  dest = m_reference;
}

// 001315F0
inline void mgCCamera::GetNextPos(glm::vec3& dest) const
{
  log_trace("mgCCamera::{}({})", __func__, fmt::ptr(&dest));

  dest = m_next_position;
}

// 00131600
inline void mgCCamera::GetNextRef(glm::vec3& dest) const
{
  log_trace("mgCCamera::{}({})", __func__, fmt::ptr(&dest));

  dest = m_next_reference;
}

// 00131610
inline float mgCCamera::GetAngleH() const
{
  log_trace("mgCCamera::{}()", __func__);

  return m_angleH;
}

// 00131620
inline float mgCCamera::GetAngleV() const
{
  log_trace("mgCCamera::{}()", __func__);

  return m_angleV;
}