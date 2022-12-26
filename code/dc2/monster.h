#pragma once
#include "common/constants.h"
#include "common/debug.h"
#include "common/types.h"

#include "dc2/character.h"

class CActiveMonster : public CActionChara
{
public:
  // 12FC
  f32 m_clip_dist{ 500.0f };
  // 1318
  u16 m_base_attack{ 0 };
  // 1324
  // Baseline HP damage to take when striking this monster with a melee weapon
  u16 m_melee_whp_penalty{ 1 };
  // 1338
  s16 m_piyori_current{ 0 };
};

class CMonsterLocateInfo
{
};

class CMonsterMan
{
};