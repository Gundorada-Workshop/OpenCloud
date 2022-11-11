#pragma once
#include <array>
#include "glm/glm.hpp"
#include "common/debug.h"
#include "common/types.h"

// ~ 002CBD00 - 002CD0E0
class CFragment
{
public:
  // 002CC230
  CFragment();

  // 0
  _DWORD m_unk_field_0;
  // 4
  _DWORD m_unk_field_4;
  // 10
  glm::vec4 m_unk_field_10;
  // 20
  glm::vec4 m_unk_field_20;
  // 30
  glm::vec4 m_unk_field_30;
  // 40
  glm::vec4 m_unk_field_40;
  // 50
  _DWORD m_unk_field_50;

  // ALIGNED SIZE 0x60 
};

class CBPot
{
public:
  // 002CC7A0
  CBPot();

  // 0
  _DWORD m_unk_field_0;
  // 4
  _DWORD m_unk_field_4;
  // 8
  _DWORD m_unk_field_8;
  // C
  _DWORD m_unk_field_C;
  // 10
  _DWORD m_unk_field_10;
  // 20
  glm::vec4 m_unk_field_20;
  // 30
  _DWORD m_unk_field_30;
  // 40
  std::array<CFragment, 32> m_fragments;
  // C40
  _DWORD m_unk_field_C40;
};

class CPot
{
public:
  // 002CD050
  CPot(bool b);
  CPot();

  // 0
  _DWORD m_unk_field_0;
  // 4
  _DWORD m_unk_field_4;
  // 10
  glm::vec4 m_unk_field_10;
  // 20
  glm::vec4 m_unk_field_20;
  // 30
  glm::vec4 m_unk_field_30;
  // 40
  glm::vec4 m_unk_field_40;
  // 50
  glm::vec4 m_unk_field_50;
  // 60
  glm::vec4 m_unk_field_60;
  // 70
  _DWORD m_unk_field_70;

  // ALIGNED SIZE 0x80
};