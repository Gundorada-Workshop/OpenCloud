#pragma once
#include <glm/glm.hpp>

#include "common/debug.h"
#include "common/log.h"

#include "dc2/font.h"
#include "dc2/mainloop.h"
#include "dc2/mg/mg_texture.h"
#include "dc2/photo.h"

set_log_channel("Photo");

// 0035E6C0
// FIXME: inline function data
constexpr static vec4 stru_35E6C0 = { 0.0f, 0.0f, 0.0f, 1.0f };
// 0035E6D0
// FIXME: inline function data
constexpr static u64 qword_35E6D0 = 0x100000000;
// 0035E6D8
// FIXME: inline function data
constexpr static u32 dword_35E6D8 = 2;
// 0035E6E0
// FIXME: inline function data
constexpr static u64 qword_35E6E0 = 0x2FFFFFFFF;
// 0035E6E8
// FIXME: inline function data
constexpr static float flt_35E6E8 = 0.0f;
// 0035E6F0
// FIXME: inline function data
constexpr static u64 qword_35E6F0 = 0xFFFFFFFF;
// 0035E6F8
// FIXME: inline function data
constexpr static u32 dword_35E6F8 = 2;
// 0035E700
// FIXME: inline function data
constexpr static vec4 stru_35E700 = { -1.0f, 3.0f, -3.0f, 1.0f };
// 0035E710
// FIXME: inline function data
constexpr static vec4 stru_35E710 = { 2.0f, -5.0f, 4.0f, -1.0f };
// 0035E720
// FIXME: inline function data
constexpr static vec4 stru_35E720 = { -1.0f, 0.0f, 1.0f, 0.0f };
// 0035E730
// FIXME: inline function data
constexpr static vec4 stru_35E730 = { 0.0f, 2.0f, 0.0f, 0.0f };
// 0035E740
// FIXME: inline function data
constexpr static vec4 stru_35E740 = { 0.0f, 0.0f, 0.0f, 1.0f };

// 00378710
static u32 TakePhotoMode;
// 00378714
static float AddProj;
// 00378718
static int CameraTexb;
// 0037871C
static mgCTexture* WorkTex;
// 00378720
static s32 ShutterAnmCnt;
// 00378724
static s32 ShowTakePhotoCnt;
// 00378728
static bool OpenMenu;
// 0037872C
static int ShowTitleCnt;
// 00378730
static int ShowLevelUpCnt;

// 01F5DDF0
static CFont Font{};
// 01F5DEA0
static char PhotoTitle[0x80];

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

	auto language_index = std::to_underlying(LanguageCode);
	if (index < 0 || mes_txt[0].size() <= index || \
		language_index < 0 || language_index >= mes_txt.size())
	{
		return "";
	}

	return mes_txt[language_index][index];
}

float PhotoAddProjection()
{
	log_trace("PhotoAddProjection()");

	if (!NowTakePhoto())
	{
		return 0.0f;
	}

	return AddProj;
}

void InitPhotoTitle()
{
	log_trace("InitPhotoTitle()");

	ShowTitleCnt = 0;
	PhotoTitle[0] = '\0';
}

void InitTakePhoto()
{
	log_trace("InitTakePhoto()");

	TakePhotoMode = 0;
	AddProj = 0.0f;
	InitPhotoTitle();
	ShowTakePhotoCnt = 0;
	CameraTexb = -1;
	ShutterAnmCnt = 0;
	OpenMenu = false;
	ShowLevelUpCnt = 0;
}

void LoadTakePhoto(int unk, mgCMemory& unused)
{
	todo;
}

void StartTakePhoto()
{
	log_trace("StartTakePhoto()");

	InitTakePhoto();
	TakePhotoMode = 2;
}

void EndTakePhoto()
{
	log_trace("EndTakePhoto()");

	InitTakePhoto();
}

bool NowTakePhoto()
{
	log_trace("NowTakePhoto()");

	return TakePhotoMode != 0;
}

bool IsEnablePhotoMenu()
{
	log_trace("IsEnablePhotoMenu()");

	return (TakePhotoMode ^ 2) == 0;
}

void HidePhoto()
{
	log_trace("HidePhoto()");

	ShowTakePhotoCnt = 0;
}

bool GhostPhotoTiming()
{
	log_trace("GhostPhotoTiming()");

	return TakePhotoMode == 5 || TakePhotoMode == 3;
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