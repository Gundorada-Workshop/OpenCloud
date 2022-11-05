#pragma once
#include <array>
#include "common/debug.h"
#include "common/types.h"
#include "mg_memory.h"

// ~ 001BE6F0 - 001EA760

// TODO THIS FILE
class CChillAfterHit {};
class CFireAfterHit {};
class CTornado {};
class CThunder {};
class CSparcEffect {};
class CMiniEffParam {};
class CPalletAnime {};
class CHealingEffectMan {};
class CSwordLuminous {};
class CSwordAfterImage {};
class CAfterWire {};
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
class CDamageScore {};
class CDamageScore2 {};
class CLockOnModel {};
class CWarningGage2 {};
class CMiniMapSymbol {};
class CHealingPoint {};
class CAutoMapGen {};
class CActiveMonster {};
class CMonsterLocateInfo {};
class CMonsterMan {};
class CPreSprite {};
struct GLID_INFO {};

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
