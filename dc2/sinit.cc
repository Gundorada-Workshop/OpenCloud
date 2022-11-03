#include "sinit.h"
#include "fishingobj.h"
#include "mainloop.h"
#include "pbuggy.h"
#include "photo.h"
#include "title.h"

namespace StaticInitializers
{
	void Init()
	{
		FishingObj::SInit();
		MainLoop_SInit::SInit();
		PBuggy::SInit();
		Photo::SInit();
		Title::SInit();
	}
}