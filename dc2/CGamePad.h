#pragma once
#include "Types.h"

// todo
struct PAD_STATUS;

class CGamePad
{
public:
  CGamePad();

  // 0014a830
  void WaitEnable();

  // 0014a8f0
  bool Connect();

  // 0014a930
  void Update();

  // 0014ae30
  void Step(int);

  // 0014af80
  sint GetRX();

  // 0014af90
  sint GetRY();

  // 0014afa0
  sint GetLX();

  // 0014afb0
  sint GetLY();

  // 0014afc0
  sint GetRX2();

  // 0014afd0
  void CancelAutoRepeat();

  // 0014b040
  void CancelAutoRepeat2();

  // 0014b0b0
  void SetAutoRepeat(sint, sint, sint);

  // 0014b130
  void SetAutoRepeat2(sint, sint, sint);

  // 0014b1c0
  void KeyLock(sint val);

  // 0014b1d0
  void KeyLock2(sint val);

  // 0014b1e0
  void DebugKeyLock(sint val);

  // 0014b1f0
  uint GetPadOn();

  // 0014b220
  uint GetPadDown();

  // 0014b250
  uint GetPadUp();

  // 0014b280
  f32 GetRXf();

  // 0014b2c0
  f32 GetRYf();

  // 0014b300
  f32 GetLXf();

  // 0014b340
  f32 GetLYf();

  // 0014b380
  f32 GetRXf2();

  // 0014b3c0
  bool On(int);

  // 0014b3f0
  bool On2(int);

  // 0014b430
  bool Down(int);

  // 0014b470
  bool Down2(int);

  // 0014b4c0
  bool Up(int);

  // 0014b500
  void AutoRepeatOff();

  // 0014b510
  void MenuModeOn(sint);

  // 0014b520
  void MenuModeOff();

  // 0014b530
  void SetVibration(sint, sint, sint);

  // 0014b590
  void VibrationEnable(sint);

  // 0014b5a0
  void StopVibration();

  // 0014b5f0
  void CaptureStart();

  // 0014b600
  void CaptureEnd();

  // 0014b610
  void CapturePlay();

  // 0014b620
  void Capture(PAD_STATUS* pad_status);

  // 0014b690
  void Play(PAD_STATUS* pad_status);

  // 0014b700
  void SaveCapture();

  // 0014b720
  void LoadCapture();
};
