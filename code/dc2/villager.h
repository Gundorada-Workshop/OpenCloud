#pragma once
#include <glm/glm.hpp>

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
  _UNKNOWN m_unk_field_C;
  // 10
  _UNKNOWN m_unk_field_10;
  // 14
  _UNKNOWN m_unk_field_14;
  // 18
  _UNKNOWN m_unk_field_18;
  // 1C
  _UNKNOWN m_unk_field_1C;
  // 20
  _UNKNOWN m_unk_field_20;
  // 24
  _UNKNOWN m_unk_field_24;
  // 28
  _UNKNOWN m_unk_field_28;
  // 2C
  _UNKNOWN m_unk_field_2C;
  // 30
  _UNKNOWN m_unk_field_30;
  // 34
  _UNKNOWN m_unk_field_34;
  // 38
  _UNKNOWN m_unk_field_38;
  // 3C
  _UNKNOWN m_unk_field_3C;
  // 40
  _UNKNOWN m_unk_field_40;
  // 50
  glm::vec4 m_unk_field_50;
  // 60
  glm::vec4 m_unk_field_60;
};

class CVillagerMngr
{
public:
  // 002CD220
  void Initialize();

  // 0
  _UNKNOWN m_unk_field_0;
  // 4
  usize m_n_villager_data;
  // 10
  std::array<CVillagerData, 0x20> m_villager_data;
};

class CVillagerInfo
{
public:

};