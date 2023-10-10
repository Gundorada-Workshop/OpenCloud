#include "common/bits.h"
#include "common/helpers.h"
#include "common/math.h"
#include "common/constants.h"
#include "common/debug.h"
#include "common/log.h"
#include "common/types.h"

#include "engine/camera.h"
#include "engine/character.h"
#include "engine/editctrl.h"
#include "engine/mainloop.h"
#include "engine/menusave.h"
#include "engine/photo.h"
#include "engine/scene.h"

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
MAYBE_UNUSED static f32 AddProj{ 0.0f };
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
static vec3 OldFixCameraPos{ };
// 01E9B2E0
static vec3 OldCameraPos{ };
// 01E9B2F0
static SLadderData LadderData{ };
// 01E9B3C0
static vec3 LdrPos{ };
// 01E9B3D0
static vec3 StdPos{ };
// 01E9B3E0
static vec3 LdrBottomPos{ };
// 01E9B3F0
static vec3 LdrTopPos{ };
// 01E9B400
static vec3 LdrTopWalk{ };
// 01E9B410
static vec3 LdrCamPos{ };

// 001A2C70
//static bool ClipBoxXZ(const vec4& max_corner1, const vec4& min_corner1, const vec4& max_corner2, const vec4& min_corner2)
//{
//  log_trace("{}({}, {}, {}, {})", __func__, fmt::ptr(&max_corner1), fmt::ptr(&min_corner1), fmt::ptr(&max_corner2), fmt::ptr(&min_corner2));
//
//  return math::vector_all_less_than_equal(min_corner1.xz(), max_corner2.xz()) &&
//    math::vector_all_greater_than_equal(max_corner1.xz(), min_corner2.xz());
//}

// 001A2CC0
//f32 OverlapPoly3AreaXZ(const matrix4* m1, const matrix4* m2, const mgVu0FBOX* box)
//{
//  log_trace("{}({}, {}, {})", __func__, fmt::ptr(m1), fmt::ptr(m2), fmt::ptr(box));
//
//  todo;
//  return 0.0f;
//}

// 001A32A0
void CEditCollision::Copy(MAYBE_UNUSED CEditCollision& other, MAYBE_UNUSED sint i) const
{
  log_trace("CEditCollision::{}({}, {})", __func__, fmt::ptr(&other), i);

  todo;
}

// 001A3490
f32 CEditCollision::AreaXZ() const
{
  log_trace("CEditCollision::{}()", __func__);

  todo;
  return 0.0f;
}

// 001A3540
//bool CEditCollision::OverlapPoly3XZ(const matrix4* m, f32* f_dest, mgVu0FBOX* box_dest) const
//{
//  log_trace("CEditCollision::{}({}, {}, {})", __func__, fmt::ptr(m), fmt::ptr(f_dest), fmt::ptr(box_dest));
//
//  todo;
//  return false;
//};

// 001A3720
//f32 CEditCollision::OverlapXZ(const CEditCollision& other, const matrix4* m, mgVu0FBOX* box_dest) const
//{
//  log_trace("CEditCollision::{}({}, {}, {})", __func__, fmt::ptr(&other), fmt::ptr(m), fmt::ptr(box_dest));
//
//  todo;
//  return 0.0f;
//}

// 001A3820
//bool CEditCollision::OverlapPoly3XZ(const matrix4* m1, const matrix4* m2, mgVu0FBOX* box_dest) const
//{
//  log_trace("CEditCollision::{}({}, {}, {})", __func__, fmt::ptr(m1), fmt::ptr(m2), fmt::ptr(box_dest));
//
//  todo;
//  return false;
//}

// 001A3B10
//void CEditCollision::ApplyMatrix(const matrix4* m)
//{
//  log_trace("CEditCollision::{}({})", __func__, fmt::ptr(m));
//
//  todo;
//}

// 001A3C50
void CEditCollision::DeleteVerticalPoly()
{
  log_trace("CEditCollision::{}()", __func__);

  todo;
}

// 001A3DF0
void CEditCollision::PickupVerticalPoly()
{
  log_trace("CEditCollision::{}()", __func__);

  todo;
}

// 001A40E0
MAYBE_UNUSED static CUserDataManager* GetUserData()
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

// 001A4170
void EditControlInit(CScene* scene)
{
  log_trace("{}({})", __func__, fmt::ptr(scene));

  new (&MoveInfo) MoveCheckInfo();
  EyeViewCancelOnce = false;
  ViewMode = EViewMode::Walk;
  InitEyeViewFlag = false;
  viewAngleH = 0.0f;
  viewAngleV = 0.0f;
  AddProj = 0.0f;
  ShutterCnt = 0;
  move_chara = nullptr;

  scene->ResetStatus(ESceneDataType::Character, scene->m_control_chrid, ESceneDataStatus::UNK_10);

  CharaAngleTarget = nullptr;
  CharaAngleTargetFlag = false;
  FixCameraFlag = false;

  InitTakePhoto();

  EditControlStatusInit(scene);

  auto camera = scene->GetCamera(scene->m_active_cmrid);
  if (camera != nullptr && camera->Iam() == CCameraControl_TypeID)
  {
    static_cast<CCameraControl*>(camera)->CancelRotBack();
  }
}

// 001A4230
void EditControlStatusInit(CScene* scene)
{
  log_trace("{}({})", __func__, fmt::ptr(scene));

  LadderMode = ELadderMode::Off;
  CharaMotionMode = ECharaMotionMode::_0;
  CharaMotionModeCnt = 0;
  CharaFallFlag = 0;
  FixCameraChgCnt = 0;

  CCharacter2* control_character = scene->GetCharacter(scene->m_control_chrid);
  if (control_character != nullptr)
  {
    control_character->SetMotion("立ち", 4); // "Stand"
    control_character->Step();
  }
}

// 001A42B0
void EditControl(CScene* scene, CPadControl* pad)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(scene), fmt::ptr(pad));

  if (LadderMode != ELadderMode::Off)
  {
    LadderControl(scene, pad);
  }
  else
  {
    CharaControl(scene, pad);
    if (scene->m_unk_field_2E88)
    {
      pad = nullptr;
    }
    CameraControl(scene, pad);
  }
}

// 001A4320
std::string GetFootEffName(sint id)
{
  log_trace("{}({})", __func__, id);

  constexpr static usize name_id[]
  {
    0, 3, 0, 0, 0,
    0, 0, 1, 1, 0,
    0, 2, 0, 1, 1,
    0, 1, 0, 2, 0,
    0, 0, 2, 0, 0,
    0, 0, 0, 0, 0,
  };

  constexpr static const char* name[]
  {
    nullptr,
    "足砂煙", // Foot dust cloud
    "足水パシャ", // Foot water splash (?)
    "足芝生", // Foot grass
  };

  if (id < 0 || id >= std::size(name_id) || name[name_id[id]] == nullptr)
  {
    return "";
  }

  return name[name_id[id]];
}

// 001A4370
//void EditMoveChara(CScene* scene, vec3* v, EditMoveCharaInfo* move_info)
//{
//  log_trace("{}({})", __func__, fmt::ptr(scene), fmt::ptr(v), fmt::ptr(move_info));
//
//  todo;
//}

// 001A4E80
//void EditCameraControl(CScene* scene, CPadControl* pad, const vec3* v)
//{
//  log_trace("{}({})", __func__, fmt::ptr(scene), fmt::ptr(pad), fmt::ptr(v));
//
//  todo;
//}

// 001A57B0
void CharaControl(MAYBE_UNUSED CScene* scene, MAYBE_UNUSED CPadControl* pad)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(scene), fmt::ptr(pad));
  
  todo;
}

// 001A5FB0
void CancelEyeViewMode()
{
  log_trace("{}()", __func__);

  EyeViewCancelOnce = true;
}

// 001A5FC0
void CameraControl(MAYBE_UNUSED CScene* scene, MAYBE_UNUSED CPadControl* pad)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(scene), fmt::ptr(pad));

  todo;
}

// 001A6300
//void InitEyeCamera(CCharacter2* chara, CCameraControl* camera)
//{
//  log_trace("{}({}, {})", __func__, fmt::ptr(chara), fmt::ptr(camera));
//
//  f32 rot = chara->GetRotation().y;
//
//  InitEyeViewFlag = true;
//  viewAngleV = 0.0f;
//  AddProj = 0.0f;
//  ShutterCnt = 0;
//  viewAngleH = rot;
//  OldCameraPos = camera->GetPos();
//}

// 001A6360
//void ResetViewMode(CScene* scene)
//{
//  log_trace("{}({})", __func__, fmt::ptr(scene));
//
//  auto camera = scene->GetCamera(scene->m_active_cmrid);
//
//  if (InitEyeViewFlag)
//  {
//    camera->SetPos(OldCameraPos);
//  }
//
//  InitEyeViewFlag = false;
//
//  if (camera != nullptr)
//  {
//    camera->Step(-1);
//  }
//
//  scene->ResetStatus(ESceneDataType::Character, scene->m_control_chrid, ESceneDataStatus::UNK_10);
//  EndTakePhoto();
//}

// 001A63F0
void EyeCamera(MAYBE_UNUSED mgCCamera* camera, MAYBE_UNUSED CCharacter2* chara, MAYBE_UNUSED bool b)
{
  log_trace("{}({}, {}, {})", __func__, fmt::ptr(camera), fmt::ptr(chara), b);

  todo;
}

// 001A66F0
void InitLadder(MAYBE_UNUSED ELadderMode ladder_mode, MAYBE_UNUSED CScene* scene, MAYBE_UNUSED CSceneEventData* event_data)
{
  log_trace("{}({}, {}, {})", __func__, common::to_underlying(ladder_mode), fmt::ptr(scene), fmt::ptr(event_data));

  todo;
}

// 001A6AB0
void EndLadder()
{
  log_trace("{}()", __func__);

  LadderMode = ELadderMode::Off;
}

// 001A6AC0
void LadderControl(MAYBE_UNUSED CScene* scene, MAYBE_UNUSED CPadControl* pad)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(scene), fmt::ptr(pad));

  todo;
}
