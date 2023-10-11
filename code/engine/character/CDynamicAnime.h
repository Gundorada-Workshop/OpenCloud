#pragma once

#include "common/types.h"

#include "engine/mg/mg_lib.h"

// ~ 0016A140 - 0017C240

class CDynamicAnime
{
public:
  void Load(MAYBE_UNUSED const char* script, MAYBE_UNUSED sint script_size,
            MAYBE_UNUSED mgCFrame* frame, MAYBE_UNUSED mgCMemory* stack);

  void NewVertexTable(MAYBE_UNUSED sint unk, MAYBE_UNUSED mgCMemory* stack);
  void NewBoundingBoxTable(MAYBE_UNUSED sint unk, MAYBE_UNUSED mgCMemory* stack);
  void NewCollisionTable(MAYBE_UNUSED sint unk, MAYBE_UNUSED mgCMemory* stack);
  // 00179E70
  //void SetWind(f32 velocity, vec4& direction);
  // 00179E80
  void ResetWind();
  // 00179E90
  void SetFloor(f32 floor);
  // 00179EA0
  void ResetFloor();

  // 68
  f32 m_wind_velocity;
  // 70
  vec4 m_wind_direction{ };

  // ?

  // 88
  bool m_unk_field_88;
  // 8C
  f32 m_floor;

  // SIZE 0x90
};