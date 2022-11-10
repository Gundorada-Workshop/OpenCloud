#pragma once
#include <array>
#include "common/debug.h"
#include "userdata.h"

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

namespace menumain
{
  // 00374440
  void SInit();
}

struct CMENU_USERPARAM
{
public:
  // 0023A5C0
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
};

struct MENU_ASKMODE_PARA
{
public:
  // 0023A670
  void Initialize();

  // 8C
  s32 m_unk_field_8C = -1;
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
  _WORD m_unk_field_0;
  // 2
  _WORD m_unk_field_2;
  // 4
  _BYTE m_unk_field_4;
  // 6
  _WORD m_unk_field_6;
  // 8
  _DWORD m_unk_field_8;
  // C
  _DWORD m_unk_field_C;
  // 10
  u32 m_unk_field_10;
  // 14
  _WORD m_unk_field_14;
  // 18
  std::array<_DWORD, 0x20> m_unk_field_18;
  // 58
  MENU_ASKMODE_PARA m_unk_field_58;
  // EE
  s16 m_unk_field_EE;
  // F0
  _WORD m_unk_field_F0;
  // F2
  s16 m_unk_field_16;
  // F4
  s32 m_unk_field_F4;
  // F8
  _DWORD m_unk_field_F8;
  // FC
  _UNKNOWNSTRUCT(0x10) m_unk_field_10C;

  // SIZE 0x110, VTABLE @ 0x10C
};

class CMenuItemInfo : CBaseMenuClass
{
public:
  // 304
  CGameDataUsed m_unk_field_304{};

  // SIZE 0x370
};