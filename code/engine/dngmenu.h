#pragma once
#include "common/debug.h"
#include "common/types.h"
#include "common/math.h"

#include "graph/rectangle.h"

#include "engine/mg/mg_lib.h"

// ~001EA760 - 001F2510

// forward-declare
class CDngFloorManager;
struct GLID_INFO;


class CMenuTreeMap
{

};

struct DNGMAP_ROOT_INFO
{
  // 0
  u8 m_unk_field_0{};
  // 1
  u8 m_unk_field_1{};
  // 2
  u8 m_unk_field_2{};
  
  // 4
  u8 m_unk_field_4{};
};

struct DNGMAP_ROOM_INFO
{
  // C
  u32 m_unk_field_C{};

  // ?

  // 14
  s8 m_unk_field_14{};

  // 3E
  s16 m_unk_field_3E{};
  // 40
  s16 m_unk_field_40{};
  // 42
  s8 m_unk_field_42{};
  
  // ?
  
  // 45
  u8 m_unk_field_45{};
  // 46
  u8 m_unk_field_46{};
  // 48
  f32 m_unk_field_48{};
};

struct TREASURE_BOX_FLOOR_INFO
{

};

struct GRID_PIECE
{
  // 0
  vec2 m_position{ };
  // 8
  GRID_PIECE* m_next{};
};

enum class EDngFreeMapFadeStatus : s32
{
  None = -1,
  FadeIn = 0,
  FadeOut = 1,
};

class CDngFreeMap
{
private:
  // 001EA830
  void InitializeTexture();

public:
  // 001EA760
  CDngFreeMap();

  // 001EE790
  void FadeIn(s32 duration);

  // 001EE7D0
  void FadeOut(s32 duration);

  // 001EE840
  // "SetKomaMove"
  void SetPieceMove(s16 i);

  // 0
  unk32 m_unk_field_0{ 0 };

  // 4
  CDngFloorManager* m_floor_manager{ nullptr };

  // 8
  bool m_unk_field_8{ true };

  // 9
  unk8 m_unk_field_9{ 0 };

  // A
  unk16 m_unk_field_A{ 0 };

  // C
  unk16 m_unk_field_C{ 0 };

  // 10
  f32 m_unk_field_10{ 0.0f };

  // 20
  graph::rect m_unk_field_20{ graph::rect::from_extent(120, 138, 420, 286) };

  // 30
  usize m_unk_field_30{ 0 };

  // 40
  std::array<graph::rect, 8> m_unk_field_40{ graph::rect::from_extent(0, 0, 0, 0) };

  // C0
  s16 m_unk_field_C0{ s16(-1) };

  // C2
  s16 m_unk_field_C2{ s16(-1) };

  // C4
  GLID_INFO* m_user_glid{ 0 };

  // C8
  s16 m_unk_field_C8{ 0 };

  // CC
  GLID_INFO* m_unk_field_CC{ nullptr };

  // D0
  s16 m_texb;

  // D4
  mgCTexture* m_unk_field_D4;

  // D8
  mgCTexture* m_unk_field_D8;

  // DC
  mgCTexture* m_unk_field_DC;

  // E0
  mgCTexture* m_unk_field_E0;

  // E4
  GRID_PIECE* m_unk_field_E4{ nullptr };

  // E8
  GRID_PIECE* m_unk_field_E8{ nullptr };

  // EC
  s16 m_unk_field_EC{ 0 };

  // F0
  f32 m_unk_field_F0{ 128.0f };

  // F4
  s32 m_fade_duration{ -1 }; // not read anywhere?

  // F8
  f32 m_fade_alpha{ 0.0f };

  // FC
  EDngFreeMapFadeStatus m_fade_status{ EDngFreeMapFadeStatus::None };

  // 100
  f32 m_unk_field_100{ 0.0f };

  // 104
  f32 m_unk_field_104{ 0.0f };

  // 108
  f32 m_unk_field_108{ 200.0f };

  // 10C
  f32 m_unk_field_10C{ 200.0f };
};