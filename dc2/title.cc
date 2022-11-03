#include "title.h"

namespace Title
{
	void SInit()
	{
		stru_1F06070.Initialize();
		stru_1F060A0.Initialize();
		stru_1F060D0.Initialize();
		stru_1F06100.Initialize();
		stru_1F06130.Initialize();

		for (auto& stack : stru_1F06160)
		{
			new (&stack) mgCMemory();
		}

		dword_1F062D0 = false;
		dword_1F062D8 = false;
		dword_1F062DC = false;
	}
}