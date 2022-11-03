#pragma once
#include <array>
#include "mg_memory.h"

// ~ 0029F050 - 002A4D90

namespace Title
{
	void SInit();

	static mgCMemory stru_1F06070;
	static mgCMemory stru_1F060A0;
	static mgCMemory stru_1F060D0;
	static mgCMemory stru_1F06100;
	static mgCMemory stru_1F06130;
	static std::array<mgCMemory, 5> stru_1F06160;

	static bool dword_1F062D0;
	static bool dword_1F062D8;
	static bool dword_1F062DC;
}