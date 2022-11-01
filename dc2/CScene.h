#pragma once
#include <array>
#include "common/debug.h"
#include "common/types.h"
#include "CCharacter2.h"
#include "CDngFloorManager.h"


// <this file>.cpp: likely 00282AC0 to 00286074


// TODO
class CEffectScriptMan;
class CMap;
class CMapSky;
class ClsMes;
class mgCCamera;
class CMdsListSet {};
class CFadeInOut {};
class CFireRaster {};
class CThunderEffect {};


class CSceneData
{
public:
	void Initialize(void);

	// 0
	_UNKNOWN m_unk_field_0;
	// 4
	_UNKNOWN m_unk_field_4;
	// 8
	char m_name[32];
	// 28
	s32 m_unk_field_28;
	// 2C
	_UNKNOWN m_unk_field_2C;
	// 30
	_UNKNOWN m_unk_field_30;
};

class CSceneCharacter : CSceneData
{
public:
	// 00282AE0
	bool AssignData(CCharacter2* chara, char* name);
	// 00282B40
	void Initialize(void);

	// 34
	_UNKNOWN m_unk_field_34;
	// 38
	s32 m_unk_field_38;
	// 3C
	s32 m_unk_field_3C;
};

class CSceneMap : CSceneData
{
public:
	// 00282B60
	void Initialize(void);
	// 00282B70
	bool AssignData(CMap* map, char* name);

	// 34
	_UNKNOWN m_unk_field_34;
};

class CSceneMessage : CSceneData
{
public:
	// 00282BF0
	void Initialize(void);
	// 00282C00
	bool AssignData(ClsMes* message, char* name);

	// 34
	_UNKNOWN m_unk_field_34;
};

class CSceneCamera : CSceneData
{
public:
	// 00282C80
	bool AssignData(mgCCamera* camera, char* name);
	// 00282D00
	void Initialize(void);

	// 34
	_UNKNOWN m_unk_field_34;
};

class CSceneSky : CSceneData
{
public:
	// 00282D10
	bool AssignData(CMapSky* sky, char* name);
	// 00282D90
	void Initialize(void);

	// 34
	_UNKNOWN m_unk_field_34;
};

class CSceneGameObj : CSceneCharacter
{
public:
	// 00282DA0
	void Initialize(void);
};

class CSceneEffect : CSceneData
{
public:
	// 00282DB0
	void Initialize(void);
	// 00282DC0
	bool AssignData(CEffectScriptMan* script_manager, char* name);

	// 34
	_UNKNOWN m_unk_field_34;
};

class CScene
{
public:
	CScene();

	// 0
	usize m_unk_field_0;
	// 4
	_UNKNOWN m_unk_field_4;
	// 8
	std::array<_UNKNOWN, 12> m_unk_field_8;
	// 38
	_UNKNOWN m_unk_field_38;
	// 3C
	_UNKNOWN m_unk_field_3C;
	// 40
	usize m_unk_field_40;
	// 44
	std::array<CSceneCharacter, 128> m_unk_field_44;
	// 2044
	usize m_unk_field_2044;
	// 2048
	std::array<CSceneCamera, 8> m_unk_field_2048;
	// 2208
	usize m_unk_field_2208;
	// 220C
	std::array<CSceneMessage, 8> m_unk_field_220C;
	// 23D0
	CMdsListSet m_unk_field_23D0;

	// ?

	// 24F0
	CFireRaster m_unk_field_24F0;
	// 27E0
	usize m_unk_field_27E0;
	// 27E4
	std::array<CSceneMap, 4> m_unk_field_27E4;
	// 28C4
	usize m_unk_field_28C4;
	// 28C8
	std::array<CSceneSky, 4> m_unk_field_28C8;
	// 29A8
	usize m_unk_field_29A8;
	// 29AC
	std::array<CSceneGameObj, 4> m_unk_field_29AC;
	// 2AAC
	usize m_unk_field_2AAC;
	// 2AB0
	std::array<CSceneEffect, 8> m_unk_field_2AB0;
	// 2C70
	CFadeInOut m_unk_field_2C70;
	// 2CA0
	_UNKNOWN m_unk_field_2CA0;

	// ?

	// 2E50
	_UNKNOWN m_unk_field_2E50;
	// 2E54
	_UNKNOWN m_unk_field_2E54;
	// 2E58
	_UNKNOWN m_unk_field_2E58;
	// 2E5C
	_UNKNOWN m_unk_field_2E5C;

	// ?

	// 2E70
	_UNKNOWN m_unk_field_2E70;
	// 2E74
	_UNKNOWN m_unk_field_2E74;
	// 2E78
	_UNKNOWN m_unk_field_2E78;
	// 2E7C
	_UNKNOWN m_unk_field_2E7C;
	// 2E80
	_UNKNOWN m_unk_field_2E80;
	// 2E84
	_UNKNOWN m_unk_field_2E84;

	// ?

	// 2F64
	_UNKNOWN m_unk_field_2F64;
	// 2F70
	_UNKNOWN m_unk_field_2F70;
	// 2F74
	_UNKNOWN m_unk_field_2F74;
	// 2F78
	_UNKNOWN m_unk_field_2F78;
	// 2F80
	alignas(16) vec4 m_unk_field_2F80;
	// 2F90
	_UNKNOWN m_unk_field_2F90;
	// 2F94
	_UNKNOWN m_unk_field_2F94;

	// ?

	// 2FA4
	CDngFloorManager m_unk_field_2FA4;
	// 2FB4
	_UNKNOWN m_unk_field_2FB4;

	// ?

	// 2FD4
	_UNKNOWN m_unk_field_2FD4;

	// ?

	// 2FFC
	_UNKNOWN m_unk_field_2FFC;

	// ?

	// 3008
	_UNKNOWN m_unk_field_3008;
	// 300C
	_UNKNOWN m_unk_field_300C;
	// 3010
	_UNKNOWN m_unk_field_3010;

	// ?

	// 3E60
	_UNKNOWN m_unk_field_3E60;
	// 3E64
	_UNKNOWN m_unk_field_3E64;
	// 3E70
	CThunderEffect m_unk_field_3E70;
};
