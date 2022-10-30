#pragma once
#include "mgCMemory.h"

namespace PBuggy
{
	struct STRU_1F5F9A0
	{
		s32 field_0;
		u32 field_4;
		bool field_8;
		float field_C;
		float field_10;
	};

	void SInit();

	static mgCMemory stru_1F5F950;

	static STRU_1F5F9A0 stru_1F5F9A0;
}