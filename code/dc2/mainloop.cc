#include <string>

#include "common/debug.h"
#include "common/helpers.h"
#include "common/log.h"

#include "host/host_interface_dwm.h"

#include "dc2/editdata.h"
#include "dc2/ls_mes.h"
#include "dc2/mainloop.h"
#include "dc2/menusave.h"
#include "dc2/mg/mg_lib.h"
#include "dc2/npc.h"
#include "dc2/scene.h"
#include "dc2/quest.h"
#include "dc2/userdata.h"

set_log_channel("mainloop")

// 00376FB4
u32 s_system_snd_id{ 0 };
// 00376FB8
bool DebugFlag{};
// 00376FBC
u32 DefStartEventNo{};
// 00376FC0
Language LanguageCode{ Language::English };
// 00376FC4
bool OmakeFlag{};
// 00376FCC
ELoopID LoopNo{};
// 00376FD0
ELoopID NextLoopNo{};
// 00376FD4
ELoopID PrevLoopNo{};
// 00376FC8
s32 MasterDebugCode{};

// 00376FE4
static CSaveData* ActiveSaveData{};

// 00376FEC
static bool PlayTimeCountFlag{ false };

// 003D8070
static SDebugInfo DebugInfo{};
// 003D8090
static CFont Font{};
// 003D8140
static INIT_LOOP_ARG InitArg{};
// 003D8190
static INIT_LOOP_ARG NextInitArg{};
// 003D81E0
static INIT_LOOP_ARG PrevInitArg{};
// 003D8230
// FIXME: 0x1A000000 bytes (26MB) in PS2. Might need to adjust slightly for windows.
// Bumped up to 40MB (0x28000000) on Windows (to adjust for slightly bigger datatypes)
static alignas(16) std::array<char, 0x28000000> main_buffer{};
// 01DD8230
static mgCMemory MainBuffer{};
// 01DD8260
static CScene MainScene{};
// 01DE87B0
static std::array<char, 0x1900> SystemSeBuff{};
// 01DEA0B0
static mgCMemory SystemSeStack{};
// 01E017E0
static mgCMemory InfoStack{};
// 01E01810
static CSaveData SaveData{};
// 01E67180
static mgCMemory MenuBuffer{};
// 01E672B0
static std::array<mgCTexture, 2> FontTex{};
// 01E67390
static ClsMes PauseMes{};

// 00190840
CFont* GetDebugFont()
{
  log_trace("{}()", __func__);

  return &Font;
}

// 00190860
u32 GetSystemSndId(void)
{
  return s_system_snd_id;
}

// 00190870
CScene* GetMainScene()
{
  log_trace("{}()", __func__);

  return &MainScene;
}

// 00190880
CSaveData* GetSaveData()
{
  return ActiveSaveData;
}

// 001908F0
mgCMemory* GetMainStack()
{
  log_trace("{}()", __func__);

  return &MainBuffer;
}

// 00190900
void NextLoop(ELoopID next_loop_id, const INIT_LOOP_ARG& init_arg)
{
  log_trace("{}()", __func__, common::to_underlying(next_loop_id), fmt::ptr(&init_arg));

  NextLoopNo = next_loop_id;
  NextInitArg = init_arg;
}

// 00190BE0
void PlayTimeCount(bool flag)
{
  PlayTimeCountFlag = flag;
}

// 00190BF0
bool GetPlayTimeCountFlag()
{
  return PlayTimeCountFlag;
}

// 00190CB0
void MainLoop()
{
  log_trace("{}()", __func__);

  todo;

  // 00190D20
  mgInit();

  todo;

  // 00190E7C
  LanguageCode = Language::English;
  GameItemDataManage.LoadData();
  GameItemDataManage.LoadItemSystemMes(LanguageCode);

  todo;

  // 00190EC4
  LoadNPCCfg();

  todo;

  g_host_interface->set_frame_divider(1);

  while (!g_host_interface->message_pump_quit_requested())
  {
    g_host_interface->start_game_frame();

    // Garbage collect the scene graph
    mgFrameManager.Step();

    g_host_interface->end_game_frame();
  }
}
