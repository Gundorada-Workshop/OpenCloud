#pragma once
#include <array>

#include "common/debug.h"
#include "common/types.h"

// ~ 002AB0E0 - 002AB570

enum class ENPCID : s16
{

};

struct SPartyNPCData
{
public:
  // 0
  ENPCID m_id{};
  // 2
  s8 m_unk_field_2{};
  // 3 (nice align bro)
  std::string m_name{};
  // 1F
  std::string m_model_name{};
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

// 002AB3A0
std::string GetNPCModelName(ENPCID npc_id);

// 002AB3D0
std::string GetNPCName(ENPCID npc_id);

// 002AB400
std::string GetPartyCharaModelName(ENPCID npc_id, int i);

// 002AB510
SPartyNPCData* GetPartyNPCData(ENPCID npc_id);
