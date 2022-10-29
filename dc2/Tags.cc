#include "Tags.h"

static bool texTEX_ANIME(SPI_STACK* stack, int)
{
  return true;
}

static bool texTEX_ANIME_DATA(SPI_STACK* stack, int)
{
  return true;
}

static bool texSRC_TEX(SPI_STACK* stack, int)
{
  return true;
}

static bool texDEST_TEX(SPI_STACK* stack, int)
{
  return true;
}

static bool texSCROLL(SPI_STACK* stack, int)
{
  return true;
}

static bool texCLUT_COPY(SPI_STACK* stack, int)
{
  return true;
}

static bool texCOLOR(SPI_STACK* stack, int)
{
  return true;
}

static bool texALPHA_BLEND(SPI_STACK* stack, int)
{
  return true;
}

static bool texALPHA_TEST(SPI_STACK* stack, int)
{
  return true;
}

static bool texWAIT(SPI_STACK* stack, int)
{
  return true;
}

static bool texTEX_ANIME_DATA_END(SPI_STACK* stack, int)
{
  return true;
}

static bool texANIME_END(SPI_STACK* stack, int)
{
  return true;
}

static bool texANIME_BUG_PATCH(SPI_STACK* stack, int)
{
  return true;
}

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

static bool __BUFFER_SIZE(SPI_STACK* stack, int)
{
  return true;
}

static bool __EFFECT_START(SPI_STACK* stack, int)
{
  return true;
}

static bool __EFFECT_END(SPI_STACK* stack, int)
{
  return true;
}

static bool __WAIT_FRAME(SPI_STACK* stack, int)
{
  return true;
}

static bool __IMG_NAME(SPI_STACK* stack, int)
{
  return true;
}

static bool __SIZE(SPI_STACK* stack, int)
{
  return true;
}

static bool __DIR(SPI_STACK* stack, int)
{
  return true;
}

static bool __NUM(SPI_STACK* stack, int)
{
  return true;
}

static bool __NUM_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __COUNT(SPI_STACK* stack, int)
{
  return true;
}

static bool __CNT_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __REPEAT(SPI_STACK* stack, int)
{
  return true;
}

static bool __REP_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __POS(SPI_STACK* stack, int)
{
  return true;
}

static bool __POS_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __VELO(SPI_STACK* stack, int)
{
  return true;
}

static bool __VELO_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __VELO_MUL(SPI_STACK* stack, int)
{
  return true;
}

static bool __ACC(SPI_STACK* stack, int)
{
  return true;
}

static bool __ACC_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __ACC_MUL(SPI_STACK* stack, int)
{
  return true;
}

static bool __MOVE_TYPE(SPI_STACK* stack, int)
{
  return true;
}

static bool __MOVE_P1(SPI_STACK* stack, int)
{
  return true;
}

static bool __MOVE_P1_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __MOVE_P2(SPI_STACK* stack, int)
{
  return true;
}

static bool __MOVE_P2_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE_TYPE(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __SVELO(SPI_STACK* stack, int)
{
  return true;
}

static bool __SVELO_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE_P1(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE_P1_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE_P2(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE_P2_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_BLEND(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_TYPE(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_P1(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_P1_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_P2(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_P2_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __TEX_GET_RECT(SPI_STACK* stack, int)
{
  return true;
}

static bool __TEX_GET_TYPE(SPI_STACK* stack, int)
{
  return true;
}

static bool __TEX_NAME(SPI_STACK* stack, int)
{
  return true;
}

static bool __GRAVITY(SPI_STACK* stack, int)
{
  return true;
}

static bool _SKIN_IMG(SPI_STACK* stack, int)
{
  return true;
}

static bool _SKIN_IMG_END(SPI_STACK* stack, int)
{
  return true;
}

static bool _SKIN_MODEL(SPI_STACK* stack, int)
{
  return true;
}

static bool _SKIN_MOTION(SPI_STACK* stack, int)
{
  return true;
}

static bool _TREE_MAPINFO(SPI_STACK* stack, int)
{
  return true;
}

static bool _GLID_INFO(SPI_STACK* stack, int)
{
  return true;
}

static bool _ROOT_INFO(SPI_STACK* stack, int)
{
  return true;
}

static bool _ROOM_INFO(SPI_STACK* stack, int)
{
  return true;
}

static bool _ROOM_LINK(SPI_STACK* stack, int)
{
  return true;
}

static bool _ROOM_OPTION(SPI_STACK* stack, int)
{
  return true;
}

static bool _ROOM_TEXNO(SPI_STACK* stack, int)
{
  return true;
}

static bool _ROOM_KEYROOM(SPI_STACK* stack, int)
{
  return true;
}

static bool _ROOM_FLOOR_INFO(SPI_STACK* stack, int)
{
  return true;
}

static bool _ROOM_TITLE(SPI_STACK* stack, int)
{
  return true;
}

// 003340b0
const std::array<SPI_TAG_PARAM, 14> tex_tag =
{
  "TEX_ANIME",          texTEX_ANIME,
  "TEX_ANIME_DATA",     texTEX_ANIME_DATA,
  "SRC_TEX",            texSRC_TEX,
  "DEST_TEX",           texDEST_TEX,
  "SCROLL",             texSCROLL,
  "CLUT_COPY",          texCLUT_COPY,
  "COLOR",              texCOLOR,
  "ALPHA_BLEND",        texALPHA_BLEND,
  "ALPHA_TEST",         texALPHA_TEST,
  "WAIT",               texWAIT,
  "TEX_ANIME_DATA_END", texTEX_ANIME_DATA_END,
  "TEX_ANIME_END",      texANIME_END,
  "BUG_PATCH",          texANIME_BUG_PATCH,
  NULL, nullptr
};

// 003349f0
const std::array<SPI_TAG_PARAM, 16> cfg_tag =
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

// 00334730
const std::array<SPI_TAG_PARAM, 88> map_tag =
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

// 00334f30
const std::array<SPI_TAG_PARAM, 48> effm_tag =
{
  "BUFFER_SIZE",   __BUFFER_SIZE,
  "EFFECT_START",  __EFFECT_START,
  "EFFECT_END",    __EFFECT_END,
  "WAIT_FRAME",    __WAIT_FRAME,
  "IMG_NAME",      __IMG_NAME,
  "SIZE",          __SIZE,
  "DIR",           __DIR,
  "NUM",           __NUM,
  "NUM_RAND",      __NUM_RAND,
  "COUNT",         __COUNT,
  "CNT_RAND",      __CNT_RAND,
  "REPEAT",        __REPEAT,
  "__REP_RAND",    __REP_RAND, // this one is __ for some reason
  "POS",           __POS,
  "POS_RAND",      __POS_RAND,
  "VELO",          __VELO,
  "VELO_RAND",     __VELO_RAND,
  "VELO_MUL",      __VELO_MUL,
  "ACC",           __ACC,
  "ACC_RAND",      __ACC_RAND,
  "ACC_MUL",       __ACC_MUL,
  "MOVE_TYPE",     __MOVE_TYPE,
  "MOVE_P1",       __MOVE_P1,
  "MOVE_P1_RAND",  __MOVE_P1_RAND,
  "MOVE_P2",       __MOVE_P2,
  "MOVE_P2_RAND",  __MOVE_P2_RAND,
  "SCALE_TYPE",    __SCALE_TYPE,
  "SCALE",         __SCALE,
  "SCALE_RAND",    __SCALE_RAND,
  "SVELO",         __SVELO,
  "SVELO_RAND",    __SVELO_RAND,
  "SCALE_P1",      __SCALE_P1,
  "SCALE_P1_RAND", __SCALE_P1_RAND,
  "SCALE_P2",      __SCALE_P2,
  "SCALE_P2_RAND", __SCALE_P2_RAND,
  "ALPHA_BLEND",   __ALPHA_BLEND,
  "ALPHA_TYPE",    __ALPHA_TYPE,
  "ALPHA",         __ALPHA,
  "ALPHA_RAND",    __ALPHA_RAND,
  "ALPHA_P1",      __ALPHA_P1,
  "ALPHA_P1_RAND", __ALPHA_P1_RAND,
  "ALPHA_P2",      __ALPHA_P2,
  "ALPHA_P2_RAND", __ALPHA_P2_RAND,
  "TEX_GET_RECT",  __TEX_GET_RECT,
  "TEX_GET_TYPE",  __TEX_GET_TYPE,
  "TEX_NAME",      __TEX_NAME,
  "GRAVITY",       __GRAVITY,
  NULL, nullptr
};

// 00334db0
const std::array<SPI_TAG_PARAM, 5> skin_tag =
{
  "IMG",     _SKIN_IMG,
  "IMG_END", _SKIN_IMG_END,
  "MODEL",   _SKIN_MODEL,
  "MOTION",  _SKIN_MOTION,
  NULL, nullptr
};

// 0035d010
const std::array<SPI_TAG_PARAM, 12> tree_map_tag =
{
  "TREE_INFO",  _TREE_MAPINFO,
  "GI",         _GLID_INFO,
  "RT",         _ROOT_INFO,
  "RI",         _ROOM_INFO,
  "RI_LINK",    _ROOM_LINK,
  "RI_OP",      _ROOM_OPTION,
  "RI_TEX",     _ROOM_TEXNO,
  "RI_KEYROOM", _ROOM_KEYROOM,
  "RF_INFO",    _ROOM_FLOOR_INFO,
  "RI_TITLE",   _ROOM_TITLE,
  NULL, nullptr
};
