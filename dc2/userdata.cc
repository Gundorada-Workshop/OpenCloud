#include <string>
#include "common/debug.h"
#include "common/log.h"
#include "common/types.h"
#include "gamedata.h"
#include "userdata.h"

set_log_channel("userdata");

// 01E9B130
static CBattleCharaInfo BattleParameter{};

// 00196C90
bool COMMON_GAGE::CheckFill()
{
  log_trace("COMMON_GAGE::{}()", __func__);

  return m_max == m_current;
}

// 00196CC0
f32 COMMON_GAGE::GetRate()
{
  log_trace("COMMON_GAGE::{}()", __func__);

  if (m_max == 0.0f)
  {
    return 0.0f;
  }

  return m_current / m_max;
}

// 00196D00
void COMMON_GAGE::SetFillRate(f32 rate)
{
  log_trace("COMMON_GAGE::{}({})", __func__, rate);

  m_current = m_max * rate;
}

// 00196D10
void COMMON_GAGE::AddPoint(f32 delta)
{
  log_trace("COMMON_GAGE::{}({})", __func__, delta);

  m_current = std::clamp(m_current + delta, 0.0f, m_max);
}

// 00196D60
void COMMON_GAGE::AddRate(f32 delta)
{
  log_trace("COMMON_GAGE::{}({})", __func__, delta);

  m_current = std::clamp(m_current + (m_max * delta), 0.0f, m_max);
}

// 00196DB0
f32 GetCommonGageRate(COMMON_GAGE* gage)
{
  log_trace("{}({})", __func__, fmt::ptr(gage));

  if (gage == nullptr)
  {
    return 0.0f;
  }
  return gage->GetRate();
}

// 0019a160
void CFishAquarium::Initialize()
{
  log_trace("CFishAquarium::Initialize()");

  m_unk_field_0 = 0;
  m_unk_field_2 = 0;

  for (auto& game_data_used : m_unk_field_4)
  {
    game_data_used.Initialize();
  }

  for (auto& game_data_used : m_unk_field_28C)
  {
    game_data_used.Initialize();
  }

  for (auto& game_data_used : m_unk_field_43C)
  {
    game_data_used.Initialize();
  }

  m_unk_field_518 = 0;
  m_unk_field_520 = 0;
  m_unk_field_528 = 0;
  m_unk_field_52C = 0;
}

// 00197090
CGameDataUsed::CGameDataUsed()
{
  log_trace("CGameDataUsed::CGameDataUsed()");

  Initialize();
}
// 001970c0
void CGameDataUsed::Initialize()
{
  log_trace("CGameDataUsed::Initialize()");

  memset(this, 0, sizeof(this));
}

// 001971D0
s16 CGameDataUsed::GetLevel()
{
  log_trace("CGameDataUsed::{}()", __func__);

  switch (m_type)
  {
    case EUsedItemType::Weapon:
      return m_sub_data.m_weapon.m_level;
    case EUsedItemType::Attach:
      return m_sub_data.m_attach.m_level;
    default:
      return 0;
  }
}

// 00197480
s16 CGameDataUsed::AddFishHp(s16 delta)
{
  log_trace("CGameDataUsed::{}({})", __func__, delta);

  if (m_type != EUsedItemType::Fish)
  {
    return 0;
  }

  m_sub_data.m_fish.m_hp = std::clamp(m_sub_data.m_fish.m_hp + delta, 0, 100);
  return m_sub_data.m_fish.m_hp;
}

// 00197630
void CGameDataUsed::SetName(const char* name)
{
  log_trace("CGameDataUsed::{}({})", __func__, name);

  std::array<char, 0x20>* name_buf = nullptr;

  switch (m_type)
  {
    case EUsedItemType::Attach:
      name_buf = &m_sub_data.m_fish.m_name;
      break;
    case EUsedItemType::Weapon:
      name_buf = &m_sub_data.m_weapon.m_name;
      break;
    case EUsedItemType::_5:
      name_buf = &m_sub_data.m_5.m_name;
      break;
    case EUsedItemType::Fish:
      name_buf = &m_sub_data.m_fish.m_name;
      break;
  }

  if (name_buf == nullptr)
  {
    return;
  }

  if (strlen(name) >= 0x20)
  {
    return;
  }

  strcpy_s(name_buf->data(), name_buf->size(), name);
  m_unk_field_5 = strcmp(GetItemMessage(m_common_index), name_buf->data()) != 0;
}

// 001992B0
bool CGameDataUsed::IsFishingRod()
{
  log_trace("CGameDataUsed::{}()", __func__);

  return m_common_index == ECommonItemData::FishingRod0 || \
    m_common_index == ECommonItemData::FishingRod1;
}

// 0019AE10
CFishingRecord::CFishingRecord()
{
  log_trace("CFishingRecord::CFishingRecord()");

  memset(this, 0, sizeof(this));
}

// 0019AF30
void CFishingTournament::Initialize()
{
  log_trace("CFishingTournament::Initialize()");

  memset(this, 0, sizeof(this));
}

// 001943B0
CUserDataManager::CUserDataManager()
{
  log_trace("CUserDataManager::CUserDataManager()");

  for (auto& game_data_used : m_unk_field_0)
  {
    new (&game_data_used) CGameDataUsed;
  }

  for (auto& unk_struct : m_unk_field_3F48)
  {
    for (auto& game_data_used : unk_struct.m_unk_field_2C)
    {
      new (&game_data_used) CGameDataUsed;
    }
    for (auto& game_data_used : unk_struct.m_unk_field_170)
    {
      new (&game_data_used) CGameDataUsed;
    }
  }

  for (auto& game_data_used : m_unk_field_4690)
  {
    new (&game_data_used) CGameDataUsed;
  }

  for (auto& game_data_used : m_unk_field_4880)
  {
    new (&game_data_used) CGameDataUsed;
  }

  for (auto& game_data_used : m_fish_aquarium.m_unk_field_4)
  {
    new (&game_data_used) CGameDataUsed;
  }

  for (auto& game_data_used : m_fish_aquarium.m_unk_field_28C)
  {
    new (&game_data_used) CGameDataUsed;
  }

  for (auto& game_data_used : m_fish_aquarium.m_unk_field_43C)
  {
    new (&game_data_used) CGameDataUsed;
  }

  m_fish_aquarium.Initialize();
  m_invent_user_data.Initialize();
  m_fishing_tournament.Initialize();
  new (&m_fishing_record) CFishingRecord;
}
// 0019B620
COMMON_GAGE* CUserDataManager::GetWHpGage(ECharacterID chara_id, ssize gage_index)
{
  log_trace("CUserDataManager::{}({}, {})", __func__, std::to_underlying(chara_id), gage_index);

  if (chara_id == ECharacterID::Steve)
  {
    todo;
  }

  return nullptr;
}

// 0019B6F0
COMMON_GAGE* CUserDataManager::GetAbsGage(ECharacterID chara_id, ssize gage_index)
{
  log_trace("CUserDataManager::{}({}, {})", __func__, std::to_underlying(chara_id), gage_index);

  todo;
  return nullptr;
}

// 0019B7C0
s32 CUserDataManager::AddWhp(ECharacterID chara_id, ssize gage_index, s32 delta)
{
  log_trace("CUserDataManager::{}({}, {}, {})", __func__, std::to_underlying(chara_id), gage_index, delta);

  auto gage = GetWHpGage(chara_id, gage_index);
  if (gage == nullptr)
  {
    return 0;
  }

  gage->AddPoint(static_cast<f32>(delta));
  return static_cast<s32>(gage->m_current);
}

// 0019B820
s32 CUserDataManager::GetWhp(ECharacterID chara_id, ssize gage_index, s32* max_dest)
{
  log_trace("CUserDataManager::{}({}, {}, {})", __func__, std::to_underlying(chara_id), gage_index, fmt::ptr(max_dest));

  auto gage = GetWHpGage(chara_id, gage_index);
  if (gage == nullptr)
  {
    // BUG: Original game doesn't write to the max value in this case
    *max_dest = 0;
    return 0;
  }

  *max_dest = static_cast<s32>(gage->m_max);
  return static_cast<s32>(gage->m_current);
}

// 0019B880
s32 CUserDataManager::AddAbs(ECharacterID chara_id, ssize gage_index, s32 delta)
{
  log_trace("CUserDataManager::{}({}, {}, {})", __func__, std::to_underlying(chara_id), gage_index, delta);

  if (chara_id == ECharacterID::Steve)
  {
    // Ridepod
    AddRoboAbs(static_cast<f32>(delta));
    return static_cast<s32>(GetRoboAbs());
  }

  // Human characters
  COMMON_GAGE* gage = GetAbsGage(chara_id, gage_index);
  if (gage == nullptr)
  {
    return 0;
  }

  gage->AddPoint(delta);
  return static_cast<s32>(gage->m_current);
}

// 0019C500
float CUserDataManager::AddRoboAbs(f32 delta)
{
  log_trace("CUserDataManager::{}({})", __func__, delta);

  m_robo_abs = std::clamp(m_robo_abs + delta, 0.0f, 99999.0f);
  return m_robo_abs;
}

// 0019C560
float CUserDataManager::GetRoboAbs()
{
  log_trace("CUserDataManager::{}()", __func__);

  return m_robo_abs;
}

// 0019B160
void CUserDataManager::Initialize()
{
  log_trace("CUserDataManager::Initialize()");

  memset(this, 0, sizeof(this));

  todo;
}

// 0019A890
MOS_HENGE_PARAM* GetMonsterHengeParam(ssize index)
{
  // 00335B90
  // FIXME: Magic numbers?
  static std::array<MOS_HENGE_PARAM, 57> mos_henge_param = {
    0, 8, 4, "f201a", nullptr, nullptr, nullptr, nullptr,
    1, 22, 12, "f201a", nullptr, nullptr, nullptr, nullptr,
    2, 64, 24, "f201a", nullptr, nullptr, nullptr, nullptr,
    3, 96, 42, "f201a", nullptr, nullptr, nullptr, nullptr,
    8, 7, 3, "f203a", "毒液L", "毒液H", nullptr, nullptr,
    9, 23, 11, "f203a", "毒液L", "毒液H", nullptr, nullptr,
    10, 60, 20, "f203a", "毒液L", "毒液H", nullptr, nullptr,
    11, 95, 41, "f203a", "毒液L", "毒液H", nullptr, nullptr,
    22, 60, 20, "f206a", "fox_銃弾", "マズルフラッシュH", nullptr, nullptr,
    23, 88, 39, "f206a", "fox_銃弾", "マズルフラッシュH", nullptr, nullptr,
    24, 8, 3, "f207a", nullptr, nullptr, nullptr, nullptr,
    25, 22, 10, "f207a", nullptr, nullptr, nullptr, nullptr,
    26, 64, 21, "f207a", nullptr, nullptr, nullptr, nullptr,
    27, 96, 39, "f207a", nullptr, nullptr, nullptr, nullptr,
    44, 7, 3, "f213a", "火弾Ｌ３", "火弾Ｈ", nullptr, nullptr,
    45, 23, 10, "f213a", "風弾Ｌ２", "風弾Ｈ", nullptr, nullptr,
    46, 60, 21, "f213a", "氷弾Ｌ２", "氷弾Ｈ", nullptr, nullptr,
    47, 95, 39, "f213a", "雷弾Ｌ２", "雷弾Ｈ", nullptr, nullptr,
    52, 9, 4, "f216a", "ヒマーラ回転攻撃", "ねばねばＬ", "ねばねばＨ", nullptr,
    53, 23, 12, "f216a", "ヒマーラ回転攻撃", "ねばねばＬ", "ねばねばＨ", nullptr,
    54, 65, 24, "f216a", "ヒマーラ回転攻撃", "ねばねばＬ", "ねばねばＨ", nullptr,
    55, 99, 42, "f216a", "ヒマーラ回転攻撃", "ねばねばＬ", "ねばねばＨ", nullptr,
    72, 7, 3, "f221a", "呪い弾Ｆ", "呪い弾Ｌ", "呪い弾Ｈ", nullptr,
    73, 23, 11, "f221a", "呪い弾Ｆ", "呪い弾Ｌ", "呪い弾Ｈ", nullptr,
    74, 60, 23, "f221a", "呪い弾Ｆ", "呪い弾Ｌ", "呪い弾Ｈ", nullptr,
    75, 95, 41, "f221a", "呪い弾Ｆ", "呪い弾Ｌ", "呪い弾Ｈ", nullptr,
    102, 59, 30, "f10a", "かぼちゃ爆弾", "Ｍ小爆発", nullptr, nullptr,
    103, 88, 50, "f10a", "かぼちゃ爆弾", "Ｍ小爆発", nullptr, nullptr,
    112, 80, 26, "f114a", "火弾Ｆ", "火弾Ｌ３", nullptr, nullptr,
    116, 44, 22, "f114a", "氷弾Ｆ", "氷弾Ｌ２", "氷弾Ｈ", nullptr,
    120, 55, 24, "f114a", "雷弾Ｆ", "雷弾Ｌ２", "雷弾Ｈ", nullptr,
    124, 33, 20, "f114a", "風弾Ｆ", "風弾Ｌ２", "風弾Ｈ", nullptr,
    128, 75, 28, "f114a", "聖弾Ｆ", "聖弾Ｌ２", "聖弾Ｈ", nullptr,
    136, 30, 12, "f06a", nullptr, nullptr, nullptr, nullptr,
    137, 70, 24, "f06a", nullptr, nullptr, nullptr, nullptr,
    139, 100, 34, "f06a", nullptr, nullptr, nullptr, nullptr,
    150, 60, 23, "f24a", "ねばねばＬ２", "ねばねばＨ", nullptr, nullptr,
    151, 95, 41, "f24a", "ねばねばＬ２", "ねばねばＨ", nullptr, nullptr,
    154, 55, 30, "f26a", "石化弾Ｌ", "ねばねばＨ", nullptr, nullptr,
    155, 88, 42, "f26a", "石化弾Ｌ", "ねばねばＨ", nullptr, nullptr,
    166, 65, 40, "f05a", nullptr, nullptr, nullptr, nullptr,
    167, 85, 60, "f05a", nullptr, nullptr, nullptr, nullptr,
    176, 7, 3, "f03a", nullptr, nullptr, nullptr, nullptr,
    177, 23, 11, "f03a", nullptr, nullptr, nullptr, nullptr,
    180, 60, 23, "f03a", nullptr, nullptr, nullptr, nullptr,
    183, 95, 41, "f03a", nullptr, nullptr, nullptr, nullptr,
    186, 61, 25, "f03a", nullptr, nullptr, nullptr, nullptr,
    187, 89, 38, "f03a", nullptr, nullptr, nullptr, nullptr,
    220, 8, 3, "f49a", "ボンバヘ自爆", nullptr, nullptr, nullptr,
    221, 22, 10, "f49a", "ボンバヘ自爆", nullptr, nullptr, nullptr,
    222, 64, 21, "f49a", "ボンバヘ自爆", nullptr, nullptr, nullptr,
    223, 96, 39, "f49a", "ボンバヘ自爆", nullptr, nullptr, nullptr,
    224, 36, 20, "f45a", nullptr, nullptr, nullptr, nullptr,
    228, 57, 24, "f45a", nullptr, nullptr, nullptr, nullptr,
    232, 66, 40, "f45a", nullptr, nullptr, nullptr, nullptr,
    236, 45, 22, "f45a", nullptr, nullptr, nullptr, nullptr,
    240, 80, 20, "f45a", nullptr, nullptr, nullptr, nullptr,
  };

  for (int i = 0; i < mos_henge_param.size(); ++i)
  {
    if (mos_henge_param[i].m_id == index)
    {
      return &mos_henge_param[i];
    }
  }
  return nullptr;
}

SMonsterBadgeData* CMonsterBox::GetMonsterBajjiData(ssize index)
{
  log_warn("Please use CMonsterBox::GetMonsterBadgeData instead of CMonsterBox::GetMonsterBajjiData");
  return GetMonsterBadgeData(index);
}

// 0019AC40
SMonsterBadgeData* CMonsterBox::GetMonsterBadgeData(ssize index)
{
  log_trace("CMonsterBox::{}({})", __func__, index);

  // BUG: last item of array is not accessible 
  if (index <= 0 || index >= m_monster_badge_data.size())
  {
    return nullptr;
  }

  return &m_monster_badge_data[index - 1];
}