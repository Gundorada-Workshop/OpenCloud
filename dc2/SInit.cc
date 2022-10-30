#include "SInit.h"
#include "FishingObj.h"
#include "Title.h"

namespace StaticInitializers
{
	void Init()
	{
		FishingObj::SInit();
		Title::SInit();
	}
}