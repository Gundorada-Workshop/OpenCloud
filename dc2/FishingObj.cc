#include <stdlib.h>
#include <string.h>
#include "common/debug.h"
#include "FishingObj.h"
#include "mgLib.h"
#include "sceVu0.h"

// 00378734
static float s_water_level;
// 00378738
static s32 dword_378738;
// 0037873C
static float flt_37873C;
// 00378740
static bool dword_378740;
// 00378744
static s32 dword_378744;
// 00378748
static s32 dword_378748;
// 0037874C
static bool dword_37874C;
// 00378750
static float flt_378750;
// 00378754
static bool s_show_hari;
// 00378758
static bool dword_378758;
// 0037875C
static u32 s_fishing_mode;
// 00378760
static s32 dword_378760;
// 00378764
static float flt_378764;
// 00378768
static s32 s_next_chance_cnt;
// 0037876C
static s32 dword_37876C;
// 00378770
static s32 dword_378770;

// 01F5DF20
static alignas(16) std::array<std::array<vec4, 3>, 5> stru_1F5DF20;
// 01F5E010
static alignas(16) std::array<vec4, 5> stru_1F5E010;
// 01F5E060
static std::array<mgCFrame*, 8> stru_1F5E060;
// 01F5E080
static std::array<float, 8> stru_1F5E080;
// 01F5E0A0
static alignas(16) std::array<std::array<vec4, 3>, 64> stru_1F5E0A0;
// 01F5ECA0
static alignas(16) std::array<std::array<vec4, 3>, 3> stru_1F5ECA0;
// 01F5ED30
static vec4 stru_1F5ED30;
// 01F5ED40
static vec4 stru_1F5ED40;
// 01F5ED50
static vec4 stru_1F5ED50;
// 01F5ED60
static vec4 stru_1F5ED60;
// 01F5ED70
static vec4 stru_1F5ED70;
// 01F5ED80
static vec4 stru_1F5ED80;
// 01F5ED90
static vec4 stru_1F5ED90;
// 01F5EDA0
static vec4 stru_1F5EDA0;
// 01F5EDB0
static vec4 stru_1F5EDB0;
// 01F5EDC0
static CFishObj s_lure_obj;
// 01F5F190
static CFishObj s_uki_obj;
// 01F5F560
static CFishObj s_hari_obj;
// 01F5F930
static vec4 stru_1F5F930;

namespace FishingObj
{
	void SInit()
	{
		memset(&s_lure_obj, 0, sizeof(s_lure_obj));
		memset(&s_uki_obj, 0, sizeof(s_uki_obj));
		memset(&s_hari_obj, 0, sizeof(s_hari_obj));
	}
}

void CFishObj::MovePoint(void)
{
	todo;
}

void CFishObj::FloatPoint(float f)
{
	todo;
}

void CFishObj::BindStep(void)
{
	todo;
}

void CFishObj::Correct(CCPoly& poly, int i, float f)
{
	todo;
}

void SetFishingMode(int fishing_mode)
{
	s_fishing_mode = fishing_mode;
}

int GetFishingMode()
{
	return s_fishing_mode;
}

void SetWaterLevel(float water_level)
{
	s_water_level = water_level;
}

float GetWaterLevel(void)
{
	return s_water_level;
}

CFishObj* GetActiveHariObj(void)
{
	if (s_fishing_mode != 2)
	{
		return &s_hari_obj;
	}
	return &s_lure_obj;
}

CFishObj* GetActiveUkiObj(void)
{
	if (s_fishing_mode != 2)
	{
		return &s_uki_obj;
	}
	return nullptr;
}

void ExtendLine(float delta)
{
	todo;
}

float GetNowLineLength(void)
{
	if (dword_37874C)
	{
		return flt_378750;
	}

	return (63 - dword_378738) * 5.0f + flt_37873C;
}

float GetMinLineLength(void)
{
	return 25.0f;
}

void InitRodPoint(mgCFrame& fr1, mgCFrame& fr2)
{
	todo;
}

void GetTriPose(matrix4& m1, matrix4& m2, vec4& v1)
{
	todo;
}

void GetHariPos(vec4& v1, vec4& v2)
{
	memcpy(&v1, &stru_1F5E0A0[stru_1F5E0A0.size() - 1][0], sizeof(vec4));
	memcpy(&v2, &stru_1F5E0A0[stru_1F5E0A0.size() - 1][1], sizeof(vec4));
}

void GetUkiPos(vec4& v1, vec4& v2)
{
	memcpy(&v1, &stru_1F5E0A0[stru_1F5E0A0.size() - 4][0], sizeof(vec4));
	memcpy(&v2, &stru_1F5E0A0[stru_1F5E0A0.size() - 4][1], sizeof(vec4));
}

void PullUki(float f)
{
	stru_1F5E0A0[stru_1F5E0A0.size() - 1][2][1] -= f;
}

void SetShowHari(bool enabled)
{
	s_show_hari = enabled;
}

bool GetShowHari(void)
{
	vec4 v1;
	vec4 v2;
	GetHariPos(v1, v2);

	float water_level = GetWaterLevel() - 3.0f;

	if (v1[1] < water_level)
	{
		return false;
	}
	return s_show_hari;
}

void SetLurePose(mgCFrame& frame)
{
	todo;
}

void SetUkiPose(mgCFrame& fr1, mgCFrame& fr2)
{
	todo;
}

void CastingLure(vec4& v)
{
	todo;
}

void EndCastingLure(void)
{
	dword_378740 = false;
	dword_378744 = 0;
	dword_378748 = 0;
}

bool CatchLine(vec4& v, float f)
{
	todo;
	return false;
}

void SlowLineVelo(float multiplier)
{
	for (usize index = dword_378738; index < stru_1F5E0A0.size(); ++index)
	{
		sceVu0ScaleVector(stru_1F5E0A0[index][2], stru_1F5E0A0[index][2], multiplier);
	}
}

void ResetLineVelo(void)
{
	todo;
}

void ResetLine(vec4& v)
{
	todo;
}

int GetNextChanceCnt(void)
{
	return rand() % 80 + 60;
}

bool InitFishBattle(void)
{
	memcpy(&stru_1F5EDB0, &stru_1F5E0A0[stru_1F5E0A0.size() - 1][0], sizeof(vec4));
	memcpy(&stru_1F5ED60, &stru_1F5E0A0[stru_1F5E0A0.size() - 1][0], sizeof(vec4));
	memcpy(&stru_1F5ED70, &stru_1F5E0A0[stru_1F5E0A0.size() - 1][0], sizeof(vec4));
	mgZeroVector(stru_1F5ED80);
	flt_378750 = mgDistVector(stru_1F5E0A0[stru_1F5E0A0.size() - 1][0], stru_1F5E0A0[4][0]);
	dword_378760 = 0;
	dword_37874C = true;
	flt_378764 = 0.0f;
	s_next_chance_cnt = GetNextChanceCnt();
	dword_37876C = 0;
	return true;
}

bool EndFishBattle(void)
{
	dword_37874C = false;
	s_next_chance_cnt = 0;
	dword_37876C = 0;
	return true;
}

int CheckRodActionChance(int i, bool& pi)
{
	pi = false;

	if (!dword_37874C)
	{
		return 0;
	}

	if (dword_37876C <= 0)
	{
		return 0;
	}

	int check = dword_378770 * i > 0;

	if (check > 0)
	{
		return 1;
	}

	if (check < 0)
	{
		return -1;
	}

	pi = (dword_37874C ^ 0x1C) == 0;
	return -1;
}

void FishBattle(CScene& scene, CCPoly& poly, int i)
{
	todo;
}

void GetFishPosVelo(vec4& pos, vec4& velocity)
{
	memcpy(&pos, &stru_1F5ED60, sizeof(vec4));
	memcpy(&velocity, &stru_1F5ED80, sizeof(vec4));
}

void BindFishObj(void)
{
	todo;
}

void RodStep(CScene& scene, CCPoly& poly)
{
	todo;
}

void BindPosition(vec4& v1, vec4& v2, float f1, float f2)
{
	alignas(16) vec4 var_10;
	alignas(16) vec4 var_20;
	alignas(16) vec4 var_30;
	sceVu0SubVector(var_30, v1, v2);
	float f0 = mgDistVector(var_30);
	float f21 = f0 - f1;
	float f20 = f0;
	f0 -= f2;
	f0 *= f21;
	sceVu0ScaleVector(var_20, var_30, f0 / f20);
	f0 = f2 * f21;
	sceVu0ScaleVector(var_10, var_30, f0 / f20);
	mgSubVector(v1, var_20);
	mgSubVector(v2, var_10);
}

void DrawFishingLine(void)
{
	todo;
}

void DrawFishingActionChance(void)
{
	todo;
}

void InitLureObj(int i, mgCFrame& frame)
{
	todo;
}

void InitUkiObj(int i, mgCFrame& frame1, mgCFrame& frame2)
{
	todo;
}

void ParaBlend(vec4& v1, float f1, vec4& v2, s32 i)
{
	todo;
}
