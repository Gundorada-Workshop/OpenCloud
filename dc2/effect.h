#pragma once
#include <array>

#include "common/debug.h"
#include "common/types.h"

#include "dc2/script_interpreter.h"
#include "dc2/mg_lib.h"

// ~ 0017C240 - 00185EF0

// TODO THIS FILE
class COutLineDraw {};
class CEffectList {};
class CEffectCtrl {};
class CWater {};
class CWaterFrame {};

class CEffect
{
public:

};

class CEffectManager
{
public:
  void GetBufferNums(const char* script, int script_size, int* unk, int* unk2);
  void GetEffectNums(int unk0, int unk2);

public:
  // 0x34
  int count{ };
  // 0x220
  int alpha_blend{ };
  // 0x224
  int alpha_type{ };
  // 0x228
  int alpha{ };
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
  std::array<_UNKNOWNSTRUCT(0x20), 20> m_unk_field_70;
};

class CThunderEffect
{
public:
  // 00184820
  void Initialize();

  // 0
  _UNKNOWN m_unk_field_0;

  // 90
  _UNKNOWN m_unk_field_90;
  // 94
  _UNKNOWN m_unk_field_94;
  // 98
  _UNKNOWN m_unk_field_98;
};

class CHitEffectImage
{
public:

  // 50
  mgRect<int> m_unk_field_50{ 0, 0, 0, 0 };
};