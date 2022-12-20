#pragma once
#include <glm/glm.hpp>

#include "dc2/mg/mg_frame.h"

// ~ 001699F0 - 0016A160

class CObject : public mgCObject
{
public:
	// 34 00160B50
	virtual unkptr Draw() override;
	// 38 00160B60
	virtual unkptr DrawDirect() override;
	// 3C 00169DE0
	virtual void Initialize() override;
	// 40 00169DB0
	virtual bool PreDraw();
	// 44 00169C10
	virtual f32 GetCameraDist();
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

	// 50
	float m_far_dist{ -1.0f };
	// 54
	bool m_fade_flag{ false };
	// 58
	float m_alpha{ -1.0f };
	// 5C
	float m_fade_delta{ 0.2f };
	// 60
	float m_near_dist{ -1.0f };
	// 64
	bool m_visible{ true };
	// 68
	bool m_unk_field_68{ false };
	
	// SIZE 0x6C
};

class CObjectFrame : public CObject
{
public:
	// 34 00169FD0
	virtual unkptr Draw() override;
	// 38 0016A010
	virtual unkptr DrawDirect() override;
	// 3C 0016A130
	virtual void Initialize() override;
	// 40 00169F30
	virtual bool PreDraw() override;
	// 44 00169F00
	virtual f32 GetCameraDist() override;
	// 4C 00169EF0
	virtual bool DrawStep() override;
	// 74 00169E80
	void UpdatePosition();
	// 78 0016A050
	void Copy(CObjectFrame& other, mgCMemory* mem); // nice try we'll get em next time

	// 70
	mgCFrame* m_frame{ nullptr };

	// SIZE 0x74
};