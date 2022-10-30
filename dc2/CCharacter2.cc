#include "CCharacter2.h"
#include "CScriptInterpreter.h"

static bool _SKIN_IMG(SPI_STACK* stack, int)
{
  return true;
}

static bool _SKIN_IMG_END(SPI_STACK* stack, int)
{
  return true;
}

static bool _SKIN_MODEL(SPI_STACK* stack, int)
{
  return true;
}

static bool _SKIN_MOTION(SPI_STACK* stack, int)
{
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
