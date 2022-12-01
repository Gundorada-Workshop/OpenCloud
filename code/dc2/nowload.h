#pragma once
#include "common/debug.h"
#include "common/types.h"

#include "dc2/mg/mg_memory.h"

// ~ 00309470 - 00309B50

class CScene;

struct NowLoadingInfo
{
  // 0
  s32 m_unk_field_0{ -1 };
  // 4
  unk32 m_unk_field_4{ 0 };
  // 8
  mgCMemory m_unk_field_8{};
  // 38
  unk32 m_unk_field_38{ 0 };
};

struct PAUSE_INFO
{
public:
  // 0
  bool skip_flag{ false };
  // 4
  CScene* scene{ nullptr };
};

// 00309B50
bool InitPauseData();

// 00309BD0
bool InitPause(usize texb);

// 00309C80
bool PauseEnable(bool value);

// 00309C90
bool GetPauseFlag();

// 00309CA0
bool PauseStart(PAUSE_INFO& pause_info);

// 00309D00
void PauseCancel();

// 00309D10
void PauseEnd();

// 00309DE0
bool PauseLoop();

// 0030A260
void PauseCount();