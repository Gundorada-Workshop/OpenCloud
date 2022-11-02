#include "common/log.h"
#include "Snd_Mngr.h"

set_log_channel("Snd_Mngr")

// 0018C550
void CLoopSeMngr::Initialize()
{
  log_trace("CLoopSeMngr::Initialize()");

  m_n_unk_field_4 = 0;
  m_unk_field_4 = nullptr;
}