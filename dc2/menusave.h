#pragma once
#include <array>
#include "editdata.h"
#include "quest.h"
#include "userdata.h"

// ~ 002F12D0 - 002F76C0

// TODO THIS FILE
class CMemoryCardManager {};
class CSphidaData {};
struct GYORACE_DATA {};
class CGyoRaceData {};
class CSubGameData {};

struct SV_CONFIG_OPTION
{
  // 35
  s8 m_unk_field_35;

  // SIZE 0xD2C
};

class CSaveDataDungeon
{
public:
  // 0019b160
  void Initialize();
};

class CMenuSystemData
{
public:
  // 002F12D0
  CMenuSystemData();
  // 002f1300
  void MenuSystemDataInit();
};

class CSaveData
{
public:
  // 002f61f0
  void Initialize();

  // 002f6780
  void InitBitCtrl();

  // ?

  // 1C24
  std::array<CEditData, 5> m_edit_data{};
  // 1C574
  SV_CONFIG_OPTION m_sv_config_option{};
  // 1D2A0
  CUserDataManager m_user_data_manager{};
  // 62A40
  CQuestData m_quest_data;
  // 65930
  CMenuSystemData m_menu_system_data;
};