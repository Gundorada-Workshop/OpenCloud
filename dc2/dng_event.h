#pragma once
#include "character.h"
#include "dng_main.h"

// ~ 0028AFC0 - 002912F0

// TODO THIS FILE
class CStartupEpisodeTitle {};
struct MessageTaskManager {};
class CRedMarkModel {};
class CTreasureBox {};
class CTreasureBoxManager {};
class CMarker {};
class CEventSprite {};
class CEventSpriteMother {};
class CEventSprite2 {};

class CGeoStone : public CCharacter2
{
public:
	// VTABLE 00376040
	// 0   0
	// 4   0
	// 8   00138810 (mgCObject::ChangeParam)
	// C   00138820 (mgCObject::UseParam)
	// 10  00172DE0 (CCharacter2::SetPosition)
	// 14  00172DE0 (CCharacter2::SetPosition)
	// 18  00136260 (mgCObject::GetPosition)
	// 1C  00136270 (mgCObject::SetRotation)
	// 20  001362F0 (mgCObject::SetRotation)
	// 24  00136330 (mgCObject::GetRotation)
	// 28  00136340 (mgCObject::SetScale)
	// 2C  001363C0 (mgCObject::SetScale)
	// 30  00136400 (mgCObject::GetScale)
	// 34  00172F60 (CCharacter2::Draw)
	// 38  001731F0 (CCharacter2::DrawDirect)
	// 3C  0028BD20
	virtual void Initialize();
	// 40  00169F30 (CObjectFrame::PreDraw)
	// 44  00173170 (CCharacter2::GetCameraDist)
	// 48  00169AC0 (CObject::FarClip)
	// 4C  00173120 (CCharacter2::DrawStep)
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
	// 7C  001751D0 (CCharacter2::LoadPack)
	// 80  00175200 (CCharacter2::LoadPackNoLine)
	// 84  00175230 (CCharacter2::LoadChrFile)
	// 88  00168410 (CCharacter2::GetMotionStatus)
	// 8C  00168420 (CCharacter2::GetNowMotionName)
	// 90  001738C0 (CCharacter2::CheckMotionEnd)
	// 94  00168440 (CCharacter2::GetNowFrameWait)
	// 98  00173890 (CCharacter2::GetChgStepWait)
	// 9C  00168450 (CCharacter2::SetNowFrame)
	// A0  001739B0 (CCharacter2::SetNowFrameWeight)
	// A4  00168460 (CCharacter2::GetNowFrame)
	// A8  00175160 (CCharacter2::GetWaitToFrame)
	// AC  00173930 (CCharacter2::SetMotion)
	// B0  001739A0 (CCharacter2::SetMotion)
	// B4  00173870 (CCharacter2::ResetMotion)
	// B8  00173860 (CCharacter2::SetStep)
	// BC  00168470 (CCharacter2::GetStep)
	// C0  00173840 (CCharacter2::GetDefaultStep)
	// C4  00168480 (CCharacter2::SetFadeFlag)
	// C8  00168490 (CCharacter2::GetFadeFlag)
	// CC  00173610 (CCharacter2::DrawShadowDirect)
	// D0  00174580 (CCharacter2::NormalDrive)
	// D4  00173ED0 (CCharacter2::Step)
	// D8  00174910 (CCharacter2::ShadowStep)
	// DC  001743C0 (CCharacter2::SetWind)
	// E0  00174440 (CCharacter2::ResetWind)
	// E4  001744A0 (CCharacter2::SetFloor)
	// E8  00174520 (CCharacter2::ResetFloor)
	// EC  00178C70 (CCharacter2::Copy)
	// F0  001684A0 (CCharacter2::GetCopySize)
	// F4  00177CB0 (CCharacter2::DrawEffect)

	// 0028BCA0
	bool CheckEvent(glm::vec4& position);
	// 0028BA80
	void GeoDraw(glm::vec4& position);
	// 0028BB70
	void DrawMiniMapSymbol(CMiniMapSymbol* mini_map_symbol);
	// 0028BBC0
	void SetFlag(bool flag);
	// 0028BC20
	void GeoStep();

	// BEGIN 0x660
  // 660
  bool m_flag;
  // 664
	float m_height_offset_sine;
  // 668
	bool m_unk_field_668;

  // ALIGNED SIZE 0x670
};

class CRandomCircle
{
public:

  // 40
  CCharacter2 m_unk_field_40;
  // SIZE 0x6A0
};