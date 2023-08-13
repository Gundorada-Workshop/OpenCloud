#include "common/debug.h"
#include "common/log.h"
#include "common/types.h"

#include "dc2/mg/mg_memory.h"
#include "dc2/mg/mg_tanime.h"
#include "dc2/mg/mg_texture.h"
#include "dc2/script_interpreter.h"

set_log_channel("mg_texture");

// 00376C1C
static mgCTextureAnime* pTexAnime{ nullptr };

// 00376C20
static mgCTextureAnime* pLoadTexAnime{ nullptr };

// 00376C24
static s32 now_group{ 0 };

// 00376C28
static mgCTextureManager* TexManager{ nullptr };

// 00376C2C
static mgCMemory* TexAnimeStack{ nullptr };

// 00376C30
static char* group_name{ nullptr };

// 00376C34
static int ta_enable{ 0 };

// 00376C38
static usize now_texb{ 0 };

// 00376C3C
static bool texBugPatch{ false };

static bool texTEX_ANIME(SPI_STACK* stack, MAYBE_UNUSED sint count)
{
  const char* s = spiGetStackString(stack);

  if (s)
  {
    auto len = strlen(s) + 1;
    auto dest = static_cast<char*>(TexAnimeStack->Alloc(BYTES_TO_BLOCKS_STRICT(len)));

    common::strings::xplat_strcpy_s(dest, len, s);

    group_name = dest;
  }

  ta_enable = spiGetStackInt(++stack);

  return true;
}

static bool texTEX_ANIME_DATA(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint count)
{
  todo;

  return true;
}

static bool texSRC_TEX(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint count)
{
  todo;

  return true;
}

static bool texDEST_TEX(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint count)
{
  todo;

  return true;
}

static bool texSCROLL(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint count)
{
  todo;

  return true;
}

static bool texCLUT_COPY(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint count)
{
  todo;

  return true;
}

static bool texCOLOR(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint count)
{
  todo;

  return true;
}

static bool texALPHA_BLEND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint count)
{
  todo;

  return true;
}

static bool texALPHA_TEST(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint count)
{
  todo;

  return true;
}

static bool texWAIT(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint count)
{
  todo;

  return true;
}

static bool texTEX_ANIME_DATA_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint count)
{
  todo;

  return true;
}

static bool texANIME_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint count)
{
  todo;

  return true;
}

static bool texANIME_BUG_PATCH(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint count)
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
mgCTextureBlock::mgCTextureBlock() = default;

// 0012C700
void mgCTextureBlock::Initialize()
{
  log_trace("mgCTextureBlock::Initialize()");
}

// 0012C720
void mgCTextureBlock::Add(mgCTexture* texture)
{
  log_trace("mgCTextureBlock::Add({})", fmt::ptr(texture));

  texture->m_next = nullptr;
  if (m_unk_field_8 == nullptr)
  {
    m_unk_field_8 = texture;
    return;
  }

  mgCTexture* tex = m_unk_field_8;
  for (; tex->m_next != nullptr; tex = tex->m_next) {}
  tex->m_next = texture;
}

// 0012C780
void mgCTextureBlock::Delete(mgCTexture* texture)
{
  log_trace("mgCTextureBlock::Delete({})", fmt::ptr(texture));

  mgCTexture* prev_tex = nullptr;
  for (mgCTexture* tex = m_unk_field_8; tex->m_next != nullptr; tex = tex->m_next)
  {
    if (texture == tex)
    {
      if (prev_tex == nullptr)
      {
        m_unk_field_8 = tex->m_next;
      }
      else
      {
        prev_tex->m_next = tex->m_next;
      }
    }
    prev_tex = tex;
  }
}

// 0012C830
void mgCTextureManager::SetTableBuffer(sint n_textures, sint n_blocks, mgCMemory* stack)
{
  log_trace("mgCTextureBlock::SetTableBuffer({}, {}, {})", n_textures, n_blocks, fmt::ptr(stack));

  m_n_blocks = n_blocks;
  mgCTextureBlock* block_buf = static_cast<mgCTextureBlock*>(
    stack->Alloc(
      BYTES_TO_BLOCKS(
        sizeof(mgCTextureBlock) * n_blocks
      )
    )
  );

  m_vram_blocks = block_buf;
  if (block_buf != nullptr)
  {
    for (int i = 0; i < n_blocks; ++i)
    {
      new (&block_buf[i]) mgCTextureBlock;
    }
  }
  else
  {
    m_n_blocks = 0;
  }

  m_n_textures = n_textures;
  mgCTexture* texture_buf = static_cast<mgCTexture*>(
    stack->Alloc(
      BYTES_TO_BLOCKS(
        sizeof(mgCTexture) * n_textures
      )
    )
  );

  m_textures = texture_buf;
  if (texture_buf != nullptr)
  {
    for (int i = 0; i < n_textures; ++i)
    {
      new (&texture_buf[i]) mgCTexture;
    }
  }

  MAYBE_UNUSED mgCTexture** p_texture_buf = static_cast<mgCTexture**>(
    stack->Alloc(
      BYTES_TO_BLOCKS_STRICT(
        sizeof(mgCTexture*) * n_textures
      )
    )
  );

  // BUG: no null check
  for (int i = 0; i < m_n_textures; ++i)
  {
    m_p_textures[i] = &m_textures[i];
  }

  m_unk_field_1C4 = 0;
  m_n_hashes_capacity = m_n_textures;

  TextureHash* hash_buf = static_cast<TextureHash*>(
    stack->Alloc(
      BYTES_TO_BLOCKS(
        sizeof(TextureHash) * m_n_hashes_capacity
      )
    )
  );

  m_hashes = hash_buf;

  TextureHash** p_hash_buf = static_cast<TextureHash**>(
    stack->Alloc(
      BYTES_TO_BLOCKS(
        sizeof(TextureHash*) * m_n_hashes_capacity
      )
    )
  );

  m_p_hashes = p_hash_buf;

  for (int i = 0; i < m_n_textures; ++i)
  {
    m_p_hashes[i] = &m_hashes[i];
  }

  m_n_hashes_length = 0;
}

// 0012CAD0
void mgCTextureManager::Initialize(void* vram_top, void* vram_bottom)
{
  log_trace("mgCTextureManager::Initialize({}, {})", fmt::ptr(vram_top), fmt::ptr(vram_bottom));

  m_vram_top = vram_top;
  m_vram_bottom = vram_bottom;

  // this is dumb don't do this
  // if (reinterpret_cast<int>(m_vram_bottom) < 0)
  // {
  //  m_vram_bottom = reinterpret_cast<void*>(0x3FE0);
  // }

  if (m_vram_blocks == nullptr)
  {
    return;
  }

  for (int i = 0; i < m_n_blocks; ++i)
  {
    m_vram_blocks[i].Initialize();
  }
  m_unk_field_14.Initialize();

  for (int i = 0; i < m_n_textures; ++i)
  {
    new (&m_textures[i]) mgCTexture();
  }

  for (int i = 0; i < m_n_blocks; ++i)
  {
    // 12CBA0
    todo;
  }

  m_unk_field_8 = -1;
  m_texture_name_suffix[0] = '\0';

  for (int i = 0; i < m_hash_list.size(); ++i)
  {
    m_hash_list[i] = nullptr;
  }

  for (int i = 0; i < m_n_hashes_capacity; ++i)
  {
    m_p_hashes[i] = &m_hashes[i];
  }

  m_n_hashes_length = 0;
}

// 0012CC70
u8 mgCTextureManager::hash(const char* str) const
{
  log_trace("mgCTextureManager::hash({})", str);

  int hash = 0;

  for (char c = *str; c != '\0'; c = *(++str))
  {
    hash &= 0xFF;
    hash <<= 8;
    hash += c;
    hash %= m_hash_list.size();
  }

  return hash & 0xFF;
}

// 0012CCC0
void mgCTextureManager::AddHash(mgCTexture* texture)
{
  log_trace("mgCTextureManager::AddHash({})", fmt::ptr(texture));

  if (m_n_hashes_length >= m_n_hashes_capacity)
  {
    return;
  }

  TextureHash* new_hash = m_p_hashes[m_n_hashes_length++];

  new_hash->m_next_hash = nullptr;
  new_hash->m_texture = texture;

  u8 hash_val = hash(texture->m_name.data());

  TextureHash* curr_hash = m_hash_list[hash_val];
  if (curr_hash == nullptr)
  {
    m_hash_list[hash_val] = new_hash;
  }
  else
  {
    for (; curr_hash->m_next_hash != nullptr; curr_hash = curr_hash->m_next_hash) {}
    curr_hash->m_next_hash = new_hash;
  }
}

// 0012CE90
mgCTexture* mgCTextureManager::SearchHash(const char* name, ssize uuid)
{
  log_trace("mgCTextureManager::SearchHash({})", name, uuid);

  u8 hash_val = hash(name);

  for (TextureHash* curr_hash = m_hash_list[hash_val]; curr_hash != nullptr; curr_hash = curr_hash->m_next_hash)
  {
    mgCTexture* texture = curr_hash->m_texture;

    if (strcmp(name, curr_hash->m_texture->m_name.data()) != 0)
    {
      continue;
    }

    if (uuid >= 0 && texture->m_hash_uuid != uuid)
    {
      continue;
    }

    return texture;
  }

  return nullptr;
}

// 0012D050
mgCTexture* mgCTextureManager::GetTexture(const char* name, ssize i)
{
  log_trace("mgCTextureManager::{}({}, {})", __func__, name, i);

  return SearchTextureName(name, i);
}

// 0012D140
void mgCTextureManager::EnterTexture(MAYBE_UNUSED usize texb, MAYBE_UNUSED const char* name,
    MAYBE_UNUSED unkptr p1, MAYBE_UNUSED s32 width,
    MAYBE_UNUSED s32 height, MAYBE_UNUSED u32 i3,
    MAYBE_UNUSED unkptr p2, MAYBE_UNUSED u64 i4, MAYBE_UNUSED sint i5)
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
void mgCTextureManager::EnterIMGFile(MAYBE_UNUSED u8* img_file_buff, MAYBE_UNUSED usize texb, MAYBE_UNUSED mgCMemory* stack, MAYBE_UNUSED mgCEnterIMGInfo* enter_info)
{
  log_trace("mgCTextureManager::{}({}, {}, {}, {})", __func__, fmt::ptr(img_file_buff), texb, fmt::ptr(stack), fmt::ptr(enter_info));

  todo;
}

// 0012E540
void mgCTextureManager::DeleteBlock(MAYBE_UNUSED usize texb)
{
  log_trace("mgCTextureManager::DeleteBlock({})", texb);

  todo;
}

// 0012E850
void mgCTextureManager::ReloadTexture(MAYBE_UNUSED usize texb, MAYBE_UNUSED sceVif1Packet* vif1_packet)
{
  log_trace("mgCTextureManager::ReloadTexture({}, {})", texb, fmt::ptr(vif1_packet));

  todo;
}

// 0012CF40
mgCTexture* mgCTextureManager::SearchTextureName(const char* name, ssize uuid)
{
  log_trace("mgCTextureManager::SearchTextureName({}, {})", name, uuid);

  if (m_texture_name_suffix[0] != '\0')
  {
    std::array<char, 0x80> buf;
    common::strings::safe_str_to_array(buf, name);
    common::strings::safe_arraycat(buf, m_texture_name_suffix);
    name = buf.data();
  }

  return SearchHash(name, uuid);
}

// 0013d8c0
void mgCTextureManager::LoadCFGFile(char* file, sint size, mgCMemory* tex_anime_stack, mgCTextureAnime* tex_anime)
{
  log_trace("mgCTextureManager::ReloadTexture({}, {}, {})", file, size, fmt::ptr(tex_anime_stack));

  CScriptInterpreter interpreter{ };

  pTexAnime = nullptr;
  group_name = nullptr;
  ta_enable = 0;
  now_texb = 0xffffffff;
  now_group = 0xffffffff;
  texBugPatch = 0;

  pLoadTexAnime = tex_anime;
  TexManager = this;
  TexAnimeStack = tex_anime_stack;

  interpreter.SetTag(tex_tag.data());
  interpreter.SetScript(file, size);
  interpreter.Run();
}
