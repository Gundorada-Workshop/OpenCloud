#include "common/debug.h"
#include "common/log.h"

#include "gamedata.h"
#include "script_interpreter.h"

set_log_channel("gamedata");

// 00194750
static bool _DATACOMINIT(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001947a0
static bool _DATACOM(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001949c0
static bool _DATAWEBNUM(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194a00
static bool _DATAWEP(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194a60
static bool _DATAWEP_ST(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194ac0
static bool _DATAWEP_ST_L(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194b20
static bool _DATAWEP2_ST(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194ba0
static bool _DATAWEP2_ST_L(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194c20
static bool _DATAWEP_SPE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194d10
static bool _DATAWEP_BUILDUP(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194dc0
static bool _DATAITEMINIT(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194e00
static bool _DATAITEM(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194ee0
static bool _DATAATTACHINIT(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194f20
static bool _DATAATTACH_ST(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00194fa0
static bool _DATAATTACH_ST2(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00195020
static bool _DATAATTACH_ST_SP(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00195070
static bool _DATAROBOINIT(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001950b0
static bool _DATAROBO_ANALYZE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001953a0
static bool _DATAGUARDNUM(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001953d0
static bool _DATAGUARD(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

static bool _DATAFISHINIT(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001952a0
static bool _DATAFISH(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

static bool _MES_SYS(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

static bool _MES_SYS_SPECTOL(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 003359a0
static const std::array<SPI_TAG_PARAM, 25> gamedata_tag =
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

CGameData::CGameData()
{
  log_trace("CGameData()");

  todo;
}
