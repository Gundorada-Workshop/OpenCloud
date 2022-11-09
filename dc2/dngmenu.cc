#include "common/log.h"
#include "dngmenu.h"
#include "mg_lib.h"

set_log_channel("dngmenu");

// 00368640
static mgRect<int> dng_light_circle;
// 00368650
static mgRect<int> dngfreemap_num;
// 01EC8DE0
static mgRect<float> treemap_root_put;
// 01EC8DF0
static mgRect<int> Floor_Info;
// 01EC8E00
static mgCMemory MenuTreeMapStack;

namespace dngmenu
{
  // 00374170
  void SInit()
  {
    log_trace("SInit()");

    dng_light_circle.Set(388, 304, 124, 80);
    dngfreemap_num.Set(0, 0, 12, 18);
    treemap_root_put.Set(0, 0, 0, 0);
    Floor_Info.Set(0, 238, 256, 18);
    MenuTreeMapStack.Initialize();
  }
}