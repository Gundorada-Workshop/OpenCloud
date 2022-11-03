#include "common/log.h"
#include "snd_mngr.h"

set_log_channel("snd_mngr")

// 0018C550
void CLoopSeMngr::Initialize()
{
  log_trace("CLoopSeMngr::Initialize()");

  m_n_unk_field_4 = 0;
  m_unk_field_4 = nullptr;
}