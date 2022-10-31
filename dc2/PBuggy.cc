#pragma once
#include <assert.h>
#include "PBuggy.h"
#include "mgLib.h"
#include "CCharacter2.h"
#include "CEffect.h"
#include "mgCMemory.h"

// 00376B34
static s32 BuggyHP = 1;

// 00378774
static CCharacter2* dword_378774;
// 00378778
static CCharacter2* dword_378778;
// 0037877C
static CCharacter2* dword_37877C;
// 00378780
static CCharacter2* dword_378780;
// 00378784
static CCharacter2* dword_378784;
// 00378788
static CCharacter2* dword_378788;
// 0037878C
static CCharacter2* dword_37878C;

// 00378790
static s32 dword_378790;

// 00378794
static s32 dword_378794;

// 00378798
static s32 dword_378798;

// 0037879C
static s32 dword_37879C;

// 003787A0
static s32 dword_3787A0;

// 003787A4
static s32 dword_3787A4;

// 003787A8
static s32 dword_3787A8;

// 003787AC
static s32 dword_3787AC;

// 003787B0
static s32 dword_3787B0;

// 003787B4
static s32 dword_3787B4;

// 003787B8
static s32 dword_3787B8;

// 003787BC
static CEffect* dword_3787BC;

// 003787C0
static s32 dword_3787C0;

// 003787C4
// FIXME: Unknown pointer type
static void* dword_3787C4;

// 003787C8
static s32 dword_3787C8;

// 003787CC
static bool dword_3787CC;

// 003787D0
static bool dword_3787D0;

// 003787D4
static s32 dword_3787D4;

// 003787D8
static bool dword_3787D8;

// 003787DC
static float flt_3787DC;

// 003787E0
static float flt_3787E0;

// 003787E4
static s32 dword_3787E4;

// 003787E8
static bool dword_3787E8;

// 003787EC
static bool dword_3787EC;

// 003787F0
static s32 dword_3787F0;

// 003787F4
static s32 dword_3787F4;

// 003787F8
static u32 dword_3787F8;

// 003787FC
static s32 dword_3787FC;

// 00378800
static bool dword_378800;

// 00378804
static s32 dword_378804;

// 00378808
static s32 dword_378808;

// 0037880C
static bool dword_37880C;

// 00378810
static s32 dword_378810;

// 01F5F950
static mgCMemory stru_1F5F950;

// 01F5F980
static vec4 stru_1F5F980;

// 01F5F990
static vec4 stru_1F5F990;

// 01F5F9A0
static STRU_1F5F9A0 stru_1F5F9A0;

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