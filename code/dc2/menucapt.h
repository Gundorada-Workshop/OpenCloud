#pragma once
#include <array>

#include "common/debug.h"
#include "common/types.h"

// ~ 002AAA20 - 002AB570

enum class ENPCID;

struct SPartyNPCData
{
public:
  // 0
  ENPCID m_id{};
  // 2
  s8 m_unk_field_2{};
  // 3 (nice align bro)
  std::array<char, 28> m_name{};
  // 1F
  std::array<char, 16> m_model_name{};
  // 2F
  s8 m_unk_field_2F{};
  // 30
  s8 m_unk_field_30{};
  // 31
  s8 m_unk_field_31{};
  // 32
  s8 m_unk_field_32{};
  // 33
  s8 m_unk_field_33{};
  // 34
  s8 m_unk_field_34{};
  // 35
  s8 m_unk_field_35{};

  // SIZE 0x36
};

// 002AB510
SPartyNPCData* GetPartyNPCData(ENPCID npc_id);

// 002AB3A0
const char* GetNPCModelName(ENPCID npc_id);

// 002AB3D0
const char* GetNPCName(ENPCID npc_id);
