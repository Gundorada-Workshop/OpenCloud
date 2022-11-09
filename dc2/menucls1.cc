#include "common/log.h"
#include "common/types.h"
#include "menucls1.h"

set_log_channel("menucls1");

// 00377828
static s32 MenuUsedTarget;

namespace menucls1
{
  // 00374300
  void SInit()
  {
    log_trace("SInit");
    
    MenuUsedTarget = -1;
  }
}