#pragma once
#include "common/debug.h"
#include "common/types.h"
#include "gamedata.h"
#include "inventmn.h"

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

namespace EUsedItemType
{
  enum EUsedItemType;
}

namespace ECommonItemData
{
  enum ECommonItemData : s16;
}

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
  s16 GetLevel();
  // 00197480
  s16 AddFishHp(s16 delta);
  // 00197630
  void SetName(const char* name);
  // 001992B0
  bool IsFishingRod();

  // 0
  EUsedItemType::EUsedItemType m_type{ static_cast<EUsedItemType::EUsedItemType>(0) };
  // 2
  ECommonItemData::ECommonItemData m_common_index;
  // 4
  s8 m_unk_field_4;
  // 5
  bool m_unk_field_5;

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
  SMonsterBadgeData* GetMonsterBadgeData(ssize index);
  SMonsterBadgeData* GetMonsterBajjiData(ssize index);

  // 0
  std::array<SMonsterBadgeData, 0x40> m_monster_badge_data;
};

struct SUserDataManagerUnkStruct1
{
  // ?

  // 2C
  std::array<CGameDataUsed, 3> m_unk_field_2C;
  // 170
  std::array<CGameDataUsed, 5> m_unk_field_170;
  // SIZE 0x38C
};

class CUserDataManager
{
public:
  // 001943B0
  CUserDataManager();

  // 0019b160
  void Initialize();

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
  std::array<CGameDataUsed, 150> m_unk_field_0;
  // 3F48
  std::array<SUserDataManagerUnkStruct1, 2> m_unk_field_3F48;

  // ?

  // 468C
  f32 m_robo_abs{};
  // 4690
  std::array<CGameDataUsed, 4> m_robopart_data;

  // ?
  
  // 4880
  std::array<CGameDataUsed, 2> m_unk_field_4880;
  // 4958
  CFishAquarium m_fish_aquarium;

  // ?

  // 4EB0
  CMonsterBox m_monster_box;

  // ??

  // 7F30
  CInventUserData m_invent_user_data;

  // ??

  // 44D90
  u16 m_unk_field_44D90;
  // 44D92
  u16 m_unk_field_44D92;
  // 44D94
  u16 m_unk_field_44D94;
  // 44D96
  u16 m_unk_field_44D96;
  // 44D98
  u16 m_unk_field_44D98;
  // 44D9A
  u16 m_unk_field_44D9A;
  // 44D9C
  u16 m_unk_field_44D9C;
  // 44D9E
  u16 m_unk_field_44D9E;
  // 44DA0
  u16 m_unk_field_44DA0;

  // ?

  // 451E8
  CFishingTournament m_fishing_tournament;
  // 45258
  CFishingRecord m_fishing_record;

  // SIZE 0x457A0
};

class CBattleCharaInfo
{
public:

  // 0
  s16 m_unk_field_0{ 0 };

  // ?

  // 6
  s16 m_unk_field_6{ -1 };
  // 8
  _UNKNOWN m_unk_field_8{ 0 };

  // ?

  // 30
  _UNKNOWN m_unk_field_30{ 0 };
  // 74
  _UNKNOWN m_unk_field_74{ 0 };

  // ?

  // 7C
  _UNKNOWN m_unk_field_7C{ 0 };
  // 80
  float m_unk_field_80{ -1.0f };
  // 84
  float m_unk_field_84{ -1.0f };

  // ?

  // Size 0x90
};

// 0019A890
MOS_HENGE_PARAM* GetMonsterHengeParam(ssize index);
