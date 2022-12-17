#include "common/log.h"

#include "dc2/mainloop.h"
#include "dc2/quest.h"
#include "dc2/script_interpreter.h"

set_log_channel("quest");

// 00378870
static CQuestManager* spi_questman{ nullptr };
// 00378874 (is mgCMemory - not used here)

static usize spi_quest_info_index{ 0 };

// 0031A7B0
static CQuestData* GetQuestData()
{
  log_trace("{}()", __func__);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return nullptr;
  }

  return &save_data->m_quest_data;
}

// 0031A800
std::shared_ptr<QUEST_INFO> CQuestManager::GetQuestInfo(usize quest_id)
{
  log_trace("CQuestManager::{}({})", __func__, quest_id);

  for (auto quest_info : m_quest_info)
  {
    if (m_quest_info[quest_id]->m_quest_id == quest_id)
    {
      return m_quest_info[quest_id];
    }
  }

  return nullptr;
}

static bool _quest_NUM(SPI_STACK* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  // Instead of using an mgCMemory here, we store all of the QUEST_INFO
  // as pointers (to avoid invalidation) in a vector, and then store the
  // current QUEST_INFO that is being created as an index.
  usize capacity = spiGetStackInt(stack);
  spi_questman->m_quest_info.reserve(capacity);
  spi_quest_info_index = 0;

  for (usize i = 0; i < capacity; ++i)
  {
    spi_questman->m_quest_info.push_back(std::make_shared<QUEST_INFO>());
  }

  return true;
}

static bool _quest_NEW(SPI_STACK* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  spi_questman->m_quest_info[spi_quest_info_index]->m_quest_id = spiGetStackInt(stack++);
  spi_questman->m_quest_info[spi_quest_info_index]->m_unk_field_4 = spiGetStackString(stack++);
  return true;
}

static bool _quest_COMMENT(SPI_STACK* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  sint i = spiGetStackInt(stack++);
  const char* s = spiGetStackString(stack++);

  if (i == 0)
  {
    spi_questman->m_quest_info[spi_quest_info_index]->m_unk_field_88 = s;
  }
  else if (i > 0)
  {
    spi_questman->m_quest_info[spi_quest_info_index]->m_unk_field_18A[i - 1] = s;
  }

  return true;
}

static bool _quest_END(SPI_STACK* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  ++spi_quest_info_index;

  return true;
}

// 0035E870
static const std::array<SPI_TAG_PARAM, 5> quest_cmd_tag =
{
  "NUM",    _quest_NUM,
  "NEW",    _quest_NEW,
  "COMENT", _quest_COMMENT, // (sic)
  "END",    _quest_END,
  NULL, nullptr
};

// 0031A9C0
void CQuestManager::LoadCfg(char* script, usize script_length)
{
  log_trace("CQuestManager::{}({}, {})", __func__, fmt::ptr(script), script_length);

  spi_questman = this;

  CScriptInterpreter interpreter{};

  interpreter.SetTag(quest_cmd_tag.data());
  interpreter.SetScript(script, script_length);
  interpreter.Run();
}

// 0031AA40
void CQuestData::SetQuestFlag(usize index, bool flag)
{
  log_trace("CQuestData::{}({}, {})", __func__, index, flag);

  if (index >= m_play_quest_data.size())
  {
    return;
  }

  m_play_quest_data[index].m_unlocked_flag = flag;
}

// 0031AA40
void CQuestData::QuestClear(usize index)
{
  log_trace("CQuestData::{}({})", __func__, index);

  if (index >= m_play_quest_data.size())
  {
    return;
  }

  m_play_quest_data[index].m_clear_flag = true;
}

// 0031AAB0
PLAY_QUEST_DATA* CQuestData::GetPlayQuestData(usize index)
{
  log_trace("CQuestData::{}({})", __func__, index);

  if (index >= m_play_quest_data.size())
  {
    return nullptr;
  }

  return &m_play_quest_data[index];
}

// 0031AAE0
void QuestRequestSetFlag(usize index, bool flag)
{
  log_trace("CQuestData::{}({}, {})", __func__, index, flag);

  auto quest_data = GetQuestData();

  if (quest_data == nullptr)
  {
    return;
  }

  quest_data->SetQuestFlag(index, flag);
}

// 0031AB30
void QuestRequestClear(usize index, bool flag)
{
  log_trace("CQuestData::{}({}, {})", __func__, index, flag);

  auto quest_data = GetQuestData();

  if (quest_data == nullptr)
  {
    return;
  }

  quest_data->QuestClear(index);
}

// 0031AB70
EQuestRequestStatus GetQuestRequestStatus(usize index)
{
  log_trace("CQuestData::{}({})", __func__, index);

  using enum EQuestRequestStatus;

  auto quest_data = GetQuestData();

  if (quest_data == nullptr)
  {
    return Invalid;
  }

  auto play_quest_data = quest_data->GetPlayQuestData(index);

  if (play_quest_data == nullptr)
  {
    return Invalid;
  }

  if (play_quest_data->m_clear_flag)
  {
    return Clear;
  }

  if (play_quest_data->m_unlocked_flag)
  {
    return Unlocked;
  }

  return Locked;
}
