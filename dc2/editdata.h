#pragma once
#include <array>
#include "common/debug.h"

class CEditData
{
public:
  // 00194550
  CEditData();
  // 002a89c0
  void Initialize();
  // 002a8a10
  void InitPlaceData();

  // 0
  _UNKNOWN m_unk_field_0;
  // 4
  _UNKNOWN m_unk_field_4;
  // 8
  usize m_n_unk_field_C;
  // C
  std::array<_UNKNOWNSTRUCT(0x24), 300> m_unk_field_C;
  // 2A3C
  usize m_n_unk_field_2A40;
  // 2A40
  std::array<_UNKNOWNSTRUCT(0x10), 32> m_unk_field_2A40;
  // 2C40
  std::array<s16, 0x800> m_unk_field_2C40;
  // 4C40
  std::array<u8, 0x400> m_unk_field_4C40;
  // 5040
  _UNKNOWNSTRUCT(0xD0) m_unk_field_5040;
};