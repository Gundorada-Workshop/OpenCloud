#pragma once
#include <assert.h>
#include "PBuggy.h"
#include "mgLib.h"

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

	bool sgInitBuggy(SubGameInfo*)
	{
		// TODO
		assert(false);
		return false;
	}

	bool sgExitBuggy(SubGameInfo*)
	{
		// TODO
		assert(false);
		return false;
	}

	bool sgLoopBuggy(SubGameInfo*)
	{
		// TODO
		assert(false);
		return false;
	}

	bool sgDrawBuggy(SubGameInfo*)
	{
		// TODO
		assert(false);
		return false;
	}

	bool sgEffectDrawBuggy(SubGameInfo*)
	{
		// TODO
		assert(false);
		return false;
	}

	bool sgSystemDrawBuggy(SubGameInfo*)
	{
		// TODO
		assert(false);
		return false;
	}

	void CharaControl(SubGameInfo*, CPadControl*)
	{
		// TODO
		assert(false);
	}

	void InitBuggy(CScene*)
	{
		// TODO
		assert(false);
	}

	void BuggyDamage(s32 i1)
	{
		if (dword_3787D4 == 1)
		{
			return;
		}

		dword_3787EC = i1;
		dword_3787D4 = 2;
		dword_3787D8 = false;
		dword_3787E4 = 1;
		dword_378800 = true;
		BuggyHP -= 1;
	}

	void PlayBuggyLoopSe(CScene*)
	{
		// TODO
		assert(false);
	}

	// 00315510
	void BuggyControl(CScene*)
	{
		// TODO
		assert(false);
	}

	void InitBomb(CScene*)
	{
		// TODO
		assert(false);
	}

	bool TakeBombCheck(void)
	{
		return (dword_3787F8 ^ 3) == 0;
	}

	bool TakeBomb(void)
	{
		if (!TakeBombCheck())
		{
			return false;
		}

		dword_3787F8 = 4;
		return true;
	}

	bool ThrowBomb(vec4& dir)
	{
		// TODO
		assert(false);
		return false;
	}

	bool BombBomb(void)
	{
		if (dword_3787F8 != 6)
		{
			return false;
		}

		mgZeroVector(stru_1F5F990);

		dword_3787FC = 0;
		dword_378800 = true;
		return true;
	}

	bool NowPutBomb(void)
	{
		return (dword_3787F8 ^ 3) == 0;
	}

	void BombControl(CScene*)
	{
		// TODO
		assert(false);
	}

	void BombCheck(CScene*)
	{
		// TODO
		assert(false);
	}
}