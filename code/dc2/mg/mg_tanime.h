#pragma once
#include <array>

#include "common/debug.h"

#include "dc2/sce_temp.h"

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
  unk8 m_unk_field_1{ 0 };
  // 2
  s8 m_unk_field_2{ -1 };
  // 3
  unk8 m_unk_field_3{ 0 };
  // 4
  unk m_unk_field_4{ 0 };
  // 8
  unk m_unk_field_8{ 0 };
  // C
  unk16 m_unk_field_C{ 0 };
  // E
  unk16 m_unk_field_E{ 0 };
  // 10
  unk16 m_unk_field_10{ 0 };
  // 12
  unk16 m_unk_field_12{ 0 };
  // 14
  unk16 m_unk_field_14{ 0 };
  // 16
  unk16 m_unk_field_16{ 0 };
  // 18
  unk16 m_unk_field_18{ 0 };
  // 1C
  unk16 m_unk_field_1C{ 0 };
  // 1E
  unk16 m_unk_field_1E{ 0 };
  // 20
  unk16 m_unk_field_20{ 0 };
  // 22
  unk16 m_unk_field_22{ 0 };
  // 24
  unk16 m_unk_field_24{ 0 };
  // 26
  unk16 m_unk_field_26{ 0 };
  // 28
  unk16 m_unk_field_28{ 0 };
  // 2A
  unk16 m_unk_field_2A{ 4 };
  // 2C
  unk8 m_unk_field_2C{ 1 };
  // 2D
  unk8 m_unk_field_2D{ 4 };
  // 2E
  s8 m_unk_field_2E{ -1 };
  // 2F
  unk8 m_unk_field_2F{ 0 };
  // 30
  u8 m_unk_field_30{ 0x80 };
  // 31
  u8 m_unk_field_31{ 0x80 };
  // 32
  u8 m_unk_field_32{ 0x80 };
  // 33
  u8 m_unk_field_33{ 0x80 };
};