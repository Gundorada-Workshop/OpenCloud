#pragma once
#include "common/debug.h"
#include "common/types.h"

#include "dc2/mg/mg_memory.h"
#include "dc2/scene.h"

// ~ 002DEC10 - 002DFDE0

struct MapJumpInfo
{
  // 002DEC40
  // NOTE: Default initialization should be fine here instead
  //MapJumpInfo();

  // 0
  _DWORD m_unk_field_0{ 0 };
  // 4
  _DWORD m_unk_field_4{ 0 };
  // 8
  s32 m_unk_field_8{ 0 };
  // C
  s32 m_unk_field_C{ 0 };
  // 10
  s32 m_unk_field_10{ 0 };
  // 14
  _UNKNOWNPOINTER m_unk_field_14{ nullptr };

  // SIZE 0x18
};

// 002DEC10
s32 GetMainMapNo();
// 002DEC20
s32 GetSubMapNo();
// 002DEC30
void ClearSubMapNo();
// 002DEC70
void SetMainMapInfo(MapJumpInfo& info);
// 002DECC0
void SetSubMapInfo(MapJumpInfo& info);
// 002DED10
void SetScriptBuffer(mgCMemory* memory);
// 002DED20
void PreLoadSync();
// 002DED50
void MapJump(CScene* scene, SCN_LOADMAP_INFO2* load_map_info, int i);
// 002DEF40
bool GetLoadMapInfo(SCN_LOADMAP_INFO2* load_map_info, int i);
// 002DF1B0
void LoadSubMap(CScene* scene, int i1, int i2);
// 002DF370
void LoadMapScript(const char* file_name);
// 002DF400
void ReloadMapScript();
// 002DF430
void LoadScript(char* file_name);
// 002DF590
s32 GetOldInteriorMapNo();
// 002DF5D0
void InitInterior();
// 002DF5F0
bool InInterior();
// 002DF600
void SaveBeforeInterior(CScene* scene);
// 002DF6F0
void SetInteriorDoorPos(CScene* scene);
// 002DF8D0
void GoToInterior(CScene* scene, int i);
// 002DFA30
void DeleteInterior(CScene* scene, int i);
// 002DFAA0
void ExitInterior(CScene* scene, int* pi);
// 002DFCF0
void InteriorMapJump(CScene* scene, int i);