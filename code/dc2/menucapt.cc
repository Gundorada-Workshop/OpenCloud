#include <array>

#include "common/log.h"
#include "common/types.h"

#include "dc2/menucapt.h"
#include "dc2/mg_lib.h"
#include "dc2/script_interpreter.h"

set_log_channel("menucapt");

// 00377FB4
static s32 NpcBaseDataTotalNum{};
// 00377FB8
static u8 npc_spi_count_num{};
// 01F0A370
static mgCMemory MenuChapterStack{};
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
  npc_info.m_unk_field_0 = spiGetStackInt(stack++);

  char* str1 = spiGetStackString(stack++);
  char* str2 = spiGetStackString(stack++);

  if (str1 != nullptr)
  {
    strcpy_s(npc_info.m_unk_field_3.data(), npc_info.m_unk_field_3.size(), str1);
  }

  if (str2 != nullptr)
  {
    strcpy_s(npc_info.m_unk_field_1F.data(), npc_info.m_unk_field_1F.size(), str2);
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