#include "common/log.h"

#include "dc2/menumain.h"
#include "dc2/menusys.h"
#include "dc2/mg_lib.h"

set_log_channel("menusys");

// 00377AA8
static s32 MenuItemUseTarget{ -1 };
// 01ECD820
static MENU_ASKMODE_PARA MenuAskParam{};
// 01ECD8C0
static CMENU_USERPARAM MenuUserParam{};
// 01ECD8E0
static mgCMemory MainCharaReadStack{};
// 01ECDB30
static mgCMemory MenuItemMainMemory{};
// 01ECDB60
static mgCMemory MenuItemBGDataMemory{};
// 01ECDB90
static mgCMemory MenuItemMemory{};
// 01ECDBC0
static mgCMemory MenuItemMemory2{};
// 01ECDBF0
static mgCMemory MenuCharaLoadStack{};
// 01ECDC70
static CGameDataUsed SpectolInfoStay{};
// 01ECDCE0
static CGameDataUsed SpectolFusionBeforeAfterCheck{};
// 01ECDD70
static CGameDataUsed save_spectol_fusion_param{};
// 01ECDE60
static CGameDataUsed MenuMoveTempGameDataUsed{};
// 01ECDF70
static CMenuItemInfo class_menu_item_info{};
// 01ECE2E0
static mgCMemory MenuDebugStack{};
