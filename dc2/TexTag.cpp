#include "TexTag.h"

static bool texTEX_ANIME(SPI_STACK* stack, int)
{
  return false;
}

static bool texTEX_ANIME_DATA(SPI_STACK* stack, int)
{
  return false;
}

static bool texSRC_TEX(SPI_STACK* stack, int)
{
  return false;
}

static bool texDEST_TEX(SPI_STACK* stack, int)
{
  return false;
}

static bool texSCROLL(SPI_STACK* stack, int)
{
  return false;
}

static bool texCLUT_COPY(SPI_STACK* stack, int)
{
  return false;
}

static bool texCOLOR(SPI_STACK* stack, int)
{
  return false;
}

static bool texALPHA_BLEND(SPI_STACK* stack, int)
{
  return false;
}

static bool texALPHA_TEST(SPI_STACK* stack, int)
{
  return false;
}

static bool texWAIT(SPI_STACK* stack, int)
{
  return false;
}

static bool texTEX_ANIME_DATA_END(SPI_STACK* stack, int)
{
  return false;
}

static bool texANIME_END(SPI_STACK* stack, int)
{
  return false;
}

static bool texANIME_BUG_PATCH(SPI_STACK* stack, int)
{
  return false;
}

const std::array<SPI_TAG_PARAM, 14> tex_tag =
{
  "TEX_ANIME", &texTEX_ANIME,
  "TEX_ANIME_DATA", &texTEX_ANIME_DATA,
  "SRC_TEX", &texSRC_TEX,
  "DEST_TEX", &texDEST_TEX,
  "SCROLL", &texSCROLL,
  "CLUT_COPY", &texCLUT_COPY,
  "COLOR", &texCOLOR,
  "ALPHA_BLEND", &texALPHA_BLEND,
  "ALPHA_TEST", &texALPHA_TEST,
  "WAIT", &texWAIT,
  "TEX_ANIME_DATA_END", &texTEX_ANIME_DATA_END,
  "TEX_ANIME_END", &texANIME_END,
  "BUG_PATCH", &texANIME_BUG_PATCH,
  NULL, nullptr
};
