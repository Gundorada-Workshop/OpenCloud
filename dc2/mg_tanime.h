#pragma once
#include <array>
#include "common/debug.h"
#include "sce_temp.h"

// ~ 00139F10 - 001411E0

class mgCTextureAnime
{
  // 124
  std::array<char*, 0x18> m_group_name;
};

class mgCTexAnimeData 
{
public:
  // 0
  s8 m_unk_field_0{ -1 };
  // 1
  _BYTE m_unk_field_1{ 0 };
  // 2
  s8 m_unk_field_2{ -1 };
  // 3
  _BYTE m_unk_field_3{ 0 };
  // 4
  _UNKNOWN m_unk_field_4{ 0 };
  // 8
  _UNKNOWN m_unk_field_8{ 0 };
  // C
  _WORD m_unk_field_C{ 0 };
  // E
  _WORD m_unk_field_E{ 0 };
  // 10
  _WORD m_unk_field_10{ 0 };
  // 12
  _WORD m_unk_field_12{ 0 };
  // 14
  _WORD m_unk_field_14{ 0 };
  // 16
  _WORD m_unk_field_16{ 0 };
  // 18
  _WORD m_unk_field_18{ 0 };
  // 1C
  _WORD m_unk_field_1C{ 0 };
  // 1E
  _WORD m_unk_field_1E{ 0 };
  // 20
  _WORD m_unk_field_20{ 0 };
  // 22
  _WORD m_unk_field_22{ 0 };
  // 24
  _WORD m_unk_field_24{ 0 };
  // 26
  _WORD m_unk_field_26{ 0 };
  // 28
  _WORD m_unk_field_28{ 0 };
  // 2A
  _WORD m_unk_field_2A{ 4 };
  // 2C
  _BYTE m_unk_field_2C{ 1 };
  // 2D
  _BYTE m_unk_field_2D{ 4 };
  // 2E
  s8 m_unk_field_2E{ -1 };
  // 2F
  _BYTE m_unk_field_2F{ 0 };
  // 30
  u8 m_unk_field_30{ 0x80 };
  // 31
  u8 m_unk_field_31{ 0x80 };
  // 32
  u8 m_unk_field_32{ 0x80 };
  // 33
  u8 m_unk_field_33{ 0x80 };
};