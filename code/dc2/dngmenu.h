#pragma once
#include "common/debug.h"
#include "common/types.h"
#include "common/rectangle.h"

#include "dc2/mg_lib.h"

// ~001EA760 - 001F2510

// TODO THIS FILE
class CMenuTreeMap;

class CDngFreeMap
{
private:
  // 001EA830
  void InitializeTexture();

public:
  // 001EA760
  CDngFreeMap();

  // 0
  unk32 m_unk_field_0;

  // 4
  unk32 m_unk_field_4;

  // 8
  bool m_unk_field_8;

  // 9
  unk8 m_unk_field_9;

  // A
  unk16 m_unk_field_A;

  // C
  unk16 m_unk_field_C;

  // 10
  unk32 m_unk_field_10;

  // 20
  rect m_unk_field_20;

  // 30
  unk32 m_unk_field_30;

  // 40
  std::array<rect, 8> m_unk_field_40;

  // C0
  unk16 m_unk_field_C0;

  // C2
  unk16 m_unk_field_C2;

  // C4
  unk32 m_unk_field_C4;

  // C8
  unk32 m_unk_field_C8;

  // CC
  unk32 m_unk_field_CC;

  // D0
  s16 m_unk_field_D0;

  // D4
  unk32 m_unk_field_D4;

  // D8
  unk32 m_unk_field_D8;

  // DC
  unk32 m_unk_field_DC;

  // E0
  unk32 m_unk_field_E0;

  // E4
  unk32 m_unk_field_E4;

  // E8
  unk32 m_unk_field_E8;

  // EC
  unk32 m_unk_field_EC;

  // F0
  f32 m_unk_field_F0;

  // F4
  s32 m_unk_field_F4;

  // F8
  unk32 m_unk_field_F8;

  // FC
  s32 m_unk_field_FC;

  // 100
  unk32 m_unk_field_100;

  // 104
  unk32 m_unk_field_104;

  // 108
  f32 m_unk_field_108;

  // 10C
  f32 m_unk_field_10C;
};