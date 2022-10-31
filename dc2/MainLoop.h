#pragma once
#include <mgCMemory.h>

namespace MainLoop_SInit
{
	void SInit();
}

// 001908F0
mgCMemory* GetMainStack(void);

// 00190CB0
void MainLoop();
