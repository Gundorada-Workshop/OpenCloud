#include "common/debug.h"
#include "common/log.h"
#include "CScene.h"

set_log_channel("CScene");

void CSceneData::Initialize()
{
	log_trace("CSceneData::Initialize()");

	m_unk_field_0 = 0;
	m_unk_field_4 = 0;
	m_name[0] = '\0';
	m_unk_field_28 = -1;
	m_unk_field_2C = 0;
	m_unk_field_30 = 0;
}

bool CSceneCharacter::AssignData(CCharacter2& chara, char* name)
{
	log_trace("CSceneCharacter::AssignData({}, {})", fmt::ptr(&chara), name);

	todo;
	return false;
}

void CSceneCharacter::Initialize()
{
	log_trace("CSceneCharacter:Initialize()");

	m_unk_field_34 = 0;
	m_unk_field_38 = -1;
	m_unk_field_3C = -1;
	CSceneData::Initialize();
}

void CSceneMap::Initialize()
{
	log_trace("CSceneMap:Initialize()");

	m_unk_field_34 = 0;
	CSceneData::Initialize();
}

bool CSceneMap::AssignData(CMap& map, char* name)
{
	log_trace("CSceneMap::AssignData({}, {})", fmt::ptr(&map), name);

	todo;
	return false;
}

void CSceneMessage::Initialize()
{
	log_trace("CSceneMessage::Initialize()");

	m_unk_field_34 = 0;
	CSceneData::Initialize();
}

bool CSceneMessage::AssignData(ClsMes& message, char* name)
{
	log_trace("CSceneMessage::AssignData({}, {})", fmt::ptr(&message), name);

	todo;
	return false;
}

bool CSceneCamera::AssignData(mgCCamera& camera, char* name)
{
	log_trace("CSceneCamera::AssignData({}, {})", fmt::ptr(&camera), name);

	todo;
	return false;
}

void CSceneCamera::Initialize()
{
	log_trace("CSceneCamera::Initialize()");

	m_unk_field_34 = 0;
	CSceneData::Initialize();
}

bool CSceneSky::AssignData(CMapSky& sky, char* name)
{
	log_trace("CSceneSky::AssignData({}, {})", fmt::ptr(&sky), name);

	todo;
	return false;
}

void CSceneSky::Initialize()
{
	log_trace("CSceneSky::Initialize()");

	m_unk_field_34 = 0;
	CSceneData::Initialize();
}

void CSceneGameObj::Initialize()
{
	log_trace("CSceneGameObj::Initialize()");

	CSceneCharacter::Initialize();
}

void CSceneEffect::Initialize()
{
	log_trace("CSceneEffect::Initialize()");

	m_unk_field_34 = 0;
	CSceneData::Initialize();
}

bool CSceneEffect::AssignData(CEffectScriptMan& script_manager, char* name)
{
	log_trace("CSceneEffect::AssignData({}, {})", fmt::ptr(&script_manager), name);

	todo;
	return false;
}

void CScene::Initialize()
{
	log_trace("CScene::Initialize()");

	todo;
}