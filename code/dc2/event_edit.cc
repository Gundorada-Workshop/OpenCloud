#include "common/debug.h"
#include "common/log.h"

#include "dc2/event_edit.h"
#include "dc2/event_func.h"

set_log_channel("event_edit");

// 01ECE430
EDIT_EVENT_INFO EdEventInfo{};

// 01F04200
CCameraPas g_cmr_pas{ };
// 01F04B50
CCharaPas g_chara_pas{ };
// 01F05000
unk g_info{ };

// 002EF9B0
void CEditEvent::Reset()
{
  log_trace("CEditEvent::Reset()");

  m_unk_field_4 = 0;
  m_unk_field_C = 0;
  m_unk_field_0 = 0;
  m_unk_field_10 = -1;
  m_unk_field_148 = -1;
  m_unk_field_128 = 0;

  memset(&m_unk_field_20, 0, sizeof(m_unk_field_20));
}

// 002EF9E0
bool CEditEvent::StartEvent(CSceneEventData* event_data)
{
  log_trace("CEditEvent::{}({})", __func__, fmt::ptr(event_data));

  todo;
  return false;
}