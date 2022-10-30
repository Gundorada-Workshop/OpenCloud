#pragma once
#include <array>
#include "common/types.h"
#include "CFont.h"
#include "CPadControl.h"
#include "CInventUserData.h"
#include "mgCMemory.h"
#include "mgCTexture.h"

namespace Photo
{
	void SInit();
}

struct USER_PICTURE_INFO
{
	u8 field_0;
	u8 field_1;
	u16 field_2;
	u16 field_4;
	u16 field_6;
	u16 field_8;
	u16 field_A;
};

// 0030E4C0
const char* GetMesTxt(ssize index);

// 0030E520
float PhotoAddProjection(void);

// 0030E550
void InitPhotoTitle(void);

// 0030E560
void InitTakePhoto(void);

// 0030E5A0
void LoadTakePhoto(int, mgCMemory& unused);

// 0030E640
void StartTakePhoto(void);

// 0030E670
void EndTakePhoto(void);

// 0030E680
bool NowTakePhoto(void);

// 0030E690
bool IsEnablePhotoMenu(void);

// 0030E6A0
void HidePhoto(void);

// 0030E6B0
bool GhostPhotoTiming(void);

// 0030E6E0
void LoopTakePhoto(CPadControl& padControl, CInventUserData& invest_user_data);

// 0030E810
void DrawTakePhoto(USER_PICTURE_INFO& picture_info, float* fp);

// 0030F610
void SetTookPhotoData(USER_PICTURE_INFO& picture_info);

// 0030F6A0
void DrawTakePhotoSystem(s32 i1, CInventUserData& invest_user_data);

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
constexpr static u32 flt_35E6E8 = 0.0f;
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