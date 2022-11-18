#pragma once
#include <array>

#include <glm/glm.hpp>

#include "common/debug.h"

#include "dc2/font.h"

// ~ 00151940 - 0015BBD0

class ClsMes : CFont
{
public:
  // 00152A60
  void SetHalfFontWPercent(float percent);
  // 00152A90
  ClsMes();
  // 00152EC0
  void SetDefColor(glm::u8vec4 default_rgba);
  // 002D44A0
  void SetDrawSize(s32 i1, s32 i2);

  // A4
  s32 m_unk_field_A4;
  // A8
  s32 m_unk_field_A8;
  // AC
  _UNKNOWN m_unk_field_AC;
  // B0
  s32 m_unk_field_B0;
  // B4
  _UNKNOWN m_unk_field_B4;
  // B8
  s32 m_unk_field_B8;
  // BC
  s32 m_unk_field_BC;
  // C0
  s32 m_unk_field_C0;
  // C4
  s32 m_unk_field_C4;
  // C8
  float m_half_font_width_percent;
  // CC
  s32 m_unk_field_CC;
  // D0
  s32 m_unk_field_D0;
  // D4
  _UNKNOWN m_unk_field_D4;
  // D8
  _UNKNOWN m_unk_field_D8;
  // DC
  _UNKNOWN m_unk_field_DC;
  // E0
  _UNKNOWN m_unk_field_E0;
  // E4
  _UNKNOWN m_unk_field_E4;
  // E8
  std::array<_UNKNOWN, 0x10> m_unk_field_E8;
  // 128
  _UNKNOWN m_unk_field_128;
  // 12C
  _UNKNOWN m_unk_field_12C;
  // 130
  _UNKNOWN m_unk_field_130;
  // 134
  s32 m_unk_field_134;
  // 138
  s32 m_unk_field_138;
  // 13C
  s32 m_unk_field_13C;
  // 140
  _UNKNOWN m_unk_field_140;
  // 144
  _UNKNOWN m_unk_field_144;
  // 148
  _UNKNOWN m_unk_field_148;
  // 14C
  _UNKNOWN m_unk_field_14C;
  // 150
  _UNKNOWN m_unk_field_150;
  // 154
  s32 m_unk_field_154;
  // 158
  s32 m_unk_field_158;
  // 15C
  s32 m_unk_field_15C;
  // 160
  s32 m_unk_field_160;
  // 164
  s32 m_unk_field_164;
  // 168
  s32 m_unk_field_168;

  // ?

  // 184
  float m_unk_field_184;
  // 188
  _UNKNOWN m_unk_field_188;
  // 18C
  _UNKNOWN m_unk_field_18C;
  // 190
  s32 m_unk_field_190;
  // 194
  s32 m_unk_field_194;
  // 198
  _UNKNOWN m_unk_field_198;
  // 19C
  _UNKNOWN m_unk_field_19C;
  // 1A0
  s32 m_unk_field_1A0;
  // 1A4
  s32 m_unk_field_1A4;
  // 1A8
  _UNKNOWN m_unk_field_1A8;
  // 1AC
  _UNKNOWN m_unk_field_1AC;
  // 1B0
  u8 m_unk_field_1B0;
  // 1B1
  u8 m_unk_field_1B1;
  // 1B2
  u8 m_unk_field_1B2;
  // 1B3
  u8 m_unk_field_1B3;
  // 1B4
  _UNKNOWN m_unk_field_1B4;
  // 1B8
  float m_unk_field_1B8;
  // 1BC
  float m_unk_field_1BC;
  // 1C0
  _UNKNOWN m_unk_field_1C0;
  // 1C4
  _UNKNOWN m_unk_field_1C4;
  // 1C8
  _UNKNOWN m_unk_field_1C8;
  // 1CC
  _UNKNOWN m_unk_field_1CC;
  // 1D0
  _UNKNOWN m_unk_field_1D0;
  // 1D4
  _UNKNOWN m_unk_field_1D4;
  // 1D8
  _UNKNOWN m_unk_field_1D8;
  // 1DC
  _UNKNOWN m_unk_field_1DC;
  // 1E0
  _UNKNOWN m_unk_field_1E0;
  // 1E4
  _UNKNOWN m_unk_field_1E4;
  // 1E8
  _UNKNOWN m_unk_field_1E8;
  // 1EC
  _UNKNOWN m_unk_field_1EC;
  // 1F0
  _UNKNOWN m_unk_field_1F0;
  // 1F4
  _UNKNOWN m_unk_field_1F4;
  // 1F8
  _UNKNOWN m_unk_field_1F8;
  // 1FC
  _UNKNOWN m_unk_field_1FC;
  // 200
  _UNKNOWN m_unk_field_200;
  // 204
  _UNKNOWN m_unk_field_204;
  // 208
  _UNKNOWN m_unk_field_208;
  // 20C
  _UNKNOWN m_unk_field_20C;
  // 210
  _UNKNOWN m_unk_field_210;
  // 214
  _UNKNOWN m_unk_field_214;
  // 218
  _UNKNOWN m_unk_field_218;
  // 21C
  _UNKNOWN m_unk_field_21C;
  // 220
  _UNKNOWN m_unk_field_220;
  // 224
  _UNKNOWN m_unk_field_224;
  // 228
  _UNKNOWN m_unk_field_228;
  // 22C
  _UNKNOWN m_unk_field_22C;
  // 230
  _UNKNOWN m_unk_field_230;
  // 234
  _UNKNOWN m_unk_field_234;
  // 238
  _UNKNOWN m_unk_field_238;
  // 23C
  _UNKNOWN m_unk_field_23C;
  // 240
  _UNKNOWN m_unk_field_240;
  // 244
  _UNKNOWN m_unk_field_244;
  // 248
  _UNKNOWN m_unk_field_248;
  // 24C
  _UNKNOWN m_unk_field_24C;
  // 250
  _UNKNOWN m_unk_field_250;
  // 254
  _UNKNOWN m_unk_field_254;
  // 258
  _UNKNOWN m_unk_field_258;
  // 25C
  u8 m_unk_field_25C;

  // ?

  // 17C0
  _UNKNOWN m_unk_field_17C0;
  // 17C4
  _UNKNOWN m_unk_field_17C4;
  // 17C8
  _UNKNOWN m_unk_field_17C8;
  // 17CC
  _UNKNOWN m_unk_field_17CC;
  // 17D0
  glm::u8vec4 m_unk_field_17D0;
  // 17D4
  glm::u8vec4 m_unk_field_17D4;
  // 17D8
  _UNKNOWN m_unk_field_17D8;
  // 17DC
  _UNKNOWN m_unk_field_17DC;
  // 17E0
  s32 m_unk_field_17E0;
  // 17E4
  s32 m_unk_field_17E4;
  // 17E8
  _UNKNOWN m_unk_field_17E8;
  // 17EC
  _UNKNOWN m_unk_field_17EC;
  // 17F0
  _UNKNOWN m_unk_field_17F0;
  // 17F4
  _UNKNOWN m_unk_field_17F4;
  // 17F8
  _UNKNOWN m_unk_field_17F8;
  // 17FC
  _UNKNOWN m_unk_field_17FC;
  // 1800
  std::array<u8, 0x201> m_unk_field_1800;
  // 1A04
  std::array<s32, 0x10> m_unk_field_1A04;
  // 1A44
  std::array<_UNKNOWN, 0x10> m_unk_field_1A44;
  // 1A84
  std::array<_UNKNOWN, 0x10> m_unk_field_1A84;
  // 1AC4
  _UNKNOWN m_unk_field_1AC4;
  // 1AC8
  _UNKNOWN m_unk_field_1AC8;
  // 1ACC
  _UNKNOWN m_unk_field_1ACC;
  // 1AD0
  _UNKNOWN m_unk_field_1AD0;
  // 1AD4
  _UNKNOWN m_unk_field_1AD4;
  // 1AD8
  _UNKNOWN m_unk_field_1AD8;
  // 1ADC
  s32 m_unk_field_1ADC;
  // 1AE0
  s32 m_unk_field_1AE0;
  // 1AE4
  s32 m_unk_field_1AE4;
  // 1AE8
  _UNKNOWN m_unk_field_1AE8;
  // 1AEC
  _UNKNOWN m_unk_field_1AEC;
  // 1AF0
  _UNKNOWN m_unk_field_1AF0;
  // 1AF4
  _UNKNOWN m_unk_field_1AF4;
  // 1AF8
  _UNKNOWN m_unk_field_1AF8;
  // 1AFC
  _UNKNOWN m_unk_field_1AFC;
  // 1B00
  _UNKNOWN m_unk_field_1B00;
  // 1B04
  s32 m_unk_field_1B04;
  // 1B08
  s32 m_unk_field_1B08;
  // 1B0C
  s32 m_unk_field_1B0C;
  // 1B10
  s32 m_unk_field_1B10;
  // 1B14
  _UNKNOWN m_unk_field_1B14;
  // 1B18
  _UNKNOWN m_unk_field_1B18;
  // 1B1C
  _UNKNOWN m_unk_field_1B1C;
  // 1B20
  _UNKNOWN m_unk_field_1B20;
  // 1B24
  _UNKNOWN m_unk_field_1B24;
  // 1B28
  _UNKNOWN m_unk_field_1B28;
  // 1B2C
  _UNKNOWN m_unk_field_1B2C;
  // 1B30
  _UNKNOWN m_unk_field_1B30;
  // 1B34
  _UNKNOWN m_unk_field_1B34;
  // 1B38
  _UNKNOWN m_unk_field_1B38;
  // 1B3C
  _UNKNOWN m_unk_field_1B3C;
  // 1B40
  _UNKNOWN m_unk_field_1B40;
  // 1B44
  std::array<_UNKNOWN, 20> m_unk_field_1B44;
  // 1B94
  std::array<_UNKNOWN, 40> m_unk_field_1B94;
  // 1C34
  std::array<_UNKNOWN, 20> m_unk_field_1C34;
  // 1C84
  std::array<s32, 20> m_unk_field_1C84;
  // 1CD4
  std::array<_UNKNOWN, 20> m_unk_field_1CD4;
  // 1D24
  std::array<_UNKNOWN, 20> m_unk_field_1D24;
  // 1D74
  std::array<_UNKNOWN, 20> m_unk_field_1D74;
  // 1DC4
  std::array<_UNKNOWN, 20> m_unk_field_1DC4;
  // 1E14
  std::array<_UNKNOWN, 20> m_unk_field_1E14;
  // 1E64
  std::array<s32, 20> m_unk_field_1E64;
  // 1EB4
  std::array<_UNKNOWN, 20> m_unk_field_1EB4;
  // 1F04
  std::array<_UNKNOWN, 20> m_unk_field_1F04;
  // 1F54
  std::array<_UNKNOWN, 20> m_unk_field_1F54;
  // 1FA4
  std::array<s32, 20> m_unk_field_1FA4;
  // 1FF4
  std::array<s32, 20> m_unk_field_1FF4;
  // 2044
  std::array<_UNKNOWN, 20> m_unk_field_2044;
  // 2094
  std::array<_UNKNOWN, 20> m_unk_field_2094;
  // 20E4
  std::array<_UNKNOWN, 20> m_unk_field_20E4;
  // 2134
  std::array<_UNKNOWN, 20> m_unk_field_2134;
  // 2184
  std::array<_UNKNOWN, 20> m_unk_field_2184;
  // 21D4
  _UNKNOWN m_unk_field_21D4;
  // 21D8
  _UNKNOWN m_unk_field_21D8;
};