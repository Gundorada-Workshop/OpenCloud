#pragma once
#include <array>

#include "common/debug.h"
#include "common/types.h"

#include "dc2/collision.h"
#include "dc2/mg/mg_frame.h"
#include "dc2/scene.h"

// ~ 0030F9B0 - 00313770

struct SUnk1
{
	// 0
	//vec4* m_unk_field_0{ nullptr };
	// 4
	//vec4* m_unk_field_4{ nullptr };
	// 8
	float m_unk_field_8{ 0.0f };
	// C
	float m_unk_field_C{ 0.0f };
};

class CFishObj
{
public:
	// 003130B0
	void MovePoint(void);
	// 00313140
	void FloatPoint(float f);
	// 00313310
	void BindStep(void);
	// 00313380
	void Correct(CCPoly& poly, int i, float f);

	// 0
	usize m_unk_field_0{ 0 };
	// 10
	//std::array<std::array<vec4, 3>, 8> m_unk_field_10{};
	// 190
	usize m_unk_field_190{ 0 };
	// 194
	std::array<SUnk1, 6> m_unk_field_194{};
	// TODO more members
};

// 0030F9B0
void SetFishingMode(int fishing_mode);
// 0030F9C0
int GetFishingMode();
// 0030F9D0
void SetWaterLevel(float water_level);
// 0030F9E0
float GetWaterLevel(void);
// 0030F9F0
CFishObj* GetActiveHariObj(void);
// 0030FA20
CFishObj* GetActiveUkiObj(void);
// 0030FA50
void ExtendLine(float delta);
// 0030FC10
float GetNowLineLength(void);
// 0030FC60
float GetMinLineLength(void);
// 0030FC70
void InitRodPoint(mgCFrame& fr1, mgCFrame& fr2);
// 00310020
//void GetTriPose(matrix4& m1, matrix4& m2, vec4& v1);
// 003101F0
//void GetHariPos(vec4& v1, vec4& v2);
// 00310220
//void GetUkiPos(vec4& v1, vec4& v2);
// 00310250
void PullUki(float f);
// 00310270
void SetShowHari(bool enabled);
// 00310280
bool GetShowHari(void);
// 003102E0
void SetLurePose(mgCFrame& frame);
// 003103D0
void SetUkiPose(mgCFrame& fr1, mgCFrame& fr2);
// 003105C0
//void CastingLure(vec4& v);
// 00310730
void EndCastingLure(void);
// 00310740
//bool CatchLine(vec4& v, float f);
// 00310890
void SlowLineVelo(float f);
// 00310910
void ResetLineVelo(void);
// 003109D0
//void ResetLine(vec4& v);
// 00310B60
int GetNextChanceCnt(void);
// 00310BA0
bool InitFishBattle(void);
// 00310C30
bool EndFishBattle(void);
// 00310C50
int CheckRodActionChance(int i, int& pi);
// 00310CC0
void FishBattle(CScene& scene, CCPoly& poly, int i);
// 00311070
//void GetFishPosVelo(vec4& pos, vec4& velocity);
// 003110A0
void BindFishObj(void);
// 00311290
void RodStep(CScene& scene, CCPoly& poly);
// 00312200
//void BindPosition(vec4& v1, vec4& v2, float f1, float f2);
// 003122E0
void DrawFishingLine(void);
// 003125D0
void DrawFishingActionChance(void);
// 003128E0
void InitLureObj(int i, mgCFrame& frame);
// 00312D20
void InitUkiObj(int i, mgCFrame& frame1, mgCFrame& frame2);
// 00313570
//void ParaBlend(vec4& v1, float f1, vec4& v2, s32 i);