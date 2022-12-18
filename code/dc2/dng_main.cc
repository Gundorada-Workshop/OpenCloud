#include <array>

#include <glm/glm.hpp>

#include "common/clock.h"
#include "common/debug.h"
#include "common/log.h"
#include "common/debug.h"
#include "common/math.h"
#include "common/macros.h"

#include "dc2/camera.h"
#include "dc2/character.h"
#include "dc2/collision.h"
#include "dc2/dng_main.h"
#include "dc2/dng_event.h"
#include "dc2/editloop.h"
#include "dc2/effect.h"
#include "dc2/map.h"
#include "dc2/mg/mg_lib.h"
#include "dc2/monster.h"
#include "dc2/nowload.h"
#include "dc2/pot.h"
#include "dc2/robopart.h"
#include "dc2/userdata.h"
#include "dc2/weapon.h"

set_log_channel("dng_main");

// 01E9F230
std::array<mgCMemory, 2> BuffPacketList{ };

// 01E9F290
std::array<mgCMemory, 2> BuffPacketData{ };

// 01E9F2F0
mgCMemory BuffStageMain{ };

// 01E9F320
mgCMemory BuffStageChara{ };

// 01E9F350
mgCMemory BuffStageSubData{ };

// 01E9F3B0
mgCMemory BuffStageSubChara{ };

// 01E9F3E0
mgCMemory BuffWorkData{ };

// 01E9F3E0
mgCMemory BuffCharacter{ };

// 01E9F410
std::array<mgCMemory, 6> BaseCharacter{ };

// 01E9F530
mgCMemory BuffTempData{ };

// 01E9F560
mgCMemory BuffScriptData{ };

// 01E9F590
mgCMemory BuffEffectScriptData{ };

// 01E9F5C0
std::array<mgCMemory, 4> BuffEventData{ };

// 01E9F680
mgCMemory BuffMDTBuild{ };

// 01E9F6B0
mgCMemory BuffMDTBuild2{ };

// 01E9F6E0
SDungeonStatus DngStatus{ };

// 01E9F700
CMapEffectsManager map_effect{ };

// 01E9F720
CAccumulateEffect AccumulateEffect{ };

// 01E9FA50
CDamageScore DamageScore{ };

// 01E9FAE0
std::array<CDamageScore, 8> DamageScoreMons{ };

// 01E9FF60
CDamageScore2 DamageScore2{ };

// 01E9FF90
MessageTaskManager MsgTaskMan{ };

// 01EA0300
CStartupEpisodeTitle StartupEpisodeTitle{ };

// 01EA0320
BattleEffectMan BattleFX{ };

// 01EA0370
CLevelupInfo LevelupInfo{ };

// 01EA03B0
CLockOnModel LockOnModel{ };

// 01EA0460
CWarningGauge2 WarningGauge2{ };

// 01EA0480
CAutoMapGen AutoMapGen{ };

// 01EA0710
CColPrimMan ColPrimMan{ };

// 01EA51C0
CGeoStone GeoStone{ };

// 01EA5830
CCameraControl MainCamera{ };

// 01EA5A20
CCameraControl EventCamera{ };

// 01EA5C10
CHealingEffectMan HealingEffectMan{ };

// 01EA5F40
CMiniEffPrimMan MiniEffPrimMan{ };

// 01EA6870
std::array<CCharacter2, 19> ItemBaseData{} ;

// 01EAE190
std::array<CAfterWire, 16> afterWire{ };

// 01EAF390
CRoboVoiceSystem VoiceUnit{ };

// 01EAF3B0
CPot BTpot{ };

// 01EAF430
CBPot BTpot2{ };

// 01EB0080
CRocketLauncherMan RocketLauncher{ };

// 01EB2600
CMachineGun MachineGun{ };

// 01EB2990
CLaserGunMan LaserGun{ };

// 01EB3C90
CCharacter2 LaserGunModel{ };

// 01EB42F0
std::array<CPullItem, 72> PullItem{ };

// 01EB66F0
NowLoadingInfo nowload{ };

// 01EB6740
CWaveTable WaveTable{ };

// 01EB7948
unk64 SparcModel{ 0 };

// 01EB7960
CSwordLuminous SwordLuminous{ };

// 01EB7980
CWeaponElement wep_effect{ };

// 01EBB780
std::array<CSparcEffect, 6> Sparc_fx{ };

// 01EBBBA0
std::array<CThunder, 6> thunder{ };

// 01EC0E20
std::array<CTornado, 6> tornado{ };

// 01EC2320
std::array<CChillAfterHit, 6> chillAfterHit{ };

// 01EC50E0
std::array<CFireAfterHit, 6> fireAfterHit{ };

// 001C2240
void CSwordAfterImage::Initialize(MAYBE_UNUSED mgCMemory* stack, MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2)
{
  log_trace("CSwordAfterImage::{}({}, {}, {})", __func__, fmt::ptr(stack), i1, i2);

  todo;
}

// 001D4850
CFireAfterHit::CFireAfterHit()
{
  log_trace("CFireAfterHit::CFireAfterHit()");

  Initialize();
}

// 001BF4F0
void CFireAfterHit::Initialize()
{
  log_trace("CFireAfterHit::Initialize()");

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;
  m_unk_field_8 = 0;
  m_unk_field_C = 0;

  memset(&m_unk_field_10, 0, sizeof(m_unk_field_10));
  memset(&m_unk_field_2B0, 0, sizeof(m_unk_field_2B0));
}

// 001D4880
CChillAfterHit::CChillAfterHit()
{
  log_trace("CChillAfterHit::CChillAfterHit()");

  Initialize();
}

// 001BE6F0
void CChillAfterHit::Initialize()
{
  log_trace("CChillAfterHit::Initialize()");

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;
  m_unk_field_8 = 0;
  memset(&m_unk_field_20, 0, sizeof(m_unk_field_20));
  m_unk_field_10 = vec4(0);
}

// 001D4C40
void CMiniMapSymbol::DrawSymbol(MAYBE_UNUSED vec3& pos, MAYBE_UNUSED EMiniMapSymbol::EMiniMapSymbol symbol_type)
{
  // 0033D8A0
  static std::array<MINIMAP_SYMBOL_DATA, EMiniMapSymbol::COUNT + 1> symbol_table
  {
    EMiniMapSymbol::SphidaShotGuide, {255, 0,   0},   10, 10, false, true,
    EMiniMapSymbol::TreasureBox,     {96,  64,  0},   10, 10, false, true,
    EMiniMapSymbol::RandomCircle,    {255, 255, 0},   10, 10, false, true,
    EMiniMapSymbol::GeoStone,        {255, 0,   180}, 10, 10, false, true,
    EMiniMapSymbol::SphidaRedGoal,   {255, 0,   0},   14, 14, false, false,
    EMiniMapSymbol::SphidaBlueGoal,  {0,   64,  255}, 14, 14, false, false,
    EMiniMapSymbol::SphidaRedBall,   {255, 0,   0},   10, 10, true,  false,
    EMiniMapSymbol::SphidaBlueBall,  {0,   0,   255}, 10, 10, true,  false,
    EMiniMapSymbol::Monster,         {255, 0,   0},   10, 10, true,  true,
    EMiniMapSymbol::TERMINATOR,      {0,   0,   0},   0,  0,  false, false,
  };

  log_trace("CMiniMapSymbol::DrawSymbol({}, {})", fmt::ptr(&pos), std::to_underlying(symbol_type));

  todo;
}

// 002F8CC0
void CDngFloorManager::Initialize()
{
  log_trace("CDngFloorManager::Initialize()");

  m_map_id = 0;
  m_glid_info = nullptr;
  m_unk_field_8 = 0;
  m_unk_field_C = 0;
  m_unk_field_E = 0;
}

// 001CB3E0
void* CLockOnModel::Draw()
{
  log_trace("CLockOnModel::Draw()");

  return nullptr;
}

// 001CB860
void CLockOnModel::Step()
{
  log_trace("CLockOnModel::Step()");

  // NOTE: DEGREES_TO_RADIANS(4.0f) == 0x3D8EFA35
  m_unk_field_88 += math::deg_to_rad(4.0f) * GAME_DT * GAME_FPS;

  if (m_unk_field_88 > math::deg_to_rad(180.0f))
  {
    m_unk_field_88 -= math::deg_to_rad(360.0f);
  }
}

// 001CBD20
void CLockOnModel::Initialize(CScene* scene)
{
  log_trace("CLockOnModel::Initialize({})", fmt::ptr(scene));

  m_scene = scene;
  m_unk_field_8C = 0;
}

// 001CB7B0
void CLockOnModel::DrawMes(MAYBE_UNUSED sint i)
{
  log_trace("CLockOnModel::DrawMes({})", i);

  todo;
}

// 001E8630
void calcWeaponParamWhp(const CActiveMonster& monster, const CColPrim& collision)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(&monster), fmt::ptr(&collision));
  
  auto chara_info = GetBattleCharaInfo();
  auto i = collision.m_damage_param->m_unk_field_18;

  using enum EDAMAGE_PARAMUnk;

  if (i != _4 && i != _0 && i != _11 && i != _12)
  {
    return;
  }

  // NOTE: There's an impossible branch here @ 001E86A0, possibly dead code from DC1
  f32 whp_penalty = static_cast<f32>(monster.m_melee_whp_penalty) * 0.5f;
  f32 wep_durability = static_cast<f32>(chara_info->m_param.m_weapons[0].m_durable) * 0.005f;

  whp_penalty -= whp_penalty * wep_durability;

  using enum ESpecialStatus;

  if ((collision.m_unk_field_A0 & _20h) != None)
  {
    whp_penalty *= 1.3f;
  }
  if ((collision.m_unk_field_A0 & _40h) != None)
  {
    whp_penalty *= 0.8f;
  }

  f32 old_whp = static_cast<f32>(chara_info->GetWhpNowVol(0));
  f32 now_whp = chara_info->AddWhp(0, -whp_penalty);

  if (now_whp <= 0.0f && old_whp > 0.0f)
  {
    // The weapon broke, remove some ABS
    chara_info->AddAbsRate(0, -0.1f, nullptr);
  }
}

// 001E87E0
void calcWeaponParam2(sint penalty_divisor)
{
  log_trace("{}({})", __func__, penalty_divisor);

  auto chara_info = GetBattleCharaInfo();
  auto special_status = chara_info->GetSpecialStatus(1);
  

  f32 whp_penalty = 1.0f - chara_info->m_param.m_weapons[1].m_durable * 0.002f;

  using enum ESpecialStatus;

  if ((special_status & _20h) != None)
  {
    whp_penalty *= 1.3f;
  }
  if ((special_status & _40h) != None)
  {
    whp_penalty *= 0.8f;
  }

  f32 old_whp = static_cast<f32>(chara_info->GetWhpNowVol(1));
  f32 new_whp = chara_info->AddWhp(1, -(whp_penalty / penalty_divisor));

  if (new_whp <= 0.0f && old_whp > 0.0f)
  {
    // The weapon broke, remove some ABS
    chara_info->AddAbsRate(1, -0.1f, nullptr);
  }
}
