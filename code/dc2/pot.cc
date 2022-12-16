#include <glm/glm.hpp>

#include "common/log.h"

#include "dc2/pot.h"

set_log_channel("pot");

// 002CC230
CFragment::CFragment()
{
  log_trace("CFragment::CFragment()");

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;
  m_unk_field_10 = vec4(0, 0, 0, 1);
  m_unk_field_20 = vec4(0, 0, 0, 1);
  m_unk_field_30 = vec4(0, 0, 0, 1);
  m_unk_field_40 = vec4(0, 0, 0, 1);
  m_unk_field_50 = 0;
};

// 002CC7A0
CBPot::CBPot()
{
  log_trace("CBPot::CBPot()");

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;
  m_unk_field_8 = 0;
  m_unk_field_C = 0;
  m_unk_field_10 = 0;
  m_unk_field_20 = vec4(0, 0, 0, 1);

  for (CFragment& fragment : m_fragments)
  {
    new (&fragment) CFragment();
  }

  m_unk_field_C40 = 0;
}

// 002CD050
CPot::CPot(bool b)
{
  log_trace("CPot::CPot({})", b);

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;
  m_position = vec3(0, 0, 0);
  if (b) m_unk_field_20 = vec4(0, 0, 0, 1);
  m_unk_field_30 = vec4(0, 0, 0, 1);
  m_unk_field_40 = vec4(0, 0, 0, 1);
  m_unk_field_50 = vec4(0, 0, 0, 1);
  if (b) m_unk_field_60 = vec4(0, 0, 0, 1);
  m_unk_field_70 = 0;
}

CPot::CPot() : CPot(false) {}