#include "common/log.h"
#include "editmenu.h"
#include "mg_lib.h"

set_log_channel("editmenu");

// 01EC92E0
mgCMemory MenuGeoramaStack;
// 01EC95E0
mgRect<int> potti0;
// 01EC95F0
mgRect<int> potti1;

namespace editmenu
{
  // 00374200
  void SInit()
  {
    MenuGeoramaStack.Initialize();
    potti0.Set(372, 190, 16, 16);
    potti1.Set(356, 190, 16, 16);
  }
}