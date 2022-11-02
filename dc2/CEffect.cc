#include "string.h"
#include "common/log.h"
#include "CEffect.h"

set_log_channel("CEffect");

// 00376f48
// this is prob a global but im just leaving it like this for now
static CEffectManager* g_tmp_effm{ nullptr };

// 0017D750
void CFadeInOut::Initialize()
{
  log_trace("CFadeInOut::Initialize()");

  m_unk_field_0 = 0.0f;
  m_unk_field_4 = 0.0f;
  m_unk_field_8 = 0.0f;
  m_unk_field_C = 0.0f;
  m_unk_field_10 = 0;
  m_unk_field_14 = false;
  m_unk_field_18 = 0.0f;
  m_unk_field_1C = 0;
  m_unk_field_20 = false;
  m_unk_field_24 = 0.0f;
  m_unk_field_28 = nullptr;
  m_unk_field_2C = 0;
}

// 00181490
static bool __BUFFER_SIZE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  const int a = spiGetStackInt(stack);
  const int b = spiGetStackInt(++stack);

  g_tmp_effm->GetEffectNums(a, b);

  return true;
}

// 001814e0
static bool __EFFECT_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181530
static bool __EFFECT_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181b30
static bool __WAIT_FRAME(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181b80
static bool __IMG_NAME(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181bb0
static bool __SIZE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181bf0
static bool __DIR(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181c20
static bool __NUM(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181c50
static bool __NUM_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181cb0
static bool __COUNT(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  g_tmp_effm->count = spiGetStackInt(stack);

  return true;
}

// 00181ce0
static bool __CNT_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181d40
static bool __REPEAT(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181db0
static bool __REP_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181e10
static bool __POS(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181e70
static bool __POS_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181ef0
static bool __VELO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181f50
static bool __VELO_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00181fd0
static bool __VELO_MUL(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182030
static bool __ACC(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182090
static bool __ACC_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182110
static bool __ACC_MUL(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182170
static bool __MOVE_TYPE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001821d0
static bool __MOVE_P1(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182230
static bool __MOVE_P1_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001822b0
static bool __MOVE_P2(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182310
static bool __MOVE_P2_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182390
static bool __SCALE_TYPE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001823d0
static bool __SCALE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182410
static bool __SCALE_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182480
static bool __SVELO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001824c0
static bool __SVELO_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182530
static bool __SCALE_P1(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182570
static bool __SCALE_P1_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001825e0
static bool __SCALE_P2(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182620
static bool __SCALE_P2_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

static bool __ALPHA_BLEND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  g_tmp_effm->alpha_blend = spiGetStackInt(stack);

  return true;
}

// 001826c0
static bool __ALPHA_TYPE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  g_tmp_effm->alpha_type = spiGetStackInt(stack);

  return true;
}

// 001826f0
static bool __ALPHA(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  g_tmp_effm->alpha = spiGetStackInt(stack);

  return true;
}

// 00182720
static bool __ALPHA_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182780
static bool __ALPHA_P1(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001827b0
static bool __ALPHA_P1_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182810
static bool __ALPHA_P2(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182840
static bool __ALPHA_P2_RAND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001828a0
static bool __TEX_GET_RECT(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00182970
static bool __TEX_GET_TYPE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001829a0
static bool __TEX_NAME(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 001829f0
static bool __GRAVITY(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

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

// 00182fa0
void CEffectManager::GetBufferNums(const char* script, int script_size, int* unk0, int* unk2)
{
  log_trace("GetBufferNums({}, {}, {}, {})", fmt::ptr(script), script_size, fmt::ptr(unk0), fmt::ptr(unk2));

  todo;
}

// 00182bc0
void CEffectManager::GetEffectNums(int unk0, int unk1)
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
  log_trace("CThunderEffect::Initialize");

  m_unk_field_0 = 0;
  m_unk_field_90 = 0;
  m_unk_field_94 = 0;
  m_unk_field_98 = 0;
}