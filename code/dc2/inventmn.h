#pragma once
#include <array>

#include "common/debug.h"

#include "dc2/gamedata.h"

// ~ 001FE130 - 0020C910

// TODO THIS FILE
class CDC2AlbumData {};
class CInventDataManager {};
class CMenuInvent {};

struct USER_PICTURE_INFO
{
  u8 m_unk_field_0;
  u8 m_unk_field_1;
  s16 m_unk_field_2;
  s16 m_unk_field_4;
  s16 m_unk_field_6;
  s16 m_unk_field_8;
  s16 m_unk_field_A;
};

// 001FE170
// Why?
void Initialize_USER_PICTURE_INFO(USER_PICTURE_INFO* user_picture_info);

struct SInventUserDataUnk1
{
  // 0
  USER_PICTURE_INFO m_user_picture_info;
  // C
  unk m_unk_field_C;
  // 10
  unk m_unk_field_10;
  // 14
  std::array<u8, 0x2000>* m_unk_field_14;
};

class CInventUserData
{
public:
  // 001fe880
  void Initialize();

  // 001fe970
  void ResetAddress();

  // 001FF070
  void SetCreateItemFlag(usize index, ECommonItemData item_id);

  // 001FF0E0
  ECommonItemData GetCreateItemId(usize index);

  // 001FF120
  ssize IsAlreadyCreatedItem(ECommonItemData item_id);

  // 001FF170
  // "GetHatsumeiNum"
  uint GetInventionNum();

  // 0
  unk m_unk_field_0;
  // 4
  unk m_unk_field_4;
  // 8
  unks<0x400> m_unk_field_8;
  // 408
  std::array<SInventUserDataUnk1, 30> m_unk_field_408;
  // 6D8
  // This may be array of some sort of struct (ECommonItemData, _WORD?), since each item is packed to 4 bytes
  std::array<ECommonItemData, 0x100> m_unk_field_6D8{ ECommonItemData::Invalid };

  // ?

  // D60
  // TODO: Just char buffers?
  std::array<std::array<u8, 0x2000>, 30> m_unk_field_D60;
  // 3CD60
  // ...?
};
