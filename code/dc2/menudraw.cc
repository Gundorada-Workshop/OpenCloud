#include "common/log.h"

#include "graph/rectangle.h"

#include "dc2/menudraw.h"
#include "dc2/mg/mg_lib.h"

set_log_channel("menudraw");

// 01ECCDD0
static graph::irect GiftBoxWindowPutPos{ graph::irect::from_extent(0, 0, 0, 0) };
// 01ECCE50
static graph::irect menu_long_hand{ graph::irect::from_extent(62, 1, 40, 24) };
// 01ECCE60
static graph::irect MenuMainFrame_PutRect{ graph::irect::from_extent(0, 0, 0, 0) };
// 01ECCE70
static graph::irect MenuMainIMG_PutRect{ graph::irect::from_extent(0, 0, 0, 0) };
// 01ECCEC0
static graph::irect star_light{ graph::irect::from_extent(0, 32, 8, 8) };
// 01ECCED0
static graph::irect MenuItemBrdKomaRect{ graph::irect::from_extent(32, 32, 40, 50) };
// 01ECCEE0
static graph::irect ItemBoardScrlBar1{ graph::irect::from_extent(96, 128, 22, 11) };
// 01ECCEF0
static graph::irect ItemBoardScrlBar2{ graph::irect::from_extent(96, 138, 22, 4) };
// 01ECCF00
static graph::irect ItemBoardScrlBar3{ graph::irect::from_extent(96, 140, 22, 12) };
// 01ECCF10
static graph::irect ItemBoardCursor{ graph::irect::from_extent(118, 128, 8, 30) };
