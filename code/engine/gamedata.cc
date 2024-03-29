#include <array>
#include <unordered_map>

#include "common/file_helpers.h"
#include "common/data_stream.h"
#include "common/debug.h"
#include "common/helpers.h"
#include "common/log.h"
#include "common/types.h"
#include "common/macros.h"
#include "common/strings.h"

#include "engine/gamedata.h"
#include "engine/script_interpreter.h"

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
CGameData GameItemDataManage{};
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
static bool _DATACOMINIT(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "COMINIT"
  trace_script_call(stack, stack_count);

  GameItemDataManage.m_n_com_itemdata = static_cast<s16>(spiGetStackInt(stack));

  comdatapt_num = 0;
  comdatapt = GameItemDataManage.m_com_itemdata;

  for (int i = 0; i < local_itemdatano_converttable.size(); ++i)
  {
    local_itemdatano_converttable[i] = -1;
  }

  return true;
}

// 001947a0
static bool _DATACOM(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "COM"
  trace_script_call(stack, stack_count);

  comdatapt->m_common_id = static_cast<ECommonItemData>(spiGetStackInt(stack++));
  comdatapt->m_type = static_cast<ECommonItemDataType>(spiGetStackInt(stack++));
  comdatapt->m_category_id = static_cast<s16>(spiGetStackInt(stack++));
  comdatapt->m_active_set_num = static_cast<u8>(spiGetStackInt(stack++));
  comdatapt->m_stack_max_1E = static_cast<s16>(spiGetStackInt(stack++));
  comdatapt->m_stack_max_A = static_cast<s16>(spiGetStackInt(stack++));

  if (ConvertUsedItemType(comdatapt->m_type) == EUsedItemType::Weapon)
  {
    // FIXME: MAGIC?
    if (comdatapt->m_stack_max_A > 100)
    {
      comdatapt->m_stack_max_A = 144;
    }
  }

  comdatapt->m_unk_field_20 = static_cast<s8>(spiGetStackInt(stack++));
  comdatapt->m_unk_field_6 = static_cast<s16>(spiGetStackInt(stack++));
  comdatapt->m_unk_field_8 = static_cast<s16>(spiGetStackInt(stack++));

  if (auto sprite_name = spiGetStackString(stack++); sprite_name != nullptr)
  {
    common::strings::safe_str_to_array(comdatapt->m_sprite_name, sprite_name);
  }

  comdatapt->m_attribute = spiGetStackInt(stack++);
  comdatapt->m_name = "";

  local_itemdatano_converttable[common::to_underlying(comdatapt->m_common_id)] = static_cast<s16>(comdatapt_num);

  ++comdatapt_num;
  ++comdatapt;

  return true;
}

// 001949c0
static bool _DATAWEPNUM(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "WEPNUM"
  trace_script_call(stack, stack_count);

  GameItemDataManage.m_n_weapondata = static_cast<s16>(spiGetStackInt(stack++));
  SpiWeaponPt = GameItemDataManage.m_weapondata;

  return true;
}

// 00194a00
static bool _DATAWEP(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "WEP"
  trace_script_call(stack, stack_count);

  if (SpiWeaponPt == nullptr)
  {
    log_warn("{}: SpiWeaponPt is nullptr!", __func__);
    return false;
  }

  SpiWeaponPt->m_whp_max = static_cast<s16>(spiGetStackInt(stack++));
  SpiWeaponPt->m_abs_max = static_cast<s16>(spiGetStackInt(stack++));

  return true;
}

// 00194a60
static bool _DATAWEP_ST(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "WEP_ST"
  trace_script_call(stack, stack_count);

  if (SpiWeaponPt == nullptr)
  {
    log_warn("{}: SpiWeaponPt is nullptr!", __func__);
    return false;
  }

  SpiWeaponPt->m_attack = static_cast<s16>(spiGetStackInt(stack++));
  SpiWeaponPt->m_durable = static_cast<s16>(spiGetStackInt(stack++));

  return true;
}

// 00194ac0
static bool _DATAWEP_ST_L(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "WEP_ST_L"
  trace_script_call(stack, stack_count);

  if (SpiWeaponPt == nullptr)
  {
    log_warn("{}: SpiWeaponPt is nullptr!", __func__);
    return false;
  }

  SpiWeaponPt->m_attack_max = static_cast<s16>(spiGetStackInt(stack++));
  SpiWeaponPt->m_durable_max = static_cast<s16>(spiGetStackInt(stack++));

  return true;
}

// 00194b20
static bool _DATAWEP2_ST(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "WEP_ST2"
  trace_script_call(stack, stack_count);

  if (SpiWeaponPt == nullptr)
  {
    log_warn("{}: SpiWeaponPt is nullptr!", __func__);
    return false;
  }

  using enum WeaponProperty;

  SpiWeaponPt->m_properties[common::to_underlying(Flame)] = static_cast<s16>(spiGetStackInt(stack++));
  SpiWeaponPt->m_properties[common::to_underlying(Chill)] = static_cast<s16>(spiGetStackInt(stack++));
  SpiWeaponPt->m_properties[common::to_underlying(Lightning)] = static_cast<s16>(spiGetStackInt(stack++));
  SpiWeaponPt->m_properties[common::to_underlying(Cyclone)] = static_cast<s16>(spiGetStackInt(stack++));
  SpiWeaponPt->m_properties[common::to_underlying(Smash)] = static_cast<s16>(spiGetStackInt(stack++));
  SpiWeaponPt->m_properties[common::to_underlying(Exorcism)] = static_cast<s16>(spiGetStackInt(stack++));
  SpiWeaponPt->m_properties[common::to_underlying(Beast)] = static_cast<s16>(spiGetStackInt(stack++));
  SpiWeaponPt->m_properties[common::to_underlying(Scale)] = static_cast<s16>(spiGetStackInt(stack++));

  return true;
}

// 00194ba0
static bool _DATAWEP2_ST_L(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "WEP_ST2_L"
  trace_script_call(stack, stack_count);

  if (SpiWeaponPt == nullptr)
  {
    log_warn("{}: SpiWeaponPt is nullptr!", __func__);
    return false;
  }

  assert_msg(SpiWeaponPt->m_properties_max.size() == 8, "not gonna read out the scripts properly if this somehow changes :^)");

  for (int i = 0; i < SpiWeaponPt->m_properties_max.size(); ++i)
  {
    SpiWeaponPt->m_properties_max[i] = static_cast<s16>(spiGetStackInt(stack++));
  }

  return true;
}

// 00194c20
static bool _DATAWEP_SPE(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "WEP_SPE"
  trace_script_call(stack, stack_count);

  if (SpiWeaponPt == nullptr)
  {
    log_warn("{}: SpiWeaponPt is nullptr!", __func__);
    return false;
  }

  SpiWeaponPt->m_fusion_point = static_cast<u8>(spiGetStackFloat(stack++));
  SpiWeaponPt->m_palette_color = static_cast<s8>(spiGetStackInt(stack++));
  SpiWeaponPt->m_unk_field_47 = static_cast<s8>(spiGetStackInt(stack++));
  SpiWeaponPt->m_level_up_fusion_point = static_cast<s8>(spiGetStackInt(stack++));
  SpiWeaponPt->m_special_status = static_cast<ESpecialStatus>(spiGetStackInt(stack++));
  SpiWeaponPt->m_attack_type = (stack_count >= 6) ? static_cast<EAttackType>(spiGetStackInt(stack++)) : static_cast<EAttackType>(0);
  SpiWeaponPt->m_model_no = (stack_count >= 7) ? static_cast<s8>(spiGetStackInt(stack++)) : 0;

  return true;
}

// 00194d10
static bool _DATAWEP_BUILDUP(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "WEP_BUILD"
  trace_script_call(stack, stack_count);

  if (SpiWeaponPt == nullptr)
  {
    log_warn("{}: SpiWeaponPt is nullptr!", __func__);
    return false;
  }

  SpiWeaponPt->m_buildup_next[0] = static_cast<ECommonItemData>(spiGetStackInt(stack++));
  SpiWeaponPt->m_buildup_next[1] = static_cast<ECommonItemData>(spiGetStackInt(stack++));
  SpiWeaponPt->m_buildup_next[2] = static_cast<ECommonItemData>(spiGetStackInt(stack++));

  if (stack_count >= 4)
  {
    SpiWeaponPt->m_unk_field_40 = static_cast<s16>(spiGetStackInt(stack++));
    SpiWeaponPt->m_unk_field_42 = static_cast<s16>(spiGetStackInt(stack++));
    SpiWeaponPt->m_unk_field_44 = static_cast<s16>(spiGetStackInt(stack++));
  }

  ++SpiWeaponPt;

  return true;
}

// 00194dc0
static bool _DATAITEMINIT(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "ITEMINIT"
  trace_script_call(stack, stack_count);

  GameItemDataManage.m_n_itemdata = static_cast<s16>(spiGetStackInt(stack++));
  SpiItemPt = GameItemDataManage.m_itemdata;

  return true;
}

// 00194e00
static bool _DATAITEM(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "ITEM"
  trace_script_call(stack, stack_count);

  auto index = static_cast<ECommonItemData>(spiGetStackInt(stack++));
  SpiItemPt = GetItemInfoData(index);

  if (SpiItemPt == nullptr)
  {
    log_warn("{}: SpiItemPt is nullptr!", __func__);
    return false;
  }

  // FIXME: MAGIC
  s32 i = spiGetStackInt(stack++);
  if ((i & 0x800000) != 0)
  {
    i &= ~(0x800000);
    i |= 0x142A8000;
  }

  SpiItemPt->m_unk_field_4 = i;
  SpiItemPt->m_unk_field_0 = spiGetStackInt(stack++);
  SpiItemPt->m_unk_field_8 = static_cast<s16>(spiGetStackInt(stack++));
  SpiItemPt->m_unk_field_A = static_cast<s16>(spiGetStackInt(stack++));
  SpiItemPt->m_unk_field_C = static_cast<s16>(spiGetStackInt(stack++));
  SpiItemPt->m_unk_field_E = static_cast<s16>(spiGetStackInt(stack++));

  return true;
}

// 00194ee0
static bool _DATAATTACHINIT(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "AT_INIT"
  trace_script_call(stack, stack_count);

  GameItemDataManage.m_n_attachdata = static_cast<s16>(spiGetStackInt(stack));
  SpiAttach = GameItemDataManage.m_attachdata;

  return true;
}

// 00194f20
static bool _DATAATTACH_ST(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "AT_ST"
  trace_script_call(stack, stack_count);

  if (SpiAttach == nullptr)
  {
    log_warn("{}: SpiAttach is nullptr!", __func__);
    return false;
  }

  SpiAttach->m_attack = static_cast<s16>(spiGetStackInt(stack++));
  SpiAttach->m_durable = static_cast<s16>(spiGetStackInt(stack++));

  return true;
}

// 00194fa0
static bool _DATAATTACH_ST2(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "AT_ST2"
  trace_script_call(stack, stack_count);

  if (SpiAttach == nullptr)
  {
    log_warn("{}: SpiAttach is nullptr!", __func__);
    return false;
  }

  for (int i = 0; i < 8; ++i)
  {
    SpiAttach->m_properties[i] = static_cast<s16>(spiGetStackInt(stack++));
  }

  return true;
}

// 00195020
static bool _DATAATTACH_ST_SP(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "AT_ST_SP"
  trace_script_call(stack, stack_count);

  if (SpiAttach == nullptr)
  {
    log_warn("{}: SpiAttach is nullptr!", __func__);
    return false;
  }

  SpiAttach->m_unk_field_14 = spiGetStackInt(stack++);
  ++SpiAttach;
  
  return true;
}

// 00195070
static bool _DATAROBOINIT(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "ROBOINIT"
  trace_script_call(stack, stack_count);

  GameItemDataManage.m_n_robodata = static_cast<s16>(spiGetStackInt(stack++));
  SpiRoboPart = GameItemDataManage.m_robodata;

  return true;
}

// 001950b0
static bool _DATAROBO_ANALYZE(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "RB_PARTS"
  trace_script_call(stack, stack_count);

  auto index = static_cast<ECommonItemData>(spiGetStackInt(stack++));
  SpiRoboPart = GameItemDataManage.GetRoboData(index);

  if (SpiRoboPart == nullptr)
  {
    log_warn("{}: SpiRoboPart is nullptr!", __func__);
    return false;
  }

  int mode = spiGetStackInt(stack++);
  SpiRoboPart->m_use_capacity = static_cast<s16>(spiGetStackInt(stack++));
  SpiRoboPart->m_offset_no = static_cast<s8>(spiGetStackInt(stack++));

  switch (mode)
  {
    case 0:
      SpiRoboPart->m_defense = static_cast<s16>(spiGetStackInt(stack++));
      break;
    case 1:
      SpiRoboPart->m_whp_max = static_cast<s16>(spiGetStackInt(stack++));
      SpiRoboPart->m_attack = static_cast<s16>(spiGetStackInt(stack++));
      SpiRoboPart->m_durable = static_cast<s16>(spiGetStackInt(stack++));

      for (int i = 0; i < 8; ++i)
      {
        SpiRoboPart->m_properties[i] = static_cast<s16>(spiGetStackInt(stack++));
      }
      SpiRoboPart->m_unk_field_1E = static_cast<EAttackType>(spiGetStackInt(stack++));
      break;
    case 2:
      SpiRoboPart->m_unk_field_4 = static_cast<s16>(spiGetStackInt(stack++));
      SpiRoboPart->m_unk_field_20 = static_cast<EAttackType>(spiGetStackInt(stack++));
      break;
    case 3:
      SpiRoboPart->m_battery_max = static_cast<s16>(spiGetStackInt(stack++));
      break;
    default:
      break;
  }

  ++SpiRoboPart;
  return true;
}

// 001953a0
static bool _DATAGUARDNUM(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "GRDNUM"
  trace_script_call(stack, stack_count);

  GameItemDataManage.m_n_guarddata = static_cast<s16>(spiGetStackInt(stack));

  return true;
}

// 001953d0
static bool _DATAGUARD(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "GRD"
  trace_script_call(stack, stack_count);

  auto index = static_cast<ECommonItemData>(spiGetStackInt(stack++));
  auto guard_data = GameItemDataManage.GetGuardData(index);

  if (guard_data == nullptr)
  {
    return false;
  }

  guard_data->m_unk_field_0 = static_cast<s16>(spiGetStackInt(stack++));

  return true;
}

static bool _DATAFISHINIT(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "FISHINIT"
  trace_script_call(stack, stack_count);

  GameItemDataManage.m_n_fishdata = static_cast<s16>(spiGetStackInt(stack++));
  SpiFish = GameItemDataManage.m_fishdata;

  return true;
}

// 001952a0
static bool _DATAFISH(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "FISH"
  trace_script_call(stack, stack_count);

  auto index = static_cast<ECommonItemData>(spiGetStackInt(stack++));
  SpiFish = GameItemDataManage.GetFishData(index);

  if (SpiFish == nullptr)
  {
    log_warn("{}: SpiFish is nullptr!", __func__);
    return false;
  }

  SpiFish->m_unk_field_0 = spiGetStackFloat(stack++);
  SpiFish->m_unk_field_4 = static_cast<s16>(spiGetStackInt(stack++));
  SpiFish->m_unk_field_6 = static_cast<s16>(spiGetStackInt(stack++));
  SpiFish->m_unk_field_A = static_cast<s16>(spiGetStackInt(stack++));
  SpiFish->m_unk_field_C = static_cast<s16>(spiGetStackInt(stack++));
  SpiFish->m_unk_field_E = static_cast<s16>(spiGetStackInt(stack++));
  SpiFish->m_unk_field_8 = static_cast<s16>(spiGetStackInt(stack++));

  if (stack_count >= 9)
  {
    SpiFish->m_unk_field_10 = static_cast<s16>(spiGetStackInt(stack++));
  }

  return true;
}

static bool _MES_SYS(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
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

static bool _MES_SYS_SPECTOL(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "MES_SYSSPE"
  trace_script_call(stack, stack_count);

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
  "ROBOINIT",  _DATAROBOINIT,
  "RB_PARTS",   _DATAROBO_ANALYZE,
  "GRDNUM",     _DATAGUARDNUM,
  "GRD",        _DATAGUARD,
  "FISHINIT",   _DATAFISHINIT,
  "FISH",       _DATAFISH,
  "MES_SYS",    _MES_SYS,
  "MES_SYSSPE", _MES_SYS_SPECTOL,
  NULL, nullptr
};

// 00194690
s16 CDataRoboPart::GetOffsetNo() const
{
  log_trace("CDataRoboPart::{}()", __func__);

  return m_offset_no;
}

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

  m_n_com_itemdata = static_cast<s16>(comdatapt_num);
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

// 00195630
void CGameData::LoadItemSystemMes(Language language)
{
  log_trace("CGameData::{}({})", __func__, common::to_underlying(language));

  using namespace common;
  auto file_path = file_helpers::resolve_data_path("menu/cfg7/comdatmes{}.cfg", common::to_underlying(language));

  auto fs = file_stream::open(file_path, "rb");
  auto file_size = fs->size();

  auto file_buf = std::make_unique<char[]>(file_size);
  bool result = fs->read_buffer_checked(file_buf.get(), file_size);

  if (file_buf != nullptr && result)
  {
    CScriptInterpreter script_interpreter{};
    script_interpreter.SetTag(gamedata_tag.data());
    script_interpreter.SetScript(file_buf.get(), file_size);
    script_interpreter.Run();
  }
  else
  {
    log_warn("{} open error!!!", file_path);
  }
}

// 00195770
SDataItemCommon* CGameData::GetCommonData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, common::to_underlying(index));

  auto id = common::to_underlying(index);
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
  log_trace("CGameData::{}({})", __func__, common::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (common_data->m_category_id >= m_n_weapondata)
  {
    return nullptr;
  }

  if (m_weapondata == nullptr)
  {
    return nullptr;
  }

  if (ConvertUsedItemType(common_data->m_type) == UsedType::Weapon)
  {
    return &m_weapondata[common_data->m_category_id];
  }
  return nullptr;
}

// 00195890
CDataItem* CGameData::GetItemData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, common::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (common_data->m_category_id >= m_n_itemdata)
  {
    return nullptr;
  }

  if (m_itemdata == nullptr)
  {
    return nullptr;
  }

  auto type = ConvertUsedItemType(common_data->m_type);
  if (type == UsedType::Gift_Box || type == UsedType::Item_8 || type == UsedType::Item_Misc)
  {
    return &m_itemdata[common_data->m_category_id];
  }
  return nullptr;
}

// 00195940
CDataAttach* CGameData::GetAttachData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, common::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (common_data->m_category_id >= m_n_attachdata)
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
    return &m_attachdata[common_data->m_category_id];
  }
  return nullptr;
}

// 001959F0
CDataRoboPart* CGameData::GetRoboData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, common::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (common_data->m_category_id >= m_n_robodata)
  {
    return nullptr;
  }

  if (m_robodata == nullptr)
  {
    return nullptr;
  }

  return &m_robodata[common_data->m_category_id];
}

// 00195A60
CDataBreedFish* CGameData::GetFishData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, common::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (common_data->m_category_id >= m_n_fishdata)
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
    return &m_fishdata[common_data->m_category_id];
  }
  return nullptr;
}

// 00195B10
CDataGuard* CGameData::GetGuardData(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, common::to_underlying(index));

  auto common_data = GetCommonData(index);
  if (common_data == nullptr)
  {
    return nullptr;
  }

  if (common_data->m_category_id >= m_n_guarddata)
  {
    return nullptr;
  }

  if (m_guarddata == nullptr)
  {
    return nullptr;
  }

  return &m_guarddata[common_data->m_category_id];
}

// 00195B80
ComType CGameData::GetDataType(ECommonItemData index)
{
  log_trace("CGameData::{}({})", __func__, common::to_underlying(index));

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

  for (int i = 0; i < m_n_com_itemdata; ++i)
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

  using namespace common;
  auto file_path = file_helpers::resolve_data_path("menu/cfg7/{}", config_file_name);

  auto fs = file_stream::open(file_path, "rb");
  auto file_size = fs->size();

  auto file_buf = std::make_unique<char[]>(file_size);
  bool result = fs->read_buffer_checked(file_buf.get(), file_size);

  if (file_buf == nullptr || !result)
  {
    log_warn("{} open error !!!", config_file_name);
    return false;
  }

  CScriptInterpreter script_interpreter{};
  script_interpreter.SetTag(gamedata_tag.data());
  script_interpreter.SetScript(file_buf.get(), file_size);
  script_interpreter.Run();
  return true;
}

// 00195C20
SDataItemCommon* GetCommonItemData(ECommonItemData index)
{
  log_trace("{}({})", __func__, common::to_underlying(index));

  return GameItemDataManage.GetCommonData(index);
}

// 00195C30
CDataItem* GetItemInfoData(ECommonItemData index)
{
  log_trace("{}({})", __func__, common::to_underlying(index));

  return GameItemDataManage.GetItemData(index);
}

// 00195C40
CDataWeapon* GetWeaponInfoData(ECommonItemData index)
{
  log_trace("{}({})", __func__, common::to_underlying(index));

  return GameItemDataManage.GetWeaponData(index);
}

// 00195C50
CDataRoboPart* GetRoboPartInfoData(ECommonItemData index)
{
  log_trace("{}({})", __func__, common::to_underlying(index));

  return GameItemDataManage.GetRoboData(index);
}

// 00195C60
CDataBreedFish* GetBreedFishInfoData(ECommonItemData index)
{
  log_trace("{}({})", __func__, common::to_underlying(index));

  return GameItemDataManage.GetFishData(index);
}

// 00195C70
std::string GetItemFileName(MAYBE_UNUSED ECommonItemData item_id, MAYBE_UNUSED sint i)
{
  log_trace("{}({}, {})", __func__, common::to_underlying(item_id), i);

  todo;
  return "";
}

// 00195C70
std::string GetItemFilePath(MAYBE_UNUSED ECommonItemData item_id, MAYBE_UNUSED sint i)
{
  log_trace("{}({})", __func__, common::to_underlying(item_id), i);

  todo;
  return "";
}

// 00195EC0
ECommonItemDataType GetItemDataType(ECommonItemData index)
{
  log_trace("{}({})", __func__, common::to_underlying(index));

  return GameItemDataManage.GetDataType(index);
}

// 00195ED0
s32 GetItemDataAttribute(ECommonItemData item_id)
{
  if (auto com_data = GameItemDataManage.GetCommonData(item_id); com_data != nullptr)
  {
    return com_data->m_attribute;
  }
  return 0;
}

// 00195F10
UsedType ConvertUsedItemType(ComType type)
{
  log_trace("CGameData::{}({})", __func__, static_cast<int>(type));

  // Did runtime analysis to determine these
  static const std::unordered_map<ComType, UsedType> convert_table = {
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
    {ComType::Spectrumized_Item, UsedType::Attach},
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
    {ComType::Gift_Capsule, UsedType::Gift_Box},
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
    if (common::to_underlying(type) < 0)
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

// 00196040
std::string GetItemMessage(ECommonItemData index)
{
  log_trace("{}({})", __func__, common::to_underlying(index));

  auto common_data = GameItemDataManage.GetCommonData(index);
  
  if (common_data == nullptr)
  {
    return "";
  }

  return common_data->m_name;
}
