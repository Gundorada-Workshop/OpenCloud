#include "SInit.h"
#include "FishingObj.h"
#include "PBuggy.h"
#include "Photo.h"
#include "Title.h"

namespace StaticInitializers
{
	void Init()
	{
		FishingObj::SInit();
		PBuggy::SInit();
		Photo::SInit();
		Title::SInit();
	}
}