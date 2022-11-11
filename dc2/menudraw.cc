#include "common/log.h"
#include "menudraw.h"
#include "mg_lib.h"

set_log_channel("menudraw");

// 01ECCDD0
static mgRect<int> GiftBoxWindowPutPos{ 0, 0, 0, 0 };
// 01ECCE50
static mgRect<int> menu_long_hand{ 62, 1, 40, 24 };
// 01ECCE60
static mgRect<int> MenuMainFrame_PutRect{ 0, 0, 0, 0 };
// 01ECCE70
static mgRect<int> MenuMainIMG_PutRect{ 0, 0, 0, 0 };
// 01ECCEC0
static mgRect<int> star_light{ 0, 32, 8, 8 };
// 01ECCED0
static mgRect<int> MenuItemBrdKomaRect{ 32, 32, 40, 50 };
// 01ECCEE0
static mgRect<int> ItemBoardScrlBar1{ 96, 128, 22, 11 };
// 01ECCEF0
static mgRect<int> ItemBoardScrlBar2{ 96, 138, 22, 4 };
// 01ECCF00
static mgRect<int> ItemBoardScrlBar3{ 96, 140, 22, 12 };
// 01ECCF10
static mgRect<int> ItemBoardCursor{ 118, 128, 8, 30 };
