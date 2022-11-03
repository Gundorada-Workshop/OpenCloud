#pragma once
#include "glm/glm.hpp"
#include "common/debug.h"
#include "common/log.h"

#include "font.h"
#include "globals.h"
#include "mg_texture.h"
#include "photo.h"

set_log_channel("Photo");

// 0035E6C0
constexpr static glm::vec4 stru_35E6C0 = { 0.0f, 0.0f, 0.0f, 1.0f };
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
constexpr static glm::vec4 stru_35E700 = { -1.0f, 3.0f, -3.0f, 1.0f };
// 0035E710
constexpr static glm::vec4 stru_35E710 = { 2.0f, -5.0f, 4.0f, -1.0f };
// 0035E720
constexpr static glm::vec4 stru_35E720 = { -1.0f, 0.0f, 1.0f, 0.0f };
// 0035E730
constexpr static glm::vec4 stru_35E730 = { 0.0f, 2.0f, 0.0f, 0.0f };
// 0035E740
constexpr static glm::vec4 stru_35E740 = { 0.0f, 0.0f, 0.0f, 1.0f };

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
		log_trace("SInit()");

		stru_1F5DDF0.Initialize();
	}
}

const char* GetMesTxt(ssize index)
{
	// 0035E6A0
	constexpr static std::array<std::array<const char*, 4>, 2> mes_txt = {
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

	log_trace("GetMesTxt({})", index);

	if (index < 0 || mes_txt[0].size() <= index || _g_language < 0 || mes_txt.size() <= _g_language)
	{
		return "";
	}

	return mes_txt[_g_language][index];
}

float PhotoAddProjection()
{
	log_trace("PhotoAddProjection()");

	if (!NowTakePhoto())
	{
		return 0.0f;
	}

	return flt_378714;
}

void InitPhotoTitle()
{
	log_trace("InitPhotoTitle()");

	dword_37872C = 0;
	byte_1F5DEA0[0] = '\0';
}

void InitTakePhoto()
{
	log_trace("InitTakePhoto()");

	dword_378710 = 0;
	flt_378714 = 0.0f;
	InitPhotoTitle();
	dword_378724 = 0;
	dword_378718 = -1;
	dword_378720 = 0;
	dword_378728 = false;
	dword_378730 = 0;
}

void LoadTakePhoto(int unk, mgCMemory& unused)
{
	todo;
}

void StartTakePhoto()
{
	log_trace("StartTakePhoto()");

	InitTakePhoto();
	dword_378710 = 2;
}

void EndTakePhoto()
{
	log_trace("EndTakePhoto()");

	InitTakePhoto();
}

bool NowTakePhoto()
{
	log_trace("NowTakePhoto()");

	return dword_378710 != 0;
}

bool IsEnablePhotoMenu()
{
	log_trace("IsEnablePhotoMenu()");

	return (dword_378710 ^ 2) == 0;
}

void HidePhoto()
{
	log_trace("HidePhoto()");

	dword_378724 = 0;
}

bool GhostPhotoTiming()
{
	log_trace("GhostPhotoTiming()");

	return dword_378710 == 5 || dword_378710 == 3;
}

void LoopTakePhoto(CPadControl& padControl, CInventUserData& invest_user_data)
{
	todo;
}

void DrawTakePhoto(USER_PICTURE_INFO& picture_info, float* fp)
{
	todo;
}

void SetTookPhotoData(USER_PICTURE_INFO& picture_info)
{
	todo;
}

void DrawTakePhotoSystem(s32 i1, CInventUserData& invent_user_data)
{
	todo;
}