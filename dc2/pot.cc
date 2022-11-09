#include "glm/glm.hpp"
#include "common/log.h"
#include "pot.h"

set_log_channel("pot");

// 002CC230
void CFragment::Initialize()
{
  log_trace("CFragment::Initialize()");

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;
  m_unk_field_10 = glm::vec4(0, 0, 0, 1);
  m_unk_field_20 = glm::vec4(0, 0, 0, 1);
  m_unk_field_30 = glm::vec4(0, 0, 0, 1);
  m_unk_field_40 = glm::vec4(0, 0, 0, 1);
  m_unk_field_50 = 0;
};

// 002CC7A0
void CBPot::Initialize()
{
  log_trace("CBPot::Initialize()");

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;
  m_unk_field_8 = 0;
  m_unk_field_C = 0;
  m_unk_field_10 = 0;
  m_unk_field_20 = glm::vec4(0, 0, 0, 1);

  for (CFragment& fragment : m_fragments)
  {
    fragment.Initialize();
  }

  m_unk_field_C40 = 0;
}

// 002CD050
void CPot::Initialize(bool b)
{
  log_trace("CPot::Initialize({})", b);

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;
  m_unk_field_10 = glm::vec4(0, 0, 0, 1);
  if (b) m_unk_field_20 = glm::vec4(0, 0, 0, 1);
  m_unk_field_30 = glm::vec4(0, 0, 0, 1);
  m_unk_field_40 = glm::vec4(0, 0, 0, 1);
  m_unk_field_50 = glm::vec4(0, 0, 0, 1);
  if (b) m_unk_field_60 = glm::vec4(0, 0, 0, 1);
  m_unk_field_70 = 0;
}