#pragma once
#include <array>

#include "common/debug.h"

// ~ 001A76C0 - 001B5FD0

// TODO THIS FILE
class CEditMap
{
};

class CEditPartsInfo
{
};

class CEditHouse
{
};

class CEditParts
{
};

class CEditEvent
{
public:
  // 002EF9B0
  void Reset();

  // 0
  unk32 m_unk_field_0{ 0 };

  // 4
  unk32 m_unk_field_4{ 0 };

  // ?

  // C
  unk32 m_unk_field_C{ 0 };

  // 10
  s32 m_unk_field_10{ -1 };

  // ?
  
  // 20
  unks<0xD0> m_unk_field_20{};

  // ?
  
  // 128
  s8 m_unk_field_128{ 0 };
  
  // ?

  // 148
  s32 m_unk_field_148{ -1 };

  // SIZE 0x14C
};

struct EditDebugInfo
{
public:
  // 0
  unk32 m_unk_field_0{ 0 };

  // 4
  unk32 m_unk_field_4{ 0 };

  // 8
  unk32 m_unk_field_8{ 0 };

  // C
  unk32 m_unk_field_C{ 0 };

  // 10
  unk32 m_unk_field_10{ 0 };

  // 14
  unk32 m_unk_field_14{ 0 };

  // 18
  unk32 m_unk_field_18{ 0 };

  // 1C
  unk32 m_unk_field_1C{ 0 };

  // 20
  unk32 m_unk_field_20{ 0 };

  // 24
  unk32 m_unk_field_24{ 0 };

  // 28
  unk32 m_unk_field_28{ 0 };

  // 2C
  unk32 m_unk_field_2C{ 0 };

  // 30
  unk32 m_unk_field_30{ 0 };

  // 34
  unk32 m_unk_field_34{ 0 };

  // 38
  unk32 m_unk_field_38{ 0 };

  // Size 0x3C (? - probably correct; aligned to 0x40)
};

class CWaveTable
{
public:
  // 001A2110
  CWaveTable();

  // 0
  std::array<std::array<unk32, 24>, 24> m_unk_field_0;

  // 900
  std::array<std::array<unk32, 24>, 24> m_unk_field_900;

  // 1200
  unk32 m_unk_field_1200;

  // SIZE 0x1208 (vtable w/ (probably not called) destructor only @ 0x1204)
};