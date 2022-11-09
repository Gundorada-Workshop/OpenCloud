#pragma once
#include <array>
#include "common/debug.h"

// ~ 001FE130 - 0020C910

// TODO THIS FILE
class CDC2AlbumData {};
class CInventDataManager {};
class CMenuInvent {};

namespace inventmn
{
  // 00374260
  void SInit();
}

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
  _UNKNOWN m_unk_field_C;
  // 10
  _UNKNOWN m_unk_field_10;
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

  // 0
  _UNKNOWN m_unk_field_0;
  // 4
  _UNKNOWN m_unk_field_4;
  // 8
  _UNKNOWNSTRUCT(0x400) m_unk_field_8;
  // 408
  std::array<SInventUserDataUnk1, 30> m_unk_field_408;
  // 6D8
  std::array<u16, 0x200> m_unk_field_6D8;

  // ?

  // D60
  // TODO: Just char buffers?
  std::array<std::array<u8, 0x2000>, 30> m_unk_field_D60;
  // 3CD60
  // ...?
};
