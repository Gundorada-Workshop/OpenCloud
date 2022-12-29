#pragma once
#include "common/types.h"

#include "dc2/collision.h"

// ~ 001A2080 - 001A76C0

class CPadControl;
class CSceneEventData;

class CEditCollision
{
public:
  // 001A32A0
  void Copy(CEditCollision& other, sint i) const;

  // 001A3490
  f32 AreaXZ() const;

  // 001A3540
  bool OverlapPoly3XZ(const matrix4* m, f32* f_dest, mgVu0FBOX* box_dest) const;

  // 001A3720
  f32 OverlapXZ(const CEditCollision& other, const matrix4* m, mgVu0FBOX* box_dest) const;

  // 001A3820
  bool OverlapPoly3XZ(const matrix4* m1, const matrix4* m2, mgVu0FBOX* box_dest) const;

  // 001A3B10
  void ApplyMatrix(const matrix4* m);

  // 001A3C50
  void DeleteVerticalPoly();

  // 001A3DF0
  void PickupVerticalPoly();
private:
  // 0
  CCollisionMDT m_collision_mdt{};
  // SIZE 0x50
};

struct EditMoveCharaInfo
{

};

struct MoveCheckInfo
{
  // TODO
  // SIZE 0x110, init all fields to 0
};

struct SLadderData
{
  // TODO
  // SIZE 0xD0
};

enum class EViewMode
{
  Walk = 0,
  _1 = 1,
  _2 = 2,
};

enum class ELadderMode
{
  Off = 0,
  _1 = 1,
  _2 = 2,
};

enum class ECharaMotionMode
{
  _0 = 0,
  _1 = 1,
};

// 001A4120
bool EditOnGround();

// 001A4160
bool IsWalkMode();

// 001A4170
void EditControlInit(CScene* scene);

// 001A4230
void EditControlStatusInit(CScene* scene);

// 001A42B0
void EditControl(CScene* scene, CPadControl* pad);

// 001A4320
std::string GetFootEffName(sint id);

// 001A4370
void EditMoveChara(CScene* scene, vec3* v, EditMoveCharaInfo* move_info);

// 001A4E80
void EditCameraControl(CScene* scene, CPadControl* pad, const vec3* v);

// 001A57B0
void CharaControl(CScene* scene, CPadControl* pad);

// 001A5FB0
void CancelEyeViewMode();

// 001A5FC0
void CameraControl(CScene* scene, CPadControl* pad);

// 001A6300
void InitEyeCamera(CCharacter2* chara, CCameraControl* camera);

// 001A6360
void ResetViewMode(CScene* scene);

// 001A63F0
void EyeCamera(mgCCamera* camera, CCharacter2* chara, bool b);

// 001A66F0
void InitLadder(ELadderMode ladder_mode, CScene* scene, CSceneEventData* event_data);

// 001A6AB0
void EndLadder();

// 001A6AC0
void LadderControl(CScene* scene, CPadControl* pad);

// 001A76C0
void EditStepChara(CScene* scene);
