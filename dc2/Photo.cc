#pragma once
#include <assert.h>
#include "Photo.h"
#include "globals.h"

namespace Photo
{
	void SInit()
	{
		stru_1F5DDF0.Initialize();
	}
}

const char* GetMesTxt(ssize index)
{
	if (index < 0 || msg_text[0].size() <= index || _g_language < 0 || msg_text.size() <= _g_language)
	{
		return null_txt;
	}

	return msg_text[_g_language][index];
}

float PhotoAddProjection(void)
{
	if (!NowTakePhoto())
	{
		return 0.0f;
	}
	return flt_378714;
}

void InitPhotoTitle(void)
{
	dword_37872C = 0;
	byte_1F5DEA0[0] = '\0';
}

void InitTakePhoto(void)
{
	dword_378710 = 0;
	flt_378714 = 0.0f;
	InitPhotoTitle();
	dword_378724 = 0;
	dword_378718 = -1;
	dword_378720 = 0;
	dword_378728 = false;
	dword_378730 = 0;
}

void LoadTakePhoto(int, mgCMemory& unused)
{
	// TODO
	assert(false);
}

void StartTakePhoto(void)
{
	InitTakePhoto();
	dword_378710 = 2;
}

void EndTakePhoto(void)
{
	InitTakePhoto();
}

bool NowTakePhoto(void)
{
	return dword_378710 != 0;
}

bool IsEnablePhotoMenu(void)
{
	return (dword_378710 ^ 2) == 0;
}

void HidePhoto(void)
{
	dword_378724 = 0;
}

bool GhostPhotoTiming(void)
{
	return dword_378710 == 5 || dword_378710 == 3;
}

void LoopTakePhoto(CPadControl& padControl, CInventUserData& invest_user_data)
{
	// TODO
	assert(false);
}

void DrawTakePhoto(USER_PICTURE_INFO& picture_info, float* fp)
{
	// TODO
	assert(false);
}

void SetTookPhotoData(USER_PICTURE_INFO& picture_info)
{
	// TODO
	assert(false);
}

void DrawTakePhotoSystem(s32 i1, CInventUserData& invest_user_data)
{
	// TODO
	assert(false);
}