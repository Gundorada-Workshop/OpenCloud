#pragma once
#include <assert.h>
#include "mgCTexture.h"
#include "CFont.h"
#include "Photo.h"
#include "globals.h"

// 0035E6A0
constexpr static std::array<std::array<const char*, 4>, 2> msg_text = {
	// Japanese (4)
	"(A):写真を確認",
	"(#):写真をとる",
	"ユリスの写真家レベルが上がった",
	"(R):ズーム",

	// English (4)
	"(A):Confirm Picture",
	"(#):Take Picture",
	"Max's photography level increased!",
	"(R):zoom (O):Back",
};
// 0035E6C0
constexpr static vec4 stru_35E6C0 = { 0.0f, 0.0f, 0.0f, 1.0f };
// 0035E6D0
constexpr static u64 qword_35E6D0 = 0x100000000;
// 0035E6D8
constexpr static u32 dword_35E6D8 = 2;
// 0035E6E0
constexpr static u64 qword_35E6E0 = 0x2FFFFFFFF;
// 0035E6E8
constexpr static float flt_35E6E8 = 0.0f;
// 0035E6F0
constexpr static u64 qword_35E6F0 = 0xFFFFFFFF;
// 0035E6F8
constexpr static u32 dword_35E6F8 = 2;
// 0035E700
constexpr static vec4 stru_35E700 = { -1.0f, 3.0f, -3.0f, 1.0f };
// 0035E710
constexpr static vec4 stru_35E710 = { 2.0f, -5.0f, 4.0f, -1.0f };
// 0035E720
constexpr static vec4 stru_35E720 = { -1.0f, 0.0f, 1.0f, 0.0f };
// 0035E730
constexpr static vec4 stru_35E730 = { 0.0f, 2.0f, 0.0f, 0.0f };
// 0035E740
constexpr static vec4 stru_35E740 = { 0.0f, 0.0f, 0.0f, 1.0f };

// 00376B30
constexpr static const char null_txt[] = "";

// 00378710
static u32 dword_378710;
// 00378714
static float flt_378714;
// 00378718
static int dword_378718;
// 0037871C
static mgCTexture* dword_37871C;
// 00378720
static s32 dword_378720;
// 00378724
static s32 dword_378724;
// 00378728
static bool dword_378728;
// 0037872C
static int dword_37872C;
// 00378730
static int dword_378730;

// 01F5DDF0
static CFont stru_1F5DDF0;
// 01F5DEA0
static char byte_1F5DEA0[0x80];

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