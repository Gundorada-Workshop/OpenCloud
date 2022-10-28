#pragma once

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
  int GetRX();

  // 0014af90
  int GetRY();

  // 0014afa0
  int GetLX();

  // 0014afb0
  int GetLY();

  // 0014afc0
  int GetRX2();

  // 0014afd0
  void CancelAutoRepeat();

  // 0014b040
  void CancelAutoRepeat2();

  // 0014b0b0
  void SetAutoRepeat(int, int, int);

  // 0014b130
  void SetAutoRepeat2(int, int, int);

  // 0014b1c0
  void KeyLock(int val);

  // 0014b1d0
  void KeyLock2(int val);

  // 0014b1e0
  void DebugKeyLock(int val);

  // 0014b1f0
  unsigned int GetPadOn();

  // 0014b220
  unsigned int GetPadDown();

  // 0014b250
  unsigned int GetPadUp();

  // 0014b280
  float GetRXf();

  // 0014b2c0
  float GetRYf();

  // 0014b300
  float GetLXf();

  // 0014b340
  float GetLYf();

  // 0014b380
  float GetRXf2();

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
  void MenuModeOn(int);

  // 0014b520
  void MenuModeOff();

  // 0014b530
  void SetVibration(int, int, int);

  // 0014b590
  void VibrationEnable(int);

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
