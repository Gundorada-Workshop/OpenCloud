#pragma once
#include <array>
#include "common/debug.h"

// ~ 001A76C0 - 001B5FD0

namespace editloop
{
  // 00373A70
  void SInit();
}

// TODO THIS FILE
class CEditMap {};
class CEditPartsInfo {};
class CEditHouse {};
class CEditParts {};

class CEditEvent
{
public:
  // 002EF9B0
  void Reset();

  // 0
  _DWORD m_unk_field_0;
  // 4
  _DWORD m_unk_field_4;
  
  // ?

  // C
  _DWORD m_unk_field_C;
  // 10
  s32 m_unk_field_10;

  // ?
  
  // 20
  _UNKNOWNSTRUCT(0xD0) m_unk_field_20;

  // ?
  
  // 128
  s8 m_unk_field_128;
  
  // ?

  // 148
  s32 m_unk_field_148;

  // SIZE 0x14C
};

struct EditDebugInfo
{
public:
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
  // 14
  _DWORD m_unk_field_14;
  // 18
  _DWORD m_unk_field_18;
  // 1C
  _DWORD m_unk_field_1C;
  // 20
  _DWORD m_unk_field_20;
  // 24
  _DWORD m_unk_field_24;
  // 28
  _DWORD m_unk_field_28;
  // 2C
  _DWORD m_unk_field_2C;
  // 30
  _DWORD m_unk_field_30;
  // 34
  _DWORD m_unk_field_34;
  // 38
  _DWORD m_unk_field_38;

  // Size 0x3C (? - probably correct; aligned to 0x40)
};

class CWaveTable
{
public:
  // 001A2110
  CWaveTable();

  // 0
  std::array<std::array<_DWORD, 24>, 24> m_unk_field_0;
  // 900
  std::array<std::array<_DWORD, 24>, 24> m_unk_field_900;
  // 1200
  _DWORD m_unk_field_1200;

  // SIZE 0x1208 (vtable w/ (probably not called) destructor only @ 0x1204)
};