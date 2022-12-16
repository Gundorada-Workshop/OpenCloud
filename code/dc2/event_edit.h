#pragma once
#include <string>

#include "common/constants.h"
#include "common/debug.h"
#include "common/types.h"

#include "dc2/event_func.h"

// ~ 0027DD00 - 00282AC0

struct EDIT_EVENT_INFO
{
  // 0
  vec4 m_unk_field_0{};
  // 10
  vec4 m_unk_field_10{};

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

  // ?

  s32 m_unk_field_F0{};

  // ?

  // 1CC
  s32 m_unk_field_1CC{};

  // ALIGNED SIZE 0x450
};

// 01ECE430
extern EDIT_EVENT_INFO EdEventInfo;

// 01F04200
extern CCameraPas g_cmr_pas;
// 01F04B50
extern CCharaPas g_chara_pas;
// 01F05000
extern unk g_info;