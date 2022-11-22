#include <array>

#include "common/data_stream.h"
#include "common/file_helpers.h"
#include "common/log.h"
#include "common/strings.h"
#include "common/types.h"

#include "dc2/mainloop.h"
#include "dc2/mg_lib.h"
#include "dc2/npc.h"
#include "dc2/script_interpreter.h"

set_log_channel("npc");

// 00377FB4
static s32 NpcBaseDataTotalNum{};
// 00377FB8
static u8 npc_spi_count_num{};
// 01F0A3A0
static std::array<SPartyNPCData, 180> NpcBaseData{};

// 002AB0E0
static bool _NPC_NUM(SPI_STACK* stack, int stack_count)
{
  // "NPC_NUM"
  trace_script_call(stack, stack_count);

  NpcBaseDataTotalNum = spiGetStackInt(stack++);

  return true;
}

// 002AB110
static bool _NPC_INFO(SPI_STACK* stack, int stack_count)
{
  // "NPC_INFO"
  trace_script_call(stack, stack_count);

  auto& npc_info = NpcBaseData[npc_spi_count_num++];
  npc_info.m_id = static_cast<ENPCID>(spiGetStackInt(stack++));

  char* name = spiGetStackString(stack++);
  char* model_name = spiGetStackString(stack++);

  if (name != nullptr)
  {
    npc_info.m_name = std::string(name);
  }

  if (model_name != nullptr)
  {
    npc_info.m_model_name = std::string(model_name);
  }

  npc_info.m_unk_field_31 = spiGetStackInt(stack++);
  npc_info.m_unk_field_30 = spiGetStackInt(stack++);
  npc_info.m_unk_field_2F = spiGetStackInt(stack++);
  npc_info.m_unk_field_32 = spiGetStackInt(stack++);
  npc_info.m_unk_field_33 = spiGetStackInt(stack++);
  npc_info.m_unk_field_34 = spiGetStackInt(stack++);
  npc_info.m_unk_field_35 = spiGetStackInt(stack++);
  npc_info.m_unk_field_2 = spiGetStackInt(stack++);

  return true;
}

// 00354520
static const std::array<SPI_TAG_PARAM, 3> npc_spitag =
{
  "NPC_NUM",  _NPC_NUM,
  "NPC_INFO", _NPC_INFO,
  NULL, nullptr
};

// 002AB250
void LoadNPCCfg()
{
  log_trace("{}()", __func__);

  npc_spi_count_num = 0;

  using namespace common;
  auto file_path = file_helpers::resolve_data_path("npc{}.cfg", std::to_underlying(LanguageCode));

  auto fs = file_stream::open(file_path, "rb");
  auto file_size = fs->size();

  auto file_buf = std::make_unique<char[]>(file_size);
  bool result = fs->read_buffer_checked(file_buf.get(), file_size);

  if (file_buf != nullptr && result)
  {
    CScriptInterpreter script_interpreter{};
    script_interpreter.SetTag(npc_spitag.data());
    script_interpreter.SetScript(file_buf.get(), file_size);
    script_interpreter.Run();
  }
  else
  {
    log_warn("{} open error!!!", file_path);
  }

  NpcBaseDataTotalNum = npc_spi_count_num;
}


// 002AB3A0
std::string GetNPCModelName(ENPCID npc_id)
{
  log_trace("{}({})", __func__, std::to_underlying(npc_id));

  auto npc_data = GetPartyNPCData(npc_id);

  if (npc_data == nullptr)
  {
    return "";
  }

  return npc_data->m_model_name;
}

// 002AB3D0
std::string GetNPCName(ENPCID npc_id)
{
  log_trace("{}({})", __func__, std::to_underlying(npc_id));

  auto npc_data = GetPartyNPCData(npc_id);

  if (npc_data == nullptr)
  {
    return "";
  }

  return npc_data->m_name;
}

// 002AB400
std::string GetPartyCharaModelName(ENPCID npc_id, int i)
{
  log_trace("{}({}, {})", __func__, std::to_underlying(npc_id), i);

  using namespace common;

  // FIXME: magic
  if (std::to_underlying(npc_id) < 0 || std::to_underlying(npc_id) > 32)
  {
    return "";
  }

  std::string model_name = GetNPCModelName(npc_id);
  if (model_name == "")
  {
    return "";
  }

  switch (i)
  {
    case 0:
      return file_helpers::resolve_data_path("chara/{}.chr", model_name);
    case 1:
      return file_helpers::resolve_data_path("info.cfg");
    case 2:
      return file_helpers::resolve_data_path("event/train/t{}.chr", model_name);
    case 3:
      return file_helpers::resolve_data_path("menu/npc/t{}.chr", model_name);
    default:
      return "";
  }
}

// 002AB510
SPartyNPCData* GetPartyNPCData(ENPCID npc_id)
{
  log_trace("{}({})", __func__, std::to_underlying(npc_id));

  for (int i = 0; i < NpcBaseDataTotalNum; ++i)
  {
    if (NpcBaseData[i].m_id == npc_id)
    {
      return &NpcBaseData[i];
    }
  }

  return nullptr;
}
