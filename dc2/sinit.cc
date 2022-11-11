#include "common/log.h"
#include "sinit.h"
#include "dng_main.h"
#include "event.h"
#include "event_func.h"
#include "gamedata.h"
#include "mainloop.h"
#include "menucls1.h"
#include "menudraw.h"

set_log_channel("sinit");

namespace StaticInitializers
{
	void Init()
	{
		log_info("Starting static initialization.");

		dng_main::SInit();
		event::SInit();
		event_func::SInit();
		gamedata::SInit();
		MainLoop_SInit::SInit();
		menucls1::SInit();
		menudraw::SInit();

		log_info("Finished static initialization.");
	}
}