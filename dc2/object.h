#pragma once
#include "glm/glm.hpp"
#include "mg_frame.h"

// ~ 001699F0 - 0016A160

class CObject : public mgCObject
{
public:
	// VTABLE 00375670
	// 0  0
	// 4  0
	// 8  00138810 (mgCObject::ChangeParam)
	// C  00138820 (mgCObject::UseParam)
	// 10 00136190 (mgCObject::SetPosition)
	// 14 00136220 (mgCObject::SetPosition)
	// 18 00136260 (mgCObject::GetPosition)
	// 1C 00136270 (mgCObject::SetRotation)
	// 20 001362F0 (mgCObject::SetRotation)
	// 24 00136330 (mgCObject::GetRotation)
	// 28 00136340 (mgCObject::SetScale)
	// 2C 001363C0 (mgCObject::SetScale)
	// 30 00136400 (mgCObject::GetScale)
	// 34 00160B50
	virtual _UNKNOWNPOINTER Draw();
	// 38 00160B60
	virtual _UNKNOWNPOINTER DrawDirect();
	// 3C 00169DE0
	virtual void Initialize();
	// 40 00169DB0
	virtual bool PreDraw();
	// 44 00169C10
	virtual float GetCameraDist();
	// 48 00169AC0
	virtual bool FarClip(float distance, float* alpha_result);
	// 4C 00169D10
	virtual bool DrawStep();
	// 50 00169D60
	virtual float GetAlpha();
	// 54 00160B70
	virtual void Show(bool visible);
	// 58 0015F110
	virtual bool GetShow();
	// 5C 00160B80
	virtual void SetFarDist(float far_dist);
	// 60 00160B90
	virtual float GetFarDist();
	// 64 00160BA0
	virtual void SetNearDist(float near_dist);
	// 68 00160BB0
	virtual float GetNearDist();
	// 6C 00169C20
	virtual bool CheckDraw();
	// 70 00160BC0
	virtual void Copy(CObject& other, mgCMemory* mem);

	// 00161DA0
	CObject();
	// 001796E0
	CObject(CObject& other);
	// 0027C700
	// ????
	//CObject(CObject& other);

	// 50
	float m_far_dist;
	// 54
	bool m_fade_flag;
	// 58
	float m_alpha;
	// 5C
	float m_fade_delta;
	// 60
	float m_near_dist;
	// 64
	bool m_visible;
	// 68
	bool m_unk_field_68;
	
	// SIZE 0x6C
};

class CObjectFrame : public CObject
{
public:
	// VTABLE 003755F0
	// 0  0
	// 4  0
	// 8  00138810 (mgCObject::ChangeParam)
	// C  00138820 (mgCObject::UseParam)
	// 10 00136190 (mgCObject::SetPosition)
	// 14 00136220 (mgCObject::SetPosition)
	// 18 00136260 (mgCObject::GetPosition)
	// 1C 00136270 (mgCObject::SetRotation)
	// 20 001362F0 (mgCObject::SetRotation)
	// 24 00136330 (mgCObject::GetRotation)
	// 28 00136340 (mgCObject::SetScale)
	// 2C 001363C0 (mgCObject::SetScale)
	// 30 00136400 (mgCObject::GetScale)
	// 34 00169FD0
	virtual _UNKNOWNPOINTER Draw();
	// 38 0016A010
	virtual _UNKNOWNPOINTER DrawDirect();
	// 3C 0016A130
	virtual void Initialize();
	// 40 00169F30
	virtual bool PreDraw();
	// 44 00169F00
	virtual float GetCameraDist();
	// 48 00169AC0 (CObject::FarClip)
	// 4C 00169EF0
	virtual bool DrawStep();
	// 50 00169D60 (CObject::GetAlpha)
	// 54 00160B70 (CObject::Show)
	// 58 0015F110 (CObject::GetShow)
	// 5C 00160B80 (CObject::SetFarDist)
	// 60 00160B90 (CObject::GetFarDist)
	// 64 00160BA0 (CObject::SetNearDist)
	// 68 00160BB0 (CObject::GetNearDist)
	// 6C 00169C20 (CObject::CheckDraw)
	// 70 00160BC0 (CObject::Copy)
	// 74 00169E80
	void UpdatePosition();
	// 78 0016A050
	void Copy(CObjectFrame& other, mgCMemory* mem); // nice try we'll get em next time

	// 00162420
	CObjectFrame();

	mgCFrame* m_unk_field_70;

	// SIZE 0x74
};