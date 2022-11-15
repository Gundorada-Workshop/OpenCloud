#pragma once
#include "common/debug.h"
#include "common/types.h"

// ~ 001937C0 - 00196130

namespace ECommonItemDataType
{
  enum ECommonItemDataType : u8
  {
    Invalid = 0,
    _1 = 1,
    _2 = 2,
    _3 = 3,
    _4 = 4,
    _5 = 5,
    _6 = 6,
    _7 = 7,
    _8 = 8,
    _9 = 9,
    _10 = 10,
    _11 = 11,
    _12 = 12,
    _13 = 13,
    _14 = 14,
    _15 = 15,
    _16 = 16,
    _17 = 17,
    _18 = 18,
    _19 = 19,
    _20 = 20,
    _21 = 21,
    _22 = 22,
    _23 = 23,
    _24 = 24,
    _25 = 25,
    _26 = 26,
    _27 = 27,
    _28 = 28,
    _29 = 29,
    _30 = 30,
    _31 = 31,
    _32 = 32,
    _33 = 33,
    _34 = 34,
    _35 = 35,
    _36 = 36,
  };
}

namespace EUsedItemType
{
  enum EUsedItemType
  {
    Invalid = 0,
    Item_1 = 1,
    Attach = 2,
    Weapon = 3,
    _4 = 4,
    _5 = 5,
    Fish = 6,
    Item_7 = 7,
    Item_8 = 8,
  };
}

struct SDataItemCommon
{
  // 0
  ECommonItemDataType::ECommonItemDataType m_type{ ECommonItemDataType::Invalid };
  // 4
  s16 m_unk_field_4{ 0 };

  _DWORD m_unk_field_28{ 0 };
  // SIZE 0x2C
};

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
  // 00195770
  SDataItemCommon* GetCommonData(ssize index);
  // 001957E0
  CDataWeapon* GetWeaponData(ssize index);
  // 00195890
  CDataItem* GetItemData(ssize index);
  // 00195940
  CDataAttach* GetAttachData(ssize index);
  // 001959F0
  CDataRoboPart* GetRoboData(ssize index);
  // 00195A60
  CDataBreedFish* GetFishData(ssize index);
  // 00195B10
  CDataGuard* GetGuardData(ssize index);

  // 0
  _DWORD m_unk_field_0{ 0 };
  // 4
  SDataItemCommon* m_com_itemdata;
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

// 00195F10
EUsedItemType::EUsedItemType ConvertUsedItemType(ECommonItemDataType::ECommonItemDataType type);