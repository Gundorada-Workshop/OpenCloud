#pragma once

// ~ ? - ?
// Maybe this is for scoops?


struct QUEST_INFO
{
  // 0
  s32 m_quest_id{};
  // 4
  std::string m_unk_field_4{};

  // 88
  std::string m_unk_field_88{};

  // 18A
  std::array<std::string, 4> m_unk_field_18A{};

  // SIZE 0x394
};


class CQuestManager
{
public:
  // 0031A800
  std::shared_ptr<QUEST_INFO> GetQuestInfo(usize quest_id);
  // 0031A9C0
  void LoadCfg(char* script, usize script_length);

  // using pointers here because other code might need
  // pointers to QUEST_INFO and we don't want to invalidate them
  std::vector<std::shared_ptr<QUEST_INFO>> m_quest_info{};

  // SIZE 0x8
};

struct PLAY_QUEST_DATA
{
  // 0
  bool m_unlocked_flag{ false };
  // 1
  bool m_clear_flag{ false };

  // Size 0x10
};

enum class EQuestRequestStatus
{
  Invalid = -1,
  Locked = 0,
  Unlocked = 1,
  Clear = 2,
};

class CQuestData
{
public:
  // Just zero-initialize all members instead, use new-placement if needed
  // 0031aa30
  //void Initialize();

  // 0031AA40
  void SetQuestFlag(usize index, bool flag);

  // 0031AA40
  void QuestClear(usize index);

  // 0031AAB0
  PLAY_QUEST_DATA* GetPlayQuestData(usize index);

  std::array<PLAY_QUEST_DATA, 0x40> m_play_quest_data{};
  // Size 0x480
};

// 0031AAE0
void QuestRequestSetFlag(usize index, bool flag);

// 0031AB30
void QuestRequestClear(usize index, bool flag);

// 0031AB70
EQuestRequestStatus GetQuestRequestStatus(usize index);
