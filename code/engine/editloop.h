#pragma once
#include <array>

#include "common/debug.h"
#include "common/types.h"

#include "engine/editmap.h"
#include "engine/event_edit.h"

// ~ 001A76C0 - 001B5FD0

class CScene;
class CSceneEventData;
struct INIT_LOOP_ARG;

struct EditDebugInfo
{
public:
  // 0
  unk32 m_unk_field_0{ 0 };

  // 4
  unk32 m_unk_field_4{ 0 };

  // 8
  unk32 m_unk_field_8{ 0 };

  // C
  unk32 m_unk_field_C{ 0 };

  // 10
  unk32 m_unk_field_10{ 0 };

  // 14
  unk32 m_unk_field_14{ 0 };

  // 18
  unk32 m_unk_field_18{ 0 };

  // 1C
  unk32 m_unk_field_1C{ 0 };

  // 20
  unk32 m_unk_field_20{ 0 };

  // 24
  unk32 m_unk_field_24{ 0 };

  // 28
  unk32 m_unk_field_28{ 0 };

  // 2C
  unk32 m_unk_field_2C{ 0 };

  // 30
  unk32 m_unk_field_30{ 0 };

  // 34
  unk32 m_unk_field_34{ 0 };

  // 38
  unk32 m_unk_field_38{ 0 };

  // Size 0x3C (? - probably correct; aligned to 0x40)
};

enum class EEditLoopMode
{
  _0 = 0,
  _1 = 1,
  _2 = 2,
  _3 = 3,
  _4 = 4,
};

enum class EEditControlMode
{
  _0 = 0,
  _1 = 1,
  _2 = 2,
};

// 001A76C0
void EditStepChara(CScene* scene);

// 001A7750
void EditDrawStepChara(CScene* scene);

// 001A77B0
void EditDrawChara(CScene* scene);

// 001A7830
void EditDrawEffectChara(CScene* scene);

// 001A78A0
void EditDebugInit();

// 001A78C0
bool EditDebugMode();

// 001A78D0
void EditDebugStart(ssize texb);

// 001A78F0
void PrintCursor(char* buf, usize index);

// 001A7930
void EditDebugLoop(CScene* scene, EditDebugInfo* debug_info);

// 001A8400
void EditDebugEnd();

// 001A8410
void InitLightingEdit();

// 001A8420
void EndLightingEdit();

// 001A8430
bool IsLightingEditMode();

// 001A8440
void LightingEdit(CScene* scene);

// 001A9A90
void LoadGyorace();

// 001A9B50
void InitLockCharaCtrl();

// 001A9B60
void LockCharaCtrl();

// 001A9B70
void UnlockCharaCtrl();

// 001A9BA0
bool IsEditMode();

// 001A9BD0
void InitEditModeChg();

// 001A9BE0
bool NowEditModeChg();

// 001A9C00
void EditModeChg(sint event);

// 001A9C20
void EditModeChgStep(CScene* scene);

// 001A9ED0
void PreExitLoop(CScene* scene);

// 001A9F40
void EditInit(INIT_LOOP_ARG init_arg);

// 001ABBD0
void EditExit();

// 001ABC30
void InitSubMapLoadStep();

// 001ABC40
void SubMapLoadStep();

// 001ABCF0
void EditLoop();

// 001ADFC0
void InitEditEvent();

// 001ADFF0
void ResetEditEvent();

// 001AE030
void RestartEditEvent();

// 001AE090
void EditStep();

// 001AE3D0
void EditDraw();

// 001AF140
void UpdateTrBoxFlag(sint box_index);

// 001AF250
void BurnEditParts();

// 001AF3A0
void editLoadSound(sint sound_id);

// 001AF4C0
void EditMapJump(sint map_id);

// 001AFBD0
void EditGotoInterior(sint interior_id, bool b);

// 001AFD10
void EditExitInterior();

// 001AFE30
void EditDataSave();

// 001AFF50
void EditDataLoad();

// 001B0150
void KeepEditAnalyze();

// 001B01D0
void EditAnalyzeChanged();

// 001B0280
void LoadComVillaager();

// 001B0290
void LoadMap();
