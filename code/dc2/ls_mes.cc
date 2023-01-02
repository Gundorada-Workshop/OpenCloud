#include "common/log.h"

#include "dc2/ls_mes.h"

set_log_channel("ls_mes");

// 00152A60
void ClsMes::SetHalfFontWPercent(float percent)
{
  log_trace("ClsMes::SetHalfFontWPercent({})", percent);

  if (percent < 0.0f)
  {
    m_half_font_width_percent = 0.55f;
  }
  else
  {
    m_half_font_width_percent = percent;
  }
}

// 00152A90
ClsMes::ClsMes()
{
  log_trace("ClsMes::ClsMes()");

  m_unk_field_B4 = 0;
  m_unk_field_B8 = 100;
  m_unk_field_BC = 50;
  m_unk_field_C0 = 15;
  m_unk_field_C4 = 24;

  SetHalfFontWPercent(-1.0f);

  SetDrawSize(16, 20);

  m_unk_field_CC = 70;
  m_unk_field_D0 = 5;
  m_unk_field_D4 = 0;
  m_unk_field_D8 = 0;
  m_unk_field_DC = 0;
  m_unk_field_E0 = 0;
  m_unk_field_E4 = 0;

  memset(&m_unk_field_E8, 0, sizeof(m_unk_field_E8));

  m_unk_field_128 = 0;
  m_unk_field_12C = 0;

  m_unk_field_134 = -1;
  m_unk_field_138 = -1;
  m_unk_field_13C = m_unk_field_B8;
  m_unk_field_140 = m_unk_field_BC;
  m_unk_field_144 = m_unk_field_C0 * m_unk_field_CC;
  m_unk_field_148 = m_unk_field_C4 * m_unk_field_D0;

  m_unk_field_14C = 0;
  m_unk_field_150 = 1;
  m_unk_field_15C = 300;
  m_unk_field_160 = 200;
  m_unk_field_154 = 320;
  m_unk_field_158 = 200;
  m_unk_field_164 = 8;
  m_unk_field_168 = 49;
  m_unk_field_130 = 1;
  m_unk_field_190 = -1;
  m_unk_field_194 = -1;
  m_unk_field_198 = 0;
  m_unk_field_19C = 0;
  m_unk_field_1A0 = -1;
  m_unk_field_1A4 = -1;
  m_unk_field_1A8 = 0;
  m_unk_field_1AC = 0;
  
  m_unk_field_1B0 = 39;
  m_unk_field_1B1 = 0x20;
  m_unk_field_1B2 = 0x20;
  m_unk_field_1B3 = 0x80;
  m_unk_field_1B8 = 0.6f;
  m_unk_field_1BC = 0.6f;
  m_unk_field_1C0 = 0;
  m_unk_field_1C4 = 0;
  m_unk_field_1C8 = 0;
  m_unk_field_184 = 0.1f;
  m_unk_field_188 = 0;
  m_unk_field_18C = 1;
  m_unk_field_1CC = 0;
  m_unk_field_1D0 = 0;
  m_unk_field_1D4 = 0;
  m_unk_field_1D8 = 0;
  m_unk_field_1DC = 0;

  //SetDefColor(glm::u8vec4(0x20, 0x20, 0x20, 0x80));

  m_unk_field_17D8 = 0;
  m_unk_field_17DC = 0;
  m_unk_field_17E0 = 30;
  m_unk_field_17E4 = -1;
  m_unk_field_17E8 = 0;
  m_unk_field_17EC = 0;
  m_unk_field_17F0 = 0;
  m_unk_field_B0 = 2;
  m_unk_field_17F4 = 1;
  m_unk_field_17F8 = 0;
  m_unk_field_17FC = 0;

  memset(&m_unk_field_1800, 0, sizeof(m_unk_field_1800));
  m_unk_field_1800[0] = 0x80;

  for (auto& i : m_unk_field_1A04)
  {
    i = -1;
  }

  for (auto& i : m_unk_field_1A44)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_1A84)
  {
    i = 0;
  }

  m_unk_field_1AC4 = 0;
  m_unk_field_1AC8 = 0;
  m_unk_field_1ACC = 1;
  m_unk_field_1AD0 = 0;
  m_unk_field_1AD4 = 0;
  m_unk_field_1AD8 = 0;
  m_unk_field_1ADC = -1;
  m_unk_field_1AE0 = -1;
  m_unk_field_1AE4 = -1;
  m_unk_field_1AE8 = 0;
  m_unk_field_1AEC = 0;
  m_unk_field_1AF0 = 0;
  m_unk_field_1AF4 = 0;
  m_unk_field_1AF8 = 0;
  m_unk_field_1AFC = 0;
  m_unk_field_1B00 = 0;
  m_unk_field_1B04 = -1;
  m_unk_field_1B08 = -1;
  m_unk_field_1B0C = -1;
  m_unk_field_1B10 = -1;
  m_unk_field_1B14 = 0;
  m_unk_field_1B18 = 0;
  m_unk_field_1B1C = 0;
  m_unk_field_1B20 = 0;
  m_unk_field_1B24 = 0;
  m_unk_field_1B28 = 0;
  m_unk_field_1B2C = 0;
  m_unk_field_1B30 = 0;
  m_unk_field_1B34 = 0;
  m_unk_field_1B38 = 0;
  m_unk_field_1B3C = 0;
  m_unk_field_1B40 = 0;

  for (auto& i : m_unk_field_1B44)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_1B94)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_1C34)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_1C84)
  {
    i = -1;
  }

  for (auto& i : m_unk_field_1CD4)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_1D24)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_1D74)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_1DC4)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_1E14)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_1E64)
  {
    i = -1;
  }

  for (auto& i : m_unk_field_1EB4)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_1F04)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_1F54)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_1FA4)
  {
    i = -1;
  }

  for (auto& i : m_unk_field_1FF4)
  {
    i = -1;
  }

  for (auto& i : m_unk_field_2044)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_2094)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_20E4)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_2134)
  {
    i = 0;
  }

  for (auto& i : m_unk_field_2184)
  {
    i = 0;
  }

  m_unk_field_21D4 = 0;
  m_unk_field_21D8 = 0;
}

// 00152EC0
//void ClsMes::SetDefColor(glm::u8vec4 default_rgba)
//{
//  log_trace("ClsMes::SetDefColor({}, {}, {}, {})", default_rgba.r, default_rgba.g, default_rgba.b, default_rgba.a);
//
//  m_unk_field_17D0 = default_rgba;
//  m_unk_field_17D4 = m_unk_field_17D0;
//}

// 002D44A0
void ClsMes::SetDrawSize(s32 i1, s32 i2)
{
  log_trace("ClsMes::SetDrawSize({}, {})", i1, i2);

  m_unk_field_A4 = i1;
  m_unk_field_A8 = i2;
}