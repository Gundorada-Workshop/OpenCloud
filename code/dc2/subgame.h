#pragma once
#include "common/debug.h"
#include "common/types.h"

// ~ 00303E70 - 003048B0

class CScene;

struct SubGameInfo
{
  // 0
  CScene* m_scene{ nullptr };
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
  // 18
  unk32 m_unk_field_18{ 0 };
  // 1C
  unk32 m_unk_field_1C{ 0 };
  // 20
  unk32 m_unk_field_20{ 0 };
  // 24
  unk32 m_unk_field_24{ 0 };
  // 28
  unk32 m_unk_field_28{ 0 };
  // 2C
  unk32 m_unk_field_2C{ 0 };
};

enum class ESubGameID
{

};

// 00303FC0
void sgInitSubGame(ESubGameID game_id, SubGameInfo* sub_game_info);
