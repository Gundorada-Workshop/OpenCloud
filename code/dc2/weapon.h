#pragma once
#include "common/types.h"

// ~001B5FD0 - 001BAA30

enum class ESpecialStatus;


enum class EDAMAGE_PARAMUnk :s8
{
  _0 = 0,
  _4 = 4,
  _11 = 11,
  _12 = 12,
};

struct DAMAGE_PARAM
{
  // 18
  EDAMAGE_PARAMUnk m_unk_field_18{};
};

// NOTE: These are probably just primitives only used for weapons
class CColPrim
{
public:
  // 8
  DAMAGE_PARAM* m_damage_param{};

  // ?

  // A0
  ESpecialStatus m_unk_field_A0{};
};

class CColPrimMan
{
};
