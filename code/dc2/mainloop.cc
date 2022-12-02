#include <string>

#include "common/debug.h"
#include "common/log.h"
#include "common/data_stream.h"
#include "common/file_helpers.h"

#include "host/host_interface_dwm.h"

#include "dc2/editdata.h"
#include "dc2/ls_mes.h"
#include "dc2/mainloop.h"
#include "dc2/menusave.h"
#include "dc2/mg/mg_memory.h"
#include "dc2/mg/mg_texture.h"
#include "dc2/npc.h"
#include "dc2/scene.h"
#include "dc2/quest.h"
#include "dc2/userdata.h"

set_log_channel("mainloop")

using namespace common;

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
static SInitArg InitArg{};
// 003D8190
static SInitArg NextInitArg{};
// 003D81E0
static SInitArg PrevInitArg{};
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

// 0030a290
// I don't know where this belongs but it's only used by MainLoop
static void SCElogoFade(bool fade_out, mgCMemory* stack_mem)
{
  // we don't need vif packets
  // auto vifpk_a = static_cast<u128*>(stack_mem->stAlloc64(10000));
  // auto vifpk_b = static_cast<u128*>(stack_mem->stAlloc64(10000));
  // mgInitVifPacket(vifpk_a, vifpk_b);
  //
  // mgCMemory mem_a{ };
  // auto a = stack_mem->stAlloc64(10000);
  // mem_a.stSetBuffer(a, 10000);
  //
  // mgCMemory mem_b{ };
  // auto b = stack_mem->stAlloc64(10000);
  // mem_b.stSetBuffer(b, 10000);
  //
  // mgSetPacketBuffer(&mem_a, &mem_b);
  //
  // mgCMemory mem_d{ };
  // auto c = stack_mem->stAlloc64(10000);
  // mem_c.stSetBuffer(c, 10000);
  //
  // mgCMemory mem_b{ };
  // auto c = stack_mem->stAlloc64(10000);
  // mem_c.stSetBuffer(c, 10000);
  //
  // mgSetDataBuffer(&mem_c, &mem_d, 1);
  //
  // mgTexManager.SetTableBuffer(10, 10, stack_mem);

  todo;
  // auto vram_top = mgGetTopVRAMAddress();
  // mgTexManager.Initialize(vram_top,-1);
  //
  // stack_mem->Align64();
  //
  // u8* image_buffer = static_cast<u8*>(stack_mem->m_stack_start) + stack_mem->m_stack_current_allocated * 16;
  // 
  // int size;
  // auto err = LoadFile2("title/title1.img", image_buffer, &size, 0);

  auto [buff, size] = g_host_interface->open_game_file_cached("title/title1.img");
  if (!buff || !size)
    panicf("Failed to open title1.img");

  mgTexManager.EnterIMGFile(buff.get(), 0, nullptr, nullptr);

  uint factor = 0;
  for (uint i = 0; i < 24; ++i)
  {
    // using enum mgCDrawPrim::Primitive;

    mgBeginFrame(nullptr);

    // mgTexManager.ReloadTexture(0, nullptr);
    // auto moji_texture = mgTexManager.GetTexture("moji", -1);
    //
    // mgCDrawPrim dp{};
    // dp.AlphaBlendEnable(true);
    // dp.TextureMapEnable(true);
    //
    // dp.Begin(Sprite);
    //
    // auto alpha = std::min(factor / 20u, 128u);
    //
    // if (fade_out)
    //   alpha = 128u - alpha;
    //
    // dp.Color(128, 128, 128, alpha);
    //
    // dp.Texture(moji_texture);
    //
    // dp.TextureCrd(0, 324);
    // dp.Vertex(0, 176, 0);
    //
    // dp.TextureCrd(512, 384);
    // dp.Vertex(512, 236, 0);
    //
    // dp.End();

    mgEndFrame(nullptr);

    factor += 128;
  }
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

  SCElogoFade(false, nullptr);
  g_host_interface->set_frame_divider(1);

  while (!g_host_interface->message_pump_quit_requested())
  {
    g_host_interface->start_game_frame();

    g_host_interface->end_game_frame();
  }
}
