#pragma once
#include "common/debug.h"
#include "common/types.h"

#include "dc2/collision.h"
#include "dc2/gamepad.h"
#include "dc2/mg/mg_camera.h"

constexpr sint CCameraControl_TypeID = 1000;

struct CameraCtrlParam
{
  // 0
  f32 m_unk_field_0{ 0.0f };

  // 4
  f32 m_unk_field_4{ 0.0f };

  // 8
  f32 m_unk_field_8{ 0.0f };

  // C
  f32 m_unk_field_C{ 0.0f };

  // 10
  f32 m_unk_field_10{ 0.0f };

  // 14
  f32 m_unk_field_14{ 0.0f };

  // 18
  f32 m_unk_field_18{ 0.0f };

  // 1C
  f32 m_unk_field_1C{ 0.0f };

  // 20
  f32 m_unk_field_20{ 0.0f };

  // 24
  f32 m_unk_field_24{ 0.0f };

  // 28
  unk32 m_unk_field_28{ 0 };
  // SIZE 0x2C
};

class CCameraControl : public mgCCameraFollow
{
public:
  // 002EBE80
  CCameraControl();

public:
  // 002EC0D0
  virtual void Stay();

  // 002EC110
  virtual void Step(MAYBE_UNUSED sint steps = 1);

  // 002ED250
  //virtual matrix4 GetCameraMatrix() const override;

  // 002ED3D0
  virtual sint Iam() const override;


  // 002EBFA0
  inline CameraCtrlParam* GetActiveParam()
  {
    return &m_camera_params[m_n_active_param];
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
  void MoveCamera(const CPadControl* pad_control, const vec3& v, CCPoly* c_poly, usize i);

  // 002EC710
  void Rotate(MAYBE_UNUSED f32 delta);

  // 002EC790
  void SetRotate(f32 rot);

  // 002EC830
  void SetHeight(f32 height);

  // 002EC890
  inline void RotBack(f32 f)
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
  //inline void SetCheckRef(const vec3& ref)
  //{
  //  m_unk_field_1E0 = true;
  //  m_unk_field_1D0 = ref;
  //}

  // 002EC8D0
  //inline void SetCheckRef(f32 x, f32 y, f32 z)
  //{
  //  SetCheckRef({ x, y, z });
  //}

  // 002ED320
  void CopyParam(CCameraControl& other);

private:
  struct Control
  {
    // 0
    f32 x{ 0.0f };

    // 4
    f32 y{ 0.0f };

    // 8
    u32 m_unk_field_8{ 0 };
  };

  // 002EC010
  // just initializes some members
  // not needed
  //inline void InitStatus();

  // 002EC1F0
  void MoveCamera(const Control& control, const vec3& v, CCPoly* c_poly, usize i);

  // 002EC910
  void CheckCollision(CCPoly* c_poly, usize i);

  // 002ECB60
  void AutoMove(CCPoly* c_poly, usize i);

  // 002ECE70
  void CheckGround(CCPoly* c_poly, usize i);

private:
  // C0
  bool m_controlling{ false };

  // C4
  u32 m_rot_camera_cancel{ 0 };

  // C8
  bool m_unk_field_C8{ false };

  // CC
  f32 m_unk_field_CC{ 0 };

  // E0
  vec3 m_unk_field_E0{ };

  // F0
  usize m_n_active_param{ 0 };

  // F4
  std::array<CameraCtrlParam, 4> m_camera_params{ };

  // 1A4
  // NOTE: This is not a pointer in the game!
  //
  // Shouldn't be an issue for the most part unless this ends up used
  // as a temporary object that might actually differ from the reference in
  // m_camera_params so keep an eye out for that
  CameraCtrlParam* m_active_param{ nullptr };

  // 1D0
  vec3 m_unk_field_1D0{ };

  // 1E0
  bool m_unk_field_1E0{ false };
};