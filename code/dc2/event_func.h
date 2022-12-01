#pragma once
#include <array>

#include "common/debug.h"
#include "common/types.h"

#include "dc2/event.h"
#include "dc2/mg/mg_lib.h"

// ~ 00255B80 - 0027DD00

struct SPLINE_KEY
{
public:
  // 00255B80
  void Initialize();

  // 0
  _DWORD m_unk_field_0;
  // 4
  _DWORD m_unk_field_4;
  // 8
  _DWORD m_unk_field_8;
  // C
  _DWORD m_unk_field_C;
  // 10
  _DWORD m_unk_field_10;
  // 14
  _DWORD m_unk_field_14;
  // 18
  _DWORD m_unk_field_18;
  // 1C
  _DWORD m_unk_field_1C;
  // 20
  _DWORD m_unk_field_20;
  // 24
  _DWORD m_unk_field_24;
  // 28
  _DWORD m_unk_field_28;
  // 2C
  _DWORD m_unk_field_2C;
  // 30
  _DWORD m_unk_field_30;
  // 34
  _DWORD m_unk_field_34;
};

class C3DSpline
{
public:
  // 00255BC0
  C3DSpline();
  // 00255BF0
  void Initialize();

  // 0
  std::array<SPLINE_KEY, 0x10> m_spline_keys;
  // 380
  _DWORD m_unk_field_380;
  // 384
  _DWORD m_unk_field_384;
  // 388
  _DWORD m_unk_field_388;
  // 398
  _DWORD m_unk_field_398;
};

class CCameraPas
{
public:
  // 00256380
  CCameraPas();
  // 00256710
  void Initialize();

  // 0
  std::array<vec4, 0x10> m_unk_field_0;
  // 100
  std::array<vec4, 0x10> m_unk_field_100;
  // 200
  _DWORD m_unk_field_200;
  // 204
  _DWORD m_unk_field_204;
  // 208
  C3DSpline m_unk_field_208{};
  // 5A4
  C3DSpline m_unk_field_5A4{};
  // 940
  _DWORD m_unk_field_940;
};

struct _SEN_CMR_SEQ
{
  // 00259100
  void Initialize();

  // 0
  _DWORD m_unk_field_0;
  // 10
  vec4 m_unk_field_10;
  // 20
  vec4 m_unk_field_20;
  // 30
  _DWORD m_unk_field_30;
  // 34
  _DWORD m_unk_field_34;
  // 38
  _DWORD m_unk_field_38;
  // 3C
  std::array<char, 0x20> m_unk_field_3C;
  // 5C
  _DWORD m_unk_field_5C;
};

class CSceneCmrSeq
{
private:
  // 002591A0
  void ZeroInitialize();
  // 00259230
  void Clear();
public:
  // 00259160
  CSceneCmrSeq();
  // 002591E0
  void Initialize(_SEN_CMR_SEQ* seq, usize length);

  // 0
  // Scene Camera Sequence?
  _SEN_CMR_SEQ* m_sequences;
  // 4
  usize m_n_sequences;
  // 8
  _DWORD m_unk_field_8;
  // C
  _DWORD m_unk_field_C;
  // 10
  _DWORD m_unk_field_10;
  // 14
  _DWORD m_unk_field_14;
  // 18
  _DWORD m_unk_field_18;
  // 1C
  _DWORD m_unk_field_1C;
  // 20
  _DWORD m_unk_field_20;
  // 24
  _DWORD m_unk_field_24;
  // 28
  _DWORD m_unk_field_28;
  // 2C
  _DWORD m_unk_field_2C;
  // 30
  _DWORD m_unk_field_30;
  // 34
  _DWORD m_unk_field_34;
  // 38
  _DWORD m_unk_field_38;
  // 3C
  _DWORD m_unk_field_3C;
  // 40
  _DWORD m_unk_field_40;
  // 44
  _DWORD m_unk_field_44;
  // 48
  _DWORD m_unk_field_48;
  // 50
  vec4 m_unk_field_50;
  // 60
  vec4 m_unk_field_60;
  // 70
  _DWORD m_unk_field_70;
  // 74
  _DWORD m_unk_field_74;
  // 78
  _DWORD m_unk_field_78;
  // 7C
  _DWORD m_unk_field_7C;
  // 80
  s32 m_unk_field_80;
  // 84
  _DWORD m_unk_field_84;
  // 90
  vec4 m_unk_field_90;
  // A0
  _DWORD m_unk_field_A0;
  // A4
  _DWORD m_unk_field_A4;
  // A8
  _DWORD m_unk_field_A8;
  // AC
  std::array<char, 0x20> m_unk_field_AC;
  // D0
  vec4 m_unk_field_D0;
  // E0
  vec4 m_unk_field_E0;
  // F0
  _DWORD m_unk_field_F0;

  // ?

  // F8
  _DWORD m_unk_field_F8;
  // FC
  _DWORD m_unk_field_FC;
  // 100
  vec4 m_unk_field_100;
  // 110
  vec4 m_unk_field_110;
  // 120
  vec4 m_unk_field_120;
  // 130
  vec4 m_unk_field_130;
  // 140
  _DWORD m_unk_field_140;
  // 150
  vec4 m_unk_field_150;
  // 160
  vec4 m_unk_field_160;
  // 170
  vec4 m_unk_field_170;
  // 180
  _DWORD m_unk_field_180;
  // 190
  vec4 m_unk_field_190;
  // 1A0
  vec4 m_unk_field_1A0;
  // 1B0
  vec4 m_unk_field_1B0;
  // 1C0
  CCameraPas m_unk_field_1C0{};
};

class CCharaPas
{
public:
  // 00256B20
  CCharaPas();
  // 00256B50
  void Initialize();

  // 0
  std::array<vec4, 16> m_unk_field_0;
  // 100
  _DWORD m_unk_field_100;
  // 104
  _DWORD m_unk_field_104;
  // 108
  C3DSpline m_unk_field_108{};
  // 4A4
  _DWORD m_unk_field_4A4;
  // 4A8
  _DWORD m_unk_field_4A8;
};

struct _SEN_OBJ_SEQ
{
public:
  // 0025C170
  void Initialize();

  // 0
  _DWORD m_unk_field_0;
  // 10
  vec4 m_unk_field_10;
  // 20
  _DWORD m_unk_field_20;
  // 24
  _DWORD m_unk_field_24;
  // 28
  _DWORD m_unk_field_28;
  // 2C
  std::array<char, 0x20> m_unk_field_2C;
  // 4C
  _DWORD m_unk_field_4C;
};

class CSceneObjSeq
{
private:
  // 0025C200
  void ZeroInitialize();
  // 0025C2A0
  void Clear();
public:
  // 0025C1C0
  CSceneObjSeq();
  // 0025C220
  void Initialize(_SEN_OBJ_SEQ* seq, usize length);

  // 0
  _SEN_OBJ_SEQ* m_sequences;
  // 4
  usize m_n_sequences;
  // 8
  _DWORD m_unk_field_8;
  // C
  _DWORD m_unk_field_C;
  // 10
  _DWORD m_unk_field_10;
  // 14
  _DWORD m_unk_field_14;
  // 18
  _DWORD m_unk_field_18;
  // 1C
  _DWORD m_unk_field_1C;
  // 20
  _DWORD m_unk_field_20;
  // 24
  _DWORD m_unk_field_24;
  // 28
  _DWORD m_unk_field_28;
  // 2C
  _DWORD m_unk_field_2C;
  // 30
  _DWORD m_unk_field_30;
  // 34
  _DWORD m_unk_field_34;
  // 38
  _DWORD m_unk_field_38;
  // 3C
  _DWORD m_unk_field_3C;
  // 40
  _DWORD m_unk_field_40;
  // 44
  _DWORD m_unk_field_44;
  // 48
  _DWORD m_unk_field_48;
  // 4C
  _DWORD m_unk_field_4C;
  // 50
  _DWORD m_unk_field_50;
  // 54
  _DWORD m_unk_field_54;
  // 58
  _DWORD m_unk_field_58;

  // ?

  // 64
  s32 m_unk_field_64;
  // 70
  vec4 m_unk_field_70;
  // 80
  vec4 m_unk_field_80;

  // ?

  // B0
  vec4 m_unk_field_B0;
  // C0
  vec4 m_unk_field_C0;
  // D0
  vec4 m_unk_field_D0;
  // E0
  vec4 m_unk_field_E0;
  // F0
  _DWORD m_unk_field_F0;
  // F4
  _DWORD m_unk_field_F4;
  // 120
  vec4 m_unk_field_120;

  // ?

  CCharaPas m_unk_field_140;
};

class CEoh
{
  // NOTE: Event Obj Handle

public:
  // 0
  s32 m_unk_field_0{ -1 };
  // 4
  s32 m_unk_field_4{ -1 };
  // 8
  bool m_unk_field_8{ true };
  // C
  _DWORD m_unk_field_C{ 0 };
};

class CEohMother
{
  // NOTE: Event Obj Handle Mother (Manager?)

public:
  std::array<CEoh, 0x20> m_handles{};
};

class CRaster
{
public:
  // 0
  _DWORD m_unk_field_0{ 0 };
  // 4
  _DWORD m_unk_field_4{ 0 };
  // 8
  _DWORD m_unk_field_8{ 0 };
  // C
  _DWORD m_unk_field_C{ 0 };
  // 10
  _DWORD m_unk_field_10{ 0 };
  // 14
  _DWORD m_unk_field_14{ 0 };
  // 18
  _DWORD m_unk_field_18{ 0 };
  // 1C
  _DWORD m_unk_field_1C{ 0 };
  // 20
  _DWORD m_unk_field_20{ 0 };
  // 24
  s32 m_unk_field_24{ -1 };
  // 28
  _DWORD m_unk_field_28{ 0 };
};

class CScreenEffect : CRaster
{
public:
  // 2C
  _DWORD m_unk_field_2C{ 0 };
  // 30
  _DWORD m_unk_field_30{ 0 };
  // 34
  _DWORD m_unk_field_34{ 0 };
  // 38
  _DWORD m_unk_field_38{ 0 };
  // 3C
  _DWORD m_unk_field_3C{ 0 };
  // 40
  _DWORD m_unk_field_40{ 0 };
  // 44
  _DWORD m_unk_field_44{ 0 };
  // 48
  _DWORD m_unk_field_48{ 0 };
};


class CRipple
{
public:
  // 0
  _DWORD m_unk_field_0{ 0 };
  // 10
  vec4 m_unk_field_10{ 0.0f, 0.0f, 0.0f, 1.0f };
  // 20
  _DWORD m_unk_field_20{ 0 };
  // 24
  _DWORD m_unk_field_24{ 0 };
  // 28
  _DWORD m_unk_field_28{ 0 };
};

class CParticle
{
public:
  // 0
  _DWORD m_unk_field_0{ 0 };
  // 10
  vec4 m_unk_field_10{ 0.0f, 0.0f, 0.0f, 1.0f };
  // 20
  vec4 m_unk_field_20{ 0.0f, 0.0f, 0.0f, 1.0f };
  // 30
  vec4 m_unk_field_30{ 0.0f, 0.0f, 0.0f, 1.0f };
  // 40
  _DWORD m_unk_field_40{ 0 };
};

class CRainDrop
{
public:
  // 00282100
  CRainDrop();

  // 0
  _DWORD m_unk_field_0{ 0 };
  // 4
  _DWORD m_unk_field_4{ 0 };
  // 10
  std::array<vec4, 8> m_unk_field_10{};
  // 90
  vec4 m_unk_field_90{ 0.0f, 0.0f, 0.0f, 1.0f };
  // A0, A4, A8, AC
  glm::u8vec4 m_color{ 128.0f, 128.0f, 128.0f, 128.0f };
};

class CRain
{
public:
  // 0
  _DWORD m_unk_field_0{ 0 };
  // 4
  _DWORD m_unk_field_4{ 0 };
  // 10
  std::array<CRainDrop, 100> m_unk_field_10{};
  // 44D0
  std::array<CRainDrop, 50> m_unk_field_44D0{};
  // 6730
  std::array<CParticle, 100> m_particles{};
  // 8670
  std::array<CRipple, 200> m_ripples{};
};

class CMarker
{
  // Dummy class? I think we can probably get rid of this
private:
  // 00290210
  void Set(int i);

  // 0
  s32 m_cnt{ 0 };
public:
  // 00290210
  void Draw();
};

class CEventSprite
{
public:
  // 0
  _DWORD m_unk_field_0{ 0 };
  // 4
  _DWORD m_unk_field_4{ 0 };
  // 8
  std::array<char, 0x40> m_name{ 0 };
  // 48
  _UNKNOWNSTRUCT(0x10) m_unk_field_48{ 0 };
  // 58
  _UNKNOWNSTRUCT(0x10) m_unk_field_58{ 0 };
  // 68
  _UNKNOWNSTRUCT(0x10) m_unk_field_68{ 0 };
  // 78
  _UNKNOWNSTRUCT(0x10) m_unk_field_78{ 0 };

  // SIZE 0x88
};

class CEventSpriteMother
{
public:
  // 00290A00
  void Initialize();

  // 0
  std::array<CEventSprite, 8> m_sprites{ 0 };
};

class CEventSprite2
{
public:
  // 00290A60
  CEventSprite2();
  // 00290A90
  void Initialize();

  // 0
  _DWORD m_unk_field_0{ 0 };
  // 4
  s32 m_unk_field_4{ -1 };
  // 8
  s32 m_unk_field_8{ -1 };
  // C
  _UNKNOWNSTRUCT(0x20) m_unk_field_C { 0 };
  // 2C
  bool m_unk_field_2C{ true };
  // 30
  vec4 m_unk_field_30{ 0.0f };
  // 40
  vec4 m_unk_field_40{ 128.0f };
  // 50
  _DWORD m_unk_field_50{ 0 };
  // 54
  _DWORD m_unk_field_54{ 0 };
  // 58
  _DWORD m_unk_field_58{ 0 };
  // 5C
  _DWORD m_unk_field_5C{ 0 };
  // 60
  _DWORD m_unk_field_60{ 0 };
  // 64
  _DWORD m_unk_field_64{ 0 };
  // 68
  _DWORD m_unk_field_68{ 0 };
  // 6C
  f32 m_unk_field_6C{ 1.0f };
  // 70
  f32 m_unk_field_70{ 1.0f };
};

class CEventScriptArg
{
public:
  // 0
  _DWORD m_unk_field_0{ 0 };
  // 4
  _DWORD m_unk_field_4{ 0 };
  // 8
  _DWORD m_unk_field_8{ 0 };
  // C
  _DWORD m_unk_field_C{ 0 };
};