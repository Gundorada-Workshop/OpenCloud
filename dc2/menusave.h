#pragma once

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
};

class CSaveDataDungeon
{
public:
  // 0019b160
  void Initialize();
};

class CSaveData
{
public:
  // 002f61f0
  void Initialize();

  // 002f6780
  void InitBitCtrl();

  // 1C574
  SV_CONFIG_OPTION sv_config_option;
};

class CMenuSystemData
{
public:
  // 002F12D0
  CMenuSystemData();
  // 002f1300
  void MenuSystemDataInit();
};
