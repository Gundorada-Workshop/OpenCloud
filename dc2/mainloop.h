#pragma once
#include "common/debug.h"
#include "common/types.h"
#include "font.h"
#include "mg_memory.h"

struct SMainLoopUnk1
{
	bool m_unk_field_0;
	s32 m_unk_field_4;
	bool m_unk_field_8;
	bool m_unk_field_C;
	s32 m_unk_field_10;
};

struct SMainLoopUnk2
{
	// 0
	_UNKNOWN m_unk_field_0;
	// 4
	// FIXME unknown type (buffer size 0x40)
	char m_unk_field_4[0x40];
	// 44
	_UNKNOWN m_unk_field_44;
	// 48
	_UNKNOWN m_unk_field_48;
	// 4C
	_UNKNOWN m_unk_field_4C;
};

namespace MainLoop_SInit
{
	void SInit();
}

// 00190840
CFont* GetDebugFont(void);

// 001908F0
mgCMemory* GetMainStack(void);

// 00190CB0
void MainLoop();
