#include "sinit.h"
#include "fishingobj.h"
#include "mainloop.h"
#include "mg_frame.h"
#include "mg_lib.h"
#include "mg_tanime.h"
#include "snd_mngr.h"
#include "pbuggy.h"
#include "photo.h"
#include "title.h"

namespace StaticInitializers
{
	void Init()
	{
		FishingObj::SInit();
		MainLoop_SInit::SInit();
		mg_frame::SInit();
		mg_lib::SInit();
		mg_tanime::SInit();
		snd_mngr::SInit();
		PBuggy::SInit();
		Photo::SInit();
		Title::SInit();
	}
}