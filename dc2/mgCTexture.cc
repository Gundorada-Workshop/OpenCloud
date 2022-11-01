#include "common/log.h"
#include "mgCTexture.h"

set_log_channel("mgCTexture");

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