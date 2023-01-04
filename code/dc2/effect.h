#pragma once
#include <array>

#include "common/debug.h"
#include "common/types.h"

#include "graph/rectangle.h"

#include "dc2/script_interpreter.h"
#include "dc2/mg/mg_lib.h"

// ~ 0017C240 - 00185EF0

// TODO THIS FILE
class COutLineDraw
{
};

class CEffectList
{
};

class CEffectCtrl
{
};

class CWater
{
};

class CWaterFrame
{
};

class CWaveTable
{
public:
  // 001A2110
  CWaveTable();

  // 0
  std::array<std::array<unk32, 24>, 24> m_unk_field_0;

  // 900
  std::array<std::array<unk32, 24>, 24> m_unk_field_900;

  // 1200
  unk32 m_unk_field_1200;

  // SIZE 0x1208 (vtable w/ (probably not called) destructor only @ 0x1204)
};

class CEffect
{
};

class CEffectManager
{
public:
  void GetBufferNums(const char* script, sint script_size, sint* unk, sint* unk2);

  void GetEffectNums(sint unk0, sint unk2);

public:
  // 0x34
  sint count{ };

  // 0x220
  sint alpha_blend{ };

  // 0x224
  sint alpha_type{ };

  // 0x228
  sint alpha{ };
};


class CFadeInOut
{
public:
  // 0
  f32 m_unk_field_0{};
  // 4
  f32 m_unk_field_4{};
  // 8
  f32 m_unk_field_8{};
  // C
  f32 m_unk_field_C{};
  // 10
  s32 m_unk_field_10{};
  // 14
  bool m_unk_field_14{};
  // 18
  f32 m_unk_field_18{};
  // 1C
  unk m_unk_field_1C{};
  // 20
  bool m_unk_field_20{};
  // 24
  f32 m_unk_field_24{};
  // 28
  mgCTexture* m_unk_field_28{ nullptr };
  // 2C
  bool m_motion_blur{};
};

class CFireRaster : public mgCTexture
{
public:
  // 001847C0
  void Initialize();

  // 70
  std::array<unks<0x20>, 20> m_unk_field_70;
};

class CThunderEffect
{
public:
  // 00184820
  void Initialize();

  // 0
  unk m_unk_field_0;

  // 90
  unk m_unk_field_90;
  // 94
  unk m_unk_field_94;
  // 98
  unk m_unk_field_98;
};

class CHitEffectImage
{
public:

  // 50
  graph::irect m_unk_field_50{ 0, 0, 0, 0 };
};