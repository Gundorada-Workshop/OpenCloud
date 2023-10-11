#include "common/debug.h"
#include "common/helpers.h"
#include "common/log.h"

#include "engine/character/CCharacter2.h"

#include "engine/scene.h"
#include "engine/userdata.h"

set_log_channel("scene");

using namespace common;

// 00285150
void SCN_LOADMAP_INFO2::Initialize()
{
	memset(this, 0, sizeof(this));
}

// 00282AE0
bool CSceneCharacter::AssignData(CCharacter2* chara, const char* name)
{
	log_trace("CSceneCharacter::AssignData({}, {})", fmt::ptr(chara), name);

	if (name == nullptr || chara == nullptr)
	{
		return false;
	}

	m_status = ESceneDataStatus::Initial;
	m_character = chara;
	common::strings::safe_str_to_array(m_name, name);

	m_status |= ESceneDataStatus::Assigned;
	
	return true;
}

// 00282B70
bool CSceneMap::AssignData(CMap* map, const char* name)
{
	log_trace("CSceneMap::AssignData({}, {})", fmt::ptr(map), name);

	if (name == nullptr || map == nullptr)
	{
		return false;
	}

	new (this) CSceneMap();

	m_status = ESceneDataStatus::Initial;
	m_map = map;
	common::strings::safe_str_to_array(m_name, name);

	m_status |= ESceneDataStatus::Assigned;

	return true;
}

// 00282C00
bool CSceneMessage::AssignData(ClsMes* message, const char* name)
{
	log_trace("CSceneMessage::AssignData({}, {})", fmt::ptr(message), name);

	if (message == nullptr)
	{
		return false;
	}

	new (this) CSceneMessage();

	m_status = ESceneDataStatus::Initial;
	m_message = message;

	if (name != nullptr)
	{
		common::strings::safe_str_to_array(m_name, name);
	}
	else
	{
		m_name[0] = '\0';
	}

	m_status |= ESceneDataStatus::Assigned;

	return true;
}

// 00282C80
bool CSceneCamera::AssignData(mgCCamera* camera, const char* name)
{
	log_trace("CSceneCamera::AssignData({}, {})", fmt::ptr(camera), name);

	if (camera == nullptr)
	{
		return false;
	}

	new (this) CSceneCamera();

	m_status = ESceneDataStatus::Initial;
	m_camera = camera;

	if (name != nullptr)
	{
		common::strings::safe_str_to_array(m_name, name);
	}
	else
	{
		m_name[0] = '\0';
	}

	m_status |= ESceneDataStatus::Assigned;

	return true;
}

// 00282D10
bool CSceneSky::AssignData(CMapSky* sky, const char* name)
{
	log_trace("CSceneSky::AssignData({}, {})", fmt::ptr(sky), name);

	if (sky == nullptr)
	{
		return false;
	}

	new (this) CSceneSky();

	m_status = ESceneDataStatus::Initial;
	m_sky = sky;

	if (name != nullptr)
	{
		common::strings::safe_str_to_array(m_name, name);
	}
	else
	{
		m_name[0] = '\0';
	}

	m_status |= ESceneDataStatus::Assigned;

	return true;
}

// 00282DC0
bool CSceneEffect::AssignData(CEffectScriptMan* script_manager, const char* name)
{
	log_trace("CSceneEffect::AssignData({}, {})", fmt::ptr(script_manager), name);

	if (script_manager == nullptr)
	{
		return false;
	}

	new (this) CSceneEffect();

	m_status = ESceneDataStatus::Initial;
	m_effect_script_manager = script_manager;

	if (name != nullptr)
	{
		common::strings::safe_str_to_array(m_name, name);
	}
	else
	{
		m_name[0] = '\0';
	}

	m_status |= ESceneDataStatus::Assigned;

	return true;
}

// 00282E40
CScene::CScene()
{
	log_trace("CScene::{}()", __func__);

	m_mds_list_set.Initialize();
	//m_fade_in_out.Initialize();
	m_scn_loadmap_info.Initialize();

	for (auto& villager_data : m_villager_manager.m_villager_data)
	{
		villager_data.Initialize();
	}

	m_villager_manager.Initialize();

	m_loop_se_manager.Initialize();

	m_fire_raster.Initialize();
	m_thunder_effect.Initialize();
	m_battle_area_scene.m_dng_floor_manager.Initialize();
}

// 00283150
void CScene::SetStack(ssize stack_index, mgCMemory& stack)
{
	log_trace("CScene::{}({}, {})", __func__, stack_index, fmt::ptr(&stack));

	if (stack_index < 0 || stack_index >= static_cast<ssize>(m_stacks.size()))
	{
		return;
	}

	m_stacks[stack_index] = &stack;
}

// 00283150
mgCMemory* CScene::GetStack(ssize stack_index)
{
	log_trace("CScene::{}({})", __func__, stack_index);

	if (stack_index < 0 || stack_index >= static_cast<ssize>(m_stacks.size()))
	{
		return nullptr;
	}

	return m_stacks[stack_index];
}

// 002831D0
void CScene::ClearStack(ssize stack_index)
{
	log_trace("CScene::{}({})", __func__, stack_index);

	for (auto i = stack_index; i < static_cast<ssize>(m_stacks.size()); ++i)
	{
		if (m_stacks[i] != nullptr)
		{
			m_stacks[i]->m_stack_current_allocated = 0;
			m_stacks[i]->m_unk_field_1C = false;

			if (stack_index != i)
			{
				m_stacks[i]->stSetBuffer(nullptr, 0);
			}
		}
	}
}

// 00283270
void CScene::AssignStack(ssize stack_index)
{
	log_trace("CScene::{}({})", __func__, stack_index);

	if (stack_index < 2)
	{
		return;
	}

	mgCMemory* current_stack = m_stacks[stack_index];
	mgCMemory* previous_stack = m_stacks[stack_index - 1];
	if (previous_stack->m_stack_max_allocated < 0)
	{
		AssignStack(stack_index - 1);
	}

	previous_stack->Align64();
	previous_stack->m_unk_field_1C = true;

	usize max_allocated = previous_stack->m_stack_max_allocated;
	usize current_allocated = previous_stack->m_stack_current_allocated;
	usize buf_size = max_allocated - current_allocated;
	void* new_stack_start = reinterpret_cast<void*>(reinterpret_cast<uptr>(previous_stack->m_stack_start) + current_allocated * 0x10);
	current_stack->stSetBuffer(new_stack_start, buf_size);

	current_stack->m_stack_current_allocated = 0;
	current_stack->m_unk_field_1C = false;
	m_n_stacks_length = stack_index;
}

// 00283340
CSceneCharacter* CScene::GetSceneCharacter(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	if (character_index < 0 || character_index >= static_cast<ssize>(m_characters.size()))
	{
		return nullptr;
	}

	return &m_characters[character_index];
}

// 00283340
CSceneMap* CScene::GetSceneMap(ssize map_index)
{
	log_trace("CScene::{}({})", __func__, map_index);

	if (map_index < 0 || map_index >= static_cast<ssize>(m_maps.size()))
	{
		return nullptr;
	}

	return &m_maps[map_index];
}

// 002833C0
CSceneMessage* CScene::GetSceneMessage(ssize message_index)
{
	log_trace("CScene::{}({})", __func__, message_index);

	if (message_index < 0 || message_index >= static_cast<ssize>(m_messages.size()))
	{
		return nullptr;
	}

	return &m_messages[message_index];
}

// 00283400
CSceneCamera* CScene::GetSceneCamera(ssize camera_index)
{
	log_trace("CScene::{}({})", __func__, camera_index);

	if (camera_index < 0 || camera_index >= static_cast<ssize>(m_cameras.size()))
	{
		return nullptr;
	}

	return &m_cameras[camera_index];
}

// 00283440
CSceneSky* CScene::GetSceneSky(ssize sky_index)
{
	log_trace("CScene::{}({})", __func__, sky_index);

	if (sky_index < 0 || sky_index >= static_cast<ssize>(m_skies.size()))
	{
		return nullptr;
	}

	return &m_skies[sky_index];
}

// 00283480
CSceneGameObj* CScene::GetSceneGameObj(ssize gameobj_index)
{
	log_trace("CScene::{}({})", __func__, gameobj_index);

	if (gameobj_index < 0 || gameobj_index >= static_cast<ssize>(m_gameobjs.size()))
	{
		return nullptr;
	}

	return &m_gameobjs[gameobj_index];
}

// 002834C0
CSceneEffect* CScene::GetSceneEffect(ssize effect_index)
{
	log_trace("CScene::{}({})", __func__, effect_index);

	if (effect_index < 0 || effect_index >= static_cast<ssize>(m_effects.size()))
	{
		return nullptr;
	}

	return &m_effects[effect_index];
}

// 00283500
bool CScene::CheckIMGName(MAYBE_UNUSED ssize map_index, MAYBE_UNUSED const char* img_name)
{
	log_trace("CScene::{}({}, {})", __func__, map_index, img_name);

	todo;
	return false;
}

// 002835D0
bool CScene::CheckMDSName(MAYBE_UNUSED ssize map_index, MAYBE_UNUSED const char* mds_name)
{
	log_trace("CScene::{}({}, {})", __func__, map_index, mds_name);

	todo;
	return false;
}

// 002836A0
CSceneData* CScene::GetData(ESceneDataType data_type, ssize index)
{
	log_trace("CScene::{}({}, {})", __func__, data_type, index);

	switch (data_type)
	{
		case ESceneDataType::Character:
			return GetSceneCharacter(index);
		case ESceneDataType::Map:
			return GetSceneMap(index);
		case ESceneDataType::Message:
			return GetSceneMessage(index);
		case ESceneDataType::Camera:
			return GetSceneCamera(index);
		case ESceneDataType::GameObj_6:
		case ESceneDataType::GameObj_7:
			return GetSceneGameObj(index);
		default:
			return nullptr;
	}
}

// 00283740
s32 CScene::AssignCamera(ssize camera_index, mgCCamera* camera, const char* name)
{
	log_trace("CScene::{}({}, {}, {})", __func__, camera_index, fmt::ptr(camera), name);

	if (camera_index < 0)
	{
		// NOTE: There's more code here, but it doesn't appear to mutate any state
		// and always leads back to the same path, so it appears to effectively be a no-op.
		return -1;
	}

	CSceneCamera* scene_camera = GetSceneCamera(camera_index);
	if (scene_camera == nullptr)
	{
		return -1;
	}

	if (name == nullptr)
	{
		name = "no_name";
	}

	if (m_active_cmrid < 0)
	{
		m_active_cmrid = static_cast<s32>(camera_index);
	}

	bool result = scene_camera->AssignData(camera, name);
	if (!result)
	{
		return -1;
	}

	return static_cast<s32>(camera_index);
}

// 00283820
ssize CScene::GetCameraID(const char* name)
{
	log_trace("CScene::{}({})", __func__, name);

	if (name == nullptr)
	{
		return -1;
	}

	for (int i = 0; i < m_cameras.size(); ++i)
	{
		CSceneCamera* camera = GetSceneCamera(i);
		if (camera == nullptr)
		{
			continue;
		}
		if (camera->m_status == ESceneDataStatus::Initial)
		{
			continue;
		}
		if (strcmp(name, camera->m_name.data()) == 0)
		{
			return i;
		}
	}

	return -1;
}

// 002838C0
mgCCamera* CScene::GetCamera(ssize camera_index)
{
	log_trace("CScene::{}({})", __func__, camera_index);

	CSceneCamera* scene_camera = GetSceneCamera(camera_index);
	if (scene_camera == nullptr)
	{
		return nullptr;
	}

	if (scene_camera->m_status == ESceneDataStatus::Initial)
	{
		return nullptr;
	}
	
	return scene_camera->m_camera;
}

// 00283910
s32 CScene::AssignMessage(ssize message_index, ClsMes* message, const char* name)
{
	log_trace("CScene::{}({}, {}, {})", __func__, message_index, fmt::ptr(message), name);

	if (message_index < 0)
	{
		// NOTE: There's more code here, but it doesn't appear to mutate any state
		// and always leads back to the same path, so it appears to effectively be a no-op.
		return -1;
	}

	CSceneMessage* scene_message = GetSceneMessage(message_index);
	if (scene_message == nullptr)
	{
		return -1;
	}

	if (name == nullptr)
	{
		name = "no_name";
	}

	bool result = scene_message->AssignData(message, name);
	if (!result)
	{
		return -1;
	}

	return static_cast<s32>(message_index);
}

// 002839E0
ClsMes* CScene::GetMessage(ssize message_index)
{
	log_trace("CScene::{}({})", __func__, message_index);

	CSceneMessage* scene_message = GetSceneMessage(message_index);
	if (scene_message == nullptr)
	{
		return nullptr;
	}

	if (scene_message->m_status == ESceneDataStatus::Initial)
	{
		return nullptr;
	}

	return scene_message->m_message;
}

// 00283A30
s32 CScene::AssignChara(ssize character_index, CCharacter2* character, const char* name)
{
	log_trace("CScene::{}({}, {}, {})", __func__, character_index, fmt::ptr(character), name);

	if (character_index < 0)
	{
		// NOTE: There's more code here, but it doesn't appear to mutate any state
		// and always leads back to the same path, so it appears to effectively be a no-op.
		return -1;
	}

	CSceneCharacter* scene_character = GetSceneCharacter(character_index);
	if (scene_character == nullptr)
	{
		return -1;
	}

	if (name == nullptr)
	{
		name = "no_name";
	}

	bool result = scene_character->AssignData(character, name);
	if (!result)
	{
		return -1;
	}

	return static_cast<s32>(character_index);
}

// 00283B00
void CScene::SetCharaNo(ssize character_index, ECharacterID character_no)
{
	log_trace("CScene::{}({})", __func__, character_index, static_cast<sint>(character_no));

	CSceneCharacter* scene_character = GetSceneCharacter(character_index);
	if (scene_character != nullptr)
	{
		scene_character->m_chara_no = character_no;
	}
}

// 00283B30
ECharacterID CScene::GetCharaNo(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	CSceneCharacter* scene_character = GetSceneCharacter(character_index);
	
	if (scene_character == nullptr)
	{
		return ECharacterID::Invalid;
	}

	return scene_character->m_chara_no;
}
;
// 00283B60
CCharacter2* CScene::GetCharacter(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	CSceneCharacter* scene_character = GetSceneCharacter(character_index);
	if (scene_character == nullptr)
	{
		return nullptr;
	}
	if (scene_character->m_status == ESceneDataStatus::Initial)
	{
		return nullptr;
	}

	return scene_character->m_character;
}

// 00283BB0
ssize CScene::AssignMap(ssize map_index, CMap* map, const char* name)
{
	log_trace("CScene::{}({}, {}, {})", __func__, map_index, fmt::ptr(map), name);

	if (map_index < 0)
	{
		// NOTE: There's more code here, but it doesn't appear to mutate any state
		// and always leads back to the same path, so it appears to effectively be a no-op.
		return -1;
	}

	CSceneMap* scene_map = GetSceneMap(map_index);
	if (scene_map == nullptr)
	{
		return -1;
	}

	if (name == nullptr)
	{
		name = "no_name";
	}

	if (m_unk_field_2E5C < 0)
	{
		m_unk_field_2E5C = static_cast<s32>(map_index);
	}

	bool result = scene_map->AssignData(map, name);
	if (!result)
	{
		return -1;
	}

	return map_index;
}

// 00283C90
const char* CScene::GetMapName(ssize map_index)
{
	log_trace("CScene::{}({})", __func__, map_index);

	CSceneMap* scene_map = GetSceneMap(map_index);
	if (scene_map != nullptr)
	{
		return scene_map->m_name.data();
	}
	return nullptr;
}

// 00283CC0
ssize CScene::GetMapID(const char* name)
{
	log_trace("CScene::{}()", __func__);

	if (name == nullptr)
	{
		return -1;
	}

	for (int i = 0; i < m_maps.size(); ++i)
	{
		CSceneMap* scene_map = GetSceneMap(i);
		if (scene_map == nullptr)
		{
			continue;
		}
		if (scene_map->m_status == ESceneDataStatus::Initial)
		{
			continue;
		}
		if (strcmp(name, scene_map->m_name.data()) == 0)
		{
			return i;
		}
	}

	return -1;
}

// 00283D60
CMap* CScene::GetMap(ssize map_index)
{
	log_trace("CScene::{}({})", __func__, map_index);

	CSceneMap* scene_map = GetSceneMap(map_index);
	if (scene_map == nullptr)
	{
		return nullptr;
	}
	if (scene_map->m_status == ESceneDataStatus::Initial)
	{
		return nullptr;
	}

	return scene_map->m_map;
}

// 00283DB0
CMapSky* CScene::GetSky(ssize sky_index)
{
	log_trace("CScene::{}({})", __func__, sky_index);

	CSceneSky* scene_sky = GetSceneSky(sky_index);
	if (scene_sky == nullptr)
	{
		return nullptr;
	}
	if (scene_sky->m_status == ESceneDataStatus::Initial)
	{
		return nullptr;
	}

	return scene_sky->m_sky;
}

// 00283E00
ssize CScene::GetMainMapNo()
{
	log_trace("CScene::{}()", __func__);

	if (m_unk_field_2E5C == 0)
	{
		return m_now_map_no;
	}
	else
	{
		return m_now_submap_no;
	}
}

// 00283E30
unkptr CScene::InScreenFunc(MAYBE_UNUSED InScreenFuncInfo& func_info)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(&func_info));

	todo;
	return nullptr;
}
;
// 002842F0
void CScene::DrawScreenFunc(MAYBE_UNUSED mgCFrame& frame)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(&frame));

	for (int i = 0; i < m_maps.size(); ++i)
	{
		MAYBE_UNUSED CMap* map = GetMap(i);
		if (IsActive(ESceneDataType::Map, i))
		{
			todo;
			// map->DrawScreenFunc(frame);
		}
	}
}

// 00284390
ssize CScene::AssignSky(ssize sky_index, CMapSky* sky, const char* name)
{
	log_trace("CScene::{}({}, {}, {})", __func__, sky_index, fmt::ptr(sky), name);

	if (sky_index < 0)
	{
		// NOTE: There's more code here, but it doesn't appear to mutate any state
		// and always leads back to the same path, so it appears to effectively be a no-op.
		return -1;
	}

	CSceneSky* scene_sky = GetSceneSky(sky_index);
	if (scene_sky == nullptr)
	{
		return -1;
	}

	if (name == nullptr)
	{
		name = "no_name";
	}

	bool result = scene_sky->AssignData(sky, name);
	if (!result)
	{
		return -1;
	}

	return sky_index;
}

// 00284460
bool CScene::DeleteSky(ssize sky_index)
{
	log_trace("CScene::{}({})", __func__, sky_index);

	CSceneSky* scene_sky = GetSceneSky(sky_index);
	if (scene_sky == nullptr)
	{
		return false;
	}

	new (&scene_sky) CSceneSky();
	return true;
}

// 002844A0
ssize CScene::AssignEffect(ssize effect_index, CEffectScriptMan* effect_manager, const char* name)
{
	log_trace("CScene::{}({}, {}, {})", __func__, effect_index, fmt::ptr(effect_manager), name);

	CSceneEffect* scene_effect = GetSceneEffect(effect_index);
	if (scene_effect == nullptr)
	{
		return -1;
	}

	if (name == nullptr)
	{
		name = "no_name";
	}

	bool result = scene_effect->AssignData(effect_manager, name);
	if (!result)
	{
		return -1;
	}

	return effect_index;
}

// 00284510
void CScene::DeleteEffect(ssize effect_index)
{
	log_trace("CScene::{}({})", __func__, effect_index);

	CSceneEffect* scene_effect = GetSceneEffect(effect_index);
	if (scene_effect != nullptr)
	{
		new (&scene_effect) CSceneEffect();
	}
}

// 00284540
CEffectScriptMan* CScene::GetEffect(ssize effect_index)
{
	log_trace("CScene::{}({})", __func__, effect_index);

	CSceneEffect* scene_effect = GetSceneEffect(effect_index);
	if (scene_effect == nullptr)
	{
		return nullptr;
	}
	return scene_effect->m_effect_script_manager;
}

// 00284570
void CScene::StepEffectScript(ssize effect_index)
{
	log_trace("CScene::{}({})", __func__, effect_index);

	CEffectScriptMan* effect;
	if (effect_index >= 0)
	{
		// Step a particular effect
		effect = GetEffect(effect_index);
		if (effect != nullptr)
		{
			todo;
			//effect->Step();
		}
		return;
	}

	// Step all effects
	for (int i = 0; i < m_effects.size(); ++i)
	{
		effect = GetEffect(i);
		if (effect != nullptr)
		{
			todo;
			//effect->Step();
		}
	}
}

// 00284600
void CScene::DrawEffectScript(ssize effect_index)
{
	log_trace("CScene::{}({})", __func__, effect_index);

	CEffectScriptMan* effect;
	if (effect_index >= 0)
	{
		// Draw a particular effect
		effect = GetEffect(effect_index);
		if (effect != nullptr)
		{
			todo;
			//effect->Draw();
		}
		return;
	}

	// Draw all effects
	for (int i = 0; i < m_effects.size(); ++i)
	{
		effect = GetEffect(i);
		if (effect != nullptr)
		{
			todo;
			//effect->Draw();
		}
	}
}

// 00284690
bool CScene::IsActive(ESceneDataType data_type, ssize data_index)
{
	log_trace("CScene::{}({}, {})", __func__, data_type, data_index);

	CSceneData* scene_data = GetData(data_type, data_index);
	if (scene_data == nullptr)
	{
		return false;
	}

	using Status = ESceneDataStatus;
	return (scene_data->m_status & (Status::Assigned | Status::Active)) \
		== (Status::Assigned | Status::Active);
}

// 002846D0
void CScene::SetActive(ESceneDataType data_type, ssize data_index)
{
	log_trace("CScene::{}({}, {})", __func__, data_type, data_index);

	CSceneData* scene_data = GetData(data_type, data_index);
	if (scene_data == nullptr)
	{
		return;
	}

	scene_data->m_status |= ESceneDataStatus::Active;
}

// 00284700
void CScene::ResetActive(ESceneDataType data_type, ssize data_index)
{
	log_trace("CScene::{}({}, {})", __func__, data_type, data_index);

	CSceneData* scene_data = GetData(data_type, data_index);
	if (scene_data == nullptr)
	{
		return;
	}

	scene_data->m_status &= ~(ESceneDataStatus::Active);
}

// 00284740
void CScene::SetStatus(ESceneDataType data_type, ssize data_index, ESceneDataStatus status)
{
	log_trace("CScene::{}({}, {}, {})", __func__, data_type, data_index, status);

	CSceneData* scene_data = GetData(data_type, data_index);
	if (scene_data == nullptr)
	{
		return;
	}

	scene_data->m_status = status;
}

// 00284780
void CScene::ResetStatus(ESceneDataType data_type, ssize data_index, ESceneDataStatus status)
{
	log_trace("CScene::{}({}, {}, {})", __func__, data_type, data_index, status);

	CSceneData* scene_data = GetData(data_type, data_index);
	if (scene_data == nullptr)
	{
		return;
	}

	scene_data->m_status &= ~(status);
}

// 002847C0
ESceneDataStatus CScene::GetStatus(ESceneDataType data_type, ssize data_index)
{
	log_trace("CScene::{}({}, {})", __func__, data_type, data_index);

	CSceneData* scene_data = GetData(data_type, data_index);
	if (scene_data == nullptr)
	{
		return ESceneDataStatus::Initial;
	}

	return scene_data->m_status;
}

// 002847F0
void CScene::SetType(MAYBE_UNUSED ESceneDataType data_type, MAYBE_UNUSED ssize data_index, MAYBE_UNUSED unk _data_type)
{
	log_trace("CScene::{}({}, {}, {})", __func__, data_type, data_index, _data_type);

	todo;
}

// 00284820
unk CScene::GetType(MAYBE_UNUSED ESceneDataType data_type, MAYBE_UNUSED ssize data_index)
{
	log_trace("CScene::{}({}, {})", __func__, data_type, data_index);

	todo;
	return 0;
}

// 00284850
// Stores active maps in maps_dest, returns amount of active maps.
usize CScene::GetActiveMaps(CMap** maps_dest, usize maps_capacity)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(maps_dest), maps_capacity);

	int found_maps = 0;
	for (int i = 0; i < m_maps.size() && found_maps < maps_capacity; ++i)
	{
		if (IsActive(ESceneDataType::Map, i))
		{
			maps_dest[found_maps++] = GetMap(i);
		}
	}
	return found_maps;
}

// 00284900
s32 CScene::GetCharaTexb(MAYBE_UNUSED ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return -1;
}

// 00284900
void CScene::SetCharaTexb(MAYBE_UNUSED ssize character_index, MAYBE_UNUSED s32 texb)
{
	log_trace("CScene::{}({}, {})", __func__, character_index, texb);

	todo;
}

// 002849C0
void CScene::SetTime(MAYBE_UNUSED f32 time)
{
	log_trace("CScene::{}({})", __func__, time);

	todo;
}

// 00284A60
void CScene::AddTime(MAYBE_UNUSED f32 time)
{
	log_trace("CScene::{}({})", __func__, time);

	todo;
}

// 00284A70
void CScene::TimeStep(MAYBE_UNUSED f32 time)
{
	log_trace("CScene::{}({})", __func__, time);

	todo;
}

// 00284B30
//void CScene::SetWind(const vec3& wind_direction, float wind_velocity)
//{
//	log_trace("CScene::{}()", __func__, fmt::ptr(&wind_direction), wind_velocity);
//
//	m_wind_velocity = wind_velocity;
//	m_wind_direction = math::vector_normalize(wind_direction);
//}

//void CScene::SetWind(const std::pair<vec3, f32>& wind)
//{
//	SetWind(wind.first, wind.second);
//}

// 00284B40
void CScene::ResetWind()
{
	log_trace("CScene::{}()", __func__);

	m_wind_velocity = 0.0f;
}

// 00284B50
// Stores direction in direction; returns velocity.
//std::pair<vec3, f32> CScene::GetWind()
//{
//	log_trace("CScene::{}()", __func__);
//
//	return { m_wind_direction, m_wind_velocity };
//}

// 00284B60
void CScene::SetNowMapNo(s32 now_map_no)
{
	log_trace("CScene::{}({})", __func__, now_map_no);

	if (m_now_map_no != now_map_no)
	{
		m_old_map_no = m_now_map_no;
	}
	m_now_map_no = now_map_no;
}

// 00284B80
void CScene::SetNowSubMapNo(s32 now_submap_no)
{
	log_trace("CScene::{}({})", __func__, now_submap_no);

	if (m_now_submap_no != now_submap_no)
	{
		m_old_submap_no = m_now_map_no;
	}
	m_now_submap_no = now_submap_no;
}

// 00284BA0
void CScene::LoadChara(MAYBE_UNUSED unk i1, MAYBE_UNUSED unkptr p1,
	MAYBE_UNUSED unkptr p2, MAYBE_UNUSED mgCMemory& m1,
	MAYBE_UNUSED mgCMemory& m2, MAYBE_UNUSED mgCMemory& m3,
	MAYBE_UNUSED unk i2, MAYBE_UNUSED unk i3)
{
	log_trace("CScene::{}({}, {}, {}, {}, {}, {}, {}, {})", __func__, i1, fmt::ptr(p1), fmt::ptr(p2), fmt::ptr(&m1), fmt::ptr(&m2), fmt::ptr(&m3), i2, i3);

	todo;
}

// 002853B0
void CScene::DeleteChara(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	CSceneCharacter* scene_character = GetSceneCharacter(character_index);
	if (scene_character != nullptr)
	{
		new (&scene_character) CSceneCharacter();
	}
}

// 002853E0
void CScene::CopyChara(MAYBE_UNUSED ssize character_index1, MAYBE_UNUSED ssize character_index2, MAYBE_UNUSED mgCMemory& memory)
{
	log_trace("CScene::{}({}, {}, {})", __func__, character_index1, character_index2, fmt::ptr(&memory));

	todo;
}

// 00285670
s32 CScene::LoadMapFromMemory(MAYBE_UNUSED sint i, MAYBE_UNUSED SCN_LOADMAP_INFO2& info)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(&info));

	todo;
	return -1;
}

// 002856F0
s32 CScene::LoadMapFromMemory(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2, MAYBE_UNUSED SCN_LOADMAP_INFO2& info)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, fmt::ptr(&info));

	todo;
	return -1;
}

// 00285C30
bool CScene::LoadMapBGStep(MAYBE_UNUSED SCN_LOADMAP_INFO2& info)
{
	log_trace("CScene::{}()", __func__);

	todo;
	return false;
}

// 00285CE0
s32 CScene::LoadMap(MAYBE_UNUSED sint i1, MAYBE_UNUSED SCN_LOADMAP_INFO2& info, MAYBE_UNUSED sint i2)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, fmt::ptr(&info), i2);

	todo;
	return -1;
}

// 00285E70
bool CScene::DeleteMap(MAYBE_UNUSED ssize map_index, MAYBE_UNUSED bool b)
{
	log_trace("CScene::{}({}, {})", __func__, map_index, b);

	todo;
	return false;
}

// 002A5B30
void CScene::InitSnd()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A5C00
void CScene::InitBGM()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A5C50
void CScene::InitSeSrc()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A5E10
void CScene::InitSeEnv()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A5EE0
void CScene::InitSeBattle()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A5F60
void CScene::InitSeBas()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A5FE0
void CScene::SeAllStop()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A6020
void CScene::SoundAllStop()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A6060
void CScene::InitLoopSeMngr()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A60E0
CScene::BGM_INFO* CScene::GetActiveBGMInfo()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return nullptr;
}

// 002A6110
void CScene::PlayBGM(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2, MAYBE_UNUSED f32 f)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, f);

	todo;
}

// 002A6210
void CScene::PauseBGM()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A6240
void CScene::ReplayBGM()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A6280
void CScene::StopBGM(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002A62E0
void CScene::SetVolBGM(MAYBE_UNUSED s32 volume)
{
	log_trace("CScene::{}({})", __func__, volume);

	todo;
}

// 002A6350
s32 CScene::GetVolBGM()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return -1;
}

// 002A6370
s32 CScene::GetBGMState()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return -1;
}

// 002A63A0
void CScene::SetVolfBGM(MAYBE_UNUSED f32 volume)
{
	log_trace("CScene::{}({})", __func__, volume);

	todo;
}

// 002A6420
float CScene::GetVolfBGM()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return 0.0f;
}

// 002A6440
void CScene::FadeOutBGM(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002A6480
void CScene::FadeInBGM(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002A64E0
void CScene::AutoChangeBGMVol(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}
;
// 002A6510
s32 CScene::GetActiveBGMStatus(MAYBE_UNUSED BGM_STATUS& status_dest)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(&status_dest));

	todo;
	return -1;
}

// 002A6580
void CScene::SetActiveBGMStatus(MAYBE_UNUSED BGM_STATUS& status)
{
	log_trace("CScene::{}()", __func__, fmt::ptr(&status));

	todo;
}

// 002A6690
void CScene::PlayEnvBGM(MAYBE_UNUSED sint i, MAYBE_UNUSED f32 f)
{
	log_trace("CScene::{}({}, {})", __func__, i, f);

	todo;
}

// 002A6720
void CScene::SetEnvBGMVol(MAYBE_UNUSED f32 volume)
{
	log_trace("CScene::{}({})", __func__, volume);

	todo;
}

// 002A67C0
void CScene::StopEnvBGMVol()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A6820
void CScene::AutoChangeEnvBGM(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002A6830
void CScene::AutoChangeEnvOffset(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002A6840
void CScene::PlayEnvBGM()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A68F0
s32 CScene::GetSeSrcID(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return -1;
}

// 002A6940
void CScene::GetNumber3(MAYBE_UNUSED char* c, MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({}, {})", __func__, c, i);

	todo;
}

// 002A69D0
void CScene::GetBGMFile(MAYBE_UNUSED char* c, MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({}, {})", __func__, c, i);

	todo;
}

// 002A6A10
void CScene::GetSeSrcFile(MAYBE_UNUSED char* c, MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({}, {})", __func__, c, i);

	todo;
}

// 002A6A50
void CScene::GetSeEnvFile(MAYBE_UNUSED char* c, MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({}, {})", __func__, c, i);

	todo;
}

// 002A6A90
void CScene::GetSeBaseFile(MAYBE_UNUSED char* c, MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({}, {})", __func__, c, i);

	todo;
}

// 002A6AD0
void CScene::GetSeBattleFile(MAYBE_UNUSED char* c, MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({}, {})", __func__, c, i);

	todo;
}

// 002A6B10
bool CScene::CheckLoadBGM(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return false;
}

// 002A6B50
bool CScene::CheckLoadSeSrc(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return false;
}

// 002A6BA0
bool CScene::CheckLoadSeEnv(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return false;
}

// 002A6BD0
bool CScene::CheckLoadSeBattle(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return false;
}

// 002A6C00
bool CScene::CheckLoadSeBase(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return false;
}

// 002A6C30
unkptr CScene::SearchSndDataID(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return nullptr;
}

// 002A6CC0
s16 CScene::GetDefBGMNo(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return -1;
}

// 002A6CF0
bool CScene::GetDefEventSeFile(MAYBE_UNUSED sint i, MAYBE_UNUSED char* c)
{
	log_trace("CScene::{}({}, {})", __func__, i, c);

	todo;
	return false;
}

// 002A7290
bool CScene::LoadBGMPack(MAYBE_UNUSED sint i, MAYBE_UNUSED unkptr p)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(p));

	todo;
	return false;
}

// 002A7340
bool CScene::LoadSeSrcPack(MAYBE_UNUSED sint i, MAYBE_UNUSED unkptr p)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(p));

	todo;
	return false;
}

// 002A7410
bool CScene::LoadSeEnvPack(MAYBE_UNUSED sint i, MAYBE_UNUSED unkptr p)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(p));

	todo;
	return false;
}

// 002A74C0
bool CScene::LoadSeBattlePack(MAYBE_UNUSED sint i, MAYBE_UNUSED unkptr p)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(p));

	todo;
	return false;
}

// 002A7560
bool CScene::LoadSeBasePack(MAYBE_UNUSED sint i, MAYBE_UNUSED unkptr p)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(p));

	todo;
	return false;
}

// 002A7600
void CScene::PrePlaySeSrc()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A7670
void CScene::PlaySeSrc(MAYBE_UNUSED sint i, MAYBE_UNUSED f32 f1, MAYBE_UNUSED f32 f2)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i, f1, f2);

	todo;
}

// 002A77B0
s32 CScene::CheckSePlay(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return -1;
}

// 002A7870
float CScene::GetTimeBGMVolf()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return 0.0f;
}

// 002A7940
void CScene::StepSnd()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A7F00
void CScene::StopSeSrc()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A7FB0
void CScene::PlayMapSeSrc()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A80A0
void CScene::SePlayOpenDoor(MAYBE_UNUSED sint i, MAYBE_UNUSED f32* unused)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(unused));

	todo;
}

// 002A80C0
void CScene::SePlayCloseDoor(MAYBE_UNUSED sint i, MAYBE_UNUSED f32* unused)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(unused));

	todo;
}

// 002A80E0
void CScene::SePlayFoot(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2, MAYBE_UNUSED f32* fp)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, fmt::ptr(fp));

	todo;
}

// 002A8160
int CScene::GetLine(MAYBE_UNUSED unkptr p1, MAYBE_UNUSED unkptr p2, MAYBE_UNUSED unkptr p3)
{
	log_trace("CScene::{}()", __func__, fmt::ptr(p1), fmt::ptr(p2), fmt::ptr(p3));

	todo;
	return -1;
}

// 002A8300
void CScene::LoadSndRevInfo(MAYBE_UNUSED unkptr p1, MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(p1), i);

	todo;
}

// 002A8320
void CScene::LoadSndFileInfo(MAYBE_UNUSED unkptr p1, MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(p1), i);

	todo;
}

// 002C79F0
void CScene::UpdateMapInfo()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002C7B50
//void CScene::GetColPoly(MAYBE_UNUSED CCPoly& col_poly, MAYBE_UNUSED mgVu0FBOX& box, MAYBE_UNUSED sint i)
//{
//	log_trace("CScene::{}({}, {}, {})", __func__, fmt::ptr(&col_poly), fmt::ptr(&box), i);
//
//	todo;
//}

// 002C7C20
//void CScene::GetCameraPoly(MAYBE_UNUSED CCPoly& col_poly, MAYBE_UNUSED mgVu0FBOX& box, MAYBE_UNUSED sint i)
//{
//	log_trace("CScene::{}({}, {}, {})", __func__, fmt::ptr(&col_poly), fmt::ptr(&box), i);
//
//	todo;
//}

// 002C7CF0
void CScene::RunEvent(MAYBE_UNUSED sint i, MAYBE_UNUSED CSceneEventData* event_data)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(event_data));

	todo;
}

// 002C7E60
//bool CScene::GetMapEvent(MAYBE_UNUSED vec4& v, MAYBE_UNUSED sint i, MAYBE_UNUSED CSceneEventData* event_data)
//{
//	log_trace("CScene::{}({}, {}, {})", __func__, fmt::ptr(&v), i, fmt::ptr(event_data));
//
//	todo;
//	return false;
//}

// 002C8070
//bool CScene::GetFixCameraPos(MAYBE_UNUSED vec4& v1, MAYBE_UNUSED vec4& v2)
//{
//	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2));
//
//	todo;
//	return false;
//}

// 002C8120
//void CScene::FixCameraPartsOnOff(MAYBE_UNUSED vec4& v)
//{
//	log_trace("CScene::{}({})", __func__, fmt::ptr(&v));
//
//	todo;
//}

// 002C81A0
void CScene::EyeViewDrawOnOff(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002C8260
//void CScene::GetSunPosition(MAYBE_UNUSED vec4& sun_position)
//{
//	log_trace("CScene::{}({})", __func__, fmt::ptr(&sun_position));
//
//	todo;
//}

// 002C8330
//void CScene::GetMoonPosition(MAYBE_UNUSED vec4& moon_position)
//{
//	log_trace("CScene::{}({})", __func__, fmt::ptr(&moon_position));
//
//	GetSunPosition(moon_position);
//	moon_position.y *= -1;
//}

// 002C8370
void CScene::DrawSky(MAYBE_UNUSED s32 i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002C8520
void CScene::DrawLensFlare(MAYBE_UNUSED ssize map_index, MAYBE_UNUSED unkptr p1, MAYBE_UNUSED unkptr p2)
{
	log_trace("CScene::{}({}, {}, {})", __func__, map_index, fmt::ptr(p1), fmt::ptr(p2));

	todo;
}

// 002C8790
void CScene::EffectStep()
{
	log_trace("CScene::{}()", __func__);

	CMap* maps[4];
	usize f = GetActiveMaps(maps, sizeof(maps) / sizeof(CMap*));

	for (int i = 0; i < f; ++i)
	{
		todo;
		//maps[i]->EffectStep();
	}

	todo;
	//m_fire_raster.Step()
}

// 002C8820
void CScene::DrawEffect(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002C8B70
bool CScene::CheckDrawChara(MAYBE_UNUSED ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return false;
}

// 002C8BF0
bool CScene::CheckDrawCharaShadow(MAYBE_UNUSED ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return false;
}

// 002C8C70
bool CScene::StepChara(MAYBE_UNUSED ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return false;
}

// 002C8D70
//void CScene::GetCharaLighting(MAYBE_UNUSED matrix4& m, MAYBE_UNUSED vec4& v)
//{
//	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(&m), fmt::ptr(&v));
//
//	todo;
//}

// 002C8F80
bool CScene::DrawChara(MAYBE_UNUSED ssize character_index, MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({}, {})", __func__, character_index, i);

	todo;
	return false;
}

// 002C9280
bool CScene::DrawCharaShadow(MAYBE_UNUSED ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return false;
}

// 002C93D0
void CScene::DrawExclamationMark(MAYBE_UNUSED mgCFrame& frame)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(&frame));

	todo;
}

// 002C94F0
s32 CScene::SearchCharaTexb(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return -1;
}

// 002C9590
void CScene::PreLoadVillager(MAYBE_UNUSED ssize villager_index, MAYBE_UNUSED unkptr p)
{
	log_trace("CScene::{}({}, {})", __func__, villager_index, fmt::ptr(p));

	todo;
}

// 002C9640
void CScene::DeleteVillager(MAYBE_UNUSED ssize villager_index)
{
	log_trace("CScene::{}({})", __func__, villager_index);

	todo;
}

// 002C9660
void CScene::DeleteSubVillager()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002C9710
void CScene::DeleteVillager()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002C97C0
s32 CScene::SearchCharaID(ECharacterID chara_no)
{
	log_trace("CScene::{}({})", __func__, common::to_underlying(chara_no));

	for (usize i = 8; i < 0x40; ++i) // FIXME: MAGIC; not sure why 8 and 0x40 here
	{
		if (GetCharaNo(i) == chara_no)
		{
			return static_cast<s32>(i);
		}
	}

	return -1;
}

// 002C9830
bool CScene::GetNowVillagerTime()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return false;
}

// 002C9880
usize CScene::GetLoadVillagerList(MAYBE_UNUSED unk i, MAYBE_UNUSED unkptr pi, MAYBE_UNUSED CVillagerPlaceInfo&& place_info)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i, fmt::ptr(pi), fmt::ptr(&place_info));

	todo;
	return 0;
}

// 002C9980
s32 CScene::SearchCopyModel(MAYBE_UNUSED unk i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return -1;
}

// 002C9B80
void CScene::CharaObjectOnOff(MAYBE_UNUSED ssize character_index, MAYBE_UNUSED mgCMemory& stack)
{
	log_trace("CScene::{}({}, {})", __func__, character_index, fmt::ptr(&stack));

	todo;
}

// 002C9D40
u32 CScene::LoadVillager(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2)
{
	log_trace("CScene::{}({}, {})", __func__, i1, i2);

	todo;
	return 0;
}

// 002CA3D0
u32 CScene::LoadSubVillager(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2)
{
	log_trace("CScene::{}({}, {})", __func__, i1, i2);

	todo;
	return 0;
}

// 002CA3D0
bool CScene::RegisterVillager(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2, MAYBE_UNUSED sint i3)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, i3);

	todo;
	return false;
}

// 002CA430
bool CScene::RegisterVillager(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2, MAYBE_UNUSED CVillagerPlaceInfo& place_info)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, fmt::ptr(&place_info));

	todo;
	return false;
}

// 002CA450
bool CScene::RegisterVillager(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2, MAYBE_UNUSED mgCMemory& stack)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, fmt::ptr(&stack));

	todo;
	return false;
}

// 002CA540
//bool CScene::GetTalkEvent(MAYBE_UNUSED vec4& v, MAYBE_UNUSED CSceneEventData& event_data)
//{
//	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(&v), fmt::ptr(&event_data));
//
//	todo;
//	return false;
//}

// 002CA880
void CScene::StepVillager()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002CACD0
//void CScene::StayNearVillager(MAYBE_UNUSED vec4& v, MAYBE_UNUSED unkptr pi)
//{
//	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(&v), fmt::ptr(pi));
//
//	todo;
//}

// 002CAE60
void CScene::CancelStayVillager(MAYBE_UNUSED unkptr pi)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(pi));

	todo;
}

// 002CAEE0
void CScene::StayVillager(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002CAF20
void CScene::CancelStayVillager(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002CAFD0
void CScene::ExModeVillager(MAYBE_UNUSED sint i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002CB010
void CScene::SetActiveVillager()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002CB110
void CScene::InScreenChara(MAYBE_UNUSED InScreenCharaInfo& chara_info, MAYBE_UNUSED f32* unused)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(&chara_info), fmt::ptr(unused));

	todo;
}

// 002CB5A0
void CScene::LoadGameObject(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2, MAYBE_UNUSED mgCMemory& stack)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, fmt::ptr(&stack));

	todo;
}

// 002CB900
//s32 CScene::GetGameObjectEvent(MAYBE_UNUSED vec4& v, MAYBE_UNUSED CSceneEventData& event_data)
//{
//	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(&v), fmt::ptr(&event_data));
//
//	todo;
//	return -1;
//}

// 002CBAA0
void CScene::DrawGameObject(MAYBE_UNUSED ssize gameobj_index)
{
	log_trace("CScene::{}()", __func__, gameobj_index);

	todo;
}

// 00284BA0
void LoadMapData(MAYBE_UNUSED SCN_LOADMAP_INFO2& info, MAYBE_UNUSED bool b)
{
	log_trace("{}()", __func__, fmt::ptr(&info), b);

	todo;
}