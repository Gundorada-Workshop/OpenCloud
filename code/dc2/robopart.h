#pragma once
#include <array>

#include "common/debug.h"

// ~ 001B5FD0 - 001BAA30

// TODO THIS FILE
class CRocketLauncher {};
class CRocketLauncherMan {};
class CMachineGun {};
class CLaserGun {};
class CLaserGunMan {};
class CPullItem {};
class CPullItemManager {};
class CRoboVoiceSystem {};

struct ROBO_INFO_DATA
{
  // 0
  std::array<char, 0x10>* m_unk_field_0;
  // 4
  std::array<char, 0x10>* m_unk_field_4;
  // 8
  std::array<char, 0x10>* m_unk_field_8;
  // C
  std::array<char, 0x40>* m_unk_field_C;
  // 10
  std::array<char, 0x10>* m_unk_field_10;
  // 14
  char* m_unk_field_14;
  // 18
  unkptr m_unk_field_18;
  // 1C
  // FIXME: enum type?
  unk32 m_robo_info_type1;
  // 20
  // FIXME: enum type?
  unk32 m_robo_info_type2;
};