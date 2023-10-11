#pragma once

#include "common/types.h"

#include "engine/gamedata.h" // EAttackType

#include "engine/character/CCharacter2.h"

// ~ 0016A140 - 0017C240

class CScene;

struct RUN_SCRIPT_ENV
{
  // 0
  CCharacter2* m_unk_field_0;

  // 4
  s32 m_unk_field_4;
};

// this might be from another file but putting them here for now
struct COLLISION_INFO
{
  // 14
  f32 m_unk_field_14{};

  // SIZE 0x28
};

enum class EMoveType : s32
{
  Human = 0,
  RoboWalk1 = 1,
  RoboTank2 = 2,
  Monster = 3,
  RoboBike = 3,
  RoboWalk4 = 4,
  RoboTank5 = 5,
  RoboAir6 = 6,
  RoboAir7 = 7,
};

// this might be from another file but putting them here for now
struct SW_EFFECT
{
  // SIZE 0x20
};

constexpr f32 DEFAULT_CHARACTER_MOVE_SPEED = 3.0f;

class CActionChara : public CCharacter2
{
public:
  using CCharacter2::SetMotion;
  using CCharacter2::Show;
  using CCharacter2::GetShow;
  using CCharacter2::GetNowFrameWait;
  using CCharacter2::GetNowFrame;
  using CCharacter2::CheckMotionEnd;
  using CCharacter2::GetMotionStatus;
  using CCharacter2::Initialize;
  using CCharacter2::Copy;
  using CCharacter2::GetWaitToFrame;

  virtual ~CActionChara() {}

  // 0016B850
  virtual unkptr Draw() override;

  // 0016B940
  virtual unkptr DrawDirect() override;

  // 0016AB60
  virtual f32 GetCameraDist() override;

  // 0016AB00
  virtual void SetFarDist(f32 far_dist) override;

  // 0016AB30
  virtual void SetNearDist(f32 near_dist) override;

  //001739A0
  virtual void SetMotion(std::string key_name, sint i1) override;

  // 0016B800
  virtual void ResetMotion() override;

  // 0016AAD0
  virtual void SetFadeFlag(bool flag) override;

  // 0016BA70
  virtual unkptr DrawShadowDirect() override;

  // 00171E80
  virtual void Step() override;

  // 00172090
  virtual void ShadowStep() override;

  // 0016BAC0
  virtual void DrawEffect() override;

  // 0016ABA0
  virtual void Show(sint i1, sint i2);

  // 0016ABE0
  virtual void GetShow(std::string chara_name);

  // 0016B780
  virtual void SetMotion(std::string key_name, sint i1, sint i2);

  // 0016B420
  virtual f32 GetNowFrameWait(std::string key_name) const;

  // 0016B4A0
  virtual f32 GetNowFrame(std::string key_name) const;

  // 0016B520
  virtual bool CheckMotionEnd(std::string key_name) const;

  // 0016B5B0
  virtual ECharacterMotionStatus GetMotionStatus(std::string key_name);

  // 0016BB00
  virtual void StepEffect();

  // if you call either of these instead of creating/using a constructor/copy constructor I'll keelhaul you
  // 001720E0
  virtual void Initialize(mgCMemory* memory);

  // 00172380
  virtual void Copy(CActionChara& other, mgCMemory* memory);

  // 0016A140
  void ResetAccele();

  // 0016A160
  void ResetAction();

  // 0016A220
  void ResetScript();

  // 0016A4C0
  void CheckRunEvent();

  // 0016A4E0
  void SetMaskFlag(u32 mask, bool active);

  // 0016A510
  unkptr EntryObject(std::string frame_name, ssize i);

  // 0016A5C0
  void CalcCollision();

  // 0016A620
  unkptr EntryBodyCol(ssize i, f32 f);

  // 0016A6B0
  COLLISION_INFO* EntryDamage2(std::string s1, std::string s2, std::string s3, f32 f1, std::string s4, f32 f2, f32 f3, std::string s5);
  
  // 0016A850
  COLLISION_INFO* EntryDamage2(mgCFrame* frame1, mgCFrame* frame2, std::string s3, f32 f1, std::string s4, f32 f2, f32 f3, std::string s5);

  // 0016A9B0
  void AllDeleteDamage();

  // 0016AA30
  SW_EFFECT* GetSwEffectPtr();

  // 0016AA70
  void SetSoundInfoCopy();

  // 0016AC60
  bool CheckKeri(std::string frame_name, bool b);

  // 0016AD30
  bool CheckEnemyCatch(std::string frame_name);

  // 0016AF40
  void ThrowItemObject();

  // 0016B020
  sint UsedItemAction();

  // 0016B1C0
  void EntryThrowItem();

  // 0016B3C0
  void RemoveThrowItem();

  // 0016B630
  f32 GetWaitToFrame(std::string chara_name);

  // 0016BC90
  CActionChara* SearchChara(std::string chara_name);

  // 0016BCF0
  mgCFrame* SearchObject(std::string frame_name);

  // 0016BD60
  void ResetParent();

  // 0016BD90
  bool SetRef(CActionChara* parent_chara, std::string frame_name);

  // 0016BE50
  f32 GetTargetDist(CScene* scene);

  // 0016BEE0
  //void CollisionCheck(const vec3& v1, const vec3& v2, const vec3& v3);

  // 0016C7A0
  // "RockOn"
  void LockOn();

  // 0016C990
  void HumanMoveIF();

  // 0016D560
  // "HumanShrowMoveIF"
  void HumanThrowMoveIF();

  // 0016D8E0
  // "HumanTameMoveIF"
  void HumanChargeUpMoveIF();

  // 0016DAA0
  void HumanGunMoveIF(std::string key_name1, std::string key_name2);

  // 0016DD80
  void RoboWalkMoveIF(sint i);

  // 0016E2A0
  void RoboTankMoveIF(sint i);

  // 0016E9F0
  void RoboBikeMoveIF(sint i);

  // 0016F330
  void RoboAirMoveIF(sint i1, sint i2);

  // 0016FA30
  void MonsterMoveIF();

  // 00170730
  bool CheckDamage();

  // 001710C0
  void LoadActionFile(char* c, int i, mgCMemory* memory);

  // 00171160
  void InitScript();

  // 00171210
  void RunScript(CScene* scene, RUN_SCRIPT_ENV* script_env);

  // 001719C0
  // "CheckReleaseTimming"
  s16 CheckReleaseTiming(sint i);

  // 001719F0
  void StepParam();

  // 678
  CActionChara* m_chara_parent{};
  // 690
  vec3 m_front_vec{ };
  // 6A4
  EAttackType m_attack_type{};
  // 6A8
  EMoveType m_move_type{};
  // 712
  s16 m_prog{ 0 };
  // 71C
  s16 m_hand_obj{};
  // 768
  bool m_invincible_flag{ false };
  // 76C
  bool m_menu_flag{ false };
  // 794
  f32 m_move_speed{ DEFAULT_CHARACTER_MOVE_SPEED };
  // 7E4
  std::array<SW_EFFECT, 9> m_unk_field_7E4{};
  // A20
  std::array<COLLISION_INFO, 11> m_unk_field_A20{};
  // BF0
  bool m_guard_flag{ false };
  // F50
  f32 m_unk_field_F50{};
  // F54
  f32 m_unk_field_F54{};
  // F58
  f32 m_unk_field_F58{};
  // F5C
  s32 m_unk_field_F5C{};

  // Took a bit to find but the aligned size is 0x1030
};

// 00378294
//extern CScene* nowScene;