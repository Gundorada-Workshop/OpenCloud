#pragma once
#include "common/debug.h"
#include "common/types.h"

#include "engine/font.h"
#include "engine/menusave.h"
#include "engine/mg/mg_memory.h"

enum class Language : s32
{
	Japanese = 0,
	English = 1,
	COUNT = 2
};

// 00376FB4
extern u32 s_system_snd_id;
// 00376FB8
extern bool DebugFlag;
// 00376FBC
extern u32 DefStartEventNo;
// 00376FC0
extern Language LanguageCode;
// 00376FC4
extern bool OmakeFlag;
// 00376FC8
extern s32 MasterDebugCode;

enum class ELoopID
{
	Edit = 1,
	Dungeon = 2,
};

struct INIT_LOOP_ARG
{
	// 0
	s32 m_unk_field_0{};

	// 44
	s32 m_unk_field_44{};
	// 48
	s32 m_unk_field_48{};
	// 4C
	s32 m_unk_field_4C{};

	// SIZE 0x50
};

struct SDebugInfo
{
	// 0
	bool m_unk_field_0{ false };
	// 4
	s32 m_unk_field_4{ -1 };
	// 8
	bool m_unk_field_8{ false };
	// C
	bool m_unk_field_C{ false };
	// 10
	s32 m_unk_field_10{ -1 };
};

// 00190840
CFont* GetDebugFont();

// 00190860
u32 GetSystemSndId();

// 00190870
CScene* GetMainScene();

// 00190880
CSaveData* GetSaveData();

// 001908F0
mgCMemory* GetMainStack();

// 00190900
void NextLoop(ELoopID next_loop_id, const INIT_LOOP_ARG& init_arg);

// 00190BE0
void PlayTimeCount(bool flag);

// 00190BF0
bool GetPlayTimeCountFlag();

// 00190CB0
void MainLoop();
