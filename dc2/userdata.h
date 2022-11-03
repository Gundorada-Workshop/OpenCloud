#pragma once
#include "common/types.h"

// ~ 00196C20 - 001A2080

// TODO THIS FILE
struct MOS_CHANGE_PARAM {};
class CFishingRecord {};
class CFishingTournament {};
class CBattleCharaInfo {};


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
};

class CGameDataUsed
{
public:
  // 001970c0
  void Init();
};

class CFishAquarium
{
public:
  // 0019a160
  void Initialize();
};

class CMonsterBox
{
public:
  // 0019ab50
  void Initialize();
};
