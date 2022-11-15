#include <array>
#include <unordered_map>
#include "common/debug.h"
#include "common/log.h"
#include "common/types.h"

#include "gamedata.h"
#include "script_interpreter.h"

set_log_channel("gamedata");

using ComType = ECommonItemDataType::ECommonItemDataType;
using UsedType = EUsedItemType::EUsedItemType;

// 0037704C
static SDataItemCommon* comdatapt{ nullptr };
// 00377050
static s32 comdatapt_num{ 0 };
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
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001947a0
static bool _DATACOM(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001949c0
static bool _DATAWEBNUM(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194a00
static bool _DATAWEP(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194a60
static bool _DATAWEP_ST(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

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
  trace_script_call(stack, stack_count);

  todo;

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
  "WEPNUM",     _DATAWEBNUM,
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
SDataItemCommon* CGameData::GetCommonData(ssize index)
{
  log_trace("CGameData::{}({})", __func__, index);

  if (index < 0 || local_itemdatano_converttable.size() <= index)
  {
    return nullptr;
  }

  auto convert_index = local_itemdatano_converttable[index];
  if (convert_index < 0)
  {
    return nullptr;
  }

  return &m_com_itemdata[convert_index];
}

// 001957E0
CDataWeapon* CGameData::GetWeaponData(ssize index)
{
  log_trace("CGameData::{}({})", __func__, index);

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (m_unk_field_26 <= common_data->m_unk_field_4)
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
    {ComType::_1, UsedType::Weapon},
    {ComType::_2, UsedType::Weapon},
    {ComType::_3, UsedType::Weapon},
    {ComType::_4, UsedType::Weapon},
    {ComType::_5, UsedType::_4},
    {ComType::_6, UsedType::_4},
    {ComType::_7, UsedType::_4},
    {ComType::_8, UsedType::_4},
    {ComType::_9, UsedType::_4},
    {ComType::_10, UsedType::_4},
    {ComType::_11, UsedType::_1},
    {ComType::_12, UsedType::_5},
    {ComType::_13, UsedType::_5},
    {ComType::_14, UsedType::_5},
    {ComType::_15, UsedType::_5},
    {ComType::_16, UsedType::_2},
    {ComType::_17, UsedType::_2},
    {ComType::_18, UsedType::_2},
    {ComType::_19, UsedType::_2},
    {ComType::_20, UsedType::_1},
    {ComType::_21, UsedType::_1},
    {ComType::_22, UsedType::_1},
    {ComType::_23, UsedType::_1},
    {ComType::_24, UsedType::_1},
    {ComType::_25, UsedType::_1},
    {ComType::_26, UsedType::_1},
    {ComType::_27, UsedType::_1},
    {ComType::_28, UsedType::_7},
    {ComType::_29, UsedType::_1},
    {ComType::_30, UsedType::_6},
    {ComType::_31, UsedType::_1},
    {ComType::_32, UsedType::_1},
    {ComType::_33, UsedType::_1},
    {ComType::_34, UsedType::_2},
    {ComType::_35, UsedType::_8},
  };

  auto result = convert_table.find(type);
  if (result == convert_table.end())
  {
    if (type < 0)
    {
      return UsedType::Invalid;
    }
    else
    {
      // ?
      return UsedType::_1;
    }
  };
  return result->second;
}