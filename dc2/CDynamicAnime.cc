#include "CDynamicAnime.h"
#include "CScriptInterpreter.h"

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

void CDynamicAnime::Load(const char* script, int script_size, mgCFrame* frame, mgCMemory* stack)
{
  // TODO
}
