#include "Tags.h"

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

static bool _DATACOMINIT(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATACOM(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEBNUM(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP_ST(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP_ST_L(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP2_ST(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP2_ST_L(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP_SPE(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP_BUILDUP(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAITEMINIT(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAITEM(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAATTACHINIT(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAATTACH_ST(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAATTACH_ST2(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAATTACH_ST_SP(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAROBOINIT(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAROBO_ANALYZE(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAGUARDNUM(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAGUARD(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAFISHINIT(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAFISH(SPI_STACK* stack, int)
{
  return true;
}

static bool _MES_SYS(SPI_STACK* stack, int)
{
  return true;
}

static bool _MES_SYS_SPECTOL(SPI_STACK* stack, int)
{
  return true;
}

static bool amapIMG(SPI_STACK* stack, int)
{
  return true;
}

static bool amapPCP(SPI_STACK* stack, int)
{
  return true;
}

static bool dynFRAME_START(SPI_STACK* stack, int)
{
  return true;
}

static bool dynFRAME(SPI_STACK* stack, int)
{
  return true;
}

static bool dynFRAME_END(SPI_STACK* stack, int)
{
  return true;
}

static bool dynVERTEX_START(SPI_STACK* stack, int)
{
  return true;
}

static bool dynVERTEX_L(SPI_STACK* stack, int)
{
  return true;
}

static bool dynVERTEX_END(SPI_STACK* stack, int)
{
  return true;
}

static bool dynFIX_VERTEX_START(SPI_STACK* stack, int)
{
  return true;
}

static bool dynFIX_VERTEX(SPI_STACK* stack, int)
{
  return true;
}

static bool dynFIX_VERTEX_C(SPI_STACK* stack, int)
{
  return true;
}

static bool dynFIX_VERTEX_S(SPI_STACK* stack, int)
{
  return true;
}

static bool dynFIX_VERTEX_END(SPI_STACK* stack, int)
{
  return true;
}

static bool dynFRAME_POSE(SPI_STACK* stack, int)
{
  return true;
}

static bool dynFRAME_POSE_L(SPI_STACK* stack, int)
{
  return true;
}

static bool dynDRAW_FRAME(SPI_STACK* stack, int)
{
  return true;
}

static bool dynBIND_VERTEX_START(SPI_STACK* stack, int)
{
  return true;
}

static bool dynBIND_VERTEX(SPI_STACK* stack, int)
{
  return true;
}

static bool dynBIND_VERTEX_END(SPI_STACK* stack, int)
{
  return true;
}

static bool dynBOUNDING_BOX_START(SPI_STACK* stack, int)
{
  return true;
}

static bool dynBOUNDING_BOX(SPI_STACK* stack, int)
{
  return true;
}

static bool dynBOUNDING_BOX_END(SPI_STACK* stack, int)
{
  return true;
}

static bool dynCOLLISION_START(SPI_STACK* stack, int)
{
  return true;
}

static bool dynCOLLISION(SPI_STACK* stack, int)
{
  return true;
}

static bool dynCOLLISION_END(SPI_STACK* stack, int)
{
  return true;
}

static bool dynGRAVITY(SPI_STACK* stack, int)
{
  return true;
}

static bool dynWIND(SPI_STACK* stack, int)
{
  return true;
}



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

// 003359a0
const std::array<SPI_TAG_PARAM, 25> gamedata_tag =
{
  "COMINIT",    _DATACOMINIT,
  "COM",        _DATACOM,
  "WEPNUM",     _DATAWEBNUM,
  "WEP",        _DATAWEP,
  "WEP_ST",     _DATAWEP_ST,
  "WEP_ST_L",   _DATAWEP_ST_L,
  "WEP_ST2",    _DATAWEP2_ST,
  "WEP_ST2_L",  _DATAWEP2_ST_L,
  "WEP_SPE",    _DATAWEP_SPE,
  "WEP_BUILD",  _DATAWEP_BUILDUP,
  "ITEMINIT",   _DATAITEMINIT,
  "ITEM",       _DATAITEM,
  "AT_INIT",    _DATAATTACHINIT,
  "AT_ST",      _DATAATTACH_ST,
  "AT_ST2",     _DATAATTACH_ST2,
  "AT_ST_SP",   _DATAATTACH_ST_SP,
  "ROBOTINIT",  _DATAROBOINIT,
  "RB_PARTS",   _DATAROBO_ANALYZE,
  "GRDNUM",     _DATAGUARDNUM,
  "GRD",        _DATAGUARD,
  "FISHINIT",   _DATAFISHINIT,
  "FISH",       _DATAFISH,
  "MES_SYS",    _MES_SYS,
  "MES_SYSSPE", _MES_SYS_SPECTOL,
  NULL, nullptr
};

// 00334a80
const std::array<SPI_TAG_PARAM, 3> add_mapinfo_tag =
{
  "IMG", amapIMG,
  "PCP", amapPCP,
  NULL, nullptr
};

const std::array<SPI_TAG_PARAM, 27> dynmc_tag =
{
  "FRAME_START",        dynFRAME_START,
  "FRAME",              dynFRAME,
  "FRAME_END",          dynFRAME_END,
  "VERTEX_START",       dynVERTEX_START,
  "VERTEX_END",         dynVERTEX_END,
  "FIX_VERTEX_START",   dynFIX_VERTEX_START,
  "FIX_VERTEX",         dynFIX_VERTEX,
  "FIX_VERTEX_C",       dynFIX_VERTEX_C,
  "FIX_VERTEX_S",       dynFIX_VERTEX_S,
  "FIX_VERTEX_END",     dynFIX_VERTEX_END,
  "FRAME_POSE",         dynFRAME_POSE,
  "FRAME_POST_L",       dynFRAME_POSE_L,
  "DRAW_FRAME",         dynDRAW_FRAME,
  "BIND_VERTEX_START",  dynBIND_VERTEX_START,
  "BIND_VERTEX",        dynBIND_VERTEX,
  "BIND_VERTEX_END",    dynBIND_VERTEX_END,
  "BOUNDING_BOX_START", dynBOUNDING_BOX_START,
  "BOUNDING_BOX",       dynBOUNDING_BOX,
  "BOUNDING_BOX_END",   dynBOUNDING_BOX_END,
  "COLLISION_START",    dynCOLLISION_START,
  "COLISSION",          dynCOLLISION,
  "GRAVITY",            dynGRAVITY,
  "WIND",               dynWIND,
  NULL, nullptr
};
