#include "CCharacter2.h"
#include "CScriptInterpreter.h"
#include "common/debug.h"
#include "common/log.h"

set_log_channel("CCharecter2");

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
