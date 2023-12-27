#include "common/log.h"
#include "common/macros.h" // MAYBE_UNUSED

#include "engine/event.h"
#include "engine/run_script.h"

set_log_channel("event");

// 00377CCC
CScene* EventScene{ nullptr };

MAYBE_UNUSED static CRunScript EventScript{ };

// 002554C0
void SkipEventStart()
{
  log_trace("{}()", __func__);

  todo;
}

// 00255B20
mgCCamera* GetActiveCamera()
{
  log_trace("{}()", __func__);

  if (EventScene == nullptr)
  {
    return nullptr;
  }

  return EventScene->GetCamera(EventScene->m_active_cmrid);
}

// 00255B50
CCharacter2* GetCharacter(ssize chara_id)
{
  log_trace("{}({})", __func__, chara_id);

  if (EventScene == nullptr)
  {
    return nullptr;
  }

  return EventScene->GetCharacter(chara_id);
}
