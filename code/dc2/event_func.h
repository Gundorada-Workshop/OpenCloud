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
  unk32 m_unk_field_0;
  // 4
  unk32 m_unk_field_4;
  // 8
  unk32 m_unk_field_8;
  // C
  unk32 m_unk_field_C;
  // 10
  unk32 m_unk_field_10;
  // 14
  unk32 m_unk_field_14;
  // 18
  unk32 m_unk_field_18;
  // 1C
  unk32 m_unk_field_1C;
  // 20
  unk32 m_unk_field_20;
  // 24
  unk32 m_unk_field_24;
  // 28
  unk32 m_unk_field_28;
  // 2C
  unk32 m_unk_field_2C;
  // 30
  unk32 m_unk_field_30;
  // 34
  unk32 m_unk_field_34;
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
  unk32 m_unk_field_380;
  // 384
  unk32 m_unk_field_384;
  // 388
  unk32 m_unk_field_388;
  // 398
  unk32 m_unk_field_398;
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
  unk32 m_unk_field_200;
  // 204
  unk32 m_unk_field_204;
  // 208
  C3DSpline m_unk_field_208{};
  // 5A4
  C3DSpline m_unk_field_5A4{};
  // 940
  unk32 m_unk_field_940;
};

struct _SEN_CMR_SEQ
{
  // 00259100
  void Initialize();

  // 0
  unk32 m_unk_field_0;
  // 10
  vec4 m_unk_field_10;
  // 20
  vec4 m_unk_field_20;
  // 30
  unk32 m_unk_field_30;
  // 34
  unk32 m_unk_field_34;
  // 38
  unk32 m_unk_field_38;
  // 3C
  std::array<char, 0x20> m_unk_field_3C;
  // 5C
  unk32 m_unk_field_5C;
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
  unk32 m_unk_field_8;
  // C
  unk32 m_unk_field_C;
  // 10
  unk32 m_unk_field_10;
  // 14
  unk32 m_unk_field_14;
  // 18
  unk32 m_unk_field_18;
  // 1C
  unk32 m_unk_field_1C;
  // 20
  unk32 m_unk_field_20;
  // 24
  unk32 m_unk_field_24;
  // 28
  unk32 m_unk_field_28;
  // 2C
  unk32 m_unk_field_2C;
  // 30
  unk32 m_unk_field_30;
  // 34
  unk32 m_unk_field_34;
  // 38
  unk32 m_unk_field_38;
  // 3C
  unk32 m_unk_field_3C;
  // 40
  unk32 m_unk_field_40;
  // 44
  unk32 m_unk_field_44;
  // 48
  unk32 m_unk_field_48;
  // 50
  vec4 m_unk_field_50;
  // 60
  vec4 m_unk_field_60;
  // 70
  unk32 m_unk_field_70;
  // 74
  unk32 m_unk_field_74;
  // 78
  unk32 m_unk_field_78;
  // 7C
  unk32 m_unk_field_7C;
  // 80
  s32 m_unk_field_80;
  // 84
  unk32 m_unk_field_84;
  // 90
  vec4 m_unk_field_90;
  // A0
  unk32 m_unk_field_A0;
  // A4
  unk32 m_unk_field_A4;
  // A8
  unk32 m_unk_field_A8;
  // AC
  std::array<char, 0x20> m_unk_field_AC;
  // D0
  vec4 m_unk_field_D0;
  // E0
  vec4 m_unk_field_E0;
  // F0
  unk32 m_unk_field_F0;

  // ?

  // F8
  unk32 m_unk_field_F8;
  // FC
  unk32 m_unk_field_FC;
  // 100
  vec4 m_unk_field_100;
  // 110
  vec4 m_unk_field_110;
  // 120
  vec4 m_unk_field_120;
  // 130
  vec4 m_unk_field_130;
  // 140
  unk32 m_unk_field_140;
  // 150
  vec4 m_unk_field_150;
  // 160
  vec4 m_unk_field_160;
  // 170
  vec4 m_unk_field_170;
  // 180
  unk32 m_unk_field_180;
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
  unk32 m_unk_field_100;
  // 104
  unk32 m_unk_field_104;
  // 108
  C3DSpline m_unk_field_108{};
  // 4A4
  unk32 m_unk_field_4A4;
  // 4A8
  unk32 m_unk_field_4A8;
};

struct _SEN_OBJ_SEQ
{
public:
  // 0025C170
  void Initialize();

  // 0
  unk32 m_unk_field_0;
  // 10
  vec4 m_unk_field_10;
  // 20
  unk32 m_unk_field_20;
  // 24
  unk32 m_unk_field_24;
  // 28
  unk32 m_unk_field_28;
  // 2C
  std::array<char, 0x20> m_unk_field_2C;
  // 4C
  unk32 m_unk_field_4C;
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
  unk32 m_unk_field_8;
  // C
  unk32 m_unk_field_C;
  // 10
  unk32 m_unk_field_10;
  // 14
  unk32 m_unk_field_14;
  // 18
  unk32 m_unk_field_18;
  // 1C
  unk32 m_unk_field_1C;
  // 20
  unk32 m_unk_field_20;
  // 24
  unk32 m_unk_field_24;
  // 28
  unk32 m_unk_field_28;
  // 2C
  unk32 m_unk_field_2C;
  // 30
  unk32 m_unk_field_30;
  // 34
  unk32 m_unk_field_34;
  // 38
  unk32 m_unk_field_38;
  // 3C
  unk32 m_unk_field_3C;
  // 40
  unk32 m_unk_field_40;
  // 44
  unk32 m_unk_field_44;
  // 48
  unk32 m_unk_field_48;
  // 4C
  unk32 m_unk_field_4C;
  // 50
  unk32 m_unk_field_50;
  // 54
  unk32 m_unk_field_54;
  // 58
  unk32 m_unk_field_58;

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
  unk32 m_unk_field_F0;
  // F4
  unk32 m_unk_field_F4;
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
  unk32 m_unk_field_C{ 0 };
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
  // 0025FF40
  void SetParam(f32 f1, f32 f2, f32 f3);
  // 0025FF50
  void StartRaster(f32 f1, f32 f2, f32 f3, s32 i);
  // 002600A0
  void StopRaster(f32 f1, f32 f2, f32 f3, s32 i);
  // 002601F0
  void StepRaster();
  // 00260340
  void DrawRaster();

  // 0
  bool m_unk_field_0{ false };
  // 4
  f32 m_unk_field_4{ 0.0f };
  // 8
  f32 m_unk_field_8{ 0.0f };
  // C
  f32 m_unk_field_C{ 0.0f };
  // 10
  f32 m_unk_field_10{ 0.0f };
  // 14
  f32 m_unk_field_14{ 0.0f };
  // 18
  f32 m_unk_field_18{ 0.0f };
  // 1C
  unk32 m_unk_field_1C{ 0 };
  // 20
  unk32 m_unk_field_20{ 0 };
  // 24
  s32 m_unk_field_24{ -1 };
  // 28
  unk32 m_unk_field_28{ 0 };
};

class CScreenEffect : CRaster
{
public:
  // 00260640
  void Step();
  // 002608D0
  void InitRaster(f32 f1, f32 f2, f32 f3);
  // 00260930
  void StartRaster(f32 f1, f32 f2, f32 f3, s32 i);
  // 00260940
  void StopRaster(f32 f1, f32 f2, f32 f3, s32 i);
  // 00260950
  void SetSepiaTexture(unkptr p1, unkptr p2);
  // 00260970
  void CaptureSepiaScreen();
  // 00260BF0
  void SetSepiaFlag(bool flag);
  // 00260C10
  void SetMonoFlashTexture(unkptr p1, unkptr p2);
  // 00260C60
  void CaptureMonoFlashScreen();
  // 00260F30
  void SetMonoFlashFlag(bool b1, bool b2);

  // 2C
  mgCTexture* m_unk_field_2C{ nullptr };
  // 30
  bool m_sepia_flag{ false };
  // 34
  bool m_unk_field_34{ false };
  // 38
  bool m_unk_field_38{ false };
  // 3C
  bool m_unk_field_3C{ false };
  // 40
  bool m_unk_field_40{ false };
  // 44
  s32 m_unk_field_44{ 0 };
  // 48
  ssize m_unk_field_48{ 0 };
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
  unk32 m_unk_field_0{ 0 };
  // 4
  unk32 m_unk_field_4{ 0 };
  // 8
  std::array<char, 0x40> m_name{ 0 };
  // 48
  unks<0x10> m_unk_field_48{ 0 };
  // 58
  unks<0x10> m_unk_field_58{ 0 };
  // 68
  unks<0x10> m_unk_field_68{ 0 };
  // 78
  unks<0x10> m_unk_field_78{ 0 };

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
  unk32 m_unk_field_0{ 0 };
  // 4
  s32 m_unk_field_4{ -1 };
  // 8
  s32 m_unk_field_8{ -1 };
  // C
  unks<0x20> m_unk_field_C { 0 };
  // 2C
  bool m_unk_field_2C{ true };
  // 30
  vec4 m_unk_field_30{ 0.0f };
  // 40
  vec4 m_unk_field_40{ 128.0f };
  // 50
  unk32 m_unk_field_50{ 0 };
  // 54
  unk32 m_unk_field_54{ 0 };
  // 58
  unk32 m_unk_field_58{ 0 };
  // 5C
  unk32 m_unk_field_5C{ 0 };
  // 60
  unk32 m_unk_field_60{ 0 };
  // 64
  unk32 m_unk_field_64{ 0 };
  // 68
  unk32 m_unk_field_68{ 0 };
  // 6C
  f32 m_unk_field_6C{ 1.0f };
  // 70
  f32 m_unk_field_70{ 1.0f };
};

class CEventScriptArg
{
public:
  // 0
  unk32 m_unk_field_0{ 0 };
  // 4
  unk32 m_unk_field_4{ 0 };
  // 8
  unk32 m_unk_field_8{ 0 };
  // C
  unk32 m_unk_field_C{ 0 };
};

// 002610D0
sint GetLocalCnt(ssize index);
