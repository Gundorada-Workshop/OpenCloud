#include "common/log.h"
#include "common/macros.h"

#include "dc2/monster.h"
#include "dc2/monster_func.h"
#include "dc2/run_script.h"
#include "dc2/script_interpreter.h"

set_log_channel("monster");

static bool _MONSTER_NAME(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "NAME"
  trace_script_call(stack, stack_count);

  todo;
  return false;
}

// 0034D2F0
static const std::array<SPI_TAG_PARAM, 2> mos_data_anlyze_tag =
{
  "NAME", _MONSTER_NAME,
  NULL, nullptr
};

