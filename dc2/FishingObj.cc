#include <stdlib.h>
#include <string.h>
#include "common/debug.h"
#include "common/log.h"
#include "FishingObj.h"
#include "mgLib.h"
#include "sceVu0.h"

set_log_channel("FishingObj")

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
static alignas(16) vec4 stru_1F5ED30;
// 01F5ED40
static alignas(16) vec4 stru_1F5ED40;
// 01F5ED50
static alignas(16) vec4 stru_1F5ED50;
// 01F5ED60
static alignas(16) vec4 stru_1F5ED60;
// 01F5ED70
static alignas(16) vec4 stru_1F5ED70;
// 01F5ED80
static alignas(16) vec4 stru_1F5ED80;
// 01F5ED90
static alignas(16) vec4 stru_1F5ED90;
// 01F5EDA0
static alignas(16) vec4 stru_1F5EDA0;
// 01F5EDB0
static alignas(16) vec4 stru_1F5EDB0;
// 01F5EDC0
static CFishObj s_lure_obj;
// 01F5F190
static CFishObj s_uki_obj;
// 01F5F560
static CFishObj s_hari_obj;
// 01F5F930
static alignas(16) vec4 stru_1F5F930;

namespace FishingObj
{
	// 00374BE0
	void SInit()
	{
		log_trace("SInit");

		memset(&s_lure_obj, 0, sizeof(s_lure_obj));
		memset(&s_uki_obj, 0, sizeof(s_uki_obj));
		memset(&s_hari_obj, 0, sizeof(s_hari_obj));
	}
}

// 003130B0
void CFishObj::MovePoint()
{
	log_trace("MovePoint");

	todo;
}

// 00313140
void CFishObj::FloatPoint(float f)
{
	log_trace("FloatPoint({})", f);

	todo;
}

// 00313310
void CFishObj::BindStep()
{
	log_trace("BindStep");

	todo;
}

// 00313380
void CFishObj::Correct(CCPoly& poly, int i, float f)
{
	log_trace("Correct({}, {}, {})", fmt::ptr(&poly), i, f);

	todo;
}

// 0030F9B0
void SetFishingMode(int fishing_mode)
{
	log_trace("SetFishingMode({})", fishing_mode);

	s_fishing_mode = fishing_mode;
}

// 0030F9C0
int GetFishingMode()
{
	log_trace("GetFishingMode");

	return s_fishing_mode;
}

// 0030F9D0
void SetWaterLevel(float water_level)
{
	log_trace("SetWaterLevel({})", water_level);

	s_water_level = water_level;
}

// 0030F9E0
float GetWaterLevel()
{
	log_trace("GetWaterLevel");

	return s_water_level;
}

// 0030F9F0
CFishObj* GetActiveHariObj()
{
	log_trace("GetActiveHariObj");

	if (s_fishing_mode != 2)
	{
		return &s_hari_obj;
	}
	return &s_lure_obj;
}

// 0030FA20
CFishObj* GetActiveUkiObj()
{
	log_trace("GetActiveUkiObj");

	if (s_fishing_mode != 2)
	{
		return &s_uki_obj;
	}
	return nullptr;
}

// 0030FA50
void ExtendLine(float delta)
{
	log_trace("ExtendLine({})", delta);

	todo;
}

// 0030FC10
float GetNowLineLength()
{
	log_trace("GetNowLineLength");

	if (dword_37874C)
	{
		return flt_378750;
	}

	return (63 - dword_378738) * 5.0f + flt_37873C;
}

// 0030FC60
float GetMinLineLength()
{
	log_trace("GetMinLineLength");

	return 25.0f;
}

// 0030FC70
void InitRodPoint(mgCFrame& fr1, mgCFrame& fr2)
{
	log_trace("InitRodPoint({}, {})", fmt::ptr(&fr1), fmt::ptr(&fr2));

	todo;
}

// 00310020
void GetTriPose(matrix4& m1, matrix4& m2, vec4& v1)
{
	log_trace("GetTriPose({}, {}, {})", fmt::ptr(&m1), fmt::ptr(&m2), fmt::ptr(&v1));

	todo;
}

// 003101F0
void GetHariPos(vec4& v1, vec4& v2)
{
	log_trace("GetHariPos({}, {})", fmt::ptr(&v1), fmt::ptr(&v2));

	sceVu0CopyVector(v1, stru_1F5E0A0[stru_1F5E0A0.size() - 1][0]);
	sceVu0CopyVector(v2, stru_1F5E0A0[stru_1F5E0A0.size() - 1][1]);
}

// 00310220
void GetUkiPos(vec4& v1, vec4& v2)
{
	log_trace("GetUkiPos({}, {})", fmt::ptr(&v1), fmt::ptr(&v2));

	sceVu0CopyVector(v1, stru_1F5E0A0[stru_1F5E0A0.size() - 4][0]);
	sceVu0CopyVector(v2, stru_1F5E0A0[stru_1F5E0A0.size() - 4][1]);
}

// 00310250
void PullUki(float f)
{
	log_trace("PullUki({})", f);

	stru_1F5E0A0[stru_1F5E0A0.size() - 1][2][1] -= f;
}

// 00310270
void SetShowHari(bool enabled)
{
	log_trace("SetShowHari({})", enabled);

	s_show_hari = enabled;
}

// 00310280
bool GetShowHari()
{
	log_trace("GetShowHari()");

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

// 003102E0
void SetLurePose(mgCFrame& frame)
{
	log_trace("SetLurePose({})", fmt::ptr(&frame));

	todo;
}

// 003103D0
void SetUkiPose(mgCFrame& fr1, mgCFrame& fr2)
{
	log_trace("SetUkiPose({}, {})", fmt::ptr(&fr1), fmt::ptr(&fr2));

	todo;
}

// 003105C0
void CastingLure(vec4& v)
{
	log_trace("CastingLure({})", fmt::ptr(&v));

	todo;
}

// 00310730
void EndCastingLure()
{
	log_trace("CastingLure()");

	dword_378740 = false;
	dword_378744 = 0;
	dword_378748 = 0;
}

// 00310740
bool CatchLine(vec4& v, float f)
{
	log_trace("CatchLine({}, {})", fmt::ptr(&v), f);

	todo;
	return false;
}

// 00310890
void SlowLineVelo(float multiplier)
{
	log_trace("SlowLineVelo({})", multiplier);

	for (usize index = dword_378738; index < stru_1F5E0A0.size(); ++index)
	{
		sceVu0ScaleVector(stru_1F5E0A0[index][2], stru_1F5E0A0[index][2], multiplier);
	}
}

// 00310910
void ResetLineVelo()
{
	log_trace("ResetLineVelo()");

	todo;
}

// 003109D0
void ResetLine(vec4& v)
{
	log_trace("ResetLine({})", fmt::ptr(&v));

	todo;
}

// 00310B60
int GetNextChanceCnt()
{
	log_trace("GetNextChanceCnt()");

	return rand() % 80 + 60;
}

// 00310BA0
bool InitFishBattle()
{
	log_trace("InitFishBattle()");

	sceVu0CopyVector(stru_1F5EDB0, stru_1F5E0A0[stru_1F5E0A0.size() - 1][0]);
	sceVu0CopyVector(stru_1F5ED60, stru_1F5E0A0[stru_1F5E0A0.size() - 1][0]);
	sceVu0CopyVector(stru_1F5ED70, stru_1F5E0A0[stru_1F5E0A0.size() - 1][0]);
	mgZeroVector(stru_1F5ED80);
	flt_378750 = mgDistVector(stru_1F5E0A0[stru_1F5E0A0.size() - 1][0], stru_1F5E0A0[4][0]);
	dword_378760 = 0;
	dword_37874C = true;
	flt_378764 = 0.0f;
	s_next_chance_cnt = GetNextChanceCnt();
	dword_37876C = 0;
	return true;
}

// 00310C30
bool EndFishBattle()
{
	log_trace("EndFishBattle()");

	dword_37874C = false;
	s_next_chance_cnt = 0;
	dword_37876C = 0;
	return true;
}

// 00310C50
int CheckRodActionChance(int i, bool& pi)
{
	log_trace("CheckRodActionChance({}, {})", i, fmt::ptr(&pi));

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

// 00310CC0
void FishBattle(CScene& scene, CCPoly& poly, int i)
{
	log_trace("FishBattle({}, {}, {})", fmt::ptr(&scene), fmt::ptr(&poly), i);

	todo;
}

// 00311070
void GetFishPosVelo(vec4& pos, vec4& velocity)
{
	log_trace("GetFishPosVelo({}, {})", fmt::ptr(&pos), fmt::ptr(&velocity));

	sceVu0CopyVector(pos, stru_1F5ED60);
	sceVu0CopyVector(velocity, stru_1F5ED80);
}

// 003110A0
void BindFishObj()
{
	log_trace("BindFishObj()");

	todo;
}

// 00311290
void RodStep(CScene& scene, CCPoly& poly)
{
	log_trace("RodStep({}, {})", fmt::ptr(&scene), fmt::ptr(&poly));

	todo;
}

// 00312200
void BindPosition(vec4& v1, vec4& v2, float f1, float f2)
{
	log_trace("BindPosition({}, {}, {}, {})", fmt::ptr(&v1), fmt::ptr(&v2), f1, f2);

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

// 003122E0
void DrawFishingLine()
{
	log_trace("DrawFishingLine()");

	todo;
}

// 003125D0
void DrawFishingActionChance()
{
	log_trace("DrawFishingActionChance()");

	todo;
}

// 003128E0
void InitLureObj(int i, mgCFrame& frame)
{
	log_trace("InitLureObj({}, {})", i, fmt::ptr(&frame));

	todo;
}

// 00312D20
void InitUkiObj(int i, mgCFrame& frame1, mgCFrame& frame2)
{
	log_trace("InitUkiObj({}, {}, {})", i, fmt::ptr(&frame1), fmt::ptr(&frame2));

	todo;
}

// 00313570
void ParaBlend(vec4& v1, float f1, vec4& v2, s32 i)
{
	log_trace("ParaBlend({}, {}, {}, {})", fmt::ptr(&v1), f1, fmt::ptr(&v2), i);

	todo;
}
