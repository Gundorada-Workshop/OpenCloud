#pragma once
#include "common/debug.h"
#include "common/types.h"

#include "dc2/gamedata.h"
#include "dc2/inventmn.h"

// ~ 00196C20 - 001A2080

// TODO THIS FILE
struct MOS_CHANGE_PARAM {};

enum class ECharacterID
{
  Max = 0,
  Monica = 1,
  Steve = 2,
  MonsterTransform = 3,
};

enum class ENPCID : s16
{
  
};

enum class EMonsterID : s16
{

};

enum class ESpecialStatus : s32
{

};

enum class EMagicSwordElement : s16
{
  Uninitialized = -1,
  Invalid = -1,
  COUNT = 4,
};

enum class EBattleCharaType : s16
{
  Uninitialized = -1,
  Human = 0,
  MonsterTransform = 1,
  Ridepod = 2,
};

enum class ECharaStatusAttribute : u16
{

};

struct MOS_HENGE_PARAM
{
  // 0
  s16 m_id{};
  // 2
  s16 m_unk_field_2{};
  // 4
  s16 m_unk_field_4{};
  // 8
  std::array<const char*, 5> m_unk_field_8{};
};

struct COMMON_GAGE
{
  // 0
  f32 m_max{};
  // 4
  f32 m_current{};

  // 00196C90
  bool CheckFill();
  // 00196CC0
  f32 GetRate();
  // 00196D00
  void SetFillRate(f32 rate);
  // 00196D10
  void AddPoint(f32 delta);
  // 00196D60
  void AddRate(f32 delta);
};

// 00196DB0
f32 GetCommonGageRate(COMMON_GAGE* gage);

enum class EUsedItemType;

enum class ECommonItemData;

struct SGameDataUsedAttachSub
{
  // 8
  COMMON_GAGE m_unk_field_8;
  // 18
  s16 m_level{ 0 };
  // 20
  std::array<char, 0x20> m_name{ 0 };
};

struct SGameDataUsedWeaponSub
{
  // 0
  COMMON_GAGE m_whp_gage{};
  // 8
  COMMON_GAGE m_abs_gage{};
  // 10
  s16 m_level{ 0 };
  // 33
  std::array<char, 0x20> m_name{ 0 };
};

struct SGameDataUsedRobopartSub
{
  // 8
  COMMON_GAGE m_whp_gage{};
  // 2C
  std::array<char, 0x20> m_name{ 0 };
};

struct SGameDataUsedFishSub
{
  // 0
  // BUG: Seems to be 20 decimal (14h) chars instead of 20h chars in original game
  std::array<char, 0x20> m_name{ 0 };
  // 20
  s32 m_hp{ 0 };

  // ?

  // 30
  s32 m_unk_field_30{ 0 };
};

union UGameDataUsedSub
{
  SGameDataUsedAttachSub m_attach;
  SGameDataUsedWeaponSub m_weapon;
  SGameDataUsedRobopartSub m_robopart;
  SGameDataUsedFishSub m_fish;
};

class CGameDataUsed
{
public:
  // 00197090
  CGameDataUsed();
  // 001970c0
  void Initialize();
  // 001971D0
  s16 GetLevel() const;
  // 00197480
  s16 AddFishHp(s16 delta);
  // 00197630
  void SetName(const char* name);
  // 001985A0
  bool IsLevelUp() const;
  // 00198620
  void LevelUp();
  // 001992B0
  bool IsFishingRod();
  // 00199830
  void TimeCheck(s32 delta);

  // 0
  EUsedItemType m_type{ static_cast<EUsedItemType>(0) };
  // 2
  ECommonItemData m_common_index{};
  // 4
  s8 m_unk_field_4{};
  // 5
  bool m_unk_field_5{};

  // 10
  UGameDataUsedSub m_sub_data = {};

  // SIZE 0x6C, all initialized to 0
};

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

class CFishingRecord
{
public:
  // 0019AE10
  CFishingRecord();
};

class CFishingTournament
{
public:
  // 0019AF30
  void Initialize();
};

struct SMonsterBadgeData
{
  COMMON_GAGE m_whp_gage;

  // SIZE 0xBC
};

class CMonsterBox
{
public:
  // 0019ab50
  void Initialize();

  // 0019AC40
  SMonsterBadgeData* GetMonsterBadgeData(EMonsterID index);
  SMonsterBadgeData* GetMonsterBajjiData(EMonsterID index);

  // 0
  std::array<SMonsterBadgeData, 0x40> m_monster_badge_data;
};

struct SCharaData
{
  // Contains information about Max's/Monica's equipped items

  // 0
  COMMON_GAGE m_unk_field_0;

  // ?

  // 2C
  std::array<CGameDataUsed, 3> m_active_item_info;
  // 170
  std::array<CGameDataUsed, 5> m_equip_table;
  // SIZE 0x38C
};

class CUserDataManager
{
public:
  // 001943B0
  CUserDataManager();

  // 0019b160
  void Initialize();

  // 0019B490
  SCharaData* GetCharaDataPtr(ECharacterID chara_id);

  // 0019B620
  COMMON_GAGE* GetWHpGage(ECharacterID chara_id, ssize gage_index);

  // 0019B6F0
  COMMON_GAGE* GetAbsGage(ECharacterID chara_id, ssize gage_index);

  // 0019B7C0
  s32 AddWhp(ECharacterID chara_id, ssize gage_index, s32 delta);

  // 0019B820
  s32 GetWhp(ECharacterID chara_id, ssize gage_index, s32* max_dest);

  // 0019B880
  s32 AddAbs(ECharacterID chara_id, ssize gage_index, s32 delta);

  // 0019b9a0
  void JoinPartyMember(s32 chara);

  // 0019baa0
  void EnableCharaChange(s32 chara);

  // 0019c420
  void SetRoboName(const char* name);

  // 0019c450
  const char* GetRoboNameDefault();

  // 0019C500
  float AddRoboAbs(f32 delta);

  // 0019C560
  float GetRoboAbs();

  // 0
  std::array<CGameDataUsed, 150> m_unk_field_0{};
  // 3F48
  std::array<SCharaData, 2> m_chara_data{};

  // ?

  // 468C
  f32 m_robo_abs{};
  // 4690
  std::array<CGameDataUsed, 4> m_robopart_data{};

  // ?
  
  // 4880
  std::array<CGameDataUsed, 2> m_unk_field_4880{};
  // 4958
  CFishAquarium m_fish_aquarium{};

  // ?

  // 4EB0
  CMonsterBox m_monster_box{};

  // ??

  // 7F30
  CInventUserData m_invent_user_data{};

  // ??

  // 44D90
  s16 m_unk_field_44D90{};
  // 44D92
  s16 m_unk_field_44D92{};
  // 44D94
  s16 m_unk_field_44D94{};
  // 44D96
  s16 m_unk_field_44D96{};
  // 44D98
  EMonsterID m_monster_id{};
  // 44D9A
  s16 m_unk_field_44D9A{};
  // 44D9C
  s16 m_unk_field_44D9C{};
  // 44D9E
  s16 m_unk_field_44D9E{};
  // 44DA0
  s16 m_unk_field_44DA0{};

  // ?

  // 451E8
  CFishingTournament m_fishing_tournament{};
  // 45258
  CFishingRecord m_fishing_record{};

  // SIZE 0x457A0
};

struct SBattleCharaInfoParamUnk1
{
  // 0
  s16 m_unk_field_0{};
  // 2
  // ?
  // 4
  s16 m_unk_field_4{};

  // ?
  

  // 14
  ESpecialStatus m_special_status{};
  // 18
  s16 m_pallet_no{};
  // SIZE 0x1C
};

struct SBattleCharaInfoParam
{
public:
  // 0
  std::array<SBattleCharaInfoParamUnk1, 2> m_unk_field_0{};
  // 38
  s16 m_defence_vol{};

  // SIZE 0x40
};

class CBattleCharaInfo
{
private:
  // 4
  ENPCID m_now_npc{};
  // 6
  EBattleCharaType m_battle_chara_type{ EBattleCharaType::Uninitialized };
  // 8
  SCharaData* m_chara_data{ nullptr };
  // C
  f32 m_unk_field_C{};
  // 10
  f32 m_unk_field_10{};
  // 14
  s16 m_unk_field_14{};
  // 16
  s16 m_unk_field_16{};
  // 18
  EMagicSwordElement m_magic_sword_element{ EMagicSwordElement::Uninitialized };
  // 1A
  s16 m_magic_sword_counter_now{};
  // 1C
  s16 m_unk_field_1C{};
  // 1E
  s16 m_unk_field_1E{};
  // 20
  s16 m_unk_field_20{};
  // 22
  s16 m_unk_field_22{};
  // 24
  s16 m_unk_field_24{};
  // 26
  s16 m_unk_field_26{};
  // 28
  s16 m_unk_field_28{};
  // 74
  COMMON_GAGE* m_hp_gage{ nullptr };
  // 78
  f32 m_unk_field_78{};
  // 7C
  f32 m_unk_field_7C{ 0.0f };
  // 80
  f32 m_unk_field_80{ -1.0f };
  // 84
  f32 m_unk_field_84{ -1.0f };
  // 88
  f32 m_unk_field_88{};
  // 8C
  f32 m_unk_field_8C{};
public:
  // 0019EFD0
  CGameDataUsed* GetEquipTablePtr(usize index);
  // 0019F010
  void SetChrNo(ECharacterID chara_id);
  // 0019F210
  EMonsterID GetMonsterID();
  // 0019F250
  ENPCID GetNowNPC();
  // 0019F260
  // NOTE: This fn takes an unused argument, so I removed it here.
  bool UseNPCPoint();
  // 0019F380
  CGameDataUsed* GetActiveItemInfo(usize index);
  // 0019F3B0
  bool UseActiveItem(CGameDataUsed* active_item);
  // 0019F480
  ESpecialStatus GetSpecialStatus(usize index);
  // 0019F4D0
  s16 GetPalletNo(usize index);
  // 0019F520
  void RefreshParameter();
  // 0019F890
  COMMON_GAGE* GetNowAccessWHp(usize weapon_index) const;
  // 0019F910
  COMMON_GAGE* GetNowAccessAbs(usize weapon_index) const;
  // 0019F990
  f32 AddWhp(usize weapon_index, f32 delta) const;
  // 0019FA10
  // NOTE: originally void return, but I changed this to be reflective
  // so it's known that the values in values_dest are valid if needed
  bool GetNowWhp(usize weapon_index, std::array<s32, 2>& values_dest) const;
  // 0019FA60
  s32 GetWhpNowVol(usize weapon_index) const;
  // 0019FAA0
  void SetMagicSwordPow(EMagicSwordElement element, s16 i1);
  // 0019FB60
  EMagicSwordElement GetMagicSwordElem();
  // 0019FB80
  s32 GetMagicSwordPow();
  // 0019FC50
  s16 GetMagicSwordCounterNow();
  // 0019FC80
  s16 GetMagicSwordCounterMax();
  // 0019FD00
  void ClearMagicSwordPow();
  // 0019FD30
  f32 AddAbs(usize weapon_index, f32 delta, bool* has_leveled_up);
  // 0019FEE0
  bool AddAbsRate(usize weapon_index, f32 delta, bool* has_leveled_up);
  // 0019FFE0
  // NOTE: originally void return, but I changed this to be reflective
  // so it's known that the values in values_dest are valid if needed
  bool GetNowAbs(usize weapon_index, std::array<s32, 2>& values_dest) const;
  // 001A0030
  bool LevelUpWeapon(CGameDataUsed* weapon);
  // 001A00A0
  s32 GetDefenceVol() const;
  // 001A00B0
  f32 AddHp_Point(f32 f1, f32 f2);
  // 001A01B0
  f32 AddHp_Rate(f32 f1, s32 i1, f32 f2);
  // 001A0370
  void SetHpRate(f32 rate) const;
  // 001A03A0
  s32 GetMaxHp_i() const;
  // 001A03E0
  s32 GetNowHp_i() const;
  // 001A0420
  ECharaStatusAttribute SetAttr(ECharaStatusAttribute attr, bool b);
  // 001A0490
  ECharaStatusAttribute SetAttrVol(ECharaStatusAttribute attr, bool b);
  // 001A0500
  ECharaStatusAttribute GetAttr();
  // 001A0550
  void ForceSet();
  // 001A08D0
  ECharaStatusAttribute StatusParamStep(s32* p);
  // 001A0C60
  void Step();

  // 0
  ECharacterID m_chara_id{ ECharacterID::Max };
  // 2
  s16 m_unk_field_2{};
  // 2C
  CGameDataUsed* m_active_item_info{ nullptr };
  // 30
  CGameDataUsed* m_equip_table{ nullptr };
  // 34
  SBattleCharaInfoParam m_param{};

  // Size 0x90
};

// 0019A890
MOS_HENGE_PARAM* GetMonsterHengeParam(EMonsterID index);

// 001A0EA0
CBattleCharaInfo* GetBattleCharaInfo();