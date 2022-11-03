#pragma once
#include "common/debug.h"
#include "common/types.h"
#include "gamedata.h"

// ~ 00196C20 - 001A2080

// TODO THIS FILE
struct MOS_CHANGE_PARAM {};
class CFishingRecord {};
class CFishingTournament {};
class CBattleCharaInfo {};

class CGameDataUsed;

class CFishAquarium
{
public:
  // 0019a160
  void Initialize();

  // 0
  u16 m_unk_field_0;
  // 2
  u16 m_unk_field_2;
  // 4
  std::array<CGameDataUsed, 6> m_unk_field_4;
  // 28C
  std::array<CGameDataUsed, 4> m_unk_field_28C;
  // 43C
  std::array<CGameDataUsed, 2> m_unk_field_43C;
  // 514
  _UNKNOWN m_unk_field_514;
  // 518 (8 bytes)
  _UNKNOWN m_unk_field_518;
  // 520 (8 bytes)
  _UNKNOWN m_unk_field_520;
  // 528
  _UNKNOWN m_unk_field_528;
  // 52C
  _UNKNOWN m_unk_field_52C;
};

struct SUserDataManagerUnkStruct1
{
  // ?

  // 2C
  std::array<CGameDataUsed, 3> m_unk_field_2C;
  // 170
  std::array<CGameDataUsed, 5> m_unk_field_170;
  // SIZE 0x38C
};

class CUserDataManager
{
public:
  // 0019b160
  void Initialize();

  // 0019b9a0
  void JoinPartyMember(s32 chara);

  // 0019baa0
  void EnableCharaChange(s32 chara);

  // 0019c420
  void SetRoboName(const char* name);

  // 0019c450
  const char* GetRoboNameDefault();

  // 0
  std::array<CGameDataUsed, 150> m_unk_field_0;
  // 3F48
  std::array<SUserDataManagerUnkStruct1, 2> m_unk_field_3F48;

  // ?

  // 4690
  std::array<CGameDataUsed, 4> m_unk_field_4690;
};

class CGameDataUsed
{
public:
  // 00197090
  CGameDataUsed();
  // 001970c0
  void Initialize();
};



class CMonsterBox
{
public:
  // 0019ab50
  void Initialize();
};
