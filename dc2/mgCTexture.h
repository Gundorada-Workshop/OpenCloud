#pragma once
#include <array>
#include "common/debug.h"
#include "common/types.h"

class mgCTexture
{
public:
  // 0012C480
  mgCTexture();
  // 0012C4B0
  void Initialize();

  // 0
  s16 m_unk_field_0;
  // 2
  s16 m_unk_field_2;
  // 4
  s16 m_unk_field_4;
  // 6
  s16 m_unk_field_6;
  // 8
  char m_unk_field_8[0x20];
  // 28
  _UNKNOWN m_unk_field_28;
  // 2C
  _UNKNOWN m_unk_field_2C;
  // 30
  _UNKNOWN m_unk_field_30;
  // ??
  // 38
  _UNKNOWN m_unk_field_38;
  // 3C
  u8 m_unk_field_3C;
  // 40
  s64 m_unk_field_40;
  // 48
  s64 m_unk_field_48;
  // 50
  std::array<float, 4> m_unk_field_50;
  // 60
  _UNKNOWN m_unk_field_60;
  // 64
  _UNKNOWN m_unk_field_64;
  // 68
  _UNKNOWN m_unk_field_68;
};
