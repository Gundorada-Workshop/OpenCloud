#pragma once
#include <array>
#include "common/debug.h"
#include "common/types.h"
#include "mg_memory.h"
#include "mg_tanime.h"
#include "sce_temp.h"

// ~ 0012C480 - 0012F1C0

// TODO
class mgCEnterIMGInfo {};

// Forward declare
class mgCTexture;

struct TextureHash
{
  mgCTexture* m_texture;
  TextureHash* m_next_hash;
};

class mgCTextureBlock
{
public:
  // 0012C6D0
  mgCTextureBlock();
  // 0012C700
  void Initialize();
  // 0012C720
  void Add(mgCTexture* texture);
  // 0012C780
  void Delete(mgCTexture* texture);

  // 0
  void* m_vram_offset;
  // 4
  mgCTextureBlock* m_unk_field_4;
  // 8
  mgCTexture* m_unk_field_8;
  // C
  mgCTextureAnime* m_texture_anime;
};

class mgCTextureManager
{
private:
  // 0012CC70
  u8 hash(const char* str) const;
  // 0012CCC0
  void AddHash(mgCTexture* texture);
  // 0012CE90
  mgCTexture* SearchHash(const char* name, int uuid);
public:
  // 0012C830
  void SetTableBuffer(int n_textures, int n_blocks, mgCMemory* stack);
  // 0012CAD0
  void Initialize(void* vram_top, void* vram_bottom);
  // 0012D050
  mgCTexture* GetTexture(const char* name, ssize i);
  // 0012D140
  void EnterTexture(usize texb, const char* name, _UNKNOWNPOINTER p1, s32 width, s32 height, u32 i3, _UNKNOWNPOINTER p2, u64 i4, int i5);
  // 0012DA90
  void EnterIMGFile(u8* img_file_buff, usize texb, mgCMemory* stack, mgCEnterIMGInfo* enter_info);
  // 0012E540
  void DeleteBlock(usize texb);
  // 0012E850
  void ReloadTexture(usize texb, sceVif1Packet* vif1_packet);
  // 0013D8C0
  void LoadCFGFile(const char* file, int size, mgCMemory* text_anime_stack, mgCTextureAnime* tex_anime);

  // 0
  void* m_vram_top;
  // 4
  void* m_vram_bottom;
  // 8
  _UNKNOWN m_unk_field_8;
  // C
  usize m_n_blocks{};
  // 10
  mgCTextureBlock* m_vram_blocks{};
  // 14
  mgCTextureBlock m_unk_field_14{};
  // 24
  std::array<TextureHash*, 101> m_hash_list;
  // 1B8
  mgCTexture* m_textures;
  // 1BC
  mgCTexture** m_p_textures;
  // 1C0
  usize m_n_textures{};
  // 1C4
  _DWORD m_unk_field_1C4;
  // 1C8
  TextureHash* m_hashes;
  // 1CC
  TextureHash** m_p_hashes;
  // 1D0
  usize m_n_hashes_capacity{};
  // 1D4
  usize m_n_hashes_length;
  // 1D8
  std::array<char, 0x18> m_unk_field_1D8;
};

class mgCTexture
{
public:
  // 0012C480
  mgCTexture();
  // 0012C4B0
  void Initialize();

  // 0
  s16 m_hash_uuid;
  // 2
  s16 m_unk_field_2;
  // 4
  s16 m_unk_field_4;
  // 6
  s16 m_unk_field_6;
  // 8
  std::array<char, 0x20> m_name;
  // 28
  _DWORD m_unk_field_28;
  // 2C
  _DWORD m_unk_field_2C;
  // 30
  _DWORD m_unk_field_30;
  // ??
  // 38
  _DWORD m_unk_field_38;
  // 3C
  u8 m_unk_field_3C;
  // 40
  s64 m_unk_field_40;
  // 48
  s64 m_unk_field_48;
  // 50
  std::array<float, 4> m_unk_field_50;
  // 60
  _DWORD m_unk_field_60;
  // 64
  _DWORD m_unk_field_64;
  // 68
  mgCTexture* m_next;
};
