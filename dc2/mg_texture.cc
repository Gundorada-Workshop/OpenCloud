#include "common/debug.h"
#include "common/log.h"
#include "mg_memory.h"
#include "mg_texture.h"
#include "script_interpreter.h"

set_log_channel("mg_texture");

// 00376C28
static mgCTextureManager* TexManager{ nullptr };
// 00376C20
static mgCTextureAnime* pLoadTexAnime{ nullptr };
// 00376C2C
static mgCMemory* TexAnimeStack{ nullptr };
// 00376C30
static char* group_name{ NULL };
// 00376C34
static int ta_enable = 0;

static bool texTEX_ANIME(SPI_STACK* stack, int)
{
  const char* s = spiGetStackString(stack);

  if (s)
  {
    auto len = strlen(s) + 1;
    auto dest = static_cast<char*>(TexAnimeStack->Alloc((len >> 4) + 1));

    strcpy(dest, s);

    group_name = dest;
  }

  ta_enable = spiGetStackInt(++stack);

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

// 0012C6D0
mgCTextureBlock::mgCTextureBlock()
{
  log_trace("mgCTextureBlock::mgCTextureBlock()");

  Initialize();
}

// 0012C700
void mgCTextureBlock::Initialize()
{
  log_trace("mgCTextureBlock::Initialize()");

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;
  m_unk_field_8 = 0;
  m_unk_field_C = 0;
}

// 0012C7E0
mgCTextureManager::mgCTextureManager()
{
  log_trace("mgCTextureManager::mgCTextureManager()");

  todo;
}

// 0012D050
mgCTexture* mgCTextureManager::GetTexture(const char* name, ssize i)
{
  log_trace("mgCTextureManager::{}({}, {})", __func__, name, i);

  todo;
  return nullptr;
}

// 0012D140
void mgCTextureManager::EnterTexture(usize texb, const char* name, _UNKNOWNPOINTER p1, s32 width, s32 height, u32 i3, _UNKNOWNPOINTER p2, u64 i4, int i5)
{
  log_trace(
    "mgCTextureManager::{}({}, {}, {}, {}, {}, {}, {}, {}, {})",
    __func__,
    texb,
    name,
    fmt::ptr(p1),
    width,
    height,
    i3,
    fmt::ptr(p2),
    i4,
    i5
  );

  todo;
}

// 0012DA90
void mgCTextureManager::EnterIMGFile(u8* img_file_buff, usize texb, mgCMemory* stack, mgCEnterIMGInfo* enter_info)
{
  log_trace("mgCTextureManager::{}({}, {}, {}, {})", __func__, fmt::ptr(img_file_buff), texb, fmt::ptr(stack), fmt::ptr(enter_info));

  todo;
}

// 0012E540
void mgCTextureManager::DeleteBlock(usize texb)
{
  log_trace("mgCTextureManager::DeleteBlock({})", texb);

  todo;
}

// 0012E850
void mgCTextureManager::ReloadTexture(usize texb, sceVif1Packet* vif1_packet)
{
  log_trace("mgCTextureManager::ReloadTexture({}, {})", texb, fmt::ptr(vif1_packet));

  todo;
}

// 0013d8c0
void mgCTextureManager::LoadCFGFile(const char* file, int size, mgCMemory* tex_anime_stack, mgCTextureAnime* tex_anime)
{
  CScriptInterpreter interpreter{ };

  unimplemented_var(_pTexAnime = 0);
  group_name = 0;
  ta_enable = 0;
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

// 0012C480
mgCTexture::mgCTexture()
{
  log_trace("mgCTexture::mgCTexture()");

  Initialize();
}

// 0012C4B0
void mgCTexture::Initialize()
{
  log_trace("mgCTexture::Initialize()");

  m_unk_field_8[0] = '\0';
  m_unk_field_0 = -1;

  for (float& f : m_unk_field_50)
  {
    f = 0.0f;
  }

  m_unk_field_60 = 0;
  m_unk_field_48 = 0;
  m_unk_field_40 = 0;
  m_unk_field_38 = 0;

  m_unk_field_48 = m_unk_field_48 & (~0b0000'0011) | 1;
  m_unk_field_48 = m_unk_field_48 & (~0b0000'1100) | 4;

  m_unk_field_6 = 0;
  m_unk_field_4 = 0;
  m_unk_field_2 = 0;
  m_unk_field_64 = 0;
  m_unk_field_28 = 0;
  m_unk_field_2C = 0;
  m_unk_field_30 = 0;
  m_unk_field_68 = 0;
}