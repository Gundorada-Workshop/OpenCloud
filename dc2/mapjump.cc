#include <array>

#include <glm/glm.hpp>

#include "common/log.h"
#include "common/types.h"

#include "dc2/mapjump.h"
#include "dc2/mg_lib.h"
#include "dc2/scene.h"

set_log_channel("mapjump");

// 0037839C
static s32 NowMainMapNo{ 0 };
// 003783A0
static s32 NowSubMapNo{ 0 };
// 003783A4
static s32 NowInteriorMapNo{ 0 };
// 003783A8
static s32 OldInteriorMapNo{ 0 };
// 003783AC
static mgCMemory* ScriptBuffer{ nullptr };
// 003783B0
static bool InteriorFlag{ false };
// 003783B4
static s32 old_bgm_no{ 0 };
// 01F58D50
static MapJumpInfo MainMapInfo{};
// 01F58D70
static MapJumpInfo SubMapInfo{};
// 01F58E10
static std::array<char, 0x40> old_mapname{ 0 };
// 01F58E50
static glm::vec4 OldPos{ 0 };
// 01F58E60
static glm::vec4 OldRot{ 0 };
// 01F58E70
static glm::vec4 OldCamPos{ 0 };
// 01F58E80
static glm::vec4 OldCamRef{ 0 };
// 01F58E90
static std::array<char, 0x40> PrevInterior{ 0 };
// 01F58ED0
static std::array<char, 0x40> NowInterior{ 0 };
// 01F58F10
static CScene::BGM_STATUS OldBgmStatus{};

// 002DEC10
s32 GetMainMapNo()
{
  log_trace("{}()", __func__);

  return NowMainMapNo;
}

// 002DEC20
s32 GetSubMapNo()
{
  log_trace("{}()", __func__);

  return NowSubMapNo;
}

// 002DEC30
void ClearSubMapNo()
{
  log_trace("{}()", __func__);

  NowSubMapNo = -1;
}

// 002DEC70
void SetMainMapInfo(MapJumpInfo& info)
{
  log_trace("{}({})", __func__, fmt::ptr(&info));

  MainMapInfo = info;
}

// 002DECC0
void SetSubMapInfo(MapJumpInfo& info)
{
  log_trace("{}({})", __func__, fmt::ptr(&info));

  SubMapInfo = info;
}

// 002DED10
void SetScriptBuffer(mgCMemory* memory)
{
  log_trace("{}({})", __func__, fmt::ptr(memory));

  ScriptBuffer = memory;
}

// 002DED20
void PreLoadSync()
{
  log_trace("{}()", __func__);

  todo;
}

// 002DED50
void MapJump(CScene* scene, SCN_LOADMAP_INFO2* load_map_info, int i)
{
  log_trace("{}({}, {}, {})", __func__, fmt::ptr(scene), fmt::ptr(load_map_info), i);

  todo;
}

// 002DEF40
bool GetLoadMapInfo(SCN_LOADMAP_INFO2* load_map_info, int i)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(load_map_info), i);

  todo;
  return false;
}

// 002DF1B0
void LoadSubMap(CScene* scene, int i1, int i2)
{
  log_trace("{}({}, {}, {})", __func__, fmt::ptr(scene), i1, i2);

  todo;
}

// 002DF370
void LoadMapScript(const char* file_name)
{
  log_trace("{}({})", __func__, file_name);

  todo;
}

// 002DF400
void ReloadMapScript()
{
  log_trace("{}()", __func__);

  todo;
}

// 002DF430
void LoadScript(char* file_name)
{
  log_trace("{}({})", __func__, file_name);

  todo;
}

// 002DF590
s32 GetOldInteriorMapNo()
{
  log_trace("{}()", __func__);

  if (InInterior())
  {
    return -1;
  }
  return OldInteriorMapNo;
}

// 002DF5D0
void InitInterior()
{
  log_trace("{}()", __func__);

  InteriorFlag = false;
  old_mapname[0] = '\0';
  PrevInterior[0] = '\0';
  NowInterior[0] = '\0';
}

// 002DF5F0
bool InInterior()
{
  log_trace("{}()", __func__);

  return InteriorFlag;
}

// 002DF600
void SaveBeforeInterior(CScene* scene)
{
  log_trace("{}({})", __func__, fmt::ptr(scene));

  todo;
}

// 002DF6F0
void SetInteriorDoorPos(CScene* scene)
{
  log_trace("{}({})", __func__, fmt::ptr(scene));

  todo;
}

// 002DF8D0
void GoToInterior(CScene* scene, int i)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(scene), i);

  todo;
}

// 002DFA30
void DeleteInterior(CScene* scene, int i)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(scene), i);

  todo;
}

// 002DFAA0
void ExitInterior(CScene* scene, int* pi)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(scene), fmt::ptr(pi));

  todo;
}

// 002DFCF0
void InteriorMapJump(CScene* scene, int i)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(scene), i);

  todo;
}
