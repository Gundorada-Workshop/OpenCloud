#pragma once
#include "PBuggy.h"

namespace PBuggy
{
	void SInit()
	{
		stru_1F5F950.Initialize();

		stru_1F5F9A0.field_0 = 0;
		stru_1F5F9A0.field_8 = false;
		stru_1F5F9A0.field_C = 1.0f;
		stru_1F5F9A0.field_10 = 1.0f;
	}
}