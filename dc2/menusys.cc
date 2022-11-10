#include "common/log.h"
#include "menumain.h"
#include "menusys.h"
#include "mg_lib.h"

set_log_channel("menusys");

// 00377AA8
static s32 MenuItemUseTarget;
// 01ECD820
static MENU_ASKMODE_PARA MenuAskParam;
// 01ECD8C0
static CMENU_USERPARAM MenuUserParam;
// 01ECD8E0
static mgCMemory MainCharaReadStack;
// 01ECDB30
static mgCMemory MenuItemMainMemory;
// 01ECDB60
static mgCMemory MenuItemBGDataMemory;
// 01ECDB90
static mgCMemory MenuItemMemory;
// 01ECDBC0
static mgCMemory MenuItemMemory2;
// 01ECDBF0
static mgCMemory MenuCharaLoadStack;
// 01ECDC70
static CGameDataUsed SpectolInfoStay;
// 01ECDCE0
static CGameDataUsed SpectolFusionBeforeAfterCheck;
// 01ECDD70
static CGameDataUsed save_spectol_fusion_param;
// 01ECDE60
static CGameDataUsed MenuMoveTempGameDataUsed;
// 01ECDF70
static CMenuItemInfo class_menu_item_info;
// 01ECE2E0
static mgCMemory MenuDebugStack;

namespace menusys
{
  // 00374490
  void SInit()
  {
    log_trace("SInit()");

    MenuAskParam.Initialize();
    MenuAskParam.m_unk_field_8C = -1;
    MenuUserParam.Initialize();
    MainCharaReadStack.Initialize();
    MenuItemMainMemory.Initialize();
    MenuItemUseTarget = -1;
    MenuItemBGDataMemory.Initialize();
    MenuItemMemory.Initialize();
    MenuItemMemory2.Initialize();
    MenuCharaLoadStack.Initialize();

    new (&SpectolInfoStay) CGameDataUsed();
    new (&SpectolFusionBeforeAfterCheck) CGameDataUsed();
    new (&save_spectol_fusion_param) CGameDataUsed();
    new (&MenuMoveTempGameDataUsed) CGameDataUsed();

    new (&class_menu_item_info) CMenuItemInfo();
  }
}