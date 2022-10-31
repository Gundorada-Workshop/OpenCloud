#include "CScene.h"

void CSceneData::Initialize(void)
{
	m_unk_field_0 = 0;
	m_unk_field_4 = 0;
	m_name[0] = '\0';
	m_unk_field_28 = -1;
	m_unk_field_2C = 0;
	m_unk_field_30 = 0;
}

bool CSceneCharacter::AssignData(CCharacter2* chara, char* name)
{
	todo;
	return false;
}

void CSceneCharacter::Initialize(void)
{
	m_unk_field_34 = 0;
	m_unk_field_38 = -1;
	m_unk_field_3C = -1;
	CSceneData::Initialize();
}

void CSceneMap::Initialize(void)
{
	m_unk_field_34 = 0;
	CSceneData::Initialize();
}

bool CSceneMap::AssignData(CMap* map, char* name)
{
	todo;
	return false;
}

void CSceneMessage::Initialize(void)
{
	m_unk_field_34 = 0;
	CSceneData::Initialize();
}

bool CSceneMessage::AssignData(ClsMes* message, char* name)
{
	todo;
	return false;
}

bool CSceneCamera::AssignData(mgCCamera* camera, char* name)
{
	todo;
	return false;
}

void CSceneCamera::Initialize(void)
{
	m_unk_field_34 = 0;
	CSceneData::Initialize();
}

bool CSceneSky::AssignData(CMapSky* sky, char* name)
{
	todo;
	return false;
}

void CSceneSky::Initialize(void)
{
	m_unk_field_34 = 0;
	CSceneData::Initialize();
}

void CSceneGameObj::Initialize(void)
{
	CSceneCharacter::Initialize();
}

void CSceneEffect::Initialize(void)
{
	m_unk_field_34 = 0;
	CSceneData::Initialize();
}

bool AssignData(CEffectScriptMan* script_manager, char* name)
{
	todo;
	return false;
}