#pragma once
#include <array>
#include "common/debug.h"
#include "common/types.h"
#include "mgCTexture.h"

class CEffect
{
public:

};

class CFadeInOut
{
public:
  // 0017D750
  void Initialize();

  // 0
  float m_unk_field_0;
  // 4
  float m_unk_field_4;
  // 8
  float m_unk_field_8;
  // C
  float m_unk_field_C;
  // 10
  s32 m_unk_field_10;
  // 14
  bool m_unk_field_14;
  // 18
  float m_unk_field_18;
  // 1C
  _UNKNOWN m_unk_field_1C;
  // 20
  bool m_unk_field_20;
  // 24
  float m_unk_field_24;
  // 28
  mgCTexture* m_unk_field_28;
  // 2C
  _UNKNOWN m_unk_field_2C;
};

class CFireRaster : public mgCTexture
{
public:
  // 001847C0
  void Initialize();

  // 70
  // FIXME: Unknown inner type (or even if it is an array?) (size 0x20)
  std::array<std::array<char, 32>, 20> m_unk_field_70;
};