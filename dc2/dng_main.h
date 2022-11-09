#pragma once
#include <array>
#include "glm/glm.hpp"
#include "common/debug.h"
#include "common/types.h"
#include "map.h"
#include "mg_frame.h"
#include "mg_memory.h"
#include "ls_mes.h"
#include "object.h"

// ~ 001BE6F0 - 001EA760

// TODO THIS FILE
class CTornado {};
class CSparcEffect {};
class CMiniEffParam {};
class CPalletAnime {};
class CHealingEffectMan {};
class CSwordLuminous {};
class CSwordAfterImage {};
class CHitEffectImage {};
class CFlushEffect {};
class CPowerLine {};
class CDeadEffect {};
struct BattleEffectMan {};
class CWeaponElement {};
class CLevelupInfo {};
class CPiyori {};
class CGiftMark {};
class CEnemyGekirin {};
class CEnemyLifeGage {};
class CDamageScore2 {};
class CWarningGauge2 {};
class CHealingPoint {};
class CActiveMonster {};
class CMonsterLocateInfo {};
class CMonsterMan {};
class CPreSprite {};
struct GLID_INFO {};

// Forward declarations
class CScene;
class CAutoMapGen;

// 01EA0480
extern CAutoMapGen AutoMapGen;

namespace dng_main
{
  // 00373CA0
  void SInit();
};

struct SDungeonStatus
{
  // 0
  _DWORD m_unk_field_0;
  // 4
  _DWORD m_unk_field_4;
  // 8
  _DWORD m_unk_field_8;
  // C
  _DWORD m_unk_field_C;
  // 10
  _DWORD m_unk_field_10;
  // 14
  _DWORD m_unk_field_14;
  // 18
  _DWORD m_unk_field_18;
};

class CAccumulateEffect
{

};

class CMiniEffPrim
{
  // 001C0FF0
  void Initialize();
  // 001C0DB0
  void SetPrim(glm::vec4* v, int i);
  // 001C0E20
  void Draw(CPreSprite* pre_sprite);
  // 001C0F70
  void Step();

  // 10
  _DWORD m_unk_field_10;
};

class CMiniEffPrimMan
{
public:
  // 001C11C0
  void Initialize();
  // 001C1000
  void CreatePrim(glm::vec4* v, int i);
  // 001C1070
  void Draw();
  // 001C1150
  void Step();

  // 0
  std::array<CMiniEffPrim, 0x40> m_mini_eff;
  // 800
  _DWORD m_unk_field_800;
  // 810
  mgCDrawPrim m_unk_field_810;
};

class CAfterWire
{
public:

  // 0
  _DWORD m_unk_field_0{ 0 };

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
  glm::u16vec3 m_rgb{ 0x80,0x80,0x80 };
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
  _DWORD m_unk_field_0;
  // 4
  _DWORD m_unk_field_4;
  // 8
  _DWORD m_unk_field_8;
  // C
  _DWORD m_unk_field_C;
  // 10
  _UNKNOWNSTRUCT(0x2A0) m_unk_field_10;
  // 2B0
  _UNKNOWNSTRUCT(0x690) m_unk_field_2B0;

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
  _DWORD m_unk_field_0;
  // 4
  _DWORD m_unk_field_4;
  // 8
  _DWORD m_unk_field_8;
  // 10
  glm::vec4 m_unk_field_10;
  // 20
  _UNKNOWNSTRUCT(0x780) m_unk_field_20;

  // SIZE 0x7A0
};

class CThunder : mgCFrame
{
public:
  // 110
  mgCFrameAttr m_unk_field_110{};

  // SIZE 0xDC0
};

class CMiniMapSymbol
{
public:
  // 001D4C40
  void DrawSymbol(glm::vec4& pos, EMiniMapSymbol::EMiniMapSymbol symbol_type);
};

class CDngFloorManager
{
public:
  // 002F8CC0
  void Initialize();
  // 002F9420
  void AnalyzeFile(const char* script, int script_size, mgCMemory* tree_stack);
  // 002F94B0
  void LoadDataTable(s8 map_id, mgCMemory* stack);
  // 002F9610
  GLID_INFO* GetDngMapFloorGlidInfo(s8 floor);
  // 002F9690
  bool IsGeoStone(s8 floor);
  // 002F96C0
  bool GetSphedaPrize(s8 floor, s32 i2, _UNKNOWNPOINTER p1, _UNKNOWNPOINTER p2);
  // 002F9760
  bool GetSphedaPrize(s32 i2, _UNKNOWNPOINTER p1, _UNKNOWNPOINTER p2);
  // 002F97E0
  u8 IsPlaySubGame();
  // 002F9840
  u8 IsSealFloor(s8 floor);
  // 002F9950
  u8 IsClearMostFastDestroy();
  // 002F9A70
  u8 IsClearPractice(usize i);
  // 002F9DA0
  _UNKNOWNPOINTER GetDngMapFloorInfo(s8 floor);
  // 002F9DA0
  _UNKNOWNPOINTER GetActiveMapFloorInfo(s8 floor);
  // 002F9E40
  void RelationGlid();
  // 002F9F30
  void CheckDrawGlidInfo();
  // 002FA2C0
  _UNKNOWNPOINTER GetNextGlid(GLID_INFO* info, s32* pi);
  // 002FA3B0
  _UNKNOWNPOINTER GetNextRoom(s8 floor, usize i2, GLID_INFO* info, int unused, s32* pi);
  // 002FA4E0
  _UNKNOWNPOINTER GetKeyNextRoom(s8 floor, usize i2, GLID_INFO* info);
  // 002FA550
  s8 GetDngMapNextFloorID(s8 floor, u8 i2);
  // 002FA680
  const char* GetFloorTitle(s8 floor);
  // 002FA710
  u8 GetDngMapNextRoot(s8 floor);

  // 0
  u8 m_map_id;
  // 4
  _UNKNOWNPOINTER m_unk_field_4;
  // 8
  s32 m_unk_field_8;
  // C
  s16 m_unk_field_C;
  // E
  s16 m_unk_field_E;
};

class CLockOnModel : public CObjectFrame
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
  // NOTE: Yes, this is a separate function than 0x34 (which still exists at that address in this class's vtable)
  // and yes, they're both named Draw and both accept no arguments, with only return type differing. No clue how they managed that one.
  // I've managled the name here slightly to squeeze it in.
  virtual void Draw_();
  // 80 001CB860
  virtual void Step();
  // 84 001CBD20
  virtual void Initialize(CScene* scene);

  // 001CB7B0
  void DrawMes(int i);

  // 80
  CScene* m_scene;
  // 84
  ClsMes* m_mes;
  // 88
  float m_unk_field_88;
  // 8C
  int m_unk_field_8C;

  // ?
  
  // A0
  glm::vec4 m_unk_field_A0;

  // SIZE 0xB0
};