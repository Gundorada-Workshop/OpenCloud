#pragma once
#include "CEffectManager.h"
#include "CScriptInterpreter.h"

// 00376f48
static CEffectManager* _g_tmp_effm{ nullptr };

static bool __BUFFER_SIZE(SPI_STACK* stack, int)
{
  return true;
}

static bool __EFFECT_START(SPI_STACK* stack, int)
{
  return true;
}

static bool __EFFECT_END(SPI_STACK* stack, int)
{
  return true;
}

static bool __WAIT_FRAME(SPI_STACK* stack, int)
{
  return true;
}

static bool __IMG_NAME(SPI_STACK* stack, int)
{
  return true;
}

static bool __SIZE(SPI_STACK* stack, int)
{
  return true;
}

static bool __DIR(SPI_STACK* stack, int)
{
  return true;
}

static bool __NUM(SPI_STACK* stack, int)
{
  return true;
}

static bool __NUM_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __COUNT(SPI_STACK* stack, int)
{
  return true;
}

static bool __CNT_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __REPEAT(SPI_STACK* stack, int)
{
  return true;
}

static bool __REP_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __POS(SPI_STACK* stack, int)
{
  return true;
}

static bool __POS_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __VELO(SPI_STACK* stack, int)
{
  return true;
}

static bool __VELO_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __VELO_MUL(SPI_STACK* stack, int)
{
  return true;
}

static bool __ACC(SPI_STACK* stack, int)
{
  return true;
}

static bool __ACC_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __ACC_MUL(SPI_STACK* stack, int)
{
  return true;
}

static bool __MOVE_TYPE(SPI_STACK* stack, int)
{
  return true;
}

static bool __MOVE_P1(SPI_STACK* stack, int)
{
  return true;
}

static bool __MOVE_P1_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __MOVE_P2(SPI_STACK* stack, int)
{
  return true;
}

static bool __MOVE_P2_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE_TYPE(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __SVELO(SPI_STACK* stack, int)
{
  return true;
}

static bool __SVELO_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE_P1(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE_P1_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE_P2(SPI_STACK* stack, int)
{
  return true;
}

static bool __SCALE_P2_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_BLEND(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_TYPE(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_P1(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_P1_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_P2(SPI_STACK* stack, int)
{
  return true;
}

static bool __ALPHA_P2_RAND(SPI_STACK* stack, int)
{
  return true;
}

static bool __TEX_GET_RECT(SPI_STACK* stack, int)
{
  return true;
}

static bool __TEX_GET_TYPE(SPI_STACK* stack, int)
{
  return true;
}

static bool __TEX_NAME(SPI_STACK* stack, int)
{
  return true;
}

static bool __GRAVITY(SPI_STACK* stack, int)
{
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
void CEffectManager::GetBufferNums(const char* script, int script_size, int* unk, int* unk2)
{
  // TODO
}