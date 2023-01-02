#pragma once
#include <array>

#include "common/debug.h"
#include "common/types.h"

// ~ 002CBD00 - 002CD0E0
class CFragment
{
public:
  // 002CC230
  CFragment();

  // 0
  unk32 m_unk_field_0;
  // 4
  unk32 m_unk_field_4;
  // 10
  //vec4 m_unk_field_10;
  // 20
  //vec4 m_unk_field_20;
  // 30
  //vec4 m_unk_field_30;
  // 40
  //vec4 m_unk_field_40;
  // 50
  unk32 m_unk_field_50;

  // ALIGNED SIZE 0x60 
};

class CBPot
{
public:
  // 002CC7A0
  CBPot();

  // 0
  unk32 m_unk_field_0;
  // 4
  unk32 m_unk_field_4;
  // 8
  unk32 m_unk_field_8;
  // C
  unk32 m_unk_field_C;
  // 10
  unk32 m_unk_field_10;
  // 20
  //vec4 m_unk_field_20;
  // 30
  unk32 m_unk_field_30;
  // 40
  std::array<CFragment, 32> m_fragments;
  // C40
  unk32 m_unk_field_C40;
};

class CPot
{
public:
  // 002CD050
  CPot(bool b);
  CPot();

  // 0
  // TODO: probably enum
  s32 m_status;
  // 4
  unk32 m_unk_field_4;
  // 10
  //vec3 m_position;
  // 20
  //vec4 m_unk_field_20;
  // 30
  //vec4 m_unk_field_30;
  // 40
  //vec4 m_unk_field_40;
  // 50
  //vec4 m_unk_field_50;
  // 60
  //vec4 m_unk_field_60;
  // 70
  unk32 m_unk_field_70;

  // ALIGNED SIZE 0x80
};