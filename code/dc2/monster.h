#pragma once
#include "common/constants.h"
#include "common/debug.h"
#include "common/types.h"

#include "dc2/character.h"

class CActiveMonster : public CActionChara
{
public:
  // 1324
  // Baseline HP damage to take when striking this monster with a melee weapon
  u16 m_melee_whp_penalty{ 1 };
};

class CMonsterLocateInfo
{
};

class CMonsterMan
{
};