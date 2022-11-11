#include "common/log.h"
#include "sinit.h"
#include "dng_main.h"
#include "mainloop.h"
#include "menucls1.h"

set_log_channel("sinit");

namespace StaticInitializers
{
	void Init()
	{
		log_info("Starting static initialization.");

		dng_main::SInit();
		MainLoop_SInit::SInit();
		menucls1::SInit();

		log_info("Finished static initialization.");
	}
}