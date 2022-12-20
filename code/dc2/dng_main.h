#pragma once
#include <array>

#include <glm/glm.hpp>

#include "common/debug.h"
#include "common/types.h"

#include "dc2/character.h"
#include "dc2/ls_mes.h"
#include "dc2/map.h"
#include "dc2/mg/mg_frame.h"
#include "dc2/mg/mg_memory.h"
#include "dc2/monster.h"
#include "dc2/object.h"
#include "dc2/pot.h"

// ~ 001BE6F0 - 001EA760

class CColPrim;


// TODO THIS FILE
class CTornado
{
};

class CSparcEffect
{
};

class CMiniEffParam
{
};

class CPalletAnime
{
};

class CHealingEffectMan
{
};

class CSwordLuminous
{
};

class CSwordAfterImage
{
public:
  // 001C2240
  void Initialize(mgCMemory* stack, sint i1, sint i2);

  // these are probably colors
  // 20
  ivec4 m_unk_field_20{ 0x80, 0x80, 0x80, 0x80 };
  // 30
  ivec4 m_unk_field_30{ 0x80, 0x80, 0x80, 0x80 };
};

class CFlushEffect
{
};

class CPowerLine
{
};

class CDeadEffect
{
};

struct BattleEffectMan
{
};

class CWeaponElement
{
};

class CLevelupInfo
{
};

class CPiyori
{
};

class CGiftMark
{
};

class CEnemyGekirin
{
};

class CEnemyLifeGage
{
};

class CDamageScore2
{
};

class CWarningGauge2
{
};

class CHealingPoint
{
};

class CPreSprite
{
};

struct GLID_INFO
{

  // SIZE 0x70
};

// Forward declarations
class CScene;
class CAutoMapGen;

// 01EA0480
extern CAutoMapGen AutoMapGen;

enum class EDungeonID : s32
{
  UndergroundWaterChannel = 0,
  RainbowButterflyWood = 1,
  StarlightCanyon = 2,
  OceanRoarCave = 3,
  MountGundor = 4,
  MoonFlowerPalace = 5,
  ZelmiteMine = 6,
  COUNT = 7,
};

struct SDungeonStatus
{
  // 0
  unk32 m_unk_field_0;
  // 4
  unk32 m_unk_field_4;
  // 8
  unk32 m_unk_field_8;
  // C
  unk32 m_unk_field_C;
  // 10
  unk32 m_unk_field_10;
  // 14
  unk32 m_unk_field_14;
  // 18
  unk32 m_unk_field_18;
};

class CAccumulateEffect
{

};

class CMiniEffPrim
{
  // 001C0FF0
  void Initialize();

  // 001C0DB0
  void SetPrim(vec4* v, sint i);

  // 001C0E20
  void Draw(CPreSprite* pre_sprite);

  // 001C0F70
  void Step();

  // 10
  unk32 m_unk_field_10;
};

class CMiniEffPrimMan
{
public:
  // 001C11C0
  void Initialize();

  // 001C1000
  void CreatePrim(vec4* v, sint i);

  // 001C1070
  void Draw();

  // 001C1150
  void Step();

  // 0
  std::array<CMiniEffPrim, 0x40> m_mini_eff{};
  // 800
  unk32 m_unk_field_800{ 0 };
  // 810
  mgCDrawPrim m_unk_field_810{};
};

class CAfterWire
{
public:

  // 0
  unk32 m_unk_field_0{ 0 };

  // SIZE 0x120
};

class CAutoMapGen
{
public:

  // 0
  CMapParts* m_map_parts;

  // 50
  mgCDrawPrim m_unk_field_50;

  // SIZE 0x290
};

class CDamageScore 
{
public:
  // 48
  std::array<u8, 6> m_unk_field_6{ 0x80,0x80,0x80,0x80,0x80,0x80 };
};

namespace EMiniMapSymbol
{
  enum EMiniMapSymbol : s16
  {
    TERMINATOR = -1,
    SphidaShotGuide = 0,
    TreasureBox = 1,
    RandomCircle = 2,
    GeoStone = 3,
    SphidaRedGoal = 4,
    SphidaBlueGoal = 5,
    SphidaRedBall = 6,
    SphidaBlueBall = 7,
    Monster = 8,
    COUNT = 9,
  };
}

struct MINIMAP_SYMBOL_DATA
{
  // 0
  EMiniMapSymbol::EMiniMapSymbol id;

  // 2, 4, 6
  glm::u16vec3 rgb;

  // 8
  s16 m_unk_field_8;

  // A
  s16 m_unk_field_A;

  // C
  bool m_unk_field_C;

  // E
  bool m_unk_field_E;
  // SIZE 0x10
};

class CFireAfterHit
{
public:
  // 001D4850
  CFireAfterHit();

  // 001BF4F0
  void Initialize();

  // 0
  unk32 m_unk_field_0;

  // 4
  unk32 m_unk_field_4;

  // 8
  unk32 m_unk_field_8;

  // C
  unk32 m_unk_field_C;

  // 10
  unks<0x2A0> m_unk_field_10;

  // 2B0
  unks<0x690> m_unk_field_2B0;

  // SIZE 0x940
};

class CChillAfterHit
{
public:
  // 001D4880
  CChillAfterHit();

  // 001BE6F0
  void Initialize();

  // 0
  unk32 m_unk_field_0;
  // 4
  unk32 m_unk_field_4;
  // 8
  unk32 m_unk_field_8;
  // 10
  vec4 m_unk_field_10;
  // 20
  unks<0x780> m_unk_field_20;

  // SIZE 0x7A0
};

class CThunder
{
public:
  // 0
  mgCFrame m_unk_field_0{};

  // 110
  mgCFrameAttr m_unk_field_110{};

  // SIZE 0xDC0
};

class CMiniMapSymbol
{
public:
  // 001D4C40
  void DrawSymbol(vec3& pos, EMiniMapSymbol::EMiniMapSymbol symbol_type);
};

class CDngFloorManager
{
public:
  // 002F8CC0
  void Initialize();

  // 002F9420
  void AnalyzeFile(const char* script, sint script_size, mgCMemory* tree_stack);

  // 002F94B0
  void LoadDataTable(s8 map_id, mgCMemory* stack);

  // 002F9610
  GLID_INFO* GetDngMapFloorGlidInfo(s8 floor);

  // 002F9690
  bool IsGeoStone(s8 floor);

  // 002F96C0
  bool GetSphedaPrize(s8 floor, s32 i2, unkptr p1, unkptr p2);

  // 002F9760
  bool GetSphedaPrize(s32 i2, unkptr p1, unkptr p2);

  // 002F97E0
  u8 IsPlaySubGame();

  // 002F9840
  u8 IsSealFloor(s8 floor);

  // 002F9950
  u8 IsClearMostFastDestroy();

  // 002F9A70
  u8 IsClearPractice(usize i);

  // 002F9DA0
  unkptr GetDngMapFloorInfo(s8 floor);

  // 002F9DA0
  unkptr GetActiveMapFloorInfo(s8 floor);

  // 002F9E40
  void RelationGlid();

  // 002F9F30
  void CheckDrawGlidInfo();

  // 002FA2C0
  unkptr GetNextGlid(GLID_INFO* info, s32* pi);

  // 002FA3B0
  unkptr GetNextRoom(s8 floor, usize i2, GLID_INFO* info, sint unused, s32* pi);

  // 002FA4E0
  unkptr GetKeyNextRoom(s8 floor, usize i2, GLID_INFO* info);

  // 002FA550
  s8 GetDngMapNextFloorID(s8 floor, u8 i2);

  // 002FA680
  const char* GetFloorTitle(s8 floor);

  // 002FA710
  u8 GetDngMapNextRoot(s8 floor);

  // 0
  u8 m_map_id;
  // 4
  GLID_INFO* m_glid_info{ nullptr };
  // 8
  s32 m_unk_field_8;
  // C
  s16 m_unk_field_C;
  // E
  s16 m_unk_field_E;
};

class CLockOnModel : CObjectFrame
{
  // VTABLE 00375B00
  // 0  0
  // 4  0
  // 8  00138810 (mgCObject::ChangeParam)
  // C  00138820 (mgCObject::UseParam)
  // 10 00136190 (mgCObject::SetPosition)
  // 14 00136220 (mgCObject::SetPosition)
  // 18 00136260 (mgCObject::GetPosition)
  // 1C 00136270 (mgCObject::SetRotation)
  // 20 001362F0 (mgCObject::SetRotation)
  // 24 00136330 (mgCObject::GetRotation)
  // 28 00136340 (mgCObject::SetScale)
  // 2C 001363C0 (mgCObject::SetScale)
  // 30 00136400 (mgCObject::GetScale)
  // 34 00169FD0 (CObjectFrame::Draw)
  // 38 0016A010 (CObjectFrame::DrawDirect)
  // 3C 0016A130 (CObjectFrame::Initialize)
  // 40 00169F30 (CObjectFrame::PreDraw)
  // 44 00169F00 (CObjectFrame::GetCameraDist)
  // 48 00169AC0 (CObject::FarClip)
  // 4C 00169EF0 (CObjectFrame::DrawStep)
  // 50 00169D60 (CObject::GetAlpha)
  // 54 00160B70 (CObject::Show)
  // 58 0015F110 (CObject::GetShow)
  // 5C 00160B80 (CObject::SetFarDist)
  // 60 00160B90 (CObject::GetFarDist)
  // 64 00160BA0 (CObject::SetNearDist)
  // 68 00160BB0 (CObject::GetNearDist)
  // 6C 00169C20 (CObject::CheckDraw)
  // 70 00160BC0 (CObject::Copy)
  // 74 00169E80 (CObjectFrame::UpdatePosition)
  // 78 0016A050 (CObjectFrame::Copy)

  // 7C 001CB3E0
  virtual void* Draw();

  // 80 001CB860
  virtual void Step();

  // 84 001CBD20
  virtual void Initialize(CScene* scene);

  // 001CB7B0
  void DrawMes(sint i);

  // 80
  CScene* m_scene{ nullptr };

  // 84
  ClsMes* m_mes{ nullptr };

  // 88
  f32 m_unk_field_88{ 0.0f };

  // 8C
  sint m_unk_field_8C{ 0 };

  // ?
  
  // A0
  vec4 m_unk_field_A0{ 0.0f };

  // SIZE 0xB0
};

// 001E8630
// Calculate weapon health for melee weapons on hit
void calcWeaponParamWhp(const CActiveMonster& monster, const CColPrim& collision);

// 001E87E0
// Calculate weapon health for ranged weapons on fire
// NOTE: This function accepts another argument which I omitted, all the fn does with it
// is return early if the argument isn't 1 or 5, and all Max attacks pass in a literal 1
// and all Monica attacks pass in a literal 5. There's nothing which doesn't pass a 1/5 literal.
void calcWeaponParam2(sint penalty_divisor);

class CSaveData;
class CSaveDataDungeon;
class CUserDataManager;

// 00377290
extern CUserDataManager* DngUserData;

// 00377294
extern CSaveData* DngSaveData;

// 00377298
extern CSaveDataDungeon* DngSaveDataDungeon;

// 0037729C
extern CScene* DngMainScene;

// 003772A0
extern CScene* BattleAreaScene;

// 003772A4
extern CMap* DngMainMap;

// 003772A8
extern CActiveMonster* ActiveMonster;

// 01EAF3B0
extern CPot BTpot;

// 01EAF430
extern CBPot BTpot2;
