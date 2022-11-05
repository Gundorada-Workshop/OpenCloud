#include "sinit.h"
#include "editctrl.h"
#include "editloop.h"
#include "fishingobj.h"
#include "gamedata.h"
#include "mainloop.h"
#include "mg_frame.h"
#include "mg_lib.h"
#include "mg_tanime.h"
#include "snd_mngr.h"
#include "sysmes.h"
#include "pbuggy.h"
#include "photo.h"
#include "title.h"
#include "userdata.h"

namespace StaticInitializers
{
	void Init()
	{
		editctrl::SInit();
		editloop::SInit();
		FishingObj::SInit();
		gamedata::SInit();
		MainLoop_SInit::SInit();
		mg_frame::SInit();
		mg_lib::SInit();
		mg_tanime::SInit();
		snd_mngr::SInit();
		sysmes::SInit();
		PBuggy::SInit();
		Photo::SInit();
		Title::SInit();
		userdata::SInit();
	}
}