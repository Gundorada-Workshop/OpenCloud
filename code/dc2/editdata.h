#pragma once
#include <array>

#include "common/debug.h"
#include "common/types.h"

struct EditAnalyzeDataSrc
{
  // 0
  unk32 m_unk_field_0{ 0 };

  // 4
  unk16 m_unk_field_4{ 0 };

  // 6
  unk16 m_unk_field_6{ 0 };

  // 8
  s8 m_unk_field_8{ -1 };

  // 9
  s8 m_unk_field_9{ -1 };

  // A
  s8 m_unk_field_A{ -1 };

  // B
  s8 m_unk_field_B{ -1 };

  // C
  s8 m_unk_field_C{ -1 };

  // D
  s8 m_unk_field_D{ -1 };

  // E
  s8 m_unk_field_E{ -1 };

  // F
  s8 m_unk_field_F{ -1 };

  // 10
  s32 m_unk_field_10{ -1 };

  // 14
  unk32 m_unk_field_14{ 0 };

  // 18
  unk32 m_unk_field_18{ 0 };
};

struct EditAnalyzeSrc
{
  // 0
  std::array<unk32, 0x40> m_unk_field_0{ };

  // 100
  std::array<unk16, 0x40> m_unk_field_100{ };

  // 180
  std::array<EditAnalyzeDataSrc, 0x10> m_unk_field_180{ };
};

class CEditData
{
public:
  // 00194550
  CEditData();

  // 002a89c0
  void Initialize();

  // 002a8a10
  void InitPlaceData();

  // 0
  unk m_unk_field_0{ 0 };

  // 4
  unk m_unk_field_4{ 0 };

  // 8
  usize m_n_unk_field_C{ 0 };

  // C
  std::array<unks<0x24>, 300> m_unk_field_C{ 0 };

  // 2A3C
  usize m_n_unk_field_2A40{ 0 };

  // 2A40
  std::array<unks<0x10>, 32> m_unk_field_2A40{ 0 };

  // 2C40
  std::array<s16, 0x800> m_unk_field_2C40{ 0 };

  // 4C40
  std::array<u8, 0x400> m_unk_field_4C40{ 0 };

  // 5040
  unks<0xD0> m_unk_field_5040 { 0 };
};