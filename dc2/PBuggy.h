#pragma once
#include "common/types.h"
#include "CCharacter2.h"
#include "CEffect.h"
#include "CPadControl.h"
#include "CScene.h"
#include "mgCMemory.h"
#include "SubGame.h"

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
}