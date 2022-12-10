#pragma once
#include "common/debug.h"
#include "common/types.h"

#include "dc2/gamedata.h"
#include "dc2/inventmn.h"

// ~ 00196130 - 001A2080

// TODO THIS FILE
struct MOS_CHANGE_PARAM {};

enum class EItemCmd
{
  _0 = 0,
  _1 = 1,
  _2 = 2,
  _3 = 3,
  _4 = 4,
  _5 = 5,
  _6 = 6,
  _7 = 7,
  _8 = 8,
  _9 = 9,
  _10 = 10,
  _11 = 11,
  _12 = 12,
  _13 = 13,
  _14 = 14,
  _15 = 15,
  _16 = 16,
  _17 = 17,
  _18 = 18,
  _19 = 19,
  _20 = 20,
  _21 = 21,
  _22 = 22,
  _23 = 23,
  _24 = 24,
  _25 = 25,
  _26 = 26,
  _27 = 27,
  _28 = 28,
  _29 = 29,
  _30 = 30,
  _31 = 31,
};

enum class ECharacterID
{
  Invalid = -1,
  Max = 0,
  Monica = 1,
  Ridepod = 2,
  Monster = 3,
};

enum class ENPCID : s16;

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
  bool CheckFill() const;
  // 00196CC0
  f32 GetRate() const;
  // 00196D00
  void SetFillRate(f32 rate);
  // 00196D10
  void AddPoint(f32 delta);
  // 00196D60
  void AddRate(f32 delta);
};

// 00196DB0
f32 GetCommonGageRate(COMMON_GAGE* gage);

struct BREEDFISH_USED
{
public:
  // 0
  // BUG: Seems to be 20 decimal (14h) chars instead of 20h chars in original game
  std::array<char, 0x20> m_name{ 0 };
  // 20
  s32 m_hp{ 0 };

  // 26
  u16 m_unk_field_26;
  // 28
  u16 m_unk_field_28;
  // 2A
  u16 m_unk_field_2A;
  // 2C
  u16 m_unk_field_2C;
  // 2E
  u16 m_unk_field_2E;

  // 00196DE0
  u32 CalcBreedFishParam();
};

enum class EUsedItemType;

enum class ECommonItemData;

struct SGameDataUsedItem_MiscSub
{
  // 0
  s16 m_stack_num{};
};

struct SGameDataUsedClothingSub
{
  // 0
  s16 m_stack_num{};
};

struct SGameDataUsedAttachSub
{
  // 0
  s8 m_unk_field_0;
  // 1
  s8 m_unk_field_1;
  // 2
  s16 m_unk_field_2;
  // 4
  s16 m_unk_field_4;
  // 6
  std::array<s16, 8> m_unk_field_6;
  // 16
  ECommonItemData m_spectrumized_item_id;
  // 18
  s16 m_level{ 0 };
  // 20
  std::array<char, 0x20> m_name{ 0 };

  // 3A (??? - is m_name erroneously short here?)
  s16 m_stack_num{};
};

struct SGameDataUsedWeaponSub
{
  // 0
  COMMON_GAGE m_whp_gage{};
  // 8
  COMMON_GAGE m_abs_gage{};
  // 10
  s16 m_level{ 0 };
  // 12
  s16 m_attack{};
  // 14
  s16 m_durable{};
  // 16
  std::array<s16, std::to_underlying(WeaponProperty::COUNT)> m_properties{};
  // 28
  s32 m_unk_field_28{};
  // 2C
  s16 m_fusion_point{};
  // 2E
  s16 m_unk_field_2E{};
  // 30
  s16 m_unk_field_30{};
  // 33
  std::array<char, 0x20> m_name{ 0 };
};

struct SGameDataUsedRobopartSub
{
  // 0
  COMMON_GAGE m_battery_gage{};
  // 8
  COMMON_GAGE m_whp_gage{};
  // 2C
  std::array<char, 0x20> m_name{ 0 };
};

struct SGameDataUsedFishSub
{
  // 0
  BREEDFISH_USED m_breed_fish{};

  // ?

  // 30
  s32 m_unk_field_30{ 0 };

  // 38
  u16 m_unk_field_38{};
};

struct SGameDataUsedGiftBoxSub
{
  // 0
  std::array<ECommonItemData, 3> m_contents{ ECommonItemData::Invalid };
};

union UGameDataUsedSub
{
  SGameDataUsedItem_MiscSub item_misc;
  SGameDataUsedClothingSub clothing;
  SGameDataUsedAttachSub attach;
  SGameDataUsedWeaponSub weapon;
  SGameDataUsedRobopartSub robopart;
  SGameDataUsedFishSub fish;
  SGameDataUsedGiftBoxSub gift_box;
};

class CGameDataUsed
{
private:
  COMMON_GAGE* GetWHpGage();
public:
  // 00197090
  CGameDataUsed();
  // 001970c0
  void Initialize();
  // 001970D0
  bool CheckTypeEnableStack() const;
  // 00197120
  std::string GetDataPath() const;
  // 00197130
  ECharacterID IsWhoEquip() const;
  // 001971D0
  s16 GetLevel() const;
  // 00197200
  s8 GetPaletteColor() const;
  // 00197250
  ECommonItemData GetSpectrumNo() const;
  // 00197270
  sint CheckStackRemain() const;
  // 001972E0
  sint GetNum() const;
  // 00197360
  u8 GetActiveSetNum() const;
  // 00197370
  s16 AddNum(sint delta, bool reset_if_empty);
  // 00197480
  sint GetUseCapacity() const;
  // 001974C0
  s16 AddFishHp(s16 delta);
  // 00197600
  u8 IsActiveSet() const;
  // 00197630
  void SetName(const char* name);
  // 00197DC0
  sint RemainFusion() const;
  // 00197DE0
  sint AddFusionPoint(sint delta);
  // 001980C0
  f32 GetWHp(sint* values_dest = nullptr);
  // 00198180
  bool IsRepair();
  // 00198270
  bool Repair(sint delta);
  // 001982F0
  // Returns the item ID used to repair this item
  ECommonItemData GetRepairItemNo() const;
  // 00198360
  bool IsEnableUseRepair(ECommonItemData item_id) const;
  // 00198390
  std::optional<WeaponAttackType> GetRoboInfoType() const;
  // 001993B0
  std::optional<u8> GetModelNo() const;
  // 00198400
  std::string GetRoboJointName() const;
  // 001984B0
  std::string GetRoboSoundFileName() const;
  // 00198550
  bool IsBroken();
  // 001985A0
  bool IsLevelUp() const;
  // 00198620
  void LevelUp();
  // 00198950
  bool IsTrush() const;
  // 001989D0
  bool IsSpectolTrans() const;
  // 00198FC0
  uint IsBuildUp(uint* total_possible_dest, ECommonItemData* buildup_item_ids_dest, bool* can_build_up_dest) const;
  // 001992B0
  bool IsFishingRod() const;
  // 001992E0
  std::optional<usize> GetActiveElem() const;
  // 00199340
  std::optional<WeaponAttackType> GetAttackType() const;
  // 001994E0
  void CheckParamLimit();
  // 00199830
  void TimeCheck(s32 delta);
  // 00199860
  ssize GetGiftBoxItemNum() const;
  // 001998B0
  ssize SetGiftBoxItem(ECommonItemData item_id, ssize index = -1);
  // 00199920
  ECommonItemData GetGiftBoxItemNo(ssize index) const;
  // 00199A50
  bool CopyDataWeapon(ECommonItemData item_id);

  // 0
  EUsedItemType m_type{ static_cast<EUsedItemType>(0) };
  // 2
  ECommonItemData m_common_index{};
  // 4
  ECommonItemDataType m_item_data_type{};
  // 5
  bool m_unk_field_5{};

  // 10
  UGameDataUsedSub as = {};

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
  unk m_unk_field_514;
  // 518 (8 bytes)
  unk m_unk_field_518;
  // 520 (8 bytes)
  unk m_unk_field_520;
  // 528
  unk m_unk_field_528;
  // 52C
  unk m_unk_field_52C;
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
  COMMON_GAGE m_chara_hp_gage;

  // ?

  // 2C
  std::array<CGameDataUsed, 3> m_active_item_info;
  // 170
  std::array<CGameDataUsed, 5> m_equip_table;
  // SIZE 0x38C
};

struct ROBO_DATA
{
  // ?

  // 20
  COMMON_GAGE m_chara_hp_gage{};
  
  // ?
  // 2C
  f32 m_abs{};
  // 30
  std::array<CGameDataUsed, 4> m_part_data{};

  // ?

  // SIZE 0x220
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

  // 0019B4C0
  COMMON_GAGE* GetCharaHpGage(ECharacterID chara_id);

  // 0019B510
  sint AddHp(ECharacterID chara_id, sint delta);

  // 0019B560
  f32 GetHp(ECharacterID chara_id);

  // 0019B5A0
  f32 AddHp_Rate(ECharacterID chara_id, f32 rate);

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

  // 0019EAF0
  s32 AddMoney(s32 delta);

  // 0
  std::array<CGameDataUsed, 150> m_inventory{};
  // 3F48
  std::array<SCharaData, 2> m_chara_data{};
  // 4660
  ROBO_DATA m_robo_data{};
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
  s32 m_money{};
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

// 00196130
usize ItemCmdMsgSet(EItemCmd cmd, s32* dest);

// 001961A0
usize GetMenuCommandMsg(ECommonItemData item_id, s32* dest);

// 00196520
bool CheckItemEquip(ECharacterID chara_id, ECommonItemData item_id);

// 001965C0
ECommonItemData SearchItemByName(const std::string name);

// 00196630
ECommonItemData GetRidePodCore(ssize index);

// 00196BE0
CUserDataManager* GetUserDataMan();

// 001993F0
std::optional<std::string> GetMainCharaModelName(ECharacterID chara_id, bool b);

// 0019A890
MOS_HENGE_PARAM* GetMonsterHengeParam(EMonsterID index);

// 001A0EA0
CBattleCharaInfo* GetBattleCharaInfo();