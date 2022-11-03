#pragma once

// ~ 002F12D0 - 002F76C0

// TODO THIS FILE
class CMemoryCardManager {};
class CSphidaData {};
struct GYORACE_DATA {};
class CGyoRaceData {};
class CSubGameData {};

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
};

class CMenuSystemData
{
public:
  // 002F12D0
  CMenuSystemData();
  // 002f1300
  void MenuSystemDataInit();
};
