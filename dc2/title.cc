#include "title.h"

static mgCMemory DataBuffer;
static mgCMemory TitleMapBuffer;
static mgCMemory TitleWorkBuffer;
static mgCMemory Stack_ReadBuff;
static mgCMemory Stack_MenuCharaBuff_Fix;
static std::array<mgCMemory, 5> Stack_MenuCharaBuff;

// FIXME; maybe size 0x10 struct?
static bool HDDINFO;
static bool dword_1F062D8;
static bool dword_1F062DC;

namespace Title
{
	void SInit()
	{
		DataBuffer.Initialize();
		TitleMapBuffer.Initialize();
		TitleWorkBuffer.Initialize();
		Stack_ReadBuff.Initialize();
		Stack_MenuCharaBuff_Fix.Initialize();

		for (auto& stack : Stack_MenuCharaBuff)
		{
			new (&stack) mgCMemory();
		}

		HDDINFO = false;
		dword_1F062D8 = false;
		dword_1F062DC = false;
	}
}