#include "common/log.h"
#include "sinit.h"
#include "dng_main.h"
#include "dngmenu.h"
#include "editctrl.h"
#include "editloop.h"
#include "editmenu.h"
#include "event.h"
#include "event_edit.h"
#include "event_func.h"
#include "gamedata.h"
#include "inventmn.h"
#include "mainloop.h"
#include "menuaqua.h"
#include "menucls1.h"
#include "menudraw.h"
#include "menumain.h"
#include "menusys.h"
#include "mg_frame.h"
#include "mg_lib.h"
#include "mg_tanime.h"
#include "snd_mngr.h"
#include "sysmes.h"
#include "userdata.h"

set_log_channel("sinit");

namespace StaticInitializers
{
	void Init()
	{
		log_info("Starting static initialization.");

		dng_main::SInit();
		dngmenu::SInit();
		editctrl::SInit();
		editloop::SInit();
		editmenu::SInit();
		event::SInit();
		event_func::SInit();
		gamedata::SInit();
		inventmn::SInit();
		MainLoop_SInit::SInit();
		menuaqua::SInit();
		menucls1::SInit();
		menudraw::SInit();
		menumain::SInit();
		menusys::SInit();
		mg_frame::SInit();
		mg_lib::SInit();
		mg_tanime::SInit();
		snd_mngr::SInit();
		sysmes::SInit();
		userdata::SInit();

		log_info("Finished static initialization.");
	}
}