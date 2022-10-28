#pragma once
#include "Types.h"

class CUserDataManager
{
public:
  // 0019b160
  void Initialize();

  // 0019b9a0
  void JoinPartyMember(sint chara);

  // 0019baa0
  void EnableCharaChange(sint chara);

  // 0019c420
  void SetRoboName(const char* name);

  // 0019c450
  char* GetRoboNameDefault();
};
