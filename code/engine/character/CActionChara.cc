#include <string>

#include "common/log.h"
#include "common/debug.h"
#include "common/macros.h"

#include "engine/character/CActionChara.h"

set_log_channel("character");

// 0016B850
unkptr CActionChara::Draw()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
  return nullptr;
}

// 0016B940
unkptr CActionChara::DrawDirect()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
  return nullptr;
}

// 0016AB60
f32 CActionChara::GetCameraDist()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
  return 0.0f;
}

// 0016AB00
void CActionChara::SetFarDist(MAYBE_UNUSED f32 far_dist)
{
  log_trace("CActionChara::{}({})", __func__, far_dist);

  todo;
}

// 0016AB30
void CActionChara::SetNearDist(MAYBE_UNUSED f32 near_dist)
{
  log_trace("CActionChara::{}({})", __func__, near_dist);

  todo;
}

// 0016B800
void CActionChara::ResetMotion()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016AAD0
void CActionChara::SetFadeFlag(MAYBE_UNUSED bool flag)
{
  log_trace("CActionChara::{}({})", __func__, flag);

  todo;
}

// 0016BA70
unkptr CActionChara::DrawShadowDirect()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
  return nullptr;
}

// 00171E80
void CActionChara::Step()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 00172090
void CActionChara::ShadowStep()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016BAC0
void CActionChara::DrawEffect()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016ABA0
void CActionChara::Show(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2)
{
  log_trace("CActionChara::{}({}, {})", __func__, i1, i2);

  todo;
}

// 0016ABE0
void CActionChara::GetShow(MAYBE_UNUSED std::string chara_name)
{
  log_trace("CActionChara::{}({})", __func__, chara_name);

  todo;
}

// 0016B780
void CActionChara::SetMotion(MAYBE_UNUSED std::string key_name, MAYBE_UNUSED sint i1)
{
  log_trace("CActionChara::{}({}, {})", __func__, key_name, i1);

  todo;
}

// 0016B780
void CActionChara::SetMotion(MAYBE_UNUSED std::string key_name, MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2)
{
  log_trace("CActionChara::{}({}, {}, {})", __func__, key_name, i1, i2);

  todo;
}

// 0016B5B0
ECharacterMotionStatus CActionChara::GetMotionStatus(MAYBE_UNUSED std::string key_name)
{
  log_trace("CActionChara::{}({})", __func__, key_name);

  todo;
  return ECharacterMotionStatus::_0;
}

// 0016BB00
void CActionChara::StepEffect()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// if you call either of these instead of creating/using a constructor/copy constructor I'll keelhaul you
// 001720E0
void CActionChara::Initialize(MAYBE_UNUSED mgCMemory* memory)
{
  log_trace("CActionChara::{}()", __func__);

  panicf("please create and use a constructor instead");
}

// 00172380
void CActionChara::Copy(MAYBE_UNUSED CActionChara& other, MAYBE_UNUSED mgCMemory* memory)
{
  log_trace("CActionChara::{}()", __func__);

  panicf("please create and use a copy constructor instead");
}

// 0016A140
void CActionChara::ResetAccele()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016A160
void CActionChara::ResetAction()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016A220
void CActionChara::ResetScript()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016A4C0
void CActionChara::CheckRunEvent()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016A4E0
void CActionChara::SetMaskFlag(MAYBE_UNUSED u32 mask, MAYBE_UNUSED bool active)
{
  log_trace("CActionChara::{}({}, {})", __func__, mask, active);

  todo;
}

// 0016A510
unkptr CActionChara::EntryObject(MAYBE_UNUSED std::string frame_name, MAYBE_UNUSED ssize i)
{
  log_trace("CActionChara::{}({}, {})", __func__, frame_name, i);

  todo;
  return nullptr;
}

// 0016A5C0
void CActionChara::CalcCollision()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016A620
unkptr CActionChara::EntryBodyCol(MAYBE_UNUSED ssize i, MAYBE_UNUSED f32 f)
{
  log_trace("CActionChara::{}({}, {})", __func__, i, f);

  todo;
  return nullptr;
}

// 0016A6B0
COLLISION_INFO* CActionChara::EntryDamage2(MAYBE_UNUSED std::string s1, MAYBE_UNUSED std::string s2, MAYBE_UNUSED std::string s3,
                                           MAYBE_UNUSED f32 f1, MAYBE_UNUSED std::string s4, MAYBE_UNUSED f32 f2, MAYBE_UNUSED f32 f3,
                                           MAYBE_UNUSED std::string s5)
{
  log_trace("CActionChara::{}({}, {}, {}, {}, {}, {}, {}, {})", __func__, s1, s2, s3, f1, s4, f2, f3, s5);

  todo;
  return nullptr;
}

// 0016A850
COLLISION_INFO* CActionChara::EntryDamage2(MAYBE_UNUSED mgCFrame* frame1, MAYBE_UNUSED mgCFrame* frame2, MAYBE_UNUSED std::string s3,
                                           MAYBE_UNUSED f32 f1, MAYBE_UNUSED std::string s4, MAYBE_UNUSED f32 f2, MAYBE_UNUSED f32 f3,
                                           MAYBE_UNUSED std::string s5)
{
  log_trace("CActionChara::{}({}, {}, {}, {}, {}, {}, {}, {})", __func__, fmt::ptr(frame1), fmt::ptr(frame2), s3, f1, s4, f2, f3, s5);

  todo;
  return nullptr;
}

// 0016A9B0
void CActionChara::AllDeleteDamage()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016AA30
SW_EFFECT* CActionChara::GetSwEffectPtr()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
  return nullptr;
}

// 0016AA70
void CActionChara::SetSoundInfoCopy()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016AC60
bool CActionChara::CheckKeri(MAYBE_UNUSED std::string frame_name, MAYBE_UNUSED bool b)
{
  log_trace("CActionChara::{}({})", __func__, frame_name, b);

  todo;
  return false;
}

// 0016AD30
bool CActionChara::CheckEnemyCatch(MAYBE_UNUSED std::string frame_name)
{
  log_trace("CActionChara::{}({})", __func__, frame_name);

  todo;
  return false;
}

// 0016AF40
void CActionChara::ThrowItemObject()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016B020
sint CActionChara::UsedItemAction()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
  return 0;
}

// 0016B1C0
void CActionChara::EntryThrowItem()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016B3C0
void CActionChara::RemoveThrowItem()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016B420
f32 CActionChara::GetNowFrameWait(MAYBE_UNUSED std::string key_name) const
{
  log_trace("CActionChara::{}({})", __func__, key_name);

  todo;
  return -1.0f;
}

// 0016B4A0
f32 CActionChara::GetNowFrame(MAYBE_UNUSED std::string key_name) const
{
  log_trace("CActionChara::{}({})", __func__, key_name);

  todo;
  return -1.0f;
}

// 0016B520
bool CActionChara::CheckMotionEnd(MAYBE_UNUSED std::string key_name) const
{
  log_trace("CActionChara::{}({})", __func__, key_name);

  todo;
  return false;
}

// 0016B630
f32 CActionChara::GetWaitToFrame(MAYBE_UNUSED std::string key_name)
{
  log_trace("CActionChara::{}({})", __func__, key_name);

  todo;
  return -1.0f;
}

// 0016BC90
CActionChara* CActionChara::SearchChara(MAYBE_UNUSED std::string chara_name)
{
  log_trace("CActionChara::{}({})", __func__, chara_name);

  todo;
  return nullptr;
}

// 0016BCF0
mgCFrame* CActionChara::SearchObject(std::string frame_name)
{
  log_trace("CActionChara::{}({})", __func__, frame_name);

  todo;
  return nullptr;
}

// 0016BD60
void CActionChara::ResetParent()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016BD90
bool CActionChara::SetRef(MAYBE_UNUSED CActionChara* parent_chara, MAYBE_UNUSED std::string frame_name)
{
  log_trace("CActionChara::{}({}, {})", __func__, fmt::ptr(parent_chara), frame_name);

  todo;
  return false;
}

// 0016BE50
f32 CActionChara::GetTargetDist(MAYBE_UNUSED CScene* scene)
{
  log_trace("CActionChara::{}({})", __func__, fmt::ptr(scene));

  todo;
  return -1.0f;
}

// 0016BEE0
//void CActionChara::CollisionCheck(const vec3& v1, const vec3& v2, const vec3& v3)
//{
//  log_trace("CActionChara::{}({}, {}, {})", __func__, v1, v2, v3);
//
//  todo;
//}

// 0016C7A0
// "RockOn"
void CActionChara::LockOn()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016C990
void CActionChara::HumanMoveIF()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016D560
// "HumanShrowMoveIF"
void CActionChara::HumanThrowMoveIF()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016D8E0
void CActionChara::HumanChargeUpMoveIF()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 0016DAA0
void CActionChara::HumanGunMoveIF(MAYBE_UNUSED std::string key_name1, MAYBE_UNUSED std::string key_name2)
{
  log_trace("CActionChara::{}({}, {})", __func__, key_name1, key_name2);

  todo;
}

// 0016DD80
void CActionChara::RoboWalkMoveIF(MAYBE_UNUSED sint i)
{
  log_trace("CActionChara::{}({})", __func__, i);

  todo;
}

// 0016E2A0
void CActionChara::RoboTankMoveIF(MAYBE_UNUSED sint i)
{
  log_trace("CActionChara::{}({})", __func__, i);

  todo;
}

// 0016E9F0
void CActionChara::RoboBikeMoveIF(MAYBE_UNUSED sint i)
{
  log_trace("CActionChara::{}({})", __func__, i);

  todo;
}

// 0016F330
void CActionChara::RoboAirMoveIF(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2)
{
  log_trace("CActionChara::{}({}, {})", __func__, i1, i2);

  todo;
}

// 0016FA30
void CActionChara::MonsterMoveIF()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 00170730
bool CActionChara::CheckDamage()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
  return false;
}

// 001710C0
void CActionChara::LoadActionFile(MAYBE_UNUSED char* c, MAYBE_UNUSED int i, MAYBE_UNUSED mgCMemory* memory)
{
  log_trace("CActionChara::{}({}, {}, {})", __func__, fmt::ptr(c), i, fmt::ptr(memory));

  todo;
}

// 00171160
void CActionChara::InitScript()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 00171210
void CActionChara::RunScript(MAYBE_UNUSED CScene* scene, MAYBE_UNUSED RUN_SCRIPT_ENV* script_env)
{
  log_trace("CActionChara::{}({}, {})", __func__, fmt::ptr(scene), fmt::ptr(script_env));

  todo;
}

// 001719C0
// "CheckReleaseTimming"
s16 CActionChara::CheckReleaseTiming(MAYBE_UNUSED sint i)
{
  log_trace("CActionChara::{}({})", __func__, i);

  todo;
  return -1;
}

// 001719F0
void CActionChara::StepParam()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}