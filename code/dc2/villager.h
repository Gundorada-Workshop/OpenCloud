#pragma once
#include "common/debug.h"
#include "common/types.h"

// ~ 002CD0E0 - 002CDDB0

class CVillagerPlace
{
public:

  struct ProgressInfo
  {
  public:

  };
};

class CVillagerPlaceInfo
{
public:

};

class CVillagerData
{
public:
  // 002CD110
  void Initialize();

  // 0
  s32 m_unk_field_0;
  // 4
  s32 m_unk_field_4;
  // 8
  s32 m_unk_field_8;
  // C
  unk m_unk_field_C;
  // 10
  unk m_unk_field_10;
  // 14
  unk m_unk_field_14;
  // 18
  unk m_unk_field_18;
  // 1C
  unk m_unk_field_1C;
  // 20
  unk m_unk_field_20;
  // 24
  unk m_unk_field_24;
  // 28
  unk m_unk_field_28;
  // 2C
  unk m_unk_field_2C;
  // 30
  unk m_unk_field_30;
  // 34
  unk m_unk_field_34;
  // 38
  unk m_unk_field_38;
  // 3C
  unk m_unk_field_3C;
  // 40
  unk m_unk_field_40;
  // 50
  vec4 m_unk_field_50;
  // 60
  vec4 m_unk_field_60;
};

class CVillagerMngr
{
public:
  // 002CD220
  void Initialize();

  // 0
  unk m_unk_field_0;
  // 4
  usize m_n_villager_data;
  // 10
  std::array<CVillagerData, 0x20> m_villager_data;
};

class CVillagerInfo
{
public:

};