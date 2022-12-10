#include <string>

#include "common/constants.h"
#include "common/debug.h"
#include "common/log.h"
#include "common/types.h"

#include "dc2/gamedata.h"
#include "dc2/mainloop.h"
#include "dc2/menumain.h"
#include "dc2/userdata.h"

set_log_channel("userdata");

// 01E9B130
static CBattleCharaInfo BattleParameter{};

// 00196130
usize ItemCmdMsgSet(EItemCmd cmd, s32* dest)
{
  log_trace("{}({}, {})", __func__, std::to_underlying(cmd), fmt::ptr(dest));

  // 00335A70
  static s8 ItemCmdMsgTbl[][8] = {
    2,  3,  4,  9,  23, 26, 1,  -1,
    9,  3,  1,  -1, 0,  0,  0,  0,
    10, 9,  26, 1,  -1, 0,  0,  0,
    5,  9,  1,  -1, 0,  0,  0,  0,
    30, 3,  1,  -1, 0,  0,  0,  0,
    2,  3,  9,  1,  -1, 0,  0,  0,
    3,  26, 34, -1, 0,  0,  0,  0,
    2,  9,  1,  -1, 0,  0,  0,  0,
    11, -1, 0,  0,  0,  0,  0,  0,
    12, -1, 0,  0,  0,  0,  0,  0,
    13, 5,  1,  -1, 0,  0,  0,  0,
    14, 45, 42, 9,  26, 1,  -1, 0,
    19, 5,  9,  1,  -1, 0,  0,  0,
    2,  3,  46, 26, 1,  -1, 0,  0,
    25, 9,  1,  -1, -1, 0,  0,  0,
    10, 22, 9,  26, 1,  -1, 0,  0,
    20, 5,  9,  1,  -1, 0,  0,  0,
    15, -1, 0,  0,  0,  0,  0,  0,
    16, -1, 0,  0,  0,  0,  0,  0,
    15, 16, -1, 0,  0,  0,  0,  0,
    29, -1, 0,  0,  0,  0,  0,  0,
    10, 3,  4,  9,  26, 1,  -1, 0,
    22, 9,  1,  -1, 0,  0,  0,  0,
    9,  1,  -1, 0,  0,  0,  0,  0,
    37, 9,  1,  -1, 0,  0,  0,  0,
    38, -1, 0,  0,  0,  0,  0,  0,
    43, 9,  1,  -1, 0,  0,  0,  0,
    44, 9,  1,  -1, 0,  0,  0,  0,
    15, 16, 1,  -1, 0,  0,  0,  0,
    47, -1, 0,  0,  0,  0,  0,  0,
    19, 20, 9,  1,  -1, 0,  0,  0,
    48, -1, 0,  0,  0,  0,  0,  0,
  };

  int i = 0;
  for (; i < std::size(ItemCmdMsgTbl[0]); ++i)
  {
    dest[i] = ItemCmdMsgTbl[std::to_underlying(cmd)][i] + 5000;
    if (dest[i] < 5000)
    {
      break;
    }
  }

  dest[i] = -1;
  return i;
}

// 001961A0
usize GetMenuCommandMsg(ECommonItemData item_id, s32* dest)
{
  log_trace("{}({}, {})", __func__, std::to_underlying(item_id), fmt::ptr(dest));

  auto item_type = GetItemDataType(item_id);

  switch (item_type)
  {
    case ECommonItemDataType::Torso_Max:
    case ECommonItemDataType::Hat_Max:
    case ECommonItemDataType::Shoes_Max:
    case ECommonItemDataType::Torso_Monica:
    case ECommonItemDataType::Hat_Monica:
    case ECommonItemDataType::Shoes_Monica:
      // 196220
      return ItemCmdMsgSet(EItemCmd::_8, dest);
    case ECommonItemDataType::Crystal:
    case ECommonItemDataType::Gem:
    case ECommonItemDataType::_34:
      // 196234
      return ItemCmdMsgSet(EItemCmd::_1, dest);
    case ECommonItemDataType::Coin:
      // 196248
      return ItemCmdMsgSet(EItemCmd::_24, dest);
    case ECommonItemDataType::Spectrumized_Item:
      // 19625C
      return ItemCmdMsgSet(EItemCmd::_5, dest);
    case ECommonItemDataType::Ridepod_Core:
      // 196270
      return ItemCmdMsgSet(EItemCmd::_7, dest);
    case ECommonItemDataType::Ridepod_Body:
    case ECommonItemDataType::Ridepod_Leg:
      // 196284
      return ItemCmdMsgSet(EItemCmd::_2, dest);
    case ECommonItemDataType::Ridepod_Arm:
      // 196298
      return ItemCmdMsgSet(EItemCmd::_22, dest);
    case ECommonItemDataType::Ridepod_Battery:
      // 1962AC
      return ItemCmdMsgSet(EItemCmd::_16, dest);
    case ECommonItemDataType::Melee_Max:
    case ECommonItemDataType::Ranged_Max:
    case ECommonItemDataType::Melee_Monica:
    case ECommonItemDataType::Ranged_Monica:
    {
      // 1961E8
      usize result = ItemCmdMsgSet(EItemCmd::_0, dest);

      if (item_id == ECommonItemData::Fishing_Rod || item_id == ECommonItemData::Lure_Rod)
      {
        result = ItemCmdMsgSet(EItemCmd::_14, dest);
      }
      return result;
    }
    case ECommonItemDataType::Food:
      // 1962C0
      return ItemCmdMsgSet(EItemCmd::_3, dest);
    case ECommonItemDataType::Crafting_Material:
    case ECommonItemDataType::Throwable:
    case ECommonItemDataType::Powder:
    case ECommonItemDataType::Amulet:
    case ECommonItemDataType::Dungeon_Key:
    case ECommonItemDataType::Story_Item:
    case ECommonItemDataType::Dungeon_Item_Or_Bait:
      switch (item_id)
      {
        case ECommonItemData::Repair_Powder:
          // 1962E0
          return ItemCmdMsgSet(EItemCmd::_13, dest);
        case ECommonItemData::Gun_Repair_Powder:
        case ECommonItemData::Armband_Repair_Powder:
          // 196308
          return ItemCmdMsgSet(EItemCmd::_17, dest);
        case ECommonItemData::Ridepod_Fuel:
          // 196320
          return ItemCmdMsgSet(EItemCmd::_23, dest);
        case ECommonItemData::Fruit_Of_Eden:
          // 19633C
          return ItemCmdMsgSet(EItemCmd::_20, dest);
        case ECommonItemData::Potato_Pie:
          // 196358
          return ItemCmdMsgSet(EItemCmd::_18, dest);
        case ECommonItemData::Witch_Parfait:
          // 196374
          return ItemCmdMsgSet(EItemCmd::_19, dest);
        case ECommonItemData::Notebook:
          // 196390
          return ItemCmdMsgSet(EItemCmd::_21, dest);
        case ECommonItemData::Heart_Throb_Cherry:
        case ECommonItemData::Mellow_Banana:
        case ECommonItemData::Resurrection_Powder:
          // 1963C4
          return ItemCmdMsgSet(EItemCmd::_3, dest);
        case ECommonItemData::Inside_Scoop_Memo:
          // 1963DC
          return ItemCmdMsgSet(EItemCmd::_26, dest);
        case ECommonItemData::Shield_Kit:
          // 1963F8
          return ItemCmdMsgSet(EItemCmd::_25, dest);
        case ECommonItemData::Escape_Powder:
          // 196414
          return ItemCmdMsgSet(EItemCmd::_27, dest);
        case ECommonItemData::Seal_Breaking_Scroll:
          // 196430
          return ItemCmdMsgSet(EItemCmd::_28, dest);
        case ECommonItemData::Monster_Notes:
          // 19644C
          return ItemCmdMsgSet(EItemCmd::_30, dest);
        case ECommonItemData::Level_Up_Powder:
          // 196468
          return ItemCmdMsgSet(EItemCmd::_31, dest);
        default:
          // 19647C
          return ItemCmdMsgSet(EItemCmd::_4, dest);
      }
    case ECommonItemDataType::Aquarium:
      // 19648C
      return ItemCmdMsgSet(EItemCmd::_9, dest);
    case ECommonItemDataType::Badge_Box:
      // 1964A0
      return ItemCmdMsgSet(EItemCmd::_10, dest);
    case ECommonItemDataType::Gift_Capsule:
      // 1964B4
      return ItemCmdMsgSet(EItemCmd::_11, dest);
    case ECommonItemDataType::Fish:
      // 1964C8
      return ItemCmdMsgSet(EItemCmd::_12, dest);
    case ECommonItemDataType::Lure:
      // 1964DC
      return ItemCmdMsgSet(EItemCmd::_15, dest);
    case ECommonItemDataType::_35:
      // 1964F0
      return ItemCmdMsgSet(EItemCmd::_29, dest);
    default:
      return 0;
  }
}

// 00196520
bool CheckItemEquip(ECharacterID chara_id, ECommonItemData item_id)
{
  log_trace("{}({}, {})", __func__, std::to_underlying(chara_id), std::to_underlying(item_id));

  if (!GetItemInfoData(item_id))
  {
    return false;
  }

  switch (item_id)
  {
    case ECommonItemData::Gun_Repair_Powder:
    case ECommonItemData::Camera:
      return chara_id == ECharacterID::Max;
    case ECommonItemData::Armband_Repair_Powder:
      return chara_id == ECharacterID::Monica;
    default:
      return true;
  }
}

// 001965C0
ECommonItemData SearchItemByName(const std::string name)
{
  log_trace("{}({})", __func__, name);

  for (int i = 1; i < std::to_underlying(ECommonItemData::COUNT); ++i)
  {
    if (GetCommonItemData(static_cast<ECommonItemData>(i))->m_name == name)
    {
      return static_cast<ECommonItemData>(i);
    }
  }

  return ECommonItemData::Invalid;
}

// 00196630
ECommonItemData GetRidePodCore(ssize index)
{
  log_trace("{}({})", __func__, index);

  // 00335B80
  static const ECommonItemData table[]
  {
    ECommonItemData::Core,
    ECommonItemData::Improved_Core,
    ECommonItemData::Core_II,
    ECommonItemData::Core_III,
    ECommonItemData::Super_Core,
    ECommonItemData::Hyper_Core,
    ECommonItemData::Master_Grade_Core,
  };

  if (index < 0 || index >= std::size(table))
  {
    return ECommonItemData::Invalid;
  }

  return table[index];
}

// 00196BE0
CUserDataManager* GetUserDataMan()
{
  log_trace("{}()", __func__);

  auto save_data = GetSaveData();
  return save_data != nullptr ? &save_data->m_user_data_manager : nullptr;
}

// 00196C90
bool COMMON_GAGE::CheckFill() const
{
  log_trace("COMMON_GAGE::{}()", __func__);

  return m_max == m_current;
}

// 00196CC0
f32 COMMON_GAGE::GetRate() const
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

// 00196DE0
u32 BREEDFISH_USED::CalcBreedFishParam()
{
  log_trace("{}()", __func__);

  return
    m_unk_field_26 +
    m_unk_field_28 +
    m_unk_field_2A +
    m_unk_field_2C +
    m_unk_field_2E;
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

// 001970D0
bool CGameDataUsed::CheckTypeEnableStack() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  if (m_type == EUsedItemType::Item_Misc)
  {
    return true;
  }

  if (m_type == EUsedItemType::Attach)
  {
    return false;
  }

  if (m_common_index == ECommonItemData::Spectrumized_Item)
  {
    return false;
  }

  return m_common_index != ECommonItemData::Monster_Drop;
}

// 00197120
std::string CGameDataUsed::GetDataPath() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  return GetItemFilePath(m_common_index, 0);
}

// 00197130
ECharacterID CGameDataUsed::IsWhoEquip() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  switch (m_type)
  {
    case EUsedItemType::Weapon:
      switch (m_item_data_type)
      {
        case ECommonItemDataType::Melee_Max:
        case ECommonItemDataType::Ranged_Max:
        case ECommonItemDataType::Torso_Max:
        case ECommonItemDataType::Hat_Max:
        case ECommonItemDataType::Shoes_Max:
          return ECharacterID::Max;
        case ECommonItemDataType::Melee_Monica:
        case ECommonItemDataType::Ranged_Monica:
        case ECommonItemDataType::Torso_Monica:
        case ECommonItemDataType::Hat_Monica:
        case ECommonItemDataType::Shoes_Monica:
          return ECharacterID::Monica;
        default:
          return ECharacterID::Invalid;
      }
    case EUsedItemType::Robopart:
      return ECharacterID::Ridepod;
    default:
      return ECharacterID::Invalid;
  }
}

// 001971D0
s16 CGameDataUsed::GetLevel() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  switch (m_type)
  {
    case EUsedItemType::Weapon:
      return as.weapon.m_level;
    case EUsedItemType::Attach:
      return as.attach.m_level;
    default:
      return 0;
  }
}

// 00197200
s8 CGameDataUsed::GetPaletteColor() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  if (m_type != EUsedItemType::Weapon)
  {
    return 0;
  }

  auto wep_data = GameItemDataManage.GetWeaponData(m_common_index);
  if (wep_data == nullptr)
  {
    return 0;
  }

  return wep_data->m_palette_color;
}

// 00197250
ECommonItemData CGameDataUsed::GetSpectrumNo() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  if (m_common_index != ECommonItemData::Spectrumized_Item)
  {
    return ECommonItemData::Invalid;
  }

  return as.attach.m_spectrumized_item_id;
}

// 00197270
sint CGameDataUsed::CheckStackRemain() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  if (!CheckTypeEnableStack())
  {
    return 0;
  }

  auto com_data = GetCommonItemData(m_common_index);
  if (com_data == nullptr)
  {
    return 0;
  }

  return com_data->m_stack_max_1E - GetNum();
}

// 001972E0
sint CGameDataUsed::GetNum() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  if (m_common_index == ECommonItemData::Invalid)
  {
    return 0;
  }

  switch (m_type)
  {
    case EUsedItemType::Item_Misc:
      return as.item_misc.m_stack_num;
    case EUsedItemType::Clothing:
      return as.clothing.m_stack_num;
    case EUsedItemType::Attach:
      if (m_item_data_type == ECommonItemDataType::Spectrumized_Item)
      {
        return true;
      }
      if (m_item_data_type == ECommonItemDataType::_34)
      {
        return true;
      }
      return as.attach.m_stack_num;
  }
}

// 00197360
u8 CGameDataUsed::GetActiveSetNum() const
{
  return IsActiveSet();
}

// 00197370
s16 CGameDataUsed::AddNum(sint delta, bool reset_if_empty)
{
  log_trace("CGameDataUsed::{}({}, {})", __func__, delta, reset_if_empty);

  if (m_common_index == ECommonItemData::Invalid)
  {
    return 0;
  }

  auto com_data = GetCommonItemData(m_common_index);

  s16 stack_num;
  if (m_type == EUsedItemType::Item_Misc)
  {
    stack_num = std::clamp<s16>(as.item_misc.m_stack_num + delta, 0, com_data->m_stack_max_A);
  }
  else if (m_type == EUsedItemType::Attach)
  {
    stack_num = std::clamp<s16>(as.attach.m_stack_num + delta, 0, com_data->m_stack_max_A);
  }
  else
  {
    // ?
    stack_num = delta + 1;
  }

  if (stack_num <= 0 && reset_if_empty)
  {
    new (this) CGameDataUsed();
  }

  return stack_num;
}

// 00197480
sint CGameDataUsed::GetUseCapacity() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  auto robo_data = GameItemDataManage.GetRoboData(m_common_index);

  if (robo_data == nullptr)
  {
    return 0;
  }

  return robo_data->m_use_capacity;
}

// 001974C0
s16 CGameDataUsed::AddFishHp(s16 delta)
{
  log_trace("CGameDataUsed::{}({})", __func__, delta);

  if (m_type != EUsedItemType::Fish)
  {
    return 0;
  }

  as.fish.m_breed_fish.m_hp = std::clamp(as.fish.m_breed_fish.m_hp + delta, 0, 100);
  return as.fish.m_breed_fish.m_hp;
}

// 00197600
u8 CGameDataUsed::IsActiveSet() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  auto com_data = GetCommonItemData(m_common_index);
  if (com_data == nullptr)
  {
    return false;
  }

  return com_data->m_active_set_num;
}

// 00197630
void CGameDataUsed::SetName(const char* name)
{
  log_trace("CGameDataUsed::{}({})", __func__, name);

  std::array<char, 0x20>* name_buf = nullptr;

  switch (m_type)
  {
    case EUsedItemType::Attach:
      name_buf = &as.attach.m_name;
      break;
    case EUsedItemType::Weapon:
      name_buf = &as.weapon.m_name;
      break;
    case EUsedItemType::Robopart:
      name_buf = &as.robopart.m_name;
      break;
    case EUsedItemType::Fish:
      name_buf = &as.fish.m_breed_fish.m_name;
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
  m_unk_field_5 = strcmp(GetItemMessage(m_common_index).data(), name_buf->data()) != 0;
}

// 00197DC0
sint CGameDataUsed::RemainFusion() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  return m_type == EUsedItemType::Weapon ? as.weapon.m_fusion_point : 0;
}

// 00197DE0
sint CGameDataUsed::AddFusionPoint(sint delta)
{
  log_trace("CGameDataUsed::{}({})", __func__, delta);

  if (m_type != EUsedItemType::Weapon)
  {
    return 0;
  }

  s16 fusion_point = std::max<s16>(as.weapon.m_fusion_point + delta, 0);

  if (IsFishingRod())
  {
    fusion_point = std::min<s16>(fusion_point, 9999);
  }
  else
  {
    fusion_point = std::min<s16>(fusion_point, 999);
  }

  as.weapon.m_fusion_point = fusion_point;
  return fusion_point;
}

COMMON_GAGE* CGameDataUsed::GetWHpGage()
{
  if (m_type == EUsedItemType::Robopart)
  {
    if (m_item_data_type == ECommonItemDataType::Ridepod_Arm)
    {
      return &as.robopart.m_whp_gage;
    }
    else if (m_item_data_type == ECommonItemDataType::Ridepod_Battery)
    {
      return &as.robopart.m_battery_gage;
    }
  }
  else if (m_type == EUsedItemType::Weapon)
  {
    return &as.weapon.m_whp_gage;
  }

  return nullptr;
}

// 001980C0
f32 CGameDataUsed::GetWHp(sint* values_dest)
{
  log_trace("CGameDataUsed::{}({})", __func__, fmt::ptr(values_dest));

  if (values_dest != nullptr)
  {
    values_dest[0] = 0;
    values_dest[1] = 0;
  }

  auto gage = GetWHpGage();

  if (gage == nullptr)
  {
    return 1.0f;
  }

  if (values_dest != nullptr)
  {
    values_dest[0] = GetDispVolumeForFloat(gage->m_current);
    values_dest[1] = static_cast<s32>(gage->m_max);
  }

  return gage->GetRate();
}

// 00198180
bool CGameDataUsed::IsRepair()
{
  // NOTE: Returns if an item *can* be repaired; not that it is repaired.

  log_trace("CGameDataUsed::{}()", __func__);

  auto gage = GetWHpGage();

  if (gage == nullptr)
  {
    return false;
  }

  return static_cast<f32>(GetDispVolumeForFloat(gage->m_current)) < gage->m_max;
}

// 00198270
bool CGameDataUsed::Repair(sint delta)
{
  log_trace("CGameDataUsed::{}()", __func__);

  auto gage = GetWHpGage();

  if (gage != nullptr)
  {
    gage->AddPoint(delta);
  }

  return true;
}

// 001982F0
ECommonItemData CGameDataUsed::GetRepairItemNo() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  switch (m_item_data_type)
  {
    case ECommonItemDataType::Melee_Max:
    case ECommonItemDataType::Melee_Monica:
    case ECommonItemDataType::Ridepod_Arm:
      return ECommonItemData::Repair_Powder;
    case ECommonItemDataType::Ranged_Max:
      return ECommonItemData::Gun_Repair_Powder;
    case ECommonItemDataType::Ranged_Monica:
      return ECommonItemData::Armband_Repair_Powder;
    case ECommonItemDataType::Ridepod_Battery:
      return ECommonItemData::Ridepod_Fuel;
    default:
      return ECommonItemData::Invalid;
  }
}

// 00198360
bool CGameDataUsed::IsEnableUseRepair(ECommonItemData item_id) const
{
  log_trace("CGameDataUsed::{}({})", __func__, std::to_underlying(item_id));

  return GetRepairItemNo() == item_id;
}

// 00198390
std::optional<WeaponAttackType> CGameDataUsed::GetRoboInfoType() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  auto robo_data = GetRoboPartInfoData(m_common_index);
  if (robo_data == nullptr)
  {
    return std::nullopt;
  }

  switch (m_item_data_type)
  {
    case ECommonItemDataType::Ridepod_Arm:
      return robo_data->m_unk_field_1E;
    case ECommonItemDataType::Ridepod_Leg:
      return robo_data->m_unk_field_20;
    default:
      return std::nullopt;
  }
}

// 00198400
std::string CGameDataUsed::GetRoboJointName() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  auto robo_data = GetRoboPartInfoData(m_common_index);
  if (robo_data == nullptr)
  {
    return "";
  }

  switch (m_item_data_type)
  {
    case ECommonItemDataType::Ridepod_Arm:
      return common::strings::format("body{}", robo_data->GetOffsetNo());
    case ECommonItemDataType::Ridepod_Body:
      return common::strings::format("arm{}", robo_data->GetOffsetNo());
    default:
      return "";
  }
}

// 001984B0
std::string CGameDataUsed::GetRoboSoundFileName() const
{
  log_trace("CGameDataUsed::{}()", __func__);
  using namespace common;

  auto robo_data = GetRoboPartInfoData(m_common_index);
  if (robo_data == nullptr)
  {
    return "";
  }

  if (m_item_data_type != ECommonItemDataType::Ridepod_Arm)
  {
    return "";
  }

  // FIXME: magic
  sint offset_no = robo_data->GetOffsetNo() + 39;
  if (offset_no < 40 || offset_no > 50)
  {
    offset_no = 40;
  }
  return strings::format("CH_0{}", offset_no);
}

// 00198550
bool CGameDataUsed::IsBroken()
{
  log_trace("CGameDataUsed::{}()", __func__);

  if (m_item_data_type == ECommonItemDataType::Ridepod_Battery)
  {
    return false;
  }

  sint whp[2];
  GetWHp(whp);
  return whp[0] <= 0;
}

// 001985A0
bool CGameDataUsed::IsLevelUp() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  if (m_type != EUsedItemType::Weapon)
  {
    return false;
  }

  if (as.weapon.m_level >= 99)
  {
    return false;
  }

  return static_cast<f32>(GetDispVolumeForFloat(as.weapon.m_abs_gage.m_current)) >=
    as.weapon.m_abs_gage.m_max;
}

// 00198620
void CGameDataUsed::LevelUp()
{
  log_trace("CGameDataUsed::{}()", __func__);

  todo;
}

// 00198950
bool CGameDataUsed::IsTrush() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  bool result = false;

  auto com_data = GetCommonItemData(m_common_index);
  if (com_data != nullptr)
  {
    // FIXME: MAGIC
    if ((com_data->m_attribute & 1) != 0)
    {
      result = true;
    }
  }

  if (m_type == EUsedItemType::Fish)
  {
    if ((as.fish.m_unk_field_38 & 2) != 0)
    {
      result = false;
    }
  }

  return result;
}

// 001989D0
bool CGameDataUsed::IsSpectolTrans() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  auto com_data = GetCommonItemData(m_common_index);

  if (com_data == nullptr)
  {
    return false;
  }

  // FIXME: MAGIC
  return (com_data->m_attribute & 2) != 0;
}

// 00198FC0
uint CGameDataUsed::IsBuildUp(uint* total_possible_dest, ECommonItemData* buildup_item_ids_dest, bool* can_build_up_dest) const
{
  log_trace("CGameDataUsed::{}({}, {}, {})", __func__, fmt::ptr(total_possible_dest), fmt::ptr(buildup_item_ids_dest), fmt::ptr(can_build_up_dest));

  using enum WeaponProperty;

  if (m_type != EUsedItemType::Weapon)
  {
    return 0;
  }

  auto wep_data = GetWeaponInfoData(m_common_index);
  if (wep_data == nullptr)
  {
    return 0;
  }

  s16 now_param[9];

  now_param[0] = as.weapon.m_attack;
  now_param[1] = as.weapon.m_properties[std::to_underlying(Flame)];
  now_param[2] = as.weapon.m_properties[std::to_underlying(Chill)];
  now_param[3] = as.weapon.m_properties[std::to_underlying(Lightning)];
  now_param[4] = as.weapon.m_properties[std::to_underlying(Cyclone)];
  now_param[5] = as.weapon.m_properties[std::to_underlying(Smash)];
  now_param[6] = as.weapon.m_properties[std::to_underlying(Exorcism)];
  now_param[7] = as.weapon.m_properties[std::to_underlying(Beast)];
  now_param[8] = as.weapon.m_properties[std::to_underlying(Scale)];

  uint total_possible = 0;
  uint total_can_build_up = 0;
  for (int i = 0; i < std::size(wep_data->m_buildup_next); ++i)
  {
    auto goal_wep_data = GetWeaponInfoData(wep_data->m_buildup_next[i]);

    if (goal_wep_data == nullptr)
    {
      continue;
    }

    ++total_possible;

    s16 goal_param[std::size(now_param)];

    goal_param[0] = goal_wep_data->m_attack;
    goal_param[1] = goal_wep_data->m_properties[std::to_underlying(Flame)];
    goal_param[2] = goal_wep_data->m_properties[std::to_underlying(Chill)];
    goal_param[3] = goal_wep_data->m_properties[std::to_underlying(Lightning)];
    goal_param[4] = goal_wep_data->m_properties[std::to_underlying(Cyclone)];
    goal_param[5] = goal_wep_data->m_properties[std::to_underlying(Smash)];
    goal_param[6] = goal_wep_data->m_properties[std::to_underlying(Exorcism)];
    goal_param[7] = goal_wep_data->m_properties[std::to_underlying(Beast)];
    goal_param[8] = goal_wep_data->m_properties[std::to_underlying(Scale)];

    bool goal_reached = true;

    for (int i = 0; i < std::size(now_param); ++i)
    {
      if (now_param[i] < goal_param[i] * 0.9f)
      {
        goal_reached = false;
        break;
      }
    }

    if (buildup_item_ids_dest != nullptr)
    {
      buildup_item_ids_dest[i] = wep_data->m_buildup_next[i];
    }

    if (can_build_up_dest != nullptr)
    {
      can_build_up_dest[i] = goal_reached;
    }

    if (goal_reached)
    {
      ++total_can_build_up;
    }
  }

  if (total_possible_dest != nullptr)
  {
    *total_possible_dest = total_possible;
  }

  return total_can_build_up;
}

// 001992B0
bool CGameDataUsed::IsFishingRod() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  return m_common_index == ECommonItemData::Fishing_Rod || \
    m_common_index == ECommonItemData::Lure_Rod;
}

// 001992E0
std::optional<usize> CGameDataUsed::GetActiveElem() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  if (m_type != EUsedItemType::Weapon)
  {
    return std::nullopt;
  }

  auto max_index = std::to_underlying(WeaponProperty::ELEMENTS_START);

  for (auto i = max_index + 1; i < std::to_underlying(WeaponProperty::ELEMENTS_END); ++i)
  {
    if (as.weapon.m_properties[i] > as.weapon.m_properties[max_index])
    {
      max_index = i;
    }
  }

  return max_index;
}

// 00199340
std::optional<WeaponAttackType> CGameDataUsed::GetAttackType() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  switch (m_type)
  {
    case EUsedItemType::Weapon:
      return GetWeaponInfoData(m_common_index)->m_attack_type;
    case EUsedItemType::Robopart:
      return GetRoboInfoType();
    default:
      return std::nullopt;
  }
}

// 001994E0
void CGameDataUsed::CheckParamLimit()
{
  log_trace("CGameDataUsed::{}()", __func__);

  using namespace common;
  using enum EUsedItemType;

  switch (m_type)
  {
    case Weapon:
    {
      auto wep_data = GetWeaponInfoData(m_common_index);
      if (wep_data == nullptr)
      {
        return;
      }

      // Clamp weapon max WHP
      as.weapon.m_whp_gage.m_max = std::min(as.weapon.m_whp_gage.m_max, static_cast<f32>(constants::u8_max));

      // Clamp weapon max attack
      as.weapon.m_attack = std::min(as.weapon.m_attack, wep_data->m_attack_max);

      // Clamp weapon max durability
      as.weapon.m_durable = std::min(as.weapon.m_durable, wep_data->m_durable_max);

      // Clamp the rest of the weapon properties
      for (auto i = 0; i < as.weapon.m_properties.size(); ++i)
      {
        as.weapon.m_properties[i] = std::min(as.weapon.m_properties[i], wep_data->m_properties_max[i]);
      }

      // This function will clamp our fusion points.
      AddFusionPoint(0);

      // Clamp weapon max ABS
      as.weapon.m_abs_gage.m_max = std::min(as.weapon.m_abs_gage.m_max, static_cast<f32>(constants::u8_max));

      // If our current ABS is *somehow* gte the max ABS, guess we need to level up.
      if (as.weapon.m_abs_gage.m_current >= as.weapon.m_abs_gage.m_max)
      {
        // Ding!
        LevelUp();
      }

      break;
    }
    case Attach:
    {
      as.attach.m_unk_field_2 = std::min<s16>(as.attach.m_unk_field_2, 999);
      as.attach.m_unk_field_4 = std::min<s16>(as.attach.m_unk_field_4, 999);

      for (auto i = 0; i < as.attach.m_unk_field_6.size(); ++i)
      {
        as.attach.m_unk_field_6[i] = std::min<s16>(as.attach.m_unk_field_6[i], 999);
      }

      break;
    }
    case Fish:
    {
      u16* p_params[] = {
        &as.fish.m_breed_fish.m_unk_field_26,
        &as.fish.m_breed_fish.m_unk_field_28,
        &as.fish.m_breed_fish.m_unk_field_2A,
        &as.fish.m_breed_fish.m_unk_field_2C,
        &as.fish.m_breed_fish.m_unk_field_2E,
      };

      // There was a loop here which checked if any particular param value was above 500,
      // and if so replace the pointer to it in p_params with nullptr (presumably to cause a crash???)
      // it's gone now.
      auto fish_param = as.fish.m_breed_fish.CalcBreedFishParam();
      if (fish_param > 500)
      {
        panicf("Woah dude, your fish parameters are way too high!! They cannot be redistributed fairly!!");
      }

      while (fish_param > 400)
      {
        auto rand_index = GetRandI(std::size(p_params));

        if (*p_params[rand_index] > 0)
        {
          *p_params[rand_index] -= 1;
          fish_param -= 1;
        }
      }
      
      for (usize i = 0; i < 4; ++i) // a1
      {
        bool clean = true; // a2
        usize j; // a3, t3
        while (true) 
        {
          auto p_curr = p_params[j]; // t4
          if (*p_curr <= 100)
          {
            ++j;
            if (j >= std::size(p_params))
            {
              break;
            }
          }

          u16* p_min = p_params[0]; // t0
          clean = false;
          
          // ugh why
          for (usize k = 0; k < std::size(p_params); ++k) // t1, t2
          {
            if (p_curr == p_params[k])
            {
              continue;
            }

            if (*p_params[k] >= *p_min)
            {
              p_min = p_params[k];
            }
          }

          *p_min -= 1;
          *p_curr += 1;
        }

        if (clean)
        {
          return;
        }
      }
      break;
    }
    default:
      break;
  }
}

// 00199860
ssize CGameDataUsed::GetGiftBoxItemNum() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  usize i = 0;
  for (; i < as.gift_box.m_contents.size(); ++i)
  {
    if (as.gift_box.m_contents[i] == ECommonItemData::Invalid)
    {
      break;
    }
  }
  return static_cast<ssize>(i);
}

// 001998B0
ssize CGameDataUsed::SetGiftBoxItem(ECommonItemData item_id, ssize index)
{
  log_trace("CGameDataUsed::{}({}, {})", __func__, std::to_underlying(item_id), index);

  if (m_type != EUsedItemType::Gift_Box)
  {
    return -1;
  }

  if (index >= 0)
  {
    as.gift_box.m_contents[index] = item_id;
  }
  else
  {
    for (usize i = 0; i < as.gift_box.m_contents.size(); ++i)
    {
      if (as.gift_box.m_contents[i] != ECommonItemData::Invalid)
      {
        as.gift_box.m_contents[i] = item_id;
        return i;
      }
    }
  }

  return -1;
}

// 00199920
ECommonItemData CGameDataUsed::GetGiftBoxItemNo(ssize index) const
{
  log_trace("CGameDataUsed::{}({})", __func__, index);

  if (m_type != EUsedItemType::Gift_Box || index < 0 || index >= as.gift_box.m_contents.size())
  {
    return ECommonItemData::Invalid;
  }

  return as.gift_box.m_contents[index];
}

// 00199960
usize CGameDataUsed::GetGiftBoxSameItemNum(ECommonItemData item_id) const
{
  log_trace("CGameDataUsed::{}({})", __func__, std::to_underlying(item_id));

  if (m_type != EUsedItemType::Gift_Box)
  {
    return 0;
  }

  usize count = 0;
  for (usize i = 0; i < as.gift_box.m_contents.size(); ++i)
  {
    if (as.gift_box.m_contents[i] == item_id)
    {
      ++count;
    }
  }
  return count;
}

// 001993B0
std::optional<u8> CGameDataUsed::GetModelNo() const
{
  log_trace("CGameDataUsed::{}()", __func__);

  switch (m_type)
  {
    case EUsedItemType::Weapon:
      return GetWeaponInfoData(m_common_index)->m_model_no;
    default:
      return std::nullopt;
  }
}

// 001993F0
std::optional<std::string> GetMainCharaModelName(ECharacterID chara_id, bool b)
{
  log_trace("{}({}, {})", __func__, std::to_underlying(chara_id), b);

  auto user_man = GetUserDataMan();

  if (user_man == nullptr)
  {
    return std::nullopt;
  }

  auto chara_data = user_man->GetCharaDataPtr(chara_id);

  if (chara_data == nullptr)
  {
    return std::nullopt;
  }

  auto model_no_opt = chara_data->m_equip_table[0].GetModelNo();
  u8 model_no = 0;

  if (model_no_opt.has_value()) [[likely]]
  {
    model_no = std::clamp<u8>(model_no_opt.value(), 0, 3);
  }

  if (chara_id == ECharacterID::Max)
  {
    model_no += 2;
  }

  constexpr std::array<const char*, 2> base_model_names
  {
    "c01_base", // Max
    "c02_base"  // Monica
  };

  if (b)
  {
    return common::strings::format("{}.chr", base_model_names[std::to_underlying(chara_id)]);
  }
  else
  {
    return common::strings::format("{}{}.chr", base_model_names[std::to_underlying(chara_id)], model_no);
  }
}

// 00199830
void CGameDataUsed::TimeCheck(s32 delta)
{
  log_trace("CGameDataUsed::{}({})", __func__, delta);

  if (m_type != EUsedItemType::Fish)
  {
    return;
  }

  as.fish.m_unk_field_30 = std::max(as.fish.m_unk_field_30 - delta, 0);
}

// 00199A50
bool CGameDataUsed::CopyDataWeapon(ECommonItemData item_id)
{
  log_trace("CGameDataUsed::{}({})", __func__, std::to_underlying(item_id));

  const auto weapon_data = GameItemDataManage.GetWeaponData(item_id);

  if (weapon_data == nullptr)
  {
    return false;
  }

  using enum WeaponProperty;

  m_type = EUsedItemType::Weapon;
  m_common_index = item_id;
  m_item_data_type = GetItemDataType(item_id);

  as.weapon.m_level = 0;

  as.weapon.m_whp_gage.m_max = static_cast<f32>(weapon_data->m_whp_max);
  as.weapon.m_whp_gage.m_current = static_cast<f32>(weapon_data->m_whp_max);

  as.weapon.m_abs_gage.m_max = static_cast<f32>(weapon_data->m_abs_max);
  as.weapon.m_abs_gage.m_current = 0.0f;

  as.weapon.m_attack = weapon_data->m_attack;
  as.weapon.m_durable = weapon_data->m_durable;

  as.weapon.m_properties[std::to_underlying(Flame)] = weapon_data->m_properties[std::to_underlying(Flame)];
  as.weapon.m_properties[std::to_underlying(Chill)] = weapon_data->m_properties[std::to_underlying(Chill)];
  as.weapon.m_properties[std::to_underlying(Lightning)]  = weapon_data->m_properties[std::to_underlying(Lightning)];
  as.weapon.m_properties[std::to_underlying(Cyclone)] = weapon_data->m_properties[std::to_underlying(Cyclone)];

  as.weapon.m_properties[std::to_underlying(Smash)] = weapon_data->m_properties[std::to_underlying(Smash)];
  as.weapon.m_properties[std::to_underlying(Exorcism)] = weapon_data->m_properties[std::to_underlying(Exorcism)];
  as.weapon.m_properties[std::to_underlying(Beast)] = weapon_data->m_properties[std::to_underlying(Beast)];
  as.weapon.m_properties[std::to_underlying(Scale)] = weapon_data->m_properties[std::to_underlying(Scale)];

  as.weapon.m_fusion_point = weapon_data->m_fusion_point;
  as.weapon.m_unk_field_28 = weapon_data->m_unk_field_2C;

  as.weapon.m_unk_field_2E = 0;
  as.weapon.m_unk_field_30 = 0;

  strcpy_s(
    as.weapon.m_name.data(),
    as.weapon.m_name.size(),
    GetItemMessage(item_id).c_str()
  );

  m_unk_field_5 = false;

  return true;
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

  for (auto& game_data_used : m_inventory)
  {
    new (&game_data_used) CGameDataUsed;
  }

  for (auto& unk_struct : m_chara_data)
  {
    for (auto& game_data_used : unk_struct.m_active_item_info)
    {
      new (&game_data_used) CGameDataUsed;
    }
    for (auto& game_data_used : unk_struct.m_equip_table)
    {
      new (&game_data_used) CGameDataUsed;
    }
  }

  for (auto& game_data_used : m_robo_data.m_part_data)
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

// 0019B490
SCharaData* CUserDataManager::GetCharaDataPtr(ECharacterID chara_id)
{
  log_trace("CUserDataManager::{}({})", __func__, std::to_underlying(chara_id));

  switch (chara_id)
  {
    case ECharacterID::Max:
    case ECharacterID::Monica:
      return &m_chara_data[std::to_underlying(chara_id)];
    default:
      return nullptr;
  }
}

// 0019B4C0
COMMON_GAGE* CUserDataManager::GetCharaHpGage(ECharacterID chara_id)
{
  log_trace("CUserDataManager::{}({})", __func__, std::to_underlying(chara_id));

  switch (chara_id)
  {
    case ECharacterID::Max:
    case ECharacterID::Monica:
      return &m_chara_data[std::to_underlying(chara_id)].m_chara_hp_gage;
    case ECharacterID::Ridepod:
      return &m_robo_data.m_chara_hp_gage;
    case ECharacterID::Monster:
      return &m_chara_data[std::to_underlying(ECharacterID::Monica)].m_chara_hp_gage;
    default:
      return nullptr;
  }
}

// 0019B510
sint CUserDataManager::AddHp(ECharacterID chara_id, sint delta)
{
  log_trace("CUserDataManager::{}({}, {})", __func__, std::to_underlying(chara_id), delta);

  auto gage = GetCharaHpGage(chara_id);
  if (gage == nullptr) 
    return 0;

  gage->AddPoint(delta);
  return static_cast<sint>(gage->m_current);
}

// 0019B560
f32 CUserDataManager::GetHp(ECharacterID chara_id)
{
  log_trace("CUserDataManager::{}({})", __func__, std::to_underlying(chara_id));

  auto gage = GetCharaHpGage(chara_id);
  if (gage == nullptr)
    return 0.0f;

  return truncf(gage->m_current);
}

// 0019B5A0
f32 CUserDataManager::AddHp_Rate(ECharacterID chara_id, f32 rate)
{
  log_trace("CUserDataManager::{}({}, {})", __func__, std::to_underlying(chara_id), rate);

  auto gage = GetCharaHpGage(chara_id);
  if (gage == nullptr)
    return 0.0f;

  gage->AddRate(rate);
  gage->m_current = std::max(gage->m_current, 1.0f);
  return gage->GetRate();
}

// 0019B620
COMMON_GAGE* CUserDataManager::GetWHpGage(ECharacterID chara_id, ssize gage_index)
{
  log_trace("CUserDataManager::{}({}, {})", __func__, std::to_underlying(chara_id), gage_index);

  switch (chara_id)
  {
    case ECharacterID::Ridepod:
      return &m_robo_data.m_part_data[0].as.robopart.m_whp_gage;
    case ECharacterID::Monster:
      return &m_monster_box.GetMonsterBadgeData(m_monster_id)->m_whp_gage;
    case ECharacterID::Max:
    case ECharacterID::Monica:
      return &m_chara_data[std::to_underlying(chara_id)].m_equip_table[gage_index].as.weapon.m_whp_gage;
    default:
      return nullptr;
  }
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

  if (chara_id == ECharacterID::Ridepod)
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

  m_robo_data.m_abs = std::clamp(m_robo_data.m_abs + delta, 0.0f, 99999.0f);
  return m_robo_data.m_abs;
}

// 0019C560
float CUserDataManager::GetRoboAbs()
{
  log_trace("CUserDataManager::{}()", __func__);

  return m_robo_data.m_abs;
}

// 0019B160
void CUserDataManager::Initialize()
{
  log_trace("CUserDataManager::Initialize()");

  memset(this, 0, sizeof(this));

  todo;
}

// 0019EAF0
s32 CUserDataManager::AddMoney(s32 delta)
{
  log_trace("CUserDataManager::{}({})", __func__, delta);

  m_money = std::clamp(m_money + delta, 0, 999'999);
  return m_money;
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

SMonsterBadgeData* CMonsterBox::GetMonsterBajjiData(EMonsterID index)
{
  log_warn("Please use CMonsterBox::GetMonsterBadgeData instead of CMonsterBox::GetMonsterBajjiData");
  return GetMonsterBadgeData(index);
}

// 0019AC40
SMonsterBadgeData* CMonsterBox::GetMonsterBadgeData(EMonsterID monster_id)
{
  log_trace("CMonsterBox::{}({})", __func__, std::to_underlying(monster_id));

  auto index = std::to_underlying(monster_id);

  // BUG: last item of array is not accessible 
  if (index <= 0 || index >= m_monster_badge_data.size())
  {
    return nullptr;
  }

  return &m_monster_badge_data[index - 1];
}

// 0019EFD0
CGameDataUsed* CBattleCharaInfo::GetEquipTablePtr(usize index)
{
  log_trace("CBattleCharaInfo::{}({})", __func__, index);

  // BUG ? : game checks less than 4 here;
  // pointer should point at an array of 5
  if (index < 0 || index >= 4)
  {
    return nullptr;
  }

  return &m_equip_table[index];
}

// 0019F010
void CBattleCharaInfo::SetChrNo(ECharacterID chara_id)
{
  log_trace("CBattleCharaInfo::{}({})", __func__, std::to_underlying(chara_id));

  todo;
}

// 0019F210
EMonsterID CBattleCharaInfo::GetMonsterID()
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  todo;
  return static_cast<EMonsterID>(0);
}

// 0019F250
ENPCID CBattleCharaInfo::GetNowNPC()
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  return m_now_npc;
}

// 0019F260
// NOTE: This fn takes an unused argument, so I removed it here.
bool CBattleCharaInfo::UseNPCPoint()
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  todo;
  return false;
}

// 0019F380
CGameDataUsed* CBattleCharaInfo::GetActiveItemInfo(usize index)
{
  log_trace("CBattleCharaInfo::{}({})", __func__, index);

  if (m_active_item_info == nullptr)
  {
    return nullptr;
  }

  return &m_active_item_info[index];
}

// 0019F3B0
bool CBattleCharaInfo::UseActiveItem(CGameDataUsed* active_item)
{
  log_trace("CBattleCharaInfo::{}({})", __func__, fmt::ptr(active_item));

  todo;
  return false;
}

// 0019F480
ESpecialStatus CBattleCharaInfo::GetSpecialStatus(usize index)
{
  log_trace("CBattleCharaInfo::{}({})", __func__, index);

  todo;
  return static_cast<ESpecialStatus>(0);
}

// 0019F4D0
s16 CBattleCharaInfo::GetPalletNo(usize index)
{
  log_trace("CBattleCharaInfo::{}({})", __func__, index);

  todo;
  return 0;
}

// 0019F520
void CBattleCharaInfo::RefreshParameter()
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  todo;
}

// 0019F890
COMMON_GAGE* CBattleCharaInfo::GetNowAccessWHp(usize weapon_index) const
{
  log_trace("CBattleCharaInfo::{}({})", __func__, weapon_index);

  switch (m_battle_chara_type)
  {
    case EBattleCharaType::Human:
      if (m_equip_table != nullptr)
      {
        return &m_equip_table[weapon_index].as.weapon.m_whp_gage;
      }
      return nullptr;
    case EBattleCharaType::MonsterTransform:
      // 0019F8DC
      todo;
      return nullptr;
    case EBattleCharaType::Ridepod:
      // 0019F8F4
      todo;
      return nullptr;
    default:
      return nullptr;
  }
}

// 0019F910
COMMON_GAGE* CBattleCharaInfo::GetNowAccessAbs(usize weapon_index) const
{
  log_trace("CBattleCharaInfo::{}({})", __func__, weapon_index);

  switch (m_battle_chara_type)
  {
    case EBattleCharaType::Human:
      if (m_equip_table != nullptr)
      {
        return &m_equip_table[weapon_index].as.weapon.m_abs_gage;
      }
      return nullptr;
    case EBattleCharaType::MonsterTransform:
      // 0019F8DC
      todo;
      return nullptr;
    case EBattleCharaType::Ridepod:
      // 0019F8F4
      todo;
      return nullptr;
    default:
      return nullptr;
  }
}

// 0019F990
f32 CBattleCharaInfo::AddWhp(usize weapon_index, f32 delta) const
{
  log_trace("CBattleCharaInfo::{}({}, {})", __func__, weapon_index, delta);

  auto whp_gage = GetNowAccessWHp(weapon_index);
  if (whp_gage == nullptr)
  {
    return 0.0f;
  }

  whp_gage->AddPoint(delta);
  if (whp_gage->m_max == 0.0f)
  {
    return 0.0f;
  }

  return whp_gage->GetRate();
}

// 0019FA10
// NOTE: originally void return, but I changed this to be reflective
// so it's known that the values in values_dest are valid if needed
bool CBattleCharaInfo::GetNowWhp(usize weapon_index, std::array<s32, 2>& values_dest) const
{
  log_trace("CBattleCharaInfo::{}({}, {})", __func__, weapon_index, fmt::ptr(&values_dest));

  auto whp_gage = GetNowAccessWHp(weapon_index);
  if (whp_gage == nullptr)
  {
    return false;
  }

  values_dest[0] = GetDispVolumeForFloat(whp_gage->m_current);
  values_dest[1] = static_cast<s32>(whp_gage->m_max);
  return true;
}

// 0019FA60
s32 CBattleCharaInfo::GetWhpNowVol(usize weapon_index) const
{
  log_trace("CBattleCharaInfo::{}({})", __func__, weapon_index);

  auto whp_gage = GetNowAccessWHp(weapon_index);
  if (whp_gage == nullptr)
  {
    return 0;
  }

  return GetDispVolumeForFloat(whp_gage->m_current);
}

// 0019FAA0
void SetMagicSwordPow(EMagicSwordElement element, s16 i1)
{
  log_trace("CBattleCharaInfo::{}({}, {})", __func__, std::to_underlying(element), i1);
  
  todo;
}

// 0019FB60
EMagicSwordElement CBattleCharaInfo::GetMagicSwordElem()
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  if (m_chara_id != ECharacterID::Monica)
  {
    return EMagicSwordElement::Invalid;
  }

  return m_magic_sword_element;
}

// 0019FB80
s32 CBattleCharaInfo::GetMagicSwordPow()
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  todo;
  return 0;
}

// 0019FC50
s16 CBattleCharaInfo::GetMagicSwordCounterNow()
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  return m_magic_sword_counter_now;
}

// 0019FC80
s16 CBattleCharaInfo::GetMagicSwordCounterMax()
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  todo;
  return 0;
}

// 0019FD00
void CBattleCharaInfo::ClearMagicSwordPow()
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  m_magic_sword_element = EMagicSwordElement::Uninitialized;
  m_magic_sword_counter_now = 0;
  m_unk_field_1C = 0;
  m_unk_field_1E = 0;
  m_unk_field_20 = 0;
  m_unk_field_22 = 0;
  m_unk_field_24 = 0;
  m_unk_field_26 = 0;
  m_unk_field_28 = 0;
}

// 0019FD30
f32 CBattleCharaInfo::AddAbs(usize weapon_index, f32 delta, bool* has_leveled_up)
{
  log_trace("CBattleCharaInfo::{}({}, {}, {})", __func__, weapon_index, delta, fmt::ptr(has_leveled_up));

  todo;
  return 0.0f;
}

// 0019FEE0
bool CBattleCharaInfo::AddAbsRate(usize weapon_index, f32 delta, bool* has_leveled_up)
{
  log_trace("CBattleCharaInfo::{}({}, {}, {})", __func__, weapon_index, delta, fmt::ptr(has_leveled_up));

  todo;
  return false;
}

// 0019FFE0
// NOTE: originally void return, but I changed this to be reflective
// so it's known that the values in values_dest are valid if needed
bool CBattleCharaInfo::GetNowAbs(usize weapon_index, std::array<s32, 2>& values_dest) const
{
  log_trace("CBattleCharaInfo::{}({}, {})", __func__, weapon_index, fmt::ptr(&values_dest));

  auto abs_gage = GetNowAccessAbs(weapon_index);
  if (abs_gage == nullptr)
  {
    return false;
  }

  values_dest[0] = GetDispVolumeForFloat(abs_gage->m_current);
  values_dest[1] = static_cast<s32>(abs_gage->m_max);
  return true;
}

// 001A0030
bool CBattleCharaInfo::LevelUpWeapon(CGameDataUsed* weapon)
{
  log_trace("CBattleCharaInfo::{}({})", __func__, fmt::ptr(weapon));

  if (m_battle_chara_type != EBattleCharaType::Human)
  {
    return false;
  }

  if (!weapon->IsLevelUp())
  {
    return false;
  }

  weapon->LevelUp();
  RefreshParameter();
  return true;
}

// 001A00A0
s32 CBattleCharaInfo::GetDefenceVol() const
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  return m_param.m_defence_vol;
}

// 001A00B0
f32 CBattleCharaInfo::AddHp_Point(f32 f1, f32 f2)
{
  log_trace("CBattleCharaInfo::{}({}, {})", __func__, f1, f2);

  todo;
  return 0.0f;
}

// 001A01B0
f32 CBattleCharaInfo::AddHp_Rate(f32 f1, s32 i1, f32 f2)
{
  log_trace("CBattleCharaInfo::{}({}, {}, {})", __func__, f1, i1, f2);

  todo;
  return 0.0f;
}

// 001A0370
void CBattleCharaInfo::SetHpRate(f32 rate) const
{
  log_trace("CBattleCharaInfo::{}({})", __func__, rate);

  if (m_hp_gage == nullptr)
  {
    return;
  }

  m_hp_gage->SetFillRate(rate);
}

// 001A03A0
s32 CBattleCharaInfo::GetMaxHp_i() const
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  if (m_hp_gage == nullptr)
  {
    return 0;
  }

  return static_cast<s32>(m_hp_gage->m_max);
}

// 001A03E0
s32 CBattleCharaInfo::GetNowHp_i() const
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  if (m_hp_gage == nullptr)
  {
    return 0;
  }

  return GetDispVolumeForFloat(m_hp_gage->m_current);
}

// 001A0420
ECharaStatusAttribute CBattleCharaInfo::SetAttr(ECharaStatusAttribute attr, bool b)
{
  log_trace("CBattleCharaInfo::{}({}, {})", __func__, std::to_underlying(attr), b);

  todo;
  return static_cast<ECharaStatusAttribute>(0);
}

// 001A0490
ECharaStatusAttribute CBattleCharaInfo::SetAttrVol(ECharaStatusAttribute attr, bool b)
{
  log_trace("CBattleCharaInfo::{}({}, {})", __func__, std::to_underlying(attr), b);

  todo;
  return static_cast<ECharaStatusAttribute>(0);
}

// 001A0500
ECharaStatusAttribute CBattleCharaInfo::GetAttr()
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  todo;
  return static_cast<ECharaStatusAttribute>(0);
}

// 001A0550
void CBattleCharaInfo::ForceSet()
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  todo;
}

// 001A08D0
ECharaStatusAttribute CBattleCharaInfo::StatusParamStep(s32* p)
{
  log_trace("CBattleCharaInfo::{}({})", __func__, fmt::ptr(p));

  todo;
  return static_cast<ECharaStatusAttribute>(0);
}

// 001A0C60
void CBattleCharaInfo::Step()
{
  log_trace("CBattleCharaInfo::{}()", __func__);

  todo;
}

// 001A0EA0
CBattleCharaInfo* GetBattleCharaInfo()
{
  log_trace("{}()", __func__);

  return &BattleParameter;
}
