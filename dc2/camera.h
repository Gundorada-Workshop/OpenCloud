#pragma once
#include <glm/glm.hpp>

#include "common/debug.h"
#include "common/types.h"

#include "dc2/collision.h"
#include "dc2/gamepad.h"
#include "dc2/mg_camera.h"

struct CameraCtrlParam
{
public:
  // 0
  float m_unk_field_0;
  // 4
  float m_unk_field_4;
  // 8
  float m_unk_field_8;
  // C
  float m_unk_field_C;
  // 10
  float m_unk_field_10;
  // 14
  float m_unk_field_14;
  // 18
  float m_unk_field_18;
  // 1C
  float m_unk_field_1C;
  // 20
  float m_unk_field_20;
  // 24
  float m_unk_field_24;
  // 28
  _DWORD m_unk_field_28{};
  // SIZE 0x2C
};

class CCameraControl : mgCCameraFollow
{
private:
  struct Control
  {
  public:
    // 0
    float x;
    // 4
    float y;
    // 8
    u32 m_unk_field_8;
  };
  // 002EC010
  inline void InitStatus()
  {
    m_rot_camera_cancel = 0;
    m_unk_field_C8 = false;
    m_unk_field_CC = 0;
    m_unk_field_E0 = glm::vec3(0.0f);
  }
  // 002EC1F0
  void MoveCamera(const Control& control, const glm::vec3& v, CCPoly* c_poly, usize i);
  // 002EC910
  void CheckCollision(CCPoly* c_poly, usize i);
  // 002ECB60
  void AutoMove(CCPoly* c_poly, usize i);
  // 002ECE70
  void CheckGround(CCPoly* c_poly, usize i);

  // C0
  bool m_controlling;
  // C4
  u32 m_rot_camera_cancel;
  // C8
  bool m_unk_field_C8;
  // CC
  float m_unk_field_CC;

  // E0
  glm::vec3 m_unk_field_E0;
  // F0
  usize m_n_active_param;
  // F4
  std::array<CameraCtrlParam, 4> m_camera_params{};
  // 1A4
  CameraCtrlParam m_active_param;

  // 1D0
  glm::vec3 m_unk_field_1D0;
  // 1E0
  bool m_unk_field_1E0;

public:
  // 002EBE80
  CCameraControl();

  // 002EC0D0
  virtual void Stay();

  // 002EC110
  virtual void Step(int steps = 1);

  // 002ED250
  virtual glm::mat4 GetCameraMatrix();

  // 002ED3D0
  virtual int Iam();


  // 002EBFA0
  inline CameraCtrlParam& GetActiveParam()
  {
    return m_camera_params[m_n_active_param];
  }

  // 002EBFD0
  inline void SetRotCameraCancel(u32 value)
  {
    m_rot_camera_cancel = value;
  }

  // 002EBFE0
  inline void BitSetRotCameraCancel(u32 value)
  {
    m_rot_camera_cancel |= value;
  }

  // 002EBFF0
  inline void BitResetRotCameraCancel(u32 value)
  {
    m_rot_camera_cancel &= (~value);
  }

  // 002EC030
  void ControlOn();

  // 002EC0C0
  inline void ControlOff()
  {
    m_controlling = false;
  }

  // 002EC370
  void MoveCamera(const CPadControl* pad_control, const glm::vec3& v, CCPoly* c_poly, usize i);

  // 002EC710
  void Rotate(float delta);

  // 002EC790
  void SetRotate(float rot);

  // 002EC830
  void SetHeight(float height);

  // 002EC890
  inline void RotBack(float f)
  {
    m_unk_field_C8 = true;
    m_unk_field_CC = f;
  }

  // 002EC8A0
  inline void CancelRotBack()
  {
    m_unk_field_C8 = false;
  }

  // 002EC8B0
  inline void SetCheckRef(const glm::vec3& ref)
  {
    m_unk_field_1E0 = true;
    m_unk_field_1D0 = ref;
  }

  // 002EC8D0
  inline void SetCheckRef(float x, float y, float z)
  {
    SetCheckRef(glm::vec3(x, y, z));
  }

  // 002ED320
  void CopyParam(CCameraControl& other);
};