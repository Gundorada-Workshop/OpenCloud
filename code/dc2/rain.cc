#include "common/log.h"

#include "dc2/rain.h"

set_log_channel("rain");

// 00282100
CRainDrop::CRainDrop()
{
  log_trace("CRainDrop::CRainDrop()");

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;

  for (auto& v : m_unk_field_10)
  {
    v = vec4(0, 0, 0, 1);
  }

  m_unk_field_90 = vec4(0, 0, 0, 1);
  m_color = glm::u8vec4(128, 128, 128, 128);
}

// 00282180
void CRain::SetCharNo(sint char_no)
{
  log_trace("CRain::{}({})", __func__, char_no);

  m_char_no = char_no;

  if (char_no == -1)
  {
    return;
  }

  for (CParticle particle : m_particles)
  {
    new (&particle) CParticle;
  }
}

// 002822D0
void CRain::Stop()
{
  log_trace("CRain::{}()", __func__);

  m_unk_field_0 = false;
}

// 002822E0
void CRain::Start()
{
  log_trace("CRain::{}()", __func__);

  todo;
}
