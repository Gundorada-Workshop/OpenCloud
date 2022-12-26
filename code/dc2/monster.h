#pragma once
#include "common/constants.h"
#include "common/debug.h"
#include "common/types.h"

#include "dc2/character.h"
#include "dc2/gamedata.h"

class CActiveMonster;

class CPiyori
{
public:
  // 001C9820
  void Reset();
  
  // NOTE: signature says mgCObject*, but they seem to upcast it
  // to at least CCharacter2, so, eh?
  // 001C98C0
  void Set(CActiveMonster* monster, s16 i);

  // 001C9900
  void Draw();

  // 001C9B40
  void Step();

private:
  // 001C9830
  void Set(CActiveMonster* monster, f32 f0, f32 f1, s16 i);

private:
  // 0
  CActiveMonster* m_monster{ nullptr };
  // 4
  std::array<f32, 3> m_unk_field_4{};
  // 10
  f32 m_unk_field_10{};
  // 14
  f32 m_unk_field_14{};
  // 18
  f32 m_unk_field_18{};
  // 1C
  s16 m_unk_field_1C{};
  // 1E
  s16 m_unk_field_1E{};
};

class CActiveMonster : public CActionChara
{
public:
  // 12A4
  EAttackType m_attack_type{ EAttackType::Invalid };
  // 12F0
  s16 m_priority{ 999 };
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