#include "common/debug.h"
#include "common/log.h"
#include "common/types.h"
#include "common/macros.h"

#include "host/host_interface_base.h"

#include "dc2/mainloop.h"
#include "dc2/title.h"

set_log_channel("title");

// 00377E6C
TITLE_INFO TitleInfo{};

// 01F06070
static mgCMemory DataBuffer{};
// 01F060A0
static mgCMemory TitleMapBuffer{};
// 01F060D0
static mgCMemory TitleWorkBuffer{};
// 01F06100
static mgCMemory Stack_ReadBuff{};
// 01F06130
static mgCMemory Stack_MenuCharaBuff_Fix{};
// 01F06160
static std::array<mgCMemory, 5> Stack_MenuCharaBuff{};
// 01F062D0
static SHDDINFO HDDINFO{};

// 0029F080
void SetSoundMode()
{
  log_trace("SetSoundMode()");

  auto save_data = GetSaveData();

  // Do we even want to bother with letting people change between mono and stereo tbh?

  if (save_data == nullptr || save_data->m_sv_config_option.m_sound == 0)
  {
    // Set the sound to stereo
    todo;
  }
  else
  {
    // Set the sound to mono
    todo;
  }
}

// 0029F110
void InitOmakeEnv(MAYBE_UNUSED int unk0, MAYBE_UNUSED INIT_LOOP_ARG* loop_arg, MAYBE_UNUSED int* unk1)
{
  todo;
}

// 0029F1F0
void TitleInit(MAYBE_UNUSED INIT_LOOP_ARG loop_arg)
{
  todo;
}

// 0029FF30
void TitleExit()
{
  log_trace("{}()", __func__);

  todo;
}

// 0029FFA0
void TitleLoop()
{
  log_trace("{}()", __func__);

  using namespace host;
  using enum pad_handler::buttons;
  if (DebugFlag && g_host_interface->pad_button_all_pressed(start | select))
  {
    // 0029FFF4
    // Close the developer console; terminate the Rush Movie
    todo;
  }

  todo;
}

// 002A0AB0
void TitleDraw()
{
  log_trace("{}()", __func__);

  todo;
}

// 002A0B70
void InitRushMovie()
{
  log_trace("{}()", __func__);

  todo;
}

// 002A0C90
s32 RushMovieKey()
{
  log_trace("{}()", __func__);

  todo;
  return false;
}

// 002A0EB0
void RushMovieDraw()
{
  log_trace("{}()", __func__);

  todo;
}

// 002A1020
void TitleModeInit()
{
  log_trace("{}()", __func__);

  todo;
}

// 002A1220
s32 TitleModeKey()
{
  log_trace("{}()", __func__);

  todo;
  return 0;
}

// 002A1B60
void TitleModeDraw()
{
  log_trace("{}()", __func__);

  todo;
}

// 002A1B60
void TitleMapDraw()
{
  log_trace("{}()", __func__);

  todo;
}

// 002A2950
void CalcPushAlpha(sint, float*)
{
  todo;
}

// 002A29F0
void TitleMCCheckInit(sint)
{
  todo;
}

// 002A2AD0
sint TitleMCCheckKey()
{
  log_trace("{}()", __func__);

  todo;
  return 0;
}

// 002A2FD0
void TitleMCCheckDraw()
{
  log_trace("{}()", __func__);

  todo;
}
