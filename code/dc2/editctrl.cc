#include <glm/glm.hpp>

#include "common/log.h"

#include "dc2/character.h"
#include "dc2/editctrl.h"
#include "dc2/mainloop.h"
#include "dc2/menusave.h"

#include "mg/mg_lib.h"

set_log_channel("editctrl");

// 00377088
static ELadderMode LadderMode{ ELadderMode::Off };
// 0037708C
static sint LadderStep{ 0 };
// 00377090
static ECharaMotionMode CharaMotionMode{ 0 };
// 00377094
static s32 CharaMotionModeCnt{ 0 };
// 00377098
static s32 CharaFallFlag{ 0 };
// 0037709C
MAYBE_UNUSED static bool CharaAngleTargetFlag{ false };
// 003770A0
MAYBE_UNUSED static unkptr CharaAngleTarget{ nullptr };
// 003770A4
static bool FixCameraFlag{ false };
// 003770A8
static s32 FixCameraChgCnt{ 0 };
// 003770AC
static bool EyeViewCancelOnce{ false };
// 003770B0
static EViewMode ViewMode{ EViewMode::Walk };
// 003770B4
static f32 viewAngleH{ 0 };
// 003770B8
static f32 viewAngleV{ 0 };
// 003770BC
MAYBE_UNUSED static unkptr AddProj{ nullptr };
// 003770C0
static s32 ShutterCnt{ 0 };
// 003770C4
static bool InitEyeViewFlag{ false };
// 003770C8
MAYBE_UNUSED static CCharacter2* move_chara{ nullptr };
// 003770E4
static mgCCamera* LadderCamera{ nullptr };
// 003770E8
static f32 LdrNext{ 0.0f };
// 003770EC
static f32 LdrRot{ 0.0f };
// 003770F0
static f32 OldMtnRate{ 0.0f };
// 003770F4
static s32 LdrSound{ 0 };
// 003770F8
static s32 LdrBtmFoot{ 0 };
// 003770FC
static s32 LdrTopFoot{ 0 };

// 01E9B1C0
static MoveCheckInfo MoveInfo{ };
// 01E9B2D0
static vec3 OldFixCameraPos{ 0 };
// 01E9B2E0
static vec3 OldCameraPos{ 0 };
// 01E9B2F0
static SLadderData LadderData{ };
// 01E9B3C0
static vec3 LdrPos{ 0 };
// 01E9B3D0
static vec3 StdPos{ 0 };
// 01E9B3E0
static vec3 LdrBottomPos{ 0 };
// 01E9B3F0
static vec3 LdrTopPos{ 0 };
// 01E9B400
static vec3 LdrTopWalk{ 0 };
// 01E9B410
static vec3 LdrCamPos{ 0 };

// 001A40E0
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

// 001A4120
bool EditOnGround()
{
  log_trace("{}()", __func__);

  if (CharaFallFlag > 0)
  {
    return false;
  }

  if (CharaMotionMode != ECharaMotionMode::_0)
  {
    return false;
  }

  if (LadderMode != ELadderMode::Off)
  {
    return false;
  }

  return true;
}

// 001A4160
bool IsWalkMode()
{
  log_trace("{}()", __func__);

  return ViewMode == EViewMode::Walk;
}
