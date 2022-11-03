#pragma once
#include "common/types.h"
#include "gamepad.h"
#include "scene.h"
#include "subgame.h"

// ~ 00313770 - 003169B0

namespace PBuggy
{
	void SInit();
}

struct STRU_1F5F9A0
{
	s32 field_0;
	u32 field_4;
	bool field_8;
	float field_C;
	float field_10;
};

// 00313770
bool sgInitBuggy(SubGameInfo*);

// 00314110
bool sgExitBuggy(SubGameInfo*);

// 003141F0
bool sgLoopBuggy(SubGameInfo*);

// 00314420
bool sgDrawBuggy(SubGameInfo*);

// 003144A0
bool sgEffectDrawBuggy(SubGameInfo*);

// 00314590
bool sgSystemDrawBuggy(SubGameInfo*);

// 003149A0
void CharaControl(SubGameInfo*, CPadControl*);

// 00315350
void InitBuggy(CScene*);

// 003153F0
void BuggyDamage(s32 i1);

// 00315430
void PlayBuggyLoopSe(CScene*);

// 00315510
void BuggyControl(CScene*);

// 00316000
void InitBomb(CScene*);

// 003160E0
bool TakeBombCheck(void);

// 00316100
bool TakeBomb(void);

// 00316140
bool ThrowBomb(vec4 &dir);

// 003161E0
bool BombBomb(void);

// 00316220
bool NowPutBomb(void);

// 00316230
void BombControl(CScene*);

// 00316860
void BombCheck(CScene*);