#pragma once
#include "common/debug.h"
#include "common/types.h"

// ~ 001937C0 - 00196130

class CDataItem
{
  // 0
  _DWORD m_unk_field_0{ 0 };
  // 4
  _DWORD m_unk_field_4{ 0 };
  // 8
  // ?
  // A
  _WORD m_unk_field_A{ 0 };
  // C
  _WORD m_unk_field_C{ 0 };
  // E
  _WORD m_unk_field_E{ 0 };
};

class CDataAttach
{
  // memset all to 0
  // SIZE 0x18
};

class CDataWeapon
{
  // memset all to 0 (except field 0 and 2)
  // 0
  s16 m_unk_field_0{ 20 };
  // 2
  s16 m_unk_field_2{ 20 };
  // SIZE 0x4C
};

class CDataRoboPart
{
  // SIZE 0x24
};

class CDataBreedFish
{
  // SIZE 0x14
};

class CDataItemCom
{
  // 28
  _DWORD m_unk_field_28{ 0 };
  // 54
  _DWORD m_unk_field_54{ 0 };
  // 80
  _DWORD m_unk_field_80{ 0 };
  // AC
  _DWORD m_unk_field_AC{ 0 };
  // D8
  _DWORD m_unk_field_D8{ 0 };
  // 104
  _DWORD m_unk_field_104{ 0 };
  // 130
  _DWORD m_unk_field_130{ 0 };
  // 15C
  _DWORD m_unk_field_15C{ 0 };

  // SIZE 0x160
};

class CDataGuard
{
  // SIZE 0x4
};

class CGameData
{
public:
  // 001946D0
  CGameData();

  // probably no copying this (saving might? will have to check)
  CGameData(CGameData& other) = delete;
  void operator=(const CGameData&) = delete;

  // 00195540
  s32 LoadData();

  // 0
  _DWORD m_unk_field_0{ 0 };
  // 4
  CDataItemCom* m_com_itemdata;
  // 8
  CDataItem* m_itemdata;
  // C
  CDataWeapon* m_weapondata;
  // 10
  CDataGuard* m_guarddata;
  // 14
  CDataAttach* m_attachdata;
  // 18
  CDataRoboPart* m_robodata;
  // 1C
  CDataBreedFish* m_fishdata;
  // 20
  _WORD m_unk_field_20{ 0 };
  // 22
  _WORD m_unk_field_22{ 0 };
  // 24
  _WORD m_unk_field_24{ 0 };
  // 26
  _WORD m_unk_field_26{ 0 };
  // 28
  _WORD m_unk_field_28{ 0 };
  // 2A
  _WORD m_unk_field_2A{ 0 };
  // 2C
  _WORD m_unk_field_2C{ 0 };
  // 2E
  _WORD m_unk_field_2E{ 0 };
};

// 00195470
bool LoadGameDataAnalyze(const char* config_file_name);