#pragma once
#include <array>
#include "common/debug.h"
#include "common/types.h"
#include "mg_memory.h"
#include "mg_tanime.h"

// ~ 0012C480 - 0012F1C0

class mgCTextureBlock
{
public:
  // 0012C6D0
  mgCTextureBlock();
  // 0012C700
  void Initialize();

  // 0
  _UNKNOWN m_unk_field_0;
  // 4
  _UNKNOWN m_unk_field_4;
  // 8
  _UNKNOWN m_unk_field_8;
  // C
  _UNKNOWN m_unk_field_C;
};

class mgCTextureManager
{
public:
  // 0012C7E0
  mgCTextureManager();
  // 0013D8C0
  void LoadCFGFile(const char* file, int size, mgCMemory* text_anime_stack, mgCTextureAnime* tex_anime);

  // 14
  mgCTextureBlock m_unk_field_14;
};

class mgCTexture
{
public:
  // 0012C480
  mgCTexture();
  // 0012C4B0
  void Initialize();

  // 0
  s16 m_unk_field_0;
  // 2
  s16 m_unk_field_2;
  // 4
  s16 m_unk_field_4;
  // 6
  s16 m_unk_field_6;
  // 8
  char m_unk_field_8[0x20];
  // 28
  _UNKNOWN m_unk_field_28;
  // 2C
  _UNKNOWN m_unk_field_2C;
  // 30
  _UNKNOWN m_unk_field_30;
  // ??
  // 38
  _UNKNOWN m_unk_field_38;
  // 3C
  u8 m_unk_field_3C;
  // 40
  s64 m_unk_field_40;
  // 48
  s64 m_unk_field_48;
  // 50
  std::array<float, 4> m_unk_field_50;
  // 60
  _UNKNOWN m_unk_field_60;
  // 64
  _UNKNOWN m_unk_field_64;
  // 68
  _UNKNOWN m_unk_field_68;
};
