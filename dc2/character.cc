#include "common/log.h"
#include "character.h"
#include "script_interpreter.h"

set_log_channel("character")

// 00177f20
static bool _SKIN_IMG(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00177f80
static bool _SKIN_IMG_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00177f90
static bool _SKIN_MODEL(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00178170
static bool _SKIN_MOTION(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00334db0
static const std::array<SPI_TAG_PARAM, 5> skin_tag =
{
  "IMG",     _SKIN_IMG,
  "IMG_END", _SKIN_IMG_END,
  "MODEL",   _SKIN_MODEL,
  "MOTION",  _SKIN_MOTION,
  NULL, nullptr
};

CDynamicAnime* dynNowDA{ nullptr };
mgCMemory* dynStack{ nullptr };

// 0017b160
static bool dynFRAME_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b190
static bool dynFRAME(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b210
static bool dynFRAME_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actually just returns true
  return true;
}

// 0017b220
static bool dynVERTEX_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  const int var = spiGetStackInt(stack);
  dynNowDA->NewVertexTable(var, dynStack);

  return true;
}

// 0017b300
static bool dynVERTEX_L(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  const int frame_id = spiGetStackInt(stack);

  vec3 vec{ };
  spiGetStackVector(vec, ++stack);

  todo;

  return true;
}

// 0017b390
static bool dynVERTEX_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b410
static bool dynFIX_VERTEX_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b530
static bool dynFIX_VERTEX(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b5c0
static bool dynFIX_VERTEX_C(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b650
static bool dynFIX_VERTEX_S(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b6e0
static bool dynFIX_VERTEX_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b8b0
static bool dynFRAME_POSE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b8b0
static bool dynFRAME_POSE_L(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b970
static bool dynDRAW_FRAME(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b9f0
static bool dynBIND_VERTEX_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017ba20
static bool dynBIND_VERTEX(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017bb80
static bool dynBIND_VERTEX_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actually just returns true
  return true;
}

// 0017bb90
static bool dynBOUNDING_BOX_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  const int var = spiGetStackInt(stack);
  dynNowDA->NewBoundingBoxTable(var, dynStack);

  return true;
}

// 0017bbc0
static bool dynBOUNDING_BOX(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017bc70
static bool dynBOUNDING_BOX_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actually just returns true
  return true;
}

// 0017bc80
static bool dynCOLLISION_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  const int var = spiGetStackInt(stack);
  dynNowDA->NewCollisionTable(var, dynStack);

  return true;
}

// 0017bcb0
static bool dynCOLLISION(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017be60
static bool dynCOLLISION_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actuall just returns true
  return true;
}

// 0017be70
static bool dynGRAVITY(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017bed0
static bool dynWIND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

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
  log_trace("Load({}, {}, {}, {})", fmt::ptr(script), script_size, fmt::ptr(frame), fmt::ptr(stack));

  todo;
}

void CDynamicAnime::NewVertexTable(int unk, mgCMemory* stack)
{
  log_trace("NewVertexTable({}, {})", unk, fmt::ptr(stack));

  todo;
}

void CDynamicAnime::NewBoundingBoxTable(int unk, mgCMemory* stack)
{
  log_trace("NewBoundingBoxTable({}, {})", unk, fmt::ptr(stack));

  todo;
}

void CDynamicAnime::NewCollisionTable(int unk, mgCMemory* stack)
{
  log_trace("NewCollisionTable({}, {})", unk, fmt::ptr(stack));

  todo;
}