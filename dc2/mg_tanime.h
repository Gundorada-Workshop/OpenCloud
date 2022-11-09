#pragma once
#include <array>
#include "common/debug.h"
#include "sce_temp.h"

// ~ 00139F10 - 001411E0

namespace mg_tanime
{
  // 00373410
  void SInit();
}

class mgCTextureAnime
{
  // 124
  std::array<char*, 0x18> m_group_name;
};

class mgCTexAnimeData 
{
public:
  // 0013BCD0
  mgCTexAnimeData();
  // 0013BD00
  void Initialize();

  // 0
  s8 m_unk_field_0;
  // 1
  s8 m_unk_field_1;
  // 2
  s8 m_unk_field_2;
  // 3
  s8 m_unk_field_3;
  // 4
  _UNKNOWN m_unk_field_4;
  // 8
  _UNKNOWN m_unk_field_8;
  // C
  s16 m_unk_field_C;
  // E
  s16 m_unk_field_E;
  // 10
  s16 m_unk_field_10;
  // 12
  s16 m_unk_field_12;
  // 14
  s16 m_unk_field_14;
  // 16
  s16 m_unk_field_16;
  // 18
  s16 m_unk_field_18;
  // 1C
  s16 m_unk_field_1C;
  // 1E
  s16 m_unk_field_1E;
  // 20
  s16 m_unk_field_20;
  // 22
  s16 m_unk_field_22;
  // 24
  s16 m_unk_field_24;
  // 26
  s16 m_unk_field_26;
  // 28
  s16 m_unk_field_28;
  // 2A
  s16 m_unk_field_2A;
  // 2C
  s8 m_unk_field_2C;
  // 2D
  s8 m_unk_field_2D;
  // 2E
  s8 m_unk_field_2E;
  // 2F
  s8 m_unk_field_2F;
  // 30
  s8 m_unk_field_30;
  // 31
  s8 m_unk_field_31;
  // 32
  s8 m_unk_field_32;
  // 33
  s8 m_unk_field_33;
};