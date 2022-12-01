#pragma once
#include <array>

#include "common/debug.h"
#include "common/types.h"

// ~ 00168B60 - 001699F0

class CMdsList
{
public:
  // 0
  char* m_unk_field_0;
  // 4
  unk m_unk_field_4;
  // 8
  unk m_unk_field_8;
};

class CIMGList
{
public:
  // 0
  char* m_unk_field_0;
  // 4
  unk m_unk_field_4;
};

class CMdsListSet
{
public:
  // 001690D0
  void Initialize();

  // 0
  usize m_n_mds_list;
  // 10
  std::array<CMdsList, 8> m_mds_list;
  // 90
  usize m_n_img_list;
  // 94
  std::array<CIMGList, 16> m_img_list;
};