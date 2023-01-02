#include <stdlib.h>
#include <string.h>

#include "common/debug.h"
#include "common/log.h"
#include "common/macros.h"

#include "dc2/fishingobj.h"

set_log_channel("fishingobj")

using namespace common;

// 00378734
static float WaterLevel;
// 00378738
static s32 LineTop;
// 0037873C
static float LineTopDist;
// 00378740
static bool CastingLureFlag;
// 00378744
static s32 CastingLureTime;
// 00378748
static s32 AddLineSpeed;
// 0037874C
static u32 BattleFlag;
// 00378750
static float BattleLineDist;
// 00378754
static bool ShowHari;
// 00378758
static bool LureLessFlag;
// 0037875C
static u32 NowMode;
// 00378760
static s32 NowFishSpeed;
// 00378764
static float NowFishRot;
// 00378768
static s32 ActionChanceNextCnt;
// 0037876C
static s32 ActionChanceCnt;
// 00378770
static s32 ActionChanceDir;

// 01F5DF20
//static std::array<std::array<vec4, 3>, 5> RodPoint;
// 01F5E010
//static std::array<vec4, 5> RodPointDist;
// 01F5E060
static std::array<mgCFrame*, 8> SaoFrame;
// 01F5E080
static std::array<float, 8> SaoDist;
// 01F5E0A0
//static std::array<std::array<vec4, 3>, 64> LinePoint;
// 01F5ECA0
//static std::array<std::array<vec4, 3>, 3> LurePoint;
// 01F5ED30
//static vec4 FlyingPoint;
// 01F5ED40
//static vec4 stru_1F5ED40;
// 01F5ED50
//static vec4 stru_1F5ED50;
// 01F5ED60
//static vec4 FishPoint;
// 01F5ED70
//static vec4 stru_1F5ED70;
// 01F5ED80
//static vec4 stru_1F5ED80;
// 01F5ED90
//static vec4 CastingPoint;
// 01F5EDA0
//static vec4 stru_1F5EDA0;
// 01F5EDB0
//static vec4 stru_1F5EDB0;
// 01F5EDC0
static CFishObj LureObj{};
// 01F5F190
static CFishObj UkiObj{};
// 01F5F560
static CFishObj HariObj{};
// 01F5F930
//static vec4 ChanceBarPos;

// 003130B0
void CFishObj::MovePoint()
{
	log_trace("MovePoint()");

	todo;
}

// 00313140
void CFishObj::FloatPoint(MAYBE_UNUSED f32 f)
{
	log_trace("FloatPoint({})", f);

	todo;
}

// 00313310
void CFishObj::BindStep()
{
	log_trace("BindStep()");

	todo;
}

// 00313380
void CFishObj::Correct(MAYBE_UNUSED CCPoly& poly, MAYBE_UNUSED sint i, MAYBE_UNUSED f32 f)
{
	log_trace("Correct({}, {}, {})", fmt::ptr(&poly), i, f);

	todo;
}

// 0030F9B0
void SetFishingMode(sint fishing_mode)
{
	log_trace("SetFishingMode({})", fishing_mode);

	NowMode = fishing_mode;
}

// 0030F9C0
sint GetFishingMode()
{
	log_trace("GetFishingMode()");

	return NowMode;
}

// 0030F9D0
void SetWaterLevel(f32 water_level)
{
	log_trace("SetWaterLevel({})", water_level);

	WaterLevel = water_level;
}

// 0030F9E0
f32 GetWaterLevel()
{
	log_trace("GetWaterLevel()");

	return WaterLevel;
}

// 0030F9F0
CFishObj* GetActiveHariObj()
{
	log_trace("GetActiveHariObj()");

	if (NowMode != 2)
	{
		return &HariObj;
	}
	return &LureObj;
}

// 0030FA20
CFishObj* GetActiveUkiObj()
{
	log_trace("GetActiveUkiObj()");

	if (NowMode != 2)
	{
		return &UkiObj;
	}
	return nullptr;
}

// 0030FA50
void ExtendLine(MAYBE_UNUSED f32 delta)
{
	log_trace("ExtendLine({})", delta);

	todo;
}

// 0030FC10
f32 GetNowLineLength()
{
	log_trace("GetNowLineLength()");

	if (BattleFlag)
	{
		return BattleLineDist;
	}

	return (63 - LineTop) * 5.0f + LineTopDist;
}

// 0030FC60
f32 GetMinLineLength()
{
	log_trace("GetMinLineLength()");

	return 25.0f;
}

// 0030FC70
void InitRodPoint(MAYBE_UNUSED mgCFrame& fr1, MAYBE_UNUSED mgCFrame& fr2)
{
	log_trace("InitRodPoint({}, {})", fmt::ptr(&fr1), fmt::ptr(&fr2));

	todo;
}

// 00310020
//void GetTriPose(MAYBE_UNUSED matrix4& m1, MAYBE_UNUSED matrix4& m2, MAYBE_UNUSED vec4& v1)
//{
//	log_trace("GetTriPose({}, {}, {})", fmt::ptr(&m1), fmt::ptr(&m2), fmt::ptr(&v1));
//
//	todo;
//}

// 003101F0
//void GetHariPos(vec4& v1, vec4& v2)
//{
//	log_trace("GetHariPos({}, {})", fmt::ptr(&v1), fmt::ptr(&v2));
//
//	v1 = LinePoint[LinePoint.size() - 1][0];
//	v2 = LinePoint[LinePoint.size() - 1][1];
//}

// 00310220
//void GetUkiPos(vec4& v1, vec4& v2)
//{
//	log_trace("GetUkiPos({}, {})", fmt::ptr(&v1), fmt::ptr(&v2));
//
//	v1 = LinePoint[LinePoint.size() - 4][0];
//	v2 = LinePoint[LinePoint.size() - 4][1];
//}

// 00310250
//void PullUki(f32 f)
//{
//	log_trace("PullUki({})", f);
//
//	LinePoint[LinePoint.size() - 1][2][1] -= f;
//}

// 00310270
void SetShowHari(bool enabled)
{
	log_trace("SetShowHari({})", enabled);

	ShowHari = enabled;
}

// 00310280
//bool GetShowHari()
//{
//	log_trace("GetShowHari()");
//
//	vec4 v1;
//	vec4 v2;
//	GetHariPos(v1, v2);
//
//	f32 water_level = GetWaterLevel() - 3.0f;
//
//	if (v1[1] < water_level)
//	{
//		return false;
//	}
//	return ShowHari;
//}

// 003102E0
void SetLurePose(MAYBE_UNUSED mgCFrame& frame)
{
	log_trace("SetLurePose({})", fmt::ptr(&frame));

	todo;
}

// 003103D0
void SetUkiPose(MAYBE_UNUSED mgCFrame& fr1, MAYBE_UNUSED mgCFrame& fr2)
{
	log_trace("SetUkiPose({}, {})", fmt::ptr(&fr1), fmt::ptr(&fr2));

	todo;
}

// 003105C0
//void CastingLure(MAYBE_UNUSED vec4& v)
//{
//	log_trace("CastingLure({})", fmt::ptr(&v));
//
//	todo;
//}

// 00310730
void EndCastingLure()
{
	log_trace("CastingLure()");

	CastingLureFlag = false;
	CastingLureTime = 0;
	AddLineSpeed = 0;
}

// 00310740
//bool CatchLine(MAYBE_UNUSED vec4& v, MAYBE_UNUSED f32 f)
//{
//	log_trace("CatchLine({}, {})", fmt::ptr(&v), f);
//
//	todo;
//	return false;
//}

// 00310890
//void SlowLineVelo(f32 multiplier)
//{
//	log_trace("SlowLineVelo({})", multiplier);
//
//	for (usize index = LineTop; index < LinePoint.size(); ++index)
//	{
//		LinePoint[index][2] *= multiplier;
//	}
//}

// 00310910
void ResetLineVelo()
{
	log_trace("ResetLineVelo()");

	todo;
}

// 003109D0
//void ResetLine(MAYBE_UNUSED vec4& v)
//{
//	log_trace("ResetLine({})", fmt::ptr(&v));
//
//	todo;
//}

// 00310B60
sint GetNextChanceCnt()
{
	log_trace("GetNextChanceCnt()");

	return rand() % 80 + 60;
}

// 00310BA0
//bool InitFishBattle()
//{
//	log_trace("InitFishBattle()");
//
//	stru_1F5EDB0 = LinePoint[LinePoint.size() - 1][0];
//	FishPoint = LinePoint[LinePoint.size() - 1][0];
//	stru_1F5ED70 = LinePoint[LinePoint.size() - 1][0];
//	stru_1F5ED80 = vec4(0.0f);
//
//	BattleLineDist = math::vector_distance(vec3(LinePoint[LinePoint.size() - 1][0]), vec3(LinePoint[4][0]));
//	NowFishSpeed = 0;
//	BattleFlag = true;
//	NowFishRot = 0.0f;
//	ActionChanceNextCnt = GetNextChanceCnt();
//	ActionChanceCnt = 0;
//	return true;
//}

// 00310C30
bool EndFishBattle()
{
	log_trace("EndFishBattle()");

	BattleFlag = false;
	ActionChanceNextCnt = 0;
	ActionChanceCnt = 0;
	return true;
}

// 00310C50
sint CheckRodActionChance(sint i, bool& pi)
{
	log_trace("CheckRodActionChance({}, {})", i, fmt::ptr(&pi));

	pi = false;

	if (!BattleFlag)
	{
		return 0;
	}

	if (ActionChanceCnt <= 0)
	{
		return 0;
	}

	int check = ActionChanceDir * i;

	if (check > 0)
	{
		return 1;
	}

	if (check < 0)
	{
		return -1;
	}

	pi = (BattleFlag ^ 0x1C) == 0;
	return -1;
}

// 00310CC0
void FishBattle(MAYBE_UNUSED CScene& scene, MAYBE_UNUSED CCPoly& poly, MAYBE_UNUSED sint i)
{
	log_trace("FishBattle({}, {}, {})", fmt::ptr(&scene), fmt::ptr(&poly), i);

	todo;
}

// 00311070
//void GetFishPosVelo(vec4& pos, vec4& velocity)
//{
//	log_trace("GetFishPosVelo({}, {})", fmt::ptr(&pos), fmt::ptr(&velocity));
//
//	pos = FishPoint;
//	velocity = stru_1F5ED80;
//}

// 003110A0
void BindFishObj()
{
	log_trace("BindFishObj()");

	todo;
}

// 00311290
void RodStep(MAYBE_UNUSED CScene& scene, MAYBE_UNUSED CCPoly& poly)
{
	log_trace("RodStep({}, {})", fmt::ptr(&scene), fmt::ptr(&poly));

	todo;
}

// 00312200
//void BindPosition(vec4& v1, vec4& v2, f32 f1, f32 f2)
//{
//	log_trace("BindPosition({}, {}, {}, {})", fmt::ptr(&v1), fmt::ptr(&v2), f1, f2);
//
//	vec4 var_10;
//	vec4 var_20;
//	vec4 var_30 = v1 - v2;
//	f32 f0 = math::vector_distance(vec3(var_30), vec3(0.0f));
//	f32 f21 = f0 - f1;
//	f32 f20 = f0;
//	f0 -= f2;
//	f0 *= f21;
//	var_20 = var_30 * (f0 / f20);
//	f0 = f2 * f21;
//	var_10 = var_30 * (f0 / f20);
//	v1 -= var_20;
//	v2 -= var_10;
//}

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
void InitLureObj(MAYBE_UNUSED sint i, MAYBE_UNUSED mgCFrame& frame)
{
	log_trace("InitLureObj({}, {})", i, fmt::ptr(&frame));

	todo;
}

// 00312D20
void InitUkiObj(MAYBE_UNUSED sint i, MAYBE_UNUSED mgCFrame& frame1, MAYBE_UNUSED mgCFrame& frame2)
{
	log_trace("InitUkiObj({}, {}, {})", i, fmt::ptr(&frame1), fmt::ptr(&frame2));

	todo;
}

// 00313570
//void ParaBlend(MAYBE_UNUSED vec4& v1, MAYBE_UNUSED f32 f1, MAYBE_UNUSED vec4& v2, MAYBE_UNUSED s32 i)
//{
//	log_trace("ParaBlend({}, {}, {}, {})", fmt::ptr(&v1), f1, fmt::ptr(&v2), i);
//
//	todo;
//}
