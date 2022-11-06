#pragma once
#include "mg_frame.h"
#include "mg_memory.h"
#include "object.h"

// ~ 0016A140 - 0017C240

// TODO THIS FILE
class CDACollision {};

class CDynamicAnime;

class CCharacter2 : public CObjectFrame
{
public:
	// VTABLE 00375810
	// 0   0
	// 4   0
	// 8   00138810 (mgCObject::ChangeParam)
	// C   00138820 (mgCObject::UseParam)
	// 10  00172DE0
	virtual void SetPosition(glm::vec4& v);
	// 14  00172DE0
	virtual void SetPosition(float x, float y, float z);
	// 18  00136260 (mgCObject::GetPosition)
	// 1C  00136270 (mgCObject::SetRotation)
	// 20  001362F0 (mgCObject::SetRotation)
	// 24  00136330 (mgCObject::GetRotation)
	// 28  00136340 (mgCObject::SetScale)
	// 2C  001363C0 (mgCObject::SetScale)
	// 30  00136400 (mgCObject::GetScale)
	// 34  00172F60
	virtual _UNKNOWNPOINTER Draw();
	// 38  001731F0
	virtual _UNKNOWNPOINTER DrawDirect();
	// 3C  00175340
	virtual void Initialize();
	// 40  00169F30 (CObjectFrame::PreDraw)
	// 44  00173170
	virtual float GetCameraDist();
	// 48  00169AC0 (CObject::FarClip)
	// 4C  00173120
	virtual bool DrawStep();
	// 50  00169D60 (CObject::GetAlpha)
	// 54  00160B70 (CObject::Show)
	// 58  0015F110 (CObject::GetShow)
	// 5C  00160B80 (CObject::SetFarDist)
	// 60  00160B90 (CObject::GetFarDist)
	// 64  00160BA0 (CObject::SetNearDist)
	// 68  00160BB0 (CObject::GetNearDist)
	// 6C  00169C20 (CObject::CheckDraw)
	// 70  00160BC0 (CObject::Copy)
	// 74  00169E80 (CObjectFrame::UpdatePosition)
	// 78  0016A050 (CObjectFrame::Copy)
	// 7C  001751D0
	virtual void LoadPack(void* file_buf, char* file_name, mgCMemory* mem1, mgCMemory* mem2, mgCMemory* mem3, _DWORD i, CCharacter2* character2);
	// 80  00175200
	virtual void LoadPackNoLine(void* file_buf, char* file_name, mgCMemory* mem1, mgCMemory* mem2, mgCMemory* mem3, _DWORD i, CCharacter2* character2);
	// 84  00175230
	virtual void LoadChrFile(void* file_buf, char* file_name, mgCMemory* mem1, mgCMemory* mem2, mgCMemory* mem3, _DWORD i, CCharacter2* character2, bool b);
	// 88  00168410
	virtual int GetMotionStatus();
	// 8C  00168420
	virtual _UNKNOWNPOINTER GetNowMotionName();
	// 90  001738C0
	virtual bool CheckMotionEnd();
	// 94  00168440
	virtual float GetNowFrameWait();
	// 98  00173890
	virtual float GetChgStepWait();
	// 9C  00168450
	virtual void SetNowFrame(float now_frame);
	// A0  001739B0
	virtual void SetNowFrameWeight(float weight);
	// A4  00168460
	virtual float GetNowFrame();
	// A8  00175160
	virtual float GetWaitToFrame(const char* c, float f);
	// AC  00173930
	virtual void SetMotion(_DWORD i1, _DWORD i2);
	// B0  001739A0
	virtual void SetMotion(char* c, int i);
	// B4  00173870
	virtual void ResetMotion();
	// B8  00173860
	virtual void SetStep(float frame_step);
	// BC  00168470
	virtual float GetStep();
	// C0  00173840
	virtual float GetDefaultStep();
	// C4  00168480
	virtual void SetFadeFlag(bool flag);
	// C8  00168490
	virtual bool GetFadeFlag();
	// CC  00173610
	virtual _UNKNOWNPOINTER DrawShadowDirect();
	// D0  00174580
	virtual void NormalDrive();
	// D4  00173ED0
	virtual void Step();
	// D8  00174910
	virtual void ShadowStep();
	// DC  001743C0
	virtual void SetWind(float velocity, glm::vec4& direction);
	// E0  00174440
	virtual void ResetWind();
	// E4  001744A0
	virtual void SetFloor(float floor);
	// E8  00174520
	virtual void ResetFloor();
	// EC  00178C70
	virtual void Copy(CCharacter2& other, mgCMemory* memory);
	// F0  001684A0
	virtual s32 GetCopySize();
	// F4  00177CB0
	virtual void DrawEffect();

	// 00173A40
	void SetMotionPara(char* c, int i1, s32 i2);

	// 74 BEGIN

	// 118
	s32 m_unk_field_118;
	// 11C
	s32 m_unk_field_11C;

	// ?

	// 12C
	usize m_n_unk_field_130;
	// 130
	CDynamicAnime* m_unk_field_130;

	// 2C0
	mgCFrame* m_unk_field_2C0;

	// 368
	_DWORD m_unk_field_368;

	// ?

	// 374
	_UNKNOWNPOINTER m_now_motion_name;

	// 380
	usize m_unk_field_380;
	// 384
	// FIXME: this is an int, but would an enum type be better?
	int m_motion_status;
	// 388
	float m_now_frame;
	// 38C
	float m_now_frame_wait;
	// 390
	float m_frame_step;

	// ?

	// 3A4
	_DWORD m_unk_field_3A4;
	// 3A8
	_DWORD m_unk_field_3A8;

	// ?

	// 508
	float m_chg_step_wait;
};

class CDynamicAnime
{
public:
  void Load(const char* script, int script_size, mgCFrame* frame, mgCMemory* stack);
  void NewVertexTable(int, mgCMemory* stack);
  void NewBoundingBoxTable(int, mgCMemory* stack);
  void NewCollisionTable(int, mgCMemory* stack);
	// 00179E70
	void SetWind(float velocity, glm::vec4& direction);
	// 00179E80
	void ResetWind();
	// 00179E90
	void SetFloor(float floor);
	// 00179EA0
	void ResetFloor();

	// 68
	float m_wind_velocity;
	// 70
	glm::vec4 m_wind_direction;

	// ?

	// 88
	bool m_unk_field_88;
	// 8C
	float m_floor;

	// SIZE 0x90
};

class CActionChara : public CCharacter2
{
public:
	// TODO
};