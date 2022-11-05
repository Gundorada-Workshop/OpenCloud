#include <string>
#include "common/log.h"
#include "userdata.h"

set_log_channel("userdata");

// 01E9B130
static CBattleCharaInfo BattleParameter;

namespace userdata
{
  void SInit()
  {
    log_trace("SInit()");

    BattleParameter.Initialize();
  }
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
    game_data_used = CGameDataUsed();
  }

  for (auto& unk_struct : m_unk_field_3F48)
  {
    for (auto& game_data_used : unk_struct.m_unk_field_2C)
    {
      game_data_used = CGameDataUsed();
    }
    for (auto& game_data_used : unk_struct.m_unk_field_170)
    {
      game_data_used = CGameDataUsed();
    }
  }

  for (auto& game_data_used : m_unk_field_4690)
  {
    game_data_used = CGameDataUsed();
  }

  for (auto& game_data_used : m_unk_field_4880)
  {
    game_data_used = CGameDataUsed();
  }

  for (auto& game_data_used : m_fish_aquarium.m_unk_field_4)
  {
    game_data_used = CGameDataUsed();
  }

  for (auto& game_data_used : m_fish_aquarium.m_unk_field_28C)
  {
    game_data_used = CGameDataUsed();
  }

  for (auto& game_data_used : m_fish_aquarium.m_unk_field_43C)
  {
    game_data_used = CGameDataUsed();
  }

  m_fish_aquarium.Initialize();
  m_invent_user_data.Initialize();
  m_fishing_tournament.Initialize();
  m_fishing_record = CFishingRecord();
}

// 0019B160
void CUserDataManager::Initialize()
{
  log_trace("CUserDataManager::Initialize()");

  memset(this, 0, sizeof(this));

  todo;
}

// 0019EF70
void CBattleCharaInfo::Initialize()
{
  log_trace("CBattleCharaInfo::Initialize()");

  memset(this, 0, sizeof(this));

  m_unk_field_0 = 0;
  m_unk_field_6 = -1;
  m_unk_field_8 = 0;
  m_unk_field_74 = 0;
  m_unk_field_30 = 0;
  m_unk_field_7C = 0;
  m_unk_field_80 = -1.0f;
  m_unk_field_84 = -1.0f;
}