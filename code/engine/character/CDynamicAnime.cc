#include "common/log.h"
#include "common/debug.h"
#include "common/macros.h"

#include "engine/script_interpreter.h"

#include "engine/character/CDynamicAnime.h"

set_log_channel("character");

// 00378294
//static CScene* nowScene{ nullptr };
CDynamicAnime* dynNowDA{ nullptr };
mgCMemory* dynStack{ nullptr };


// 00177f20
static bool _SKIN_IMG(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00177f80
static bool _SKIN_IMG_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00177f90
static bool _SKIN_MODEL(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00178170
static bool _SKIN_MOTION(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
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

// 0017b160
static bool dynFRAME_START(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b190
static bool dynFRAME(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b210
static bool dynFRAME_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actually just returns true
  return true;
}

// 0017b220
static bool dynVERTEX_START(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  const sint var = spiGetStackInt(stack);
  dynNowDA->NewVertexTable(var, dynStack);

  return true;
}

// 0017b300
//MAYBE_UNUSED static bool dynVERTEX_L(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
//{
//  trace_script_call(stack, stack_count);
//
//  const sint frame_id = spiGetStackInt(stack);
//
//  unused_v(frame_id);
//
//  vec3 vec{ };
//  spiGetStackVector(vec, ++stack);
//
//  todo;
//
//  return true;
//}

// 0017b390
static bool dynVERTEX_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b410
static bool dynFIX_VERTEX_START(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b530
static bool dynFIX_VERTEX(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b5c0
static bool dynFIX_VERTEX_C(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b650
static bool dynFIX_VERTEX_S(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b6e0
static bool dynFIX_VERTEX_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b8b0
static bool dynFRAME_POSE(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b8b0
static bool dynFRAME_POSE_L(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b970
static bool dynDRAW_FRAME(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b9f0
static bool dynBIND_VERTEX_START(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017ba20
static bool dynBIND_VERTEX(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017bb80
static bool dynBIND_VERTEX_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actually just returns true
  return true;
}

// 0017bb90
static bool dynBOUNDING_BOX_START(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  const sint var = spiGetStackInt(stack);
  dynNowDA->NewBoundingBoxTable(var, dynStack);

  return true;
}

// 0017bbc0
static bool dynBOUNDING_BOX(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017bc70
static bool dynBOUNDING_BOX_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actually just returns true
  return true;
}

// 0017bc80
static bool dynCOLLISION_START(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  const sint var = spiGetStackInt(stack);
  dynNowDA->NewCollisionTable(var, dynStack);

  return true;
}

// 0017bcb0
static bool dynCOLLISION(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017be60
MAYBE_UNUSED static bool dynCOLLISION_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actuall just returns true
  return true;
}

// 0017be70
static bool dynGRAVITY(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017bed0
static bool dynWIND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
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


void CDynamicAnime::Load(MAYBE_UNUSED const char* script, MAYBE_UNUSED sint script_size,
                         MAYBE_UNUSED mgCFrame* frame, MAYBE_UNUSED mgCMemory* stack)
{
  log_trace("CDynamicAnime::Load({}, {}, {}, {})", fmt::ptr(script), script_size, fmt::ptr(frame), fmt::ptr(stack));

  todo;
}

void CDynamicAnime::NewVertexTable(MAYBE_UNUSED sint unk, MAYBE_UNUSED mgCMemory* stack)
{
  log_trace("CDynamicAnime::NewVertexTable({}, {})", unk, fmt::ptr(stack));

  todo;
}

void CDynamicAnime::NewBoundingBoxTable(MAYBE_UNUSED sint unk, MAYBE_UNUSED mgCMemory* stack)
{
  log_trace("CDynamicAnime::NewBoundingBoxTable({}, {})", unk, fmt::ptr(stack));

  todo;
}

void CDynamicAnime::NewCollisionTable(MAYBE_UNUSED sint unk, MAYBE_UNUSED mgCMemory* stack)
{
  log_trace("CDynamicAnime::NewCollisionTable({}, {})", unk, fmt::ptr(stack));

  todo;
}

// 00179E70
//void CDynamicAnime::SetWind(f32 velocity, vec4& direction)
//{
//  log_trace("CDynamicAnime::SetWind({}, {})", velocity, fmt::ptr(&direction));
//
//  m_wind_velocity = velocity;
//  m_wind_direction = normalize(direction);
//}

// 00179E80
void CDynamicAnime::ResetWind()
{
  log_trace("CDynamicAnime::ResetWind()");

  m_wind_velocity = 0.0f;
}

// 00179E90
void CDynamicAnime::SetFloor(f32 floor)
{
  log_trace("CDynamicAnime::SetFloor({})", floor);

  m_unk_field_88 = true;
  m_floor = floor;
}

// 00179EA0
void CDynamicAnime::ResetFloor()
{
  log_trace("CDynamicAnime::ResetFloor()");

  m_unk_field_88 = false;
}