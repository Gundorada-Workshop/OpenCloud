#pragma once

class CUserDataManager
{
public:
  // 0019b160
  void Initialize();

  // 0019b9a0
  void JoinPartyMember(int chara);

  // 0019baa0
  void EnableCharaChange(int chara);

  // 0019c420
  void SetRoboName(const char* name);

  // 0019c450
  char* GetRoboNameDefault();
};
