#include "common/debug.h"
#include "common/log.h"

#include "CDngFloorManager.h"
#include "CScriptInterpreter.h"

set_log_channel("CDngFloorMAnager");

static CDngFloorManager* _tree_dngmap{ nullptr };
static mgCMemory* _tree_spi_stack{ nullptr };

// 002f8ce0
static bool _TREE_MAPINFO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f8db0
static bool _GLID_INFO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f8ea0
static bool _ROOT_INFO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f8f00
static bool _ROOM_INFO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f8fd0
static bool _ROOM_LINK(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f9050
static bool _ROOM_OPTION(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f91d0
static bool _ROOM_TEXNO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f9160
static bool _ROOM_KEYROOM(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f9230
static bool _ROOM_FLOOR_INFO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f93a0
static bool _ROOM_TITLE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0035d010
static const std::array<SPI_TAG_PARAM, 12> tree_map_tag =
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

// 002f9420
void CDngFloorManager::AnalyzeFile(const char* script, int script_size, mgCMemory* tree_stack)
{
  log_trace("AnalyzeFile({}, {}, {})", fmt::ptr(script), script_size, fmt::ptr(tree_stack));

  _tree_dngmap = this;
  _tree_spi_stack = tree_stack;

  tree_stack->Align64();
  unimplemented_var(_menu_dng_debug_glidcnt = 0);

  CScriptInterpreter interpreter{ };
  interpreter.SetTag(tree_map_tag.data());
  interpreter.SetScript(script, script_size);
  interpreter.Run();

  _tree_spi_stack->Align64();

  RelationGlid();
}

// 002f9e40
void CDngFloorManager::RelationGlid()
{
  log_trace("RelationGlid()");

  todo;
}
