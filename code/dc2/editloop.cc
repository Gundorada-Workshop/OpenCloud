#include <array>

#include "common/debug.h"
#include "common/log.h"
#include "common/math.h"

#include "graph/rectangle.h"

#include "dc2/editloop.h"
#include "dc2/effect.h"
#include "dc2/ls_mes.h"
#include "dc2/mainloop.h"
#include "dc2/mg/mg_frame.h"
#include "dc2/mg/mg_memory.h"
#include "dc2/scene.h"
#include "dc2/subgame.h"

set_log_channel("editloop");

// 00377100
static bool EditDebugFlag{};

// 00377104
static ssize EditDebugTexb{};

// 00377108
static ssize Select{};

// 0037710C
static ssize SelTAG{};

// 00377110
static ESubGameID sg_type{};

// 00377114
static sint map_jump{};

// 00377118
static sint save_no{};

// 0037711C
static sint load_no{};

// 00377120
static sint condition{};

// 00377124
static sint map_flag_no{};

// 00377128
static bool LEditFlag{};

// 0037712C
static sint LightType{};

// 00377130
static ssize DirLightNo{};

// 00377134
static sint fish_num{};

// 00377138
MAYBE_UNUSED static mgCFrame* WaterFrame{};

// 0037713C
static mgCFrame* RedBicMark{};

// 00377140
static mgCFrame* BlueBicMark{};

// 00377144
static CMapTreasureBox* TreasureBox{};

// 00377148
static sint MapNo{};

// 0037714C
static mgCCamera* Camera{};

// 00377150
static mgCCamera* EventCamera{};

// 00377154
static mgCCamera* FixCamera{};

// 00377158
static mgCCamera* EditCamera{};

// 0037715C
static sint ActiveCharaNo{};

// 00377160
static sint ControlCharaID{};

// 00377164
static CCharacter2* WalkChara{};

// 00377168
static sint LoopCounter{};

// 0037716C
static EEditLoopMode LoopMode{};

// 00377170
static EEditControlMode ControlMode{};

// 00377174
static bool SubMapLoadBG{};

// 00377178
static sint now_load_map_nop{};

// 0037717C
MAYBE_UNUSED static bool EventSquareJump{};

// 00377180
static bool EditDrawFlag{};

// 00377184
static bool EditDrawCancelFlag{};

// 00377188
static bool PauseFlag{};

// 0037718C
static sint LockChara{};

// 00377190
static sint PreEditMenuCnt{};

// 00377194
static bool EditModeChgFlag{};

// 00377198
static sint EditModeChgCnt{};

// 0037719C
static sint EditModeChgEvent{};

// 003771A0
static CScene* MainScene{};

// 003771AC
static char* read_buffer_end{};

// 003771B0
static char* MenuDataBuf{};

// 003771B4
static usize MenuDataSize{};

// 003771BC
static char* CrossFadeBuff{};

// 00377204
static bool DelMainNPCFlag{};

// 00377208
static CEditMap* emapMap{};

// 0037720C
static CEditInfoMngr* emapInfo{};

// 00377210
static mgCMemory* emapStack{};

// 00377214
MAYBE_UNUSED static sint emapIdx{};

// 00377218
MAYBE_UNUSED static CEditInfoMngr* emapNowInfo{};

// 0037721C
MAYBE_UNUSED static graph::rect* emapRect{};

// 00377220
MAYBE_UNUSED static sint emapRectNum{};

// 00377224
MAYBE_UNUSED static sint emapRectIdx{};

// 00377228
static sint emapFixNum{};

// 0037722C
static sint emapInitNum{};

// 00377230
static sint emapFixIdx{};

// 00377234
static sint emapInitIdx{};

// 00377238
static sint emapFix{};

// 0037723C
static sint emapInit{};

// 01E9B440
static CWaveTable WaveTable{ };

// 01E9C650
static vec4 CharaOldPos{ };

// 01E9C660
static ClsMes EventMes1{ };

// 01E9E840
static mgCMemory buf0{ };

// 01E9E870
static mgCMemory buf1{ };

// 01E9E8A0
static std::array<mgCMemory, 2> data_buf{ };

// 01E9E900
static std::array<mgCMemory, 2> init_dbuf{ };

// 01E9E960
static mgCMemory WorkBuffer{ };

// 01E9E990
static mgCMemory MenuBuffer{ };

// 01E9E9C0
static mgCMemory ChrEffBuffer{ };

// 01E9E990
static mgCMemory Script_Buffer{ };

// 01E9EA20
static mgCMemory TotalDataBuff{ };

// 01E9EA50
static mgCMemory ControlCharaBuff{ };

// 01E9EA80
static mgCMemory MainDataBuff{ };

// 01E9EA80
static mgCMemory MainCharaBuff{ };

// 01E9EAE0
static mgCMemory SubDataBuff{ };

// 01E9EB10
static mgCMemory SubCharaBuff{ };

// 01E9EB40
static std::array<mgCMemory, 4> EventBuff{ };

// 01E9EC00
static std::array<mgCMemory, 8> CharaBufs{ };

// 01E9ED80
static mgCMemory FishingBuff{ };

// 01E9EDB0
static mgCMemory SkyBuff{ };

// 01E9EDE0
static CEditEvent EditEvent{ };

// 01E9EF30
static EditDebugInfo EdDebugInfo{ };

// 01E9EF70
static mgCVisualMDT TestVisual{ };

// 01E9EFC0
static std::shared_ptr<mgCFrame> TestFrame = mgCFrame::Create();

// 01E9F0F0
static std::array<unk32, 0x10> beforeAnalyze{ };

// 001A76C0
void EditStepChara(CScene* scene)
{
  log_trace("{}({})", __func__, fmt::ptr(scene));

  scene->StepChara(scene->m_control_chrid);

  for (usize i = 8; i < 64; ++i)
  {
    scene->StepChara(i);
  }

  scene->StepChara(120);
  scene->StepChara(121);
  scene->StepChara(122);
  scene->StepChara(123);
}

// 001A7750
void EditDrawStepChara(CScene* scene)
{
  log_trace("{}({})", __func__, fmt::ptr(scene));

  scene->DrawCharaShadow(scene->m_control_chrid);

  for (usize i = 8; i < 0x40; ++i)
  {
    scene->DrawCharaShadow(i);
  }
}

// 001A77B0
void EditDrawChara(CScene* scene)
{
  log_trace("{}({})", __func__, fmt::ptr(scene));

  scene->DrawChara(scene->m_control_chrid, 0);

  for (usize i = 8; i < 0x40; ++i)
  {
    // FIXME: MAGIC
    if (scene->GetType(ESceneDataType::Character, i) != 4)
    {
      scene->DrawChara(i, 1);
    }
  }
}

// 001A7830
void EditDrawEffectChara(CScene* scene)
{
  log_trace("{}({})", __func__, fmt::ptr(scene));

  scene->DrawChara(scene->m_control_chrid, 0);

  for (usize i = 8; i < 0x40; ++i)
  {
    // FIXME: MAGIC
    if (scene->GetType(ESceneDataType::Character, i) != 4)
    {
      scene->DrawChara(i, 2);
    }
  }
}

// 001A78A0
void EditDebugInit()
{
  log_trace("{}()", __func__);

  EditDebugFlag = false;
  Select = 0;
  EditDebugTexb = -1;
}

// 001A78C0
bool EditDebugMode()
{
  log_trace("{}()", __func__);

  return EditDebugFlag;
}

// 001A78D0
void EditDebugStart(ssize texb)
{
  log_trace("{}()", __func__);

  EditDebugFlag = true;
  EditDebugTexb = texb;
}

// 001A78F0
void PrintCursor(char* buffer, usize index)
{
  log_trace("{}()", __func__);

  if (index == Select)
  {
    sprintf(buffer, "->");
  }
  else
  {
    sprintf(buffer, "  ");
  }
}

// 001A7930
void EditDebugLoop(CScene* scene, EditDebugInfo* debug_info)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(scene), fmt::ptr(debug_info));

  return;
}

// 001A8400
void EditDebugEnd()
{
  log_trace("{}()", __func__);

  EditDebugInit();
}

// 001A8410
void InitLightingEdit()
{
  log_trace("{}()", __func__);

  LEditFlag = false;
}

// 001A8420
void EndLightingEdit()
{
  log_trace("{}()", __func__);

  InitLightingEdit();
}

// 001A8430
bool IsLightingEditMode()
{
  log_trace("{}()", __func__);

  return LEditFlag;
}

// 001A8440
void LightingEdit(CScene* scene)
{
  log_trace("{}({})", __func__, fmt::ptr(scene));

  todo;
}

// 001A9A90
void LoadGyorace()
{
  log_trace("{}()", __func__);

  todo;
}

// 001A9B10
static CUserDataManager* GetUserData()
{
  log_trace("{}()", __func__);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return nullptr;
  }

  return &save_data->m_user_data_manager;
}

// 001A9B50
void InitLockCharaCtrl()
{
  log_trace("{}()", __func__);

  LockChara = 0;
}

// 001A9B60
void LockCharaCtrl()
{
  log_trace("{}()", __func__);

  LockChara += 1;
}

// 001A9B70
void UnlockCharaCtrl()
{
  log_trace("{}()", __func__);

  LockChara = std::max(LockChara - 1, 0);
}

// 001A9BA0
bool IsEditMode()
{
  log_trace("{}()", __func__);

  return LoopMode != EEditLoopMode::_2 && LoopMode != EEditLoopMode::_4;
}

// 001A9BD0
void InitEditModeChg()
{
  log_trace("{}()", __func__);

  EditModeChgFlag = false;
  EditModeChgCnt = 0;
  EditModeChgEvent = 0;
}

// 001A9BE0
bool NowEditModeChg()
{
  log_trace("{}()", __func__);

  return EditModeChgFlag && EditModeChgCnt > 0;
}

// 001A9C00
void EditModeChg(sint event)
{
  log_trace("{}({})", __func__, event);

  EditModeChgEvent = event;
  EditModeChgCnt = 30;
  EditModeChgFlag = true;

  LockCharaCtrl();
}

// 001A9C20
void EditModeChgStep(CScene* scene)
{
  log_trace("{}({})", __func__, fmt::ptr(scene));

  if (!EditModeChgFlag)
  {
    return;
  }

  --EditModeChgCnt;

  if (EditModeChgCnt > 0)
  {
    return;
  }

  EditModeChgFlag = false;
  EditModeChgCnt = 0;
  
  UnlockCharaCtrl();

  if (scene->m_unk_field_2E88)
  {
    return;
  }

  if (EditModeChgEvent <= 0)
  {
    return;
  }

  scene->RunEvent(EditModeChgEvent, nullptr);
}

// 001A9ED0
void PreExitLoop(MAYBE_UNUSED CScene* scene)
{
  log_trace("{}()", __func__, fmt::ptr(scene));

  todo;
}

// 001A9F40
void EditInit(MAYBE_UNUSED INIT_LOOP_ARG init_arg)
{
  log_trace("{}()", __func__);

  todo;
}

// 001ABBD0
void EditExit()
{
  log_trace("{}()", __func__);

  todo;
}

// 001ABC30
void InitSubMapLoadStep()
{
  log_trace("{}()", __func__);

  SubMapLoadBG = false;
  now_load_map_nop = -1;
}

// 001ABC40
void SubMapLoadStep()
{
  log_trace("{}()", __func__);

  todo;
}

// 001ABCF0
void EditLoop()
{
  log_trace("{}()", __func__);

  todo;
}

// 001ADFC0
void InitEditEvent()
{
  log_trace("{}()", __func__);

  InitLockCharaCtrl();
  EditEvent.Reset();
}

// 001ADFF0
void ResetEditEvent()
{
  log_trace("{}()", __func__);

  if (EditEvent.m_unk_field_4 == 1)
  {
    EditEvent.Reset();
    UnlockCharaCtrl();
  }
}

// 001AE030
void RestartEditEvent()
{
  log_trace("{}()", __func__);

  if (EditEvent.m_unk_field_4 == 1)
  {
    ResetEditEvent();
    bool success = EditEvent.StartEvent(&MainScene->m_scene_event_data);
    if (success)
    {
      LockCharaCtrl();
    }
  }
}

// 001AE090
void EditStep()
{
  log_trace("{}()", __func__);

  todo;
}

// 001AE3D0
void EditDraw()
{
  log_trace("{}()", __func__);

  todo;
}

// 001AF140
void UpdateTrBoxFlag(sint box_index)
{
  log_trace("{}({})", __func__, box_index);

  todo;
};

// 001AF250
void BurnEditParts()
{
  log_trace("{}()", __func__);

  todo;
}

// 001AF3A0
void editLoadSound(sint sound_id)
{
  log_trace("{}({})", __func__, sound_id);

  todo;
}

// 001AF4C0
void EditMapJump(sint map_id)
{
  log_trace("{}({})", __func__, map_id);

  todo;
}

// 001AFBD0
void EditGotoInterior(sint interior_id, bool b)
{
  log_trace("{}({}, {})", __func__, interior_id, b);

  todo;
}

// 001AFD10
void EditExitInterior()
{
  log_trace("{}()", __func__);

  todo;
}

// 001AFE30
void EditDataSave()
{
  log_trace("{}()", __func__);

  todo;
}

// 001AFF50
void EditDataLoad()
{
  log_trace("{}()", __func__);

  todo;
}

// 001B0150
void KeepEditAnalyze()
{
  log_trace("{}()", __func__);

  todo;
}

// 001B01D0
void EditAnalyzeChanged()
{
  log_trace("{}()", __func__);

  todo;
}

// 001B0280
void LoadComVillaager()
{
  log_trace("{}()", __func__);

  return;
}

// 001B0290
void LoadMap()
{
  log_trace("{}()", __func__);

  LoadComVillaager();
}
