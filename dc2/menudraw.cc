#include "common/log.h"
#include "menudraw.h"
#include "mg_lib.h"

set_log_channel("menudraw");

// 01ECCDD0
static mgRect<int> GiftBoxWindowPutPos;
// 01ECCE50
static mgRect<int> menu_long_hand;
// 01ECCE60
static mgRect<int> MenuMainFrame_PutRect;
// 01ECCE70
static mgRect<int> MenuMainIMG_PutRect;
// 01ECCEC0
static mgRect<int> star_light;
// 01ECCED0
static mgRect<int> MenuItemBrdKomaRect;
// 01ECCEE0
static mgRect<int> ItemBoardScrlBar1;
// 01ECCEF0
static mgRect<int> ItemBoardScrlBar2;
// 01ECCF00
static mgRect<int> ItemBoardScrlBar3;
// 01ECCF10
static mgRect<int> ItemBoardCursor;

namespace menudraw
{
  // 00374310
  void SInit()
  {
    log_trace("SInit()");

    GiftBoxWindowPutPos.Set(0, 0, 0, 0);
    menu_long_hand.Set(62, 1, 40, 24);
    MenuMainFrame_PutRect.Set(0, 0, 0, 0);
    MenuMainIMG_PutRect.Set(0, 0, 0, 0);
    star_light.Set(0, 32, 8, 8);
    MenuItemBrdKomaRect.Set(32, 32, 40, 50);
    ItemBoardScrlBar1.Set(96, 128, 22, 11);
    ItemBoardScrlBar2.Set(96, 138, 22, 4);
    ItemBoardScrlBar3.Set(96, 140, 22, 12);
    ItemBoardCursor.Set(118, 128, 8, 30);
  }
}