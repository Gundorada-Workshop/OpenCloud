#pragma once
#include "common/debug.h"
#include "common/log.h"
#include "common/macros.h"

#include "dc2/character.h"
#include "dc2/effect_script.h"
#include "dc2/mg/mg_lib.h"
#include "dc2/mg/mg_memory.h"
#include "dc2/pbuggy.h"

set_log_channel("pbuggy");

// 00376B34
static s32 BuggyHP = 1;

// 00378774
static CCharacter2* BuggyChara;
// 00378778
static CCharacter2* PorcussChara;
// 0037877C
static CCharacter2* MucchoChara;
// 00378780
static CCharacter2* BombChara;
// 00378784
static CCharacter2* StarbullChara;
// 00378788
static CCharacter2* GunFireEff;
// 0037878C
static CCharacter2* GunHitEff;

// 00378790
static s32 BombEffHandle;

// 00378794
static s32 SmokeEffHandle;

// 00378798
static s32 BuggyTexb;

// 0037879C
static s32 PorcussTexb;

// 003787A0
static s32 MucchoTexb;

// 003787A4
static s32 EffectTexb;

// 003787A8
static s32 EffectTexbNum;

// 003787AC
static s32 BombTexb;

// 003787B0
static s32 StarbullTexb;

// 003787B4
static s32 GunEffTexb;

// 003787B8
static s32 SysTexb;

// 003787BC
static CEffectScriptMan* EffectMan;

// 003787C0
static s32 RunEventNo;

// 003787C4
char *WorkBuff;

// 003787C8
static s32 BuggySndID;

// 003787CC
static bool IntroHelpMesFlag;

// 003787D0
static int CharaStatus;

// 003787D4
static s32 BuggyStatus;

// 003787D8
static bool BuggyStatusStep;

// 003787DC
static float BuggyHPf;

// 003787E0
static float TrainHP;

// 003787E4
static s32 BuggyActCount;

// 003787E8
static s32 BuggySidePos;

// 003787EC
static s32 BuggyDamageMotion;

// 003787F0
static s32 GunFireEffDraw;

// 003787F4
static s32 GunHitEffDraw;

// 003787F8
static u32 BombStatus;

// 003787FC
static s32 BombCount;

// 00378800
static bool BombHitObj;

// 00378804
static s32 BombImpact;

// 00378808
// FIXME: static fn var
static s32 test$1252;

// 0037880C
// FIXME: static fn var
static bool init$1253;

// 00378810
// FIXME: static fn var
static s32 reload_cnt$1348;

// 01F5F940
//static vec4 StarbullPos;

// 01F5F950
static mgCMemory EffectBuff{};

// 01F5F980
//static vec4 BuggyVelo;

// 01F5F990
//static vec4 BombVelo;

// 01F5F9A0
static STRU_1F5F9A0 PolVoice{};

bool sgInitBuggy(MAYBE_UNUSED SubGameInfo* info)
{
	log_trace("sgInitBuggy({})", fmt::ptr(info));

	todo;

	return false;
}

bool sgExitBuggy(MAYBE_UNUSED SubGameInfo* info)
{
	log_trace("sgExitBuggy({})", fmt::ptr(info));

	todo;

	return false;
}

bool sgLoopBuggy(MAYBE_UNUSED SubGameInfo* info)
{
	log_trace("sgLoopBuggy({})", fmt::ptr(info));

	todo;

	return false;
}

bool sgDrawBuggy(MAYBE_UNUSED SubGameInfo* info)
{
	log_trace("sgDrawBuggy({})", fmt::ptr(info));

	todo;

	return false;
}

bool sgEffectDrawBuggy(MAYBE_UNUSED SubGameInfo* info)
{
	log_trace("sgEffectDrawBuggy({})", fmt::ptr(info));

	todo;

	return false;
}

bool sgSystemDrawBuggy(MAYBE_UNUSED SubGameInfo* info)
{
	log_trace("sgSystemDrawBuggy({})", fmt::ptr(info));

	todo;

	return false;
}

void CharaControl(MAYBE_UNUSED SubGameInfo* info, MAYBE_UNUSED CPadControl* padctrl)
{
	log_trace("CharaControl({}, {})", fmt::ptr(info), fmt::ptr(padctrl));

	todo;
}

void InitBuggy(MAYBE_UNUSED CScene* scene)
{
	log_trace("InitBuggy({})", fmt::ptr(scene));

	todo;
}

void BuggyDamage(s32 i1)
{
	log_trace("BuggyDamage({})", i1);

	if (BuggyStatus == 1)
	{
		return;
	}

	BuggyDamageMotion = i1;
	BuggyStatus = 2;
	BuggyStatusStep = false;
	BuggyActCount = 1;
	BombHitObj = true;
	BuggyHP -= 1;
}

void PlayBuggyLoopSe(MAYBE_UNUSED CScene* scene)
{
	log_trace("PlayBuggyLoopSe({})", fmt::ptr(scene));

	todo;
}

// 00315510
void BuggyControl(MAYBE_UNUSED CScene* scene)
{
	log_trace("BuggyControl({})", fmt::ptr(scene));

	todo;
}

void InitBomb(MAYBE_UNUSED CScene* scene)
{
	log_trace("InitBomb({})", fmt::ptr(scene));

	todo;
}

bool TakeBombCheck()
{
	log_trace("TakeBombCheck()");

	return (BombStatus ^ 3) == 0;
}

bool TakeBomb()
{
	log_trace("TakeBomb()");

	if (!TakeBombCheck())
	{
		return false;
	}

	BombStatus = 4;

	return true;
}

//bool ThrowBomb(MAYBE_UNUSED vec4& dir)
//{
//	// todo: need formatter for vec4
//	// log_trace("ThrowBomb({})", dir);
//	log_trace("ThrowBomb(dir)");
//
//	todo;
//
//	return false;
//}

bool BombBomb()
{
	log_trace("BombBomb()");

	if (BombStatus != 6)
	{
		return false;
	}

	//BombVelo = vec4(0.0f);

	BombCount = 0;
	BombHitObj = true;

	return true;
}

bool NowPutBomb()
{
	log_trace("NowPutBomb()");

	return (BombStatus ^ 3) == 0;
}

void BombControl(MAYBE_UNUSED CScene* scene)
{
	log_trace("BombControl({})", fmt::ptr(scene));

	todo;
}

void BombCheck(MAYBE_UNUSED CScene* scene)
{
	log_trace("BombCheck({})", fmt::ptr(scene));

	todo;
}