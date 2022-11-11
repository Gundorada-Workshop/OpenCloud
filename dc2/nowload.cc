#include <array>
#include "common/log.h"
#include "common/types.h"
#include "dc2io.h"
#include "event.h"
#include "gamepad.h"
#include "mainloop.h"
#include "mg_lib.h"
#include "nowload.h"
#include "scene.h"

set_log_channel("nowload");

// 00378694
static bool load_skip_img{};
// 00378698
static bool PauseFlag{};
// 0037869C
static bool PauseEnableFlag{};
// 003786A0
static s32 PauseCancelCnt{};
// 003786A4
static usize PauseTexb{};
// 003786A8
static PAUSE_INFO PauseInfo{};
// 003786B0
static s32 InitFlag{};
// 003786B4
static float SeCoreVol{};
// 003786B8
static bool play_time_count{};
// 003786BC
// NOTE: never written to :(
static bool wave_status{};
// 01F5B480
static NowLoadingInfo LoadInfo{};
// 01F5B4C0
static std::array<u8, 0x2800> SkipImage;
// 01F5DCC0
static u32 bgm_status{};

// 00309B50
bool InitPauseData()
{
  log_trace("{}()", __func__);

  usize read_bytes;
  std::array<u8, 0x10000> file_buf;
  if (!LoadFile2("img/skip.img", &file_buf, &read_bytes, 0))
  {
    return false;
  }

  if (read_bytes > SkipImage.size())
  {
    return false;
  }

  memcpy(&SkipImage, &file_buf, read_bytes);
  load_skip_img = true;
  return true;
}

// 00309BD0
bool InitPause(usize texb)
{
  log_trace("{}({})", __func__, texb);

  PauseEnableFlag = true;
  PauseFlag = false;
  InitFlag = false;
  PauseCancelCnt = 0;

  mgTexManager.DeleteBlock(texb);
  mgTexManager.EnterTexture(
    texb,
    "pause_work",
    nullptr,
    mgScreenWidth,
    mgScreenHeight,
    0x20,
    nullptr,
    0,
    0
  );

  if (load_skip_img)
  {
    mgTexManager.EnterIMGFile(SkipImage.data(), texb, nullptr, nullptr);
  }

  PauseTexb = texb;
  return true;
}

// 00309C80
bool PauseEnable(bool value)
{
  log_trace("{}()", __func__);

  bool old_value = PauseEnableFlag;
  PauseEnableFlag = value;
  return old_value;
}

// 00309C90
bool GetPauseFlag()
{
  log_trace("{}()", __func__);

  return PauseEnableFlag;
}

// 00309CA0
bool PauseStart(PAUSE_INFO& pause_info)
{
  log_trace("{}({})", __func__, fmt::ptr(&pause_info));

  if (!PauseEnableFlag)
  {
    return false;
  }

  if (PauseCancelCnt > 0)
  {
    return false;
  }

  PauseCancelCnt = 10;
  InitFlag = 0;
  PauseFlag = true;
  PauseInfo.skip_flag = pause_info.skip_flag;
  PauseInfo.scene = pause_info.scene;
  SeCoreVol = -1.0f;

  return true;
}

// 00309D00
void PauseCancel()
{
  log_trace("{}()", __func__);

  PauseFlag = false;
}

// 00309D10
void PauseEnd()
{
  log_trace("{}()", __func__);

  if (!PauseFlag || InitFlag <= 0)
  {
    return;
  }

  if (bgm_status)
  {
    PauseInfo.scene->ReplayBGM();
  }

  if ((wave_status & 0x1000) != 0)
  {
    sndStreamRePlay();
  }

  sndPortSqReplay(4);
  sndPortSqReplay(0);

  PlayTimeCount(play_time_count);

  if (SeCoreVol >= 0.0f)
  {
    sndMasterVolFadeInOut(1, 15, SeCoreVol, 0.0f);
  }

  sndSePlay(GetSystemSndId(), 25, 0);
}

// 00309DE0
bool PauseLoop()
{
  log_trace("{}()", __func__);

  if (!PauseFlag)
  {
    return false;
  }

  mgBeginFrame(nullptr);

  mgTexManager.ReloadTexture(PauseTexb, nullptr);
  mgCTexture* pause_work = mgTexManager.GetTexture("pause_work", -1);

  if (InitFlag == 0)
  {
    sndSePlay(GetSystemSndId(), 25, 0);
    SeCoreVol = sndGetMasterVol(1);
    sndMasterVolFadeInOut(1, 15, 0.0f, -1.0f);
    sndPortSqPause(4);
    sndPortSqPause(0);

    mgCTexture var_190;
    mgRect<int> var_120;
    var_120.Set(0, 0, (mgScreenWidth - 1) << 4, (mgScreenHeight - 1) << 4);

    mgSetPkMoveImage(&var_190, &var_120, pause_work, 0, 0, 0);

    play_time_count = GetPlayTimeCountFlag();
    PlayTimeCount(false);
    wave_status = 0;
  }

  if (InitFlag == 15)
  {
    wave_status = sndStreamGetState();

    if (wave_status & 0x1000)
    {
      sndStreamPause();
      sndSetMasterVol(0.0f, 1);
    }
  }

  if (InitFlag <= 15)
  {
    sndStep(2.0f);
  }

  InitFlag = std::min(InitFlag + 1, 1000);

  auto sv_config_option = GetSaveData()->m_sv_config_option;

  mgCDrawPrim draw_prim = mgCDrawPrim(nullptr, nullptr);
  draw_prim.DepthTestEnable(false);
  draw_prim.AlphaBlendEnable(false);
  draw_prim.Bilinear(false);
  draw_prim.ZMask(-1);
  draw_prim.TextureMapEnable(true);
  draw_prim.Begin(6);
  draw_prim.Texture(pause_work);
  u8 rgb = sv_config_option.m_unk_field_35 ? 0x80 : 0x40;
  draw_prim.Color(rgb, rgb, rgb, 0x80);
  draw_prim.TextureCrd(0, 0);
  draw_prim.Vertex(0, 0, 0);
  draw_prim.TextureCrd(mgScreenWidth + 1, mgScreenHeight + 1);
  draw_prim.Vertex(mgScreenWidth, mgScreenHeight, 0);
  draw_prim.End();

  mgCTexture* skip_texture = mgTexManager.GetTexture("skip", -1);
  if (skip_texture != nullptr && !sv_config_option.m_unk_field_35)
  {
    int t = (PauseInfo.skip_flag == 1) ? 46 : 22;
    int x = (mgScreenWidth / 2) - 41;
    int y = (mgScreenHeight / 2) - (t / 2);

    draw_prim.AlphaBlendEnable(true);
    draw_prim.Begin(6);
    draw_prim.Texture(skip_texture);
    draw_prim.Color(0x80, 0x80, 0x80, 0x80);
    draw_prim.TextureCrd(0, 0);
    draw_prim.Vertex(x, y, 0);
    draw_prim.TextureCrd(82, t);
    draw_prim.Vertex(x + 82, y + t, 0);
    draw_prim.End();
  }

  mgEndFrame(nullptr);

  GamePad.Update();
  PadCtrl.Update(&GamePad);

  bool should_unpause = false;

  if (InitFlag >= 18 && PadCtrl.Btn(21))
  {
    should_unpause = true;
  }

  if (PauseInfo.skip_flag == 1 && PadCtrl.Btn(22))
  {
    SkipEventStart();
    should_unpause = true;
  }

  if (should_unpause)
  {
    PauseEnd();
    return false;
  }
  return true;
}

// 0030A260
void PauseCount()
{
  log_trace("{}()", __func__);

  PauseCancelCnt = std::max(PauseCancelCnt - 1, 0);
}