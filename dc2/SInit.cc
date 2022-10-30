#include "SInit.h"
#include "FishingObj.h"
#include "PBuggy.h"
#include "Title.h"

namespace StaticInitializers
{
	void Init()
	{
		FishingObj::SInit();
		PBuggy::SInit();
		Title::SInit();
	}
}