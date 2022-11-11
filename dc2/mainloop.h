#pragma once
#include "common/debug.h"
#include "common/types.h"
#include "font.h"
#include "menusave.h"
#include "mg_memory.h"

namespace Language
{
	enum Language : s32
	{
		Japanese = 0,
		English = 1,
		COUNT = 2
	};
}

// 00376FC0
extern Language::Language LanguageCode;

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

struct SInitArg
{
	// 0
	_UNKNOWN m_unk_field_0{ 0 };
	// 4
	_UNKNOWNSTRUCT(0x40) m_unk_field_4{ 0 };
	// 44
	_UNKNOWN m_unk_field_44{ 0 };
	// 48
	_UNKNOWN m_unk_field_48{ 0 };
	// 4C
	_UNKNOWN m_unk_field_4C{ 0 };
};

namespace MainLoop_SInit
{
	void SInit();
}

// 00190840
CFont* GetDebugFont();

// 00190860
u32 GetSystemSndId();

// 00190880
CSaveData* GetSaveData();

// 001908F0
mgCMemory* GetMainStack();

// 00190BE0
void PlayTimeCount(bool flag);

// 00190BF0
bool GetPlayTimeCountFlag();

// 00190CB0
void MainLoop();
