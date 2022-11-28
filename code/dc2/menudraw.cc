#include "common/log.h"
#include "common/rectangle.h"

#include "dc2/menudraw.h"
#include "dc2/mg_lib.h"

set_log_channel("menudraw");

// 01ECCDD0
static irect GiftBoxWindowPutPos{ irect::from_extent(0, 0, 0, 0) };
// 01ECCE50
static irect menu_long_hand{ irect::from_extent(62, 1, 40, 24) };
// 01ECCE60
static irect MenuMainFrame_PutRect{ irect::from_extent(0, 0, 0, 0) };
// 01ECCE70
static irect MenuMainIMG_PutRect{ irect::from_extent(0, 0, 0, 0) };
// 01ECCEC0
static irect star_light{ irect::from_extent(0, 32, 8, 8) };
// 01ECCED0
static irect MenuItemBrdKomaRect{ irect::from_extent(32, 32, 40, 50) };
// 01ECCEE0
static irect ItemBoardScrlBar1{ irect::from_extent(96, 128, 22, 11) };
// 01ECCEF0
static irect ItemBoardScrlBar2{ irect::from_extent(96, 138, 22, 4) };
// 01ECCF00
static irect ItemBoardScrlBar3{ irect::from_extent(96, 140, 22, 12) };
// 01ECCF10
static irect ItemBoardCursor{ irect::from_extent(118, 128, 8, 30) };
