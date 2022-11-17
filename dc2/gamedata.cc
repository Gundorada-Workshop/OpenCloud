#include <array>
#include <unordered_map>
#include "common/debug.h"
#include "common/log.h"
#include "common/types.h"

#include "gamedata.h"
#include "script_interpreter.h"

set_log_channel("gamedata");

using ComType = ECommonItemDataType;
using UsedType = EUsedItemType;

// 0037704C
static SDataItemCommon* comdatapt{ nullptr };
// 00377050
static s32 comdatapt_num{ 0 };
// 00377054
static CDataWeapon* SpiWeaponPt{ nullptr };
// 00377058
static CDataItem* SpiItemPt{ nullptr };
// 0037705C
static CDataAttach* SpiAttach{ nullptr };
// 00377060
static CDataRoboPart* SpiRoboPart{ nullptr };
// 00377064
static CDataBreedFish* SpiFish{ nullptr };
// 01E69570
static CGameData GameItemDataManage{};
// 01E695A0
// FIXME: MAGIC: capacity
static std::array<SDataItemCommon, 0x1B0> local_com_itemdata{};
// 01E6DFE0
// FIXME: MAGIC: capacity
static std::array<CDataItem, 162> local_itemdata{};
// 01E6DFE0
// FIXME: MAGIC: capacity
static std::array<CDataWeapon, 116> local_weapondata{};
// 01E70C70
// FIXME: MAGIC: capacity
static std::array<CDataAttach, 38> local_attachdata{};
// 01E71000
// FIXME: MAGIC: capacity
static std::array<CDataRoboPart, 68> local_robodata{};
// 01E71990
// FIXME: MAGIC: capacity
static std::array<CDataBreedFish, 20> local_fishdata{};
// 01E71B20
// FIXME: MAGIC: capacity
static std::array<CDataGuard, 20> local_guarddata{};
// 01E71B70
static std::array<s16, 0x200> local_itemdatano_converttable{ -1 };

// 00194750
static bool _DATACOMINIT(SPI_STACK* stack, int stack_count)
{
  // "COMINIT"
  trace_script_call(stack, stack_count);

  GameItemDataManage.m_unk_field_22 = spiGetStackInt(stack);

  comdatapt_num = 0;
  comdatapt = GameItemDataManage.m_com_itemdata;

  for (int i = 0; i < local_itemdatano_converttable.size(); ++i)
  {
    local_itemdatano_converttable[i] = -1;
  }

  return true;
}

// 001947a0
static bool _DATACOM(SPI_STACK* stack, int stack_count)
{
  // "COM"
  trace_script_call(stack, stack_count);

  comdatapt->m_common_id = static_cast<ECommonItemData>(spiGetStackInt(stack++));
  comdatapt->m_type = static_cast<ECommonItemDataType>(spiGetStackInt(stack++));
  comdatapt->m_unk_field_4 = spiGetStackInt(stack++);
  comdatapt->m_unk_field_1C = spiGetStackInt(stack++);
  comdatapt->m_unk_field_1E = spiGetStackInt(stack++);
  comdatapt->m_unk_field_A = spiGetStackInt(stack++);

  if (ConvertUsedItemType(comdatapt->m_type) == EUsedItemType::Weapon)
  {
    // FIXME: MAGIC?
    if (comdatapt->m_unk_field_A > 100)
    {
      comdatapt->m_unk_field_A = 144;
    }
  }

  comdatapt->m_unk_field_20 = spiGetStackInt(stack++);
  comdatapt->m_unk_field_6 = spiGetStackInt(stack++);
  comdatapt->m_unk_field_8 = spiGetStackInt(stack++);

  if (auto sprite_name = spiGetStackString(stack++); sprite_name != nullptr)
  {
    strcpy_s(comdatapt->m_sprite_name.data(), comdatapt->m_sprite_name.size(), sprite_name);
  }

  comdatapt->m_unk_field_24 = spiGetStackInt(stack++);
  comdatapt->m_name = "";

  local_itemdatano_converttable[std::to_underlying(comdatapt->m_common_id)] = comdatapt_num;

  ++comdatapt_num;
  ++comdatapt;

  return true;
}

// 001949c0
static bool _DATAWEPNUM(SPI_STACK* stack, int stack_count)
{
  // "WEPNUM"
  trace_script_call(stack, stack_count);

  GameItemDataManage.m_n_weapondata = spiGetStackInt(stack++);
  SpiWeaponPt = GameItemDataManage.m_weapondata;

  return true;
}

// 00194a00
static bool _DATAWEP(SPI_STACK* stack, int stack_count)
{
  // "WEP"
  trace_script_call(stack, stack_count);

  if (SpiWeaponPt == nullptr)
  {
    log_warn("{}: SpiWeaponPt is nullptr!", __func__);
    return false;
  }

  SpiWeaponPt->m_unk_field_0 = spiGetStackInt(stack++);
  SpiWeaponPt->m_unk_field_2 = spiGetStackInt(stack++);

  return true;
}

// 00194a60
static bool _DATAWEP_ST(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  if (SpiWeaponPt == nullptr)
  {
    log_warn("{}: SpiWeaponPt is nullptr!", __func__);
    return false;
  }

  SpiWeaponPt->m_unk_field_4 = spiGetStackInt(stack++);
  SpiWeaponPt->m_unk_field_6 = spiGetStackInt(stack++);

  return true;
}

// 00194ac0
static bool _DATAWEP_ST_L(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194b20
static bool _DATAWEP2_ST(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194ba0
static bool _DATAWEP2_ST_L(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194c20
static bool _DATAWEP_SPE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194d10
static bool _DATAWEP_BUILDUP(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194dc0
static bool _DATAITEMINIT(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194e00
static bool _DATAITEM(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194ee0
static bool _DATAATTACHINIT(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194f20
static bool _DATAATTACH_ST(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194fa0
static bool _DATAATTACH_ST2(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00195020
static bool _DATAATTACH_ST_SP(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00195070
static bool _DATAROBOINIT(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001950b0
static bool _DATAROBO_ANALYZE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001953a0
static bool _DATAGUARDNUM(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001953d0
static bool _DATAGUARD(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

static bool _DATAFISHINIT(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001952a0
static bool _DATAFISH(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

static bool _MES_SYS(SPI_STACK* stack, int stack_count)
{
  // "MES_SYS"
  trace_script_call(stack, stack_count);

  ECommonItemData index = static_cast<ECommonItemData>(spiGetStackInt(stack++));
  char* name = spiGetStackString(stack++);

  auto common_data = GameItemDataManage.GetCommonData(index);

  if (common_data != nullptr && name != nullptr)
  {
    common_data->m_name = std::string(name);
  }

  return true;
}

static bool _MES_SYS_SPECTOL(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 003359a0
static const std::array<SPI_TAG_PARAM, 25> gamedata_tag =
{
  "COMINIT",    _DATACOMINIT,
  "COM",        _DATACOM,
  "WEPNUM",     _DATAWEPNUM,
  "WEP",        _DATAWEP,
  "WEP_ST",     _DATAWEP_ST,
  "WEP_ST_L",   _DATAWEP_ST_L,
  "WEP_ST2",    _DATAWEP2_ST,
  "WEP_ST2_L",  _DATAWEP2_ST_L,
  "WEP_SPE",    _DATAWEP_SPE,
  "WEP_BUILD",  _DATAWEP_BUILDUP,
  "ITEMINIT",   _DATAITEMINIT,
  "ITEM",       _DATAITEM,
  "AT_INIT",    _DATAATTACHINIT,
  "AT_ST",      _DATAATTACH_ST,
  "AT_ST2",     _DATAATTACH_ST2,
  "AT_ST_SP",   _DATAATTACH_ST_SP,
  "ROBOTINIT",  _DATAROBOINIT,
  "RB_PARTS",   _DATAROBO_ANALYZE,
  "GRDNUM",     _DATAGUARDNUM,
  "GRD",        _DATAGUARD,
  "FISHINIT",   _DATAFISHINIT,
  "FISH",       _DATAFISH,
  "MES_SYS",    _MES_SYS,
  "MES_SYSSPE", _MES_SYS_SPECTOL,
  NULL, nullptr
};

// 001946D0
CGameData::CGameData()
{
  log_trace("CGameData()");

  m_com_itemdata = local_com_itemdata.data();
  m_itemdata = local_itemdata.data();
  m_weapondata = local_weapondata.data();
  m_guarddata = local_guarddata.data();
  m_attachdata = local_attachdata.data();
  m_robodata = local_robodata.data();
  m_fishdata = local_fishdata.data();

  // 00195720
  for (int i = 0; i < local_com_itemdata.size(); ++i)
  {
    new (&local_com_itemdata[i]) SDataItemCommon();
  }
}

// 00195540
s32 CGameData::LoadData()
{
  log_trace("CGameData::{}()", __func__);

  new (this) CGameData();

  comdatapt_num = 0;
  comdatapt = m_com_itemdata;
  for (int i = 0; i < local_itemdatano_converttable.size(); ++i)
  {
    local_itemdatano_converttable[i] = -1;
  }

  LoadGameDataAnalyze("comdat.cfg");
  LoadGameDataAnalyze("wepdat.cfg");
  LoadGameDataAnalyze("itemdat.cfg");
  LoadGameDataAnalyze("atdat.cfg");
  LoadGameDataAnalyze("robodat.cfg");
  LoadGameDataAnalyze("fishdat.cfg");
  LoadGameDataAnalyze("grddat.cfg");

  m_unk_field_22 = comdatapt_num;
  m_unk_field_20 = 0;

  for (int i = 0; i < local_itemdatano_converttable.size(); ++i)
  {
    if (local_itemdatano_converttable[i] >= 0)
    {
      m_unk_field_20 = local_itemdatano_converttable[i];
    }
  }

  return m_unk_field_0;
}

// 00195770
SDataItemCommon* CGameData::GetCommonData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  auto id = std::to_underlying(index);
  if (id < 0 || local_itemdatano_converttable.size() <= id)
  {
    return nullptr;
  }

  auto convert_index = local_itemdatano_converttable[id];
  if (convert_index < 0)
  {
    return nullptr;
  }

  return &m_com_itemdata[convert_index];
}

// 001957E0
CDataWeapon* CGameData::GetWeaponData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (m_n_weapondata <= common_data->m_unk_field_4)
  {
    return nullptr;
  }

  if (m_weapondata == nullptr)
  {
    return nullptr;
  }

  if (ConvertUsedItemType(common_data->m_type) == UsedType::Weapon)
  {
    return &m_weapondata[common_data->m_unk_field_4];
  }
  return nullptr;
}

// 00195890
CDataItem* CGameData::GetItemData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (m_unk_field_24 <= common_data->m_unk_field_4)
  {
    return nullptr;
  }

  if (m_itemdata == nullptr)
  {
    return nullptr;
  }

  auto type = ConvertUsedItemType(common_data->m_type);
  if (type == UsedType::Item_Gift || type == UsedType::Item_8 || type == UsedType::Item_Misc)
  {
    return &m_itemdata[common_data->m_unk_field_4];
  }
  return nullptr;
}

// 00195940
CDataAttach* CGameData::GetAttachData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (m_unk_field_2A <= common_data->m_unk_field_4)
  {
    return nullptr;
  }

  if (m_attachdata == nullptr)
  {
    return nullptr;
  }

  auto type = ConvertUsedItemType(common_data->m_type);
  if (type == UsedType::Attach)
  {
    return &m_attachdata[common_data->m_unk_field_4];
  }
  return nullptr;
}

// 001959F0
CDataRoboPart* CGameData::GetRoboData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (m_unk_field_2C <= common_data->m_unk_field_4)
  {
    return nullptr;
  }

  if (m_robodata == nullptr)
  {
    return nullptr;
  }

  return &m_robodata[common_data->m_unk_field_4];
}

// 00195A60
CDataBreedFish* CGameData::GetFishData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (m_unk_field_2E <= common_data->m_unk_field_4)
  {
    return nullptr;
  }

  if (m_fishdata == nullptr)
  {
    return nullptr;
  }

  auto type = ConvertUsedItemType(common_data->m_type);
  if (type == UsedType::Fish)
  {
    return &m_fishdata[common_data->m_unk_field_4];
  }
  return nullptr;
}

// 00195B10
CDataGuard* CGameData::GetGuardData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (m_unk_field_28 <= common_data->m_unk_field_4)
  {
    return nullptr;
  }

  if (m_guarddata == nullptr)
  {
    return nullptr;
  }

  return &m_guarddata[common_data->m_unk_field_4];
}

// 00195B80
ComType CGameData::GetDataType(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return ComType::Invalid;
  }
  return common_data->m_type;
}

// 00195BB0
ECommonItemData CGameData::GetDataStartListNo(ComType type)
{
  log_trace("CGameData::{}({})", __func__, static_cast<int>(type));

  auto common_data = GetCommonData(static_cast<ECommonItemData>(1));

  for (int i = 0; i < m_unk_field_22; ++i)
  {
    if (common_data[i].m_type == type)
    {
      return common_data[i].m_common_id;
    }
  }
  return ECommonItemData::Invalid;
}

// 00195470
bool LoadGameDataAnalyze(const char* config_file_name)
{
  log_trace("LoadGameDataAnalyze({})", config_file_name);

  todo;
  return false;
}

// 00195F10
UsedType ConvertUsedItemType(ComType type)
{
  log_trace("CGameData::{}({})", __func__, static_cast<int>(type));

  // Did runtime analysis to determine these
  static std::unordered_map<ComType, UsedType> convert_table = {
    {ComType::Invalid, UsedType::Invalid},
    {ComType::Melee_Max, UsedType::Weapon},
    {ComType::Ranged_Max, UsedType::Weapon},
    {ComType::Melee_Monica, UsedType::Weapon},
    {ComType::Ranged_Monica, UsedType::Weapon},
    {ComType::Torso_Max, UsedType::Clothing},
    {ComType::Hat_Max, UsedType::Clothing},
    {ComType::Shoes_Max, UsedType::Clothing},
    {ComType::Torso_Monica, UsedType::Clothing},
    {ComType::Hat_Monica, UsedType::Clothing},
    {ComType::Shoes_Monica, UsedType::Clothing},
    {ComType::Ridepod_Core, UsedType::Item_Misc},
    {ComType::Ridepod_Body, UsedType::Robopart},
    {ComType::Ridepod_Arm, UsedType::Robopart},
    {ComType::Ridepod_Leg, UsedType::Robopart},
    {ComType::Ridepod_Battery, UsedType::Robopart},
    {ComType::Crystal, UsedType::Attach},
    {ComType::_17, UsedType::Attach},
    {ComType::Gem, UsedType::Attach},
    {ComType::Coin, UsedType::Attach},
    {ComType::Crafting_Material, UsedType::Item_Misc},
    {ComType::Badge_Box, UsedType::Item_Misc},
    {ComType::Food, UsedType::Item_Misc},
    {ComType::Throwable, UsedType::Item_Misc},
    {ComType::Powder, UsedType::Item_Misc},
    {ComType::Amulet, UsedType::Item_Misc},
    {ComType::Dungeon_Key, UsedType::Item_Misc},
    {ComType::Story_Item, UsedType::Item_Misc},
    {ComType::Gift_Capsule, UsedType::Item_Gift},
    {ComType::Aquarium, UsedType::Item_Misc},
    {ComType::Fish, UsedType::Fish},
    {ComType::_31, UsedType::Item_Misc},
    {ComType::Lure, UsedType::Item_Misc},
    {ComType::Dungeon_Item_Or_Bait, UsedType::Item_Misc},
    {ComType::_34, UsedType::Attach},
    {ComType::_35, UsedType::Item_8},
  };

  auto result = convert_table.find(type);
  if (result == convert_table.end())
  {
    if (std::to_underlying(type) < 0)
    {
      return UsedType::Invalid;
    }
    else
    {
      // ?
      return UsedType::Item_Misc;
    }
  };
  return result->second;
}

// 00195C20
SDataItemCommon* GetCommonItemData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  return GameItemDataManage.GetCommonData(index);
}

// 00195C30
CDataItem* GetItemInfoData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  return GameItemDataManage.GetItemData(index);
}

// 00195C40
CDataWeapon* GetWeaponInfoData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  return GameItemDataManage.GetWeaponData(index);
}

// 00195C50
CDataRoboPart* GetRoboPartInfoData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  return GameItemDataManage.GetRoboData(index);
}

// 00195C60
CDataBreedFish* GetBreedFishInfoData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, std::to_underlying(index));

  return GameItemDataManage.GetFishData(index);
}


// 00196040
std::string GetItemMessage(ECommonItemData index)
{
  log_trace("{}({})", __func__, std::to_underlying(index));

  auto common_data = GameItemDataManage.GetCommonData(index);
  
  if (common_data == nullptr)
  {
    return "";
  }

  return common_data->m_name;
}