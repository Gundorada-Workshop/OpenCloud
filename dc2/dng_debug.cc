#include "common/log.h"
#include "dng_debug.h"
#include "font.h"

set_log_channel("dng_debug");

// 01E9F140
static CFont dbFont;

namespace dng_debug
{
  // 00373C90
  void SInit()
  {
    log_trace("SInit()");

    dbFont.Initialize();
  }
}