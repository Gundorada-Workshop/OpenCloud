#pragma once
#include <string>

#include "common/constants.h"
#include "common/debug.h"
#include "common/types.h"

#include "engine/event_func.h"

// ~ 0027DD00 - 00282AC0

struct EDIT_EVENT_INFO
{
  // 0
  //vec4 m_unk_field_0{};
  // 10
  //vec4 m_unk_field_10{};

  // 64
  s32 m_unk_field_64{};
  // 68 (buf size 0x20)
  std::string m_unk_field_68{};
  // 88
  s32 m_unk_field_88{};
  // 8C (buf size 0x40)
  std::string m_unk_field_8C{};
  // CC
  s32 m_unk_field_CC{};
  // D0
  s32 m_unk_field_D0{};
  // D4
  unk32 m_unk_field_D4{};
  // D8
  unk32 m_unk_field_D8{};

  // ?

  // E0
  unk32 m_unk_field_E0{};
  // E4
  unk32 m_unk_field_E4{};
  // E8
  unk32 m_unk_field_E8{};
  // EC
  unk32 m_unk_field_EC{};
  // F0
  s32 m_unk_field_F0{};

  // ?

  // 13C
  unk32 m_unk_field_13C{};
  // 140
  s32 m_unk_field_140{};
  // 144
  s32 m_unk_field_144{};

  // ?

  // 17C
  f32 m_unk_field_17C{};
  // 180
  f32 m_unk_field_180{};
  // 184
  f32 m_unk_field_184{};
  // 188
  f32 m_unk_field_188{};

  // 1BC
  s32 m_unk_field_1BC{};
  // 1C0
  s32 m_unk_field_1C0{};
  // 1C4
  s32 m_unk_field_1C4{};
  // 1C8
  s32 m_unk_field_1C8{};
  // 1CC
  s32 m_unk_field_1CC{};

  // 44C
  f32 m_keep_time{};

  // ALIGNED SIZE 0x450
};

class CEditEvent
{
public:
  // 002EF9B0
  void Reset();
  // 002EF9E0
  bool StartEvent(CSceneEventData* event_data);

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

// 01ECE430
extern EDIT_EVENT_INFO EdEventInfo;

// 01F04200
extern CCameraPas g_cmr_pas;
// 01F04B50
extern CCharaPas g_chara_pas;
// 01F05000
extern unk g_info;