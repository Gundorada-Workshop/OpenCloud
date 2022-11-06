#pragma once
#include "common/debug.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// ~ 00131110 - 00131B60

class mgCCamera
{
public:
  // 00131630
  // speed is how long it takes the camera to reach its target, in frames (30fps).
  mgCCamera(float speed);
  // 001CE150
  // should be handled by compiler
  //mgCCamera(mgCCamera& other);
  // 00131110
  virtual void Step(int steps = 1);
  // 00131B30
  virtual void Suspend();
  // 00131B40
  virtual void Resume();
  // 001313A0
  virtual void Stay();
  // 001314D0
  virtual void GetCameraMatrix(glm::mat4& dest) const;
  // 00131B50
  virtual int Iam() const;

  // 001313E0
  inline void SetPos(float x, float y, float z);
  // 00131410
  inline void SetPos(const glm::vec3& pos);
  // 00131420
  inline void SetNextPos(float x, float y, float z);
  // 00131430
  inline void SetNextPos(const glm::vec3& next_pos);
  // 00131440
  inline void SetRef(float h, float p, float r);
  // 00131460
  inline void SetRef(const glm::vec3& ref);
  // 00131470
  inline void SetNextRef(float h, float p, float r);
  // 00131480
  inline void SetNextRef(const glm::vec3& next_ref);
  // 00131490
  inline void GetDir(glm::vec3& dest) const;
  // 001315C0
  inline void SetRoll(float roll);
  // 001315D0
  inline void GetPos(glm::vec3& dest) const;
  // 001315E0
  inline void GetRef(glm::vec3& dest) const;
  // 001315F0
  inline void GetNextPos(glm::vec3& dest) const;
  // 00131600
  inline void GetNextRef(glm::vec3& dest) const;
  // 00131610
  inline float GetAngleH() const;
  // 00131620
  inline float GetAngleV() const;

  static bool StopCamera;

  // 0
  glm::vec3 m_position;
  // 10
  glm::vec3 m_reference;
  // 20
  glm::vec3 m_next_position;
  // 30
  glm::vec3 m_next_reference;
  // 40
  float m_roll;
  // 44
  _DWORD m_unk_field_44;
  // 48
  float m_position_speed;
  // 4C
  float m_rotation_speed;
  // 50
  float m_angleH;
  // 54
  float m_angleV;
  // 58
  float m_step_epsilon;
  // 5C
  bool m_stopped;
};

class mgCCameraFollow : public mgCCamera
{
public:

};