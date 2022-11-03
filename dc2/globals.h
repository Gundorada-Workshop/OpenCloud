#pragma once
#include "common/types.h"

namespace Language
{
	enum Language : s32
	{
		Japanese = 0,
		English = 1,
		COUNT = 2
	};
}

// 00376FC0
extern Language::Language _g_language;