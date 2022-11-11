#pragma once
#include "mg_lib.h"
#include "object.h"

// ~ 0016A140 - 0017C240

// TODO THIS FILE
class CDACollision {};

class CDynamicAnime;
class CSwordAfterEffect;

struct SEntryEffect
{
	_DWORD m_unk_field_0;
	_DWORD m_unk_field_4;
	_DWORD m_unk_field_8;
};

class CCharacter2 : public CObjectFrame
{
public:
	// 10  00172DE0
	virtual void SetPosition(glm::vec4& v);
	// 14  00172DE0
	virtual void SetPosition(float x, float y, float z);
	// 34  00172F60
	virtual _UNKNOWNPOINTER Draw();
	// 38  001731F0
	virtual _UNKNOWNPOINTER DrawDirect();
	// 3C  00175340
	virtual void Initialize();
	// 44  00173170
	virtual float GetCameraDist();
	// 4C  00173120
	virtual bool DrawStep();
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

	CCharacter2();

	// 80
	f32 m_unk_field_80{ 0.0f };
	// 84
	f32 m_unk_field_84{ 0.0f };
	// 88
	f32 m_unk_field_88{ 0.0f };
	// 8C
	f32 m_unk_field_8C{ 0.0f };
	// 90
	f32 m_unk_field_90{ 0.0f };
	// 94
	f32 m_unk_field_94{ 0.0f };
	// 98
	f32 m_unk_field_98{ 0.0f };
	// 9C
	f32 m_unk_field_9C{ 0.0f };
	// A0
	f32 m_unk_field_A0{ 0.0f };
	// B0
	glm::mat4 m_unk_field_B0{ 1.0f };
	// F0
	std::array<char, 0x10> m_unk_field_F0{ 0 };
	// 100
	f32 m_unk_field_100{ 1.0f };
	// 104
	_DWORD m_unk_field_104{ 0 };
	// 108
	_DWORD m_unk_field_108{ 0 };
	// 10C
	f32 m_unk_field_10C{ 0.0f };
	// 110
	f32 m_unk_field_110{ 0.0f };
	// 114
	f32 m_unk_field_114{ 0.0f };
	// 118
	s32 m_unk_field_118{ 0 };
	// 11C
	s32 m_unk_field_11C{ 0 };
	// 120
	s16 m_unk_field_120{ 0 };
	// 124
	_UNKNOWNPOINTER m_unk_field_124{ nullptr };
	// 128
	s32 m_unk_field_128{ 0 };
	// 12C
	usize m_n_unk_field_130{ 0 };
	// 130
	CDynamicAnime* m_unk_field_130{ nullptr };
	// 134
	_DWORD m_unk_field_134{ 0 };
	// 138
	bool m_unk_field_138{ false };
	// 13C
	_DWORD m_unk_field_13C{ 0 };
	// 140
	std::array<glm::ivec4, 0x18> m_unk_field_140{};
	// 2C0
	mgCFrame* m_unk_field_2C0{ nullptr };
	// 2C4
	_DWORD m_unk_field_2C4{ 0 };
	// 2C8
	_DWORD m_unk_field_2C8{ 0 };
	// 2CC
	_DWORD m_unk_field_2CC{ 0 };
	// 2D0
	_DWORD m_unk_field_2D0{ 0 };
	// 2D4
	_DWORD m_unk_field_2D4{ 0 };
	// 2D8
	_DWORD m_unk_field_2D8{ 0 };
	// 2DC
	_DWORD m_unk_field_2DC{ 0 };
	// 2E0
	_DWORD m_unk_field_2E0{ 0 };
	// 2E4
	_DWORD m_unk_field_2E4{ 0 };
	// 2E8
	std::array<_DWORD, 0x18> m_unk_field_2E8{ 0 };
	// 348
	_DWORD m_unk_field_348{ 0 };
	// 34C
	_DWORD m_unk_field_34C{ 0 };
	// 350
	_DWORD m_unk_field_350{ 0 };
	// 354
	s32 m_unk_field_354{ -1 };
	// 358
	bool m_unk_field_358{ true };
	// 35C
	_DWORD m_unk_field_35C{ 0 };
	// 360
	_DWORD m_unk_field_360{ 0 };
	// 364
	_DWORD m_unk_field_364{ 0 };
	// 368
	_DWORD m_unk_field_368{ 0 };
	// 36C
	u32 m_unk_field_36C{ 0 };
	// 370
	usize m_unk_field_370{ 0 };
	// 374
	_UNKNOWNPOINTER m_now_motion_name{ nullptr };
	// 378
	bool m_unk_field_378{ false };
	// 37C
	u32 m_unk_field_37C{ 0 };
	// 380
	usize m_unk_field_380{ 0 };
	// 384
	// FIXME: this is an int, but would an enum type be better?
	int m_motion_status{ 0 };
	// 388
	f32 m_now_frame{ 0.0f };
	// 38C
	f32 m_now_frame_wait{ 0.0f };
	// 390
	f32 m_frame_step{ 0.0f };
	// 394
	_UNKNOWNPOINTER m_unk_field_394;
	// 398
	u32 m_unk_field_398{ 0 };
	// 39C
	usize m_unk_field_39C{ 0 };
	// 3A0
	f32 m_unk_field_3A0{ 0.0f };
	// 3A4
	_DWORD m_unk_field_3A4{ 0 };
	// 3A8
	_DWORD m_unk_field_3A8{ 0 };
	// 3AC
	_UNKNOWNPOINTER m_unk_field_3AC{ nullptr };
	// 3B0
	u32 m_unk_field_3B0{ 0 };
	// 3B4
	s32 m_unk_field_3B4{ 0 };
	// 3B8
	s32 m_unk_field_3B8{ 0 };
	// 3BC
	bool m_unk_field_3BC{ false };
	// 3C0
	std::array<_DWORD, 20> m_unk_field_3C0{ 0 };

	// ?

	// 460
	_UNKNOWNSTRUCT(0xA0) m_unk_field_460 { 0 };
	// 500
	_DWORD m_unk_field_500{ 0 };
	// 504
	_DWORD m_unk_field_504{ 0 };
	// 508
	f32 m_chg_step_wait{ 0.0f };
	// 50C
	f32 m_unk_field_50C{ 0.0f };
	// 510
	_DWORD m_unk_field_510{ 0 };
	// 514
	_DWORD m_unk_field_514{ 0 };
	// 518
	_DWORD m_unk_field_518{ 0 };
	// 51C
	_DWORD m_unk_field_51C{ 0 };
	// 520
	_DWORD m_unk_field_520{ 0 };
	// 524
	_DWORD m_unk_field_524{ 0 };
	// 528
	_DWORD m_unk_field_528{ 0 };
	// 52C
	_DWORD m_unk_field_52C{ 0 };
	// 530
	_DWORD m_unk_field_530{ 0 };
	// 534
	_DWORD m_unk_field_534{ 0 };
	// 538
	_DWORD m_unk_field_538{ 0 };
	// 53C
	_DWORD m_unk_field_53C{ 0 };
	// 540
	_DWORD m_unk_field_540{ 0 };
	// 544
	_DWORD m_unk_field_544{ 0 };
	// 548
	_DWORD m_unk_field_548{ 0 };
	// 54C
	_DWORD m_unk_field_54C{ 0 };
	// 550
	_DWORD m_unk_field_550{ 0 };
	// 554
	_DWORD m_unk_field_554{ 0 };
	// 558
	_DWORD m_unk_field_558{ 0 };
	// 55C
	_DWORD m_unk_field_55C{ 0 };
	// 560
	_DWORD m_unk_field_560{ 0 };
	// 564
	_DWORD m_unk_field_564{ 0 };
	// 568
	_DWORD m_unk_field_568{ 0 };
	// 56C
	_DWORD m_unk_field_56C{ 0 };
	// 570
	std::array<CSwordAfterEffect*, 3> m_sword_after_effects;
	// 57C
	_DWORD m_unk_field_57C{ 0 };
	// 580
	_DWORD m_unk_field_580{ 0 };
	// 584
	_DWORD m_unk_field_584{ 0 };
	// 588
	_DWORD m_unk_field_588{ 0 };
	// 58C
	_DWORD m_unk_field_58C{ 0 };
	// 590
	_DWORD m_unk_field_590{ 0 };
	// 594
	_DWORD m_unk_field_594{ 0 };
	// 598
	_DWORD m_unk_field_598{ 0 };
	// 59C
	_DWORD m_unk_field_59C{ 0 };
	// 5A0
	_DWORD m_unk_field_5A0{ 0 };
	// 5A4
	_DWORD m_unk_field_5A4{ 0 };
	// 5A8
	_DWORD m_unk_field_5A8{ 0 };
	// 5AC
	_DWORD m_unk_field_5AC{ 0 };
	// 5B0
	_DWORD m_unk_field_5B0{ 0 };
	// 5B4
	_DWORD m_unk_field_5B4{ 0 };
	// 5B8
	_DWORD m_unk_field_5B8{ 0 };
	// 5BC
	_DWORD m_unk_field_5BC{ 0 };
	// 5C0
	_DWORD m_unk_field_5C0{ 0 };
	// 5C4
	_DWORD m_unk_field_5C4{ 0 };
	// 5C8
	_DWORD m_unk_field_5C8{ 0 };
	// 5CC
	_DWORD m_unk_field_5CC{ 0 };
	// 5D0
	_DWORD m_unk_field_5D0{ 0 };
	// 5D4
	_DWORD m_unk_field_5D4{ 0 };
	// 5D8
	_DWORD m_unk_field_5D8{ 0 };
	// 5DC
	_DWORD m_unk_field_5DC{ 0 };
	// 5E0
	_DWORD m_unk_field_5E0{ 0 };
	// 5E4
	_DWORD m_unk_field_5E4{ 0 };
	// 5E8
	_DWORD m_unk_field_5E8{ 0 };
	// 5EC
	std::array<SEntryEffect, 8> m_entry_effects{};
	// 64C
	_DWORD m_unk_field_64C{ 0 };
	// 650
	_DWORD m_unk_field_650{ 0 };
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