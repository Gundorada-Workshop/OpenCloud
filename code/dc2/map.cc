#include "dc2/map.h"
#include "dc2/script_interpreter.h"

// 00164520
static bool cfgDRAW_OFF_RECT(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgOCCLUSION_PLANE(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgFUNC_DATA(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgFUNC_NAME(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgFUNC_EVENT_DATA(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgFUNC_DATA_END(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_SURFACE_NUM(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_SURFACE_START(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_VERTEX(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_POS(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_PARAM(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_SHAKE(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_SURFACE_END(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_DRAW_NUM(SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_DRAW(SPI_STACK* stack, int)
{
  return true;
}

static bool mapDummy(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFAR_CLIP(SPI_STACK* stack, int)
{
  return true;
}

static bool mapLIGHT_FLAG(SPI_STACK* stack, int)
{
  return true;
}

static bool mapMOVE_FLAG(SPI_STACK* stack, int)
{
  return true;
}

static bool mapLOD_START(SPI_STACK* stack, int)
{
  return true;
}

static bool mapLOD_BLEND(SPI_STACK* stack, int)
{
  return true;
}

static bool mapLOD_PIECE(SPI_STACK* stack, int)
{
  return true;
}

static bool mapLOD_END(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_POS(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_NAME(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_ROT(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_SCALE(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_MATERIAL_START(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_MATERIAL(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_MATERIAL_END(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_COL_TYPE(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_TIME(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_END(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS_END(SPI_STACK* stack, int)
{
  return true;
}

static bool mapMAP_PARTS(SPI_STACK* stack, int)
{
  return true;
}

static bool mapMAP_FAR_CLIP(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS_NAME(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS_GROUP(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS_POS(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS_ROT(SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS_SCALE(SPI_STACK* stack, int)
{
  return true;
}

static bool mapMAP_PARTS_END(SPI_STACK* stack, int)
{
  return true;
}

static bool mapMAP_INFO_TOP(SPI_STACK* stack, int)
{
  return true;
}

static bool mapCAMERA_INFO(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFIX_CAMERA(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFIX_CAMERA_POS(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFIX_CAMERA_POS2(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFIX_CAMERA_OFF_GROUP(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFIX_CAMERA_RECT(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFIX_CAMERA_END(SPI_STACK* stack, int)
{
  return true;
}

static bool mapCAMERA_INFO_END(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_POINT(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_DATA(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_NAME(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_FLAG(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_FIRE_DATA(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_EFFECT_NAME(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_PLIGHT_DATA(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_ANIME_DATA(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_INVENT_DATA(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_EVENT_DATA(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_POS(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_DATA_END(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_POINT_END(SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_SOUND_DATA(SPI_STACK* stack, int)
{
  return true;
}

// 00334730
static const std::array<SPI_TAG_PARAM, 88> map_tag =
{
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "PARTS",                  mapPARTS,
  "FAR_CLIP",               mapFAR_CLIP,
  "LIGHT_FLAG",             mapLIGHT_FLAG,
  "MOVE_FLAG",              mapMOVE_FLAG,
  "LOD_START",              mapLOD_START,
  "LOD_BLEND",              mapLOD_BLEND,
  "LOD_PIECE",              mapLOD_PIECE,
  "LOD_END",                mapLOD_END,
  "PIECE",                  mapPIECE,
  "PIECE_POS",              mapPIECE_POS,
  "PIECE_NAME",             mapPIECE_NAME,
  "PIECE_ROT",              mapPIECE_ROT,
  "PIECE_SCALE",            mapPIECE_SCALE,
  "PIECE_MATERIAL_START",   mapPIECE_MATERIAL_START,
  "MAP_PIECE_MATERIAL",     mapPIECE_MATERIAL,
  "MAP_PIECE_MATERIAL_END", mapPIECE_MATERIAL_END,
  "PIECE_COL_TYPE",         mapPIECE_COL_TYPE,
  "PIECE_TIME",             mapPIECE_TIME,
  "PIECE_END",              mapPIECE_END,
  "PARTS_END",              mapPARTS_END,
  "MAP_PARTS",              mapPARTS,
  "MAP_FAR_CLIP",           mapMAP_FAR_CLIP,
  "PARTS_NAME",             mapPARTS_NAME,
  "PARTS_GROUP",            mapPARTS_GROUP,
  "PARTS_POS",              mapPARTS_POS,
  "PARTS_ROT",              mapPARTS_ROT,
  "PARTS_SCALE",            mapPARTS_SCALE,
  "MAP_PARTS_END",          mapPARTS_END,
  "_MAP_INFO_TOP",          mapMAP_INFO_TOP,
  "CAMERA_INFO",            mapCAMERA_INFO,
  "FIX_CAMERA",             mapFIX_CAMERA,
  "FIX_CAMERA_POS",         mapFIX_CAMERA_POS,
  "FIX_CAMERA_POS2",        mapFIX_CAMERA_POS2,
  "FIX_CAMERA_OFF_GROUP",   mapFIX_CAMERA_OFF_GROUP,
  "FIX_CAMERA_RECT",        mapFIX_CAMERA_RECT,
  "FIX_CAMERA_END",         mapFIX_CAMERA_END,
  "CAMERA_INFO_END",        mapCAMERA_INFO_END,
  "FUNC_POINT",             mapFUNC_POINT,
  "FUNC_DATA",              mapFUNC_DATA,
  "FUNC_NAME",              mapFUNC_NAME,
  "FUNC_FLAG",              mapFUNC_FLAG,
  "FUNC_FIRE_DATA",         mapFUNC_FIRE_DATA,
  "FUNC_EFFECT_NAME",       mapFUNC_EFFECT_NAME,
  "FUNC_FIRE_DATA",         mapFUNC_EFFECT_NAME,
  "FUNC_PLIGHT_DATA",       mapFUNC_PLIGHT_DATA,
  "FUNC_ANIME_DATA",        mapFUNC_ANIME_DATA,
  "FUNC_INVENT_DATA",       mapFUNC_INVENT_DATA,
  "FUNC_EVENT_DATA",        mapFUNC_EVENT_DATA,
  "FUNC_POS",               mapFUNC_POS,
  "FUNC_DATA_END",          mapFUNC_DATA_END,
  "FUNC_POINT_END",         mapFUNC_POINT_END,
  "FUNC_SOUND_DATA",        mapFUNC_SOUND_DATA,
  NULL, nullptr
};

// 003349f0
static const std::array<SPI_TAG_PARAM, 16> cfg_tag =
{
  "DRAW_OFF_RECT",       cfgDRAW_OFF_RECT,
  "FUNC_DATA",           cfgFUNC_DATA,
  "FUNC_NAME",           cfgFUNC_NAME,
  "FUNC_EVENT_DATA",     cfgFUNC_EVENT_DATA,
  "FUNC_POS",            mapFUNC_POS,
  "FUNC_DATA",           cfgFUNC_DATA_END,
  "WATER_SURFACE_NUM",   cfgWATER_SURFACE_NUM,
  "WATER_SURFACE_START", cfgWATER_SURFACE_START,
  "WATER_VERTEX",        cfgWATER_VERTEX,
  "WATER_POS",           cfgWATER_POS,
  "WATER_PARAM",         cfgWATER_PARAM,
  "WATER_SHAKE",         cfgWATER_SHAKE,
  "WATER_SURFACE_END",   cfgWATER_SURFACE_END,
  "WATER_DRAW_NUM",      cfgWATER_DRAW_NUM,
  "WATER_DRAW",          cfgWATER_DRAW,
  NULL, nullptr,
};

// 00376e04
static CMap* _mapMap{ nullptr };
// 00376e10
static mgCMemory* _mapStack{ nullptr };

// 00376E40
void CMap::LoadCfgFile(char* file, int size, mgCMemory* map_stack)
{
  CScriptInterpreter interpreter{ };

  // _ReserveFuncFlag = 0;
  // _WaterIndex = 0;
  // _cfgWater = 0;
  _mapMap = this;
  _mapStack = map_stack;

  interpreter.SetTag(cfg_tag.data());
  interpreter.SetScript(file, size);
  interpreter.Run();
}

static bool amapIMG(SPI_STACK* stack, int)
{
  return true;
}

static bool amapPCP(SPI_STACK* stack, int)
{
  return true;
}

// 00334a80
static const std::array<SPI_TAG_PARAM, 3> add_mapinfo_tag =
{
  "IMG", amapIMG,
  "PCP", amapPCP,
  NULL, nullptr
};
