#include "mgCTextureManager.h"
#include "CScriptInterpreter.h"

#include "common/debug.h"

static mgCTextureManager* TexManager{ nullptr };
static mgCTextureAnime* pLoadTexAnime{ nullptr };
static mgCMemory* TexAnimeStack{ nullptr };
static char* _group_name{ NULL };
static int _ta_enable = 0;

static bool texTEX_ANIME(SPI_STACK* stack, int)
{
  const char* s = spiGetStackString(stack);

  if (s)
  {
    auto len = strlen(s) + 1;
    auto dest = static_cast<char*>(TexAnimeStack->Alloc((len >> 4) + 1));

    strcpy(dest, s);

    _group_name = dest;
  }

  _ta_enable = spiGetStackInt(++stack);

  return true;
}

static bool texTEX_ANIME_DATA(SPI_STACK* stack, int)
{
  todo;

  return true;
}

static bool texSRC_TEX(SPI_STACK* stack, int)
{
  todo;

  return true;
}

static bool texDEST_TEX(SPI_STACK* stack, int)
{
  todo;

  return true;
}

static bool texSCROLL(SPI_STACK* stack, int)
{
  todo;

  return true;
}

static bool texCLUT_COPY(SPI_STACK* stack, int)
{
  todo;

  return true;
}

static bool texCOLOR(SPI_STACK* stack, int)
{
  todo;

  return true;
}

static bool texALPHA_BLEND(SPI_STACK* stack, int)
{
  todo;

  return true;
}

static bool texALPHA_TEST(SPI_STACK* stack, int)
{
  todo;

  return true;
}

static bool texWAIT(SPI_STACK* stack, int)
{
  todo;

  return true;
}

static bool texTEX_ANIME_DATA_END(SPI_STACK* stack, int)
{
  todo;

  return true;
}

static bool texANIME_END(SPI_STACK* stack, int)
{
  todo;

  return true;
}

static bool texANIME_BUG_PATCH(SPI_STACK* stack, int)
{
  todo;

  return true;
}

// 003340b0
const std::array<SPI_TAG_PARAM, 14> tex_tag =
{
  "TEX_ANIME",          texTEX_ANIME,
  "TEX_ANIME_DATA",     texTEX_ANIME_DATA,
  "SRC_TEX",            texSRC_TEX,
  "DEST_TEX",           texDEST_TEX,
  "SCROLL",             texSCROLL,
  "CLUT_COPY",          texCLUT_COPY,
  "COLOR",              texCOLOR,
  "ALPHA_BLEND",        texALPHA_BLEND,
  "ALPHA_TEST",         texALPHA_TEST,
  "WAIT",               texWAIT,
  "TEX_ANIME_DATA_END", texTEX_ANIME_DATA_END,
  "TEX_ANIME_END",      texANIME_END,
  "BUG_PATCH",          texANIME_BUG_PATCH,
  NULL, nullptr
};

// 0013d8c0
void mgCTextureManager::LoadCFGFile(const char* file, int size, mgCMemory* tex_anime_stack, mgCTextureAnime* tex_anime)
{
  CScriptInterpreter interpreter{ };

  unimplemented_var(_pTexAnime = 0);
  _group_name = 0;
  _ta_enable = 0;
  unimplemented_var(_now_texb = 0xffffffff);
  unimplemented_var(_now_group = 0xffffffff);
  unimplemented_var(texBugPatch = 0);

  pLoadTexAnime = tex_anime;
  TexManager = this;
  TexAnimeStack = tex_anime_stack;

  interpreter.SetTag(tex_tag.data());
  interpreter.SetScript(file, size);
  interpreter.Run();
}
