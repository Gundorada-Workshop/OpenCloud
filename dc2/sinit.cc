#include "common/log.h"
#include "sinit.h"
#include "mainloop.h"

set_log_channel("sinit");

namespace StaticInitializers
{
	void Init()
	{
		log_info("Starting static initialization.");

		MainLoop_SInit::SInit();

		log_info("Finished static initialization.");
	}
}