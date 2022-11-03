#include "sinit.h"
#include "fishingobj.h"
#include "mainloop.h"
#include "mg_frame.h"
#include "mg_tanime.h"
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
		mg_tanime::SInit();
		PBuggy::SInit();
		Photo::SInit();
		Title::SInit();
	}
}