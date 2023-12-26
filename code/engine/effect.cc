#include <string.h>

#include "common/log.h"
#include "common/macros.h"

#include "engine/effect.h"

set_log_channel("effect");

// 00376f48
// this is prob a global but im just leaving it like this for now
static CEffectManager* g_tmp_effm{ nullptr };

// 00181490
static bool __BUFFER_SIZE(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  const int a = spiGetStackInt(stack);
  const int b = spiGetStackInt(++stack);

  g_tmp_effm->GetEffectNums(a, b);

  return true;
}

// 001814e0
static bool __EFFECT_START(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181530
static bool __EFFECT_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181b30
static bool __WAIT_FRAME(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181b80
static bool __IMG_NAME(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181bb0
static bool __SIZE(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181bf0
static bool __DIR(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181c20
static bool __NUM(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181c50
static bool __NUM_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181cb0
static bool __COUNT(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  g_tmp_effm->count = spiGetStackInt(stack);

  return true;
}

// 00181ce0
static bool __CNT_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181d40
static bool __REPEAT(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181db0
static bool __REP_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181e10
static bool __POS(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181e70
static bool __POS_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181ef0
static bool __VELO(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181f50
static bool __VELO_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181fd0
static bool __VELO_MUL(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182030
static bool __ACC(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182090
static bool __ACC_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182110
static bool __ACC_MUL(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182170
static bool __MOVE_TYPE(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001821d0
static bool __MOVE_P1(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182230
static bool __MOVE_P1_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001822b0
static bool __MOVE_P2(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182310
static bool __MOVE_P2_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182390
static bool __SCALE_TYPE(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001823d0
static bool __SCALE(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182410
static bool __SCALE_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182480
static bool __SVELO(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001824c0
static bool __SVELO_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182530
static bool __SCALE_P1(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182570
static bool __SCALE_P1_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001825e0
static bool __SCALE_P2(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182620
static bool __SCALE_P2_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

static bool __ALPHA_BLEND(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  g_tmp_effm->alpha_blend = spiGetStackInt(stack);

  return true;
}

// 001826c0
static bool __ALPHA_TYPE(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  g_tmp_effm->alpha_type = spiGetStackInt(stack);

  return true;
}

// 001826f0
static bool __ALPHA(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  g_tmp_effm->alpha = spiGetStackInt(stack);

  return true;
}

// 00182720
static bool __ALPHA_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182780
static bool __ALPHA_P1(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001827b0
static bool __ALPHA_P1_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182810
static bool __ALPHA_P2(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182840
static bool __ALPHA_P2_RAND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001828a0
static bool __TEX_GET_RECT(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182970
static bool __TEX_GET_TYPE(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001829a0
static bool __TEX_NAME(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001829f0
static bool __GRAVITY(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00334f30
const std::array<SPI_TAG_PARAM, 48> effm_tag =
{
  SPI_TAG_PARAM{ "BUFFER_SIZE",   __BUFFER_SIZE   },
  SPI_TAG_PARAM{ "EFFECT_START",  __EFFECT_START  },
  SPI_TAG_PARAM{ "EFFECT_END",    __EFFECT_END    },
  SPI_TAG_PARAM{ "WAIT_FRAME",    __WAIT_FRAME    },
  SPI_TAG_PARAM{ "IMG_NAME",      __IMG_NAME      },
  SPI_TAG_PARAM{ "SIZE",          __SIZE          },
  SPI_TAG_PARAM{ "DIR",           __DIR           },
  SPI_TAG_PARAM{ "NUM",           __NUM           },
  SPI_TAG_PARAM{ "NUM_RAND",      __NUM_RAND      },
  SPI_TAG_PARAM{ "COUNT",         __COUNT         },
  SPI_TAG_PARAM{ "CNT_RAND",      __CNT_RAND      },
  SPI_TAG_PARAM{ "REPEAT",        __REPEAT        },
  SPI_TAG_PARAM{ "__REP_RAND",    __REP_RAND      }, // this one is __ for some reason
  SPI_TAG_PARAM{ "POS",           __POS           },
  SPI_TAG_PARAM{ "POS_RAND",      __POS_RAND      },
  SPI_TAG_PARAM{ "VELO",          __VELO          },
  SPI_TAG_PARAM{ "VELO_RAND",     __VELO_RAND     },
  SPI_TAG_PARAM{ "VELO_MUL",      __VELO_MUL      },
  SPI_TAG_PARAM{ "ACC",           __ACC           },
  SPI_TAG_PARAM{ "ACC_RAND",      __ACC_RAND      },
  SPI_TAG_PARAM{ "ACC_MUL",       __ACC_MUL       },
  SPI_TAG_PARAM{ "MOVE_TYPE",     __MOVE_TYPE     },
  SPI_TAG_PARAM{ "MOVE_P1",       __MOVE_P1       },
  SPI_TAG_PARAM{ "MOVE_P1_RAND",  __MOVE_P1_RAND  },
  SPI_TAG_PARAM{ "MOVE_P2",       __MOVE_P2       },
  SPI_TAG_PARAM{ "MOVE_P2_RAND",  __MOVE_P2_RAND  },
  SPI_TAG_PARAM{ "SCALE_TYPE",    __SCALE_TYPE    },
  SPI_TAG_PARAM{ "SCALE",         __SCALE         },
  SPI_TAG_PARAM{ "SCALE_RAND",    __SCALE_RAND    },
  SPI_TAG_PARAM{ "SVELO",         __SVELO         },
  SPI_TAG_PARAM{ "SVELO_RAND",    __SVELO_RAND    },
  SPI_TAG_PARAM{ "SCALE_P1",      __SCALE_P1      },
  SPI_TAG_PARAM{ "SCALE_P1_RAND", __SCALE_P1_RAND },
  SPI_TAG_PARAM{ "SCALE_P2",      __SCALE_P2      },
  SPI_TAG_PARAM{ "SCALE_P2_RAND", __SCALE_P2_RAND },
  SPI_TAG_PARAM{ "ALPHA_BLEND",   __ALPHA_BLEND   },
  SPI_TAG_PARAM{ "ALPHA_TYPE",    __ALPHA_TYPE    },
  SPI_TAG_PARAM{ "ALPHA",         __ALPHA         },
  SPI_TAG_PARAM{ "ALPHA_RAND",    __ALPHA_RAND    },
  SPI_TAG_PARAM{ "ALPHA_P1",      __ALPHA_P1      },
  SPI_TAG_PARAM{ "ALPHA_P1_RAND", __ALPHA_P1_RAND },
  SPI_TAG_PARAM{ "ALPHA_P2",      __ALPHA_P2      },
  SPI_TAG_PARAM{ "ALPHA_P2_RAND", __ALPHA_P2_RAND },
  SPI_TAG_PARAM{ "TEX_GET_RECT",  __TEX_GET_RECT  },
  SPI_TAG_PARAM{ "TEX_GET_TYPE",  __TEX_GET_TYPE  },
  SPI_TAG_PARAM{ "TEX_NAME",      __TEX_NAME      },
  SPI_TAG_PARAM{ "GRAVITY",       __GRAVITY       },
  SPI_TAG_PARAM{ NULL,            nullptr         }
};

// 00182fa0
void CEffectManager::GetBufferNums(MAYBE_UNUSED const char* script, MAYBE_UNUSED sint script_size, MAYBE_UNUSED sint* unk0, MAYBE_UNUSED sint* unk2)
{
  log_trace("GetBufferNums({}, {}, {}, {})", fmt::ptr(script), script_size, fmt::ptr(unk0), fmt::ptr(unk2));

  todo;
}

// 00182bc0
void CEffectManager::GetEffectNums(MAYBE_UNUSED sint unk0, MAYBE_UNUSED sint unk1)
{
  log_trace("GetEffectNums({}, {})", unk0, unk1);

  todo;
}

// 001847C0
void CFireRaster::Initialize()
{
  log_trace("CFireRaster::Initialize()");

  for (auto& unk_var : m_unk_field_70)
  {
    memset(&unk_var, 0, sizeof(unk_var));
  }
}

// 00184820
void CThunderEffect::Initialize()
{
  log_trace("CThunderEffect::Initialize()");

  m_unk_field_0 = 0;
  m_unk_field_90 = 0;
  m_unk_field_94 = 0;
  m_unk_field_98 = 0;
}

// 001A2110
CWaveTable::CWaveTable()
{
  log_trace("CWaveTable::CWaveTable()");

  memset(&m_unk_field_0, 0, sizeof(m_unk_field_0));
  memset(&m_unk_field_900, 0, sizeof(m_unk_field_900));
  m_unk_field_1200 = 0;
}