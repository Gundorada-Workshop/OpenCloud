#pragma once
#include <array>

#include "common/debug.h"
#include "common/types.h"

#include "dc2/userdata.h"
#include "dc2/mg/mg_lib.h"

// ~ 0022D3B0 - 002518A0 (?)

// TODO THIS FILE
class CRepairEffect {};
class CRepairManager {};
class CLevelUpEffect {};
class CStarDust {};
class CEffVerticalLine {};
class CMenuEffect {};
struct MENU_INIT_ARG {};
struct MENU_SWAPITEM_INFO;
class CItemSelect {};

struct CMENU_USERPARAM
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
  // 10
  unk32 m_unk_field_10{ 0 };
  // 14
  unk32 m_unk_field_14{ 0 };
};

struct MENU_ASKMODE_PARA
{
public:
  // 8C
  s32 m_unk_field_8C{ 0 };
  // SIZE 0x94
};

class CBaseMenuClass
{
public:
  // 002370B0
  CBaseMenuClass();
  // 00239DA0
  void SetAskParam(MENU_ASKMODE_PARA* param);
  
  // 0
  unk16 m_unk_field_0;
  // 2
  unk16 m_unk_field_2;
  // 4
  unk8 m_unk_field_4;
  // 6
  unk16 m_unk_field_6;
  // 8
  unk32 m_unk_field_8;
  // C
  unk32 m_unk_field_C;
  // 10
  u32 m_unk_field_10;
  // 14
  unk16 m_unk_field_14;
  // 18
  std::array<unk32, 0x20> m_unk_field_18;
  // 58
  MENU_ASKMODE_PARA m_unk_field_58;
  // EE
  s16 m_unk_field_EE;
  // F0
  unk16 m_unk_field_F0;
  // F2
  s16 m_unk_field_16;
  // F4
  s32 m_unk_field_F4;
  // F8
  unk32 m_unk_field_F8;
  // FC
  unks<0x10> m_unk_field_10C;

  // SIZE 0x110, VTABLE @ 0x10C
};

class CMenuItemInfo : CBaseMenuClass
{
public:
  // 304
  CGameDataUsed m_unk_field_304{};

  // SIZE 0x370
};

// 002506C0
sint GetRandI(sint n);

// 00250700
f32 GetRandF(f32 n);

// 002507D0
f32 MenuAdjustPolygonScale(mgCFrame* frame, f32 scale);

// 002516C0
// Returns number of digits in a number
u32 GetNumberKeta(s32 n);

// 00251720
s32 GetDispVolumeForFloat(f32 f);

// 00251780
f32 GetFloatCommaValue(f32 f);
