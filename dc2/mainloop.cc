#include <string>
#include "common/debug.h"
#include "common/log.h"
#include "editdata.h"
#include "ls_mes.h"
#include "mainloop.h"
#include "menusave.h"
#include "mg_memory.h"
#include "mg_texture.h"
#include "scene.h"
#include "quest.h"
#include "userdata.h"

set_log_channel("mainloop")

// 00376FC0
Language::Language g_language;

// 003D8070
static SMainLoopUnk1 stru_3D8070;
// 003D8090
static CFont s_debug_font;
// 003D8140
static SMainLoopUnk2 stru_3D8140;
// 003D8190
static SMainLoopUnk2 stru_3D8190;
// 003D81E0
static SMainLoopUnk2 stru_3D81E0;
// 003D8230
// FIXME: Magic?
static alignas(16) char s_sub_game_save_data[80000];
// 01DD8230
// FIXME: 27182976 bytes in PS2. Might need to adjust slightly for windows.
// Bumped up to 32MB (33554432) on Windows (to adjust for slightly bigger datatypes)
static alignas(16) char s_main_stack_data[33554432];
// 01DD8230
static mgCMemory s_main_stack;
// 01DD8260
static CScene s_main_scene;
// 01DEA0B0
static mgCMemory stru_1DEA0B0;
// 01E017E0
static mgCMemory stru_1E017E0;
// 01E03434
static std::array<CEditData, 5> stru_1E03434;
// 01E1EAB0
static CUserDataManager stru_1E1EAB0;
// 01E64250
static CQuestData stru_1E64250;
// 01E658D0
static CMenuSystemData stru_1E658D0;
// 01E67180
static mgCMemory stru_1E67180;
// 01E672B0
static std::array<mgCTexture, 2> stru_1E672B0;
// 01E67390
static ClsMes stru_1E67390;

namespace MainLoop_SInit
{
	// 00373580
	void SInit()
	{
		log_trace("SInit");

		memset(&stru_3D8070, 0, sizeof(stru_3D8070));

		s_debug_font.Initialize();

		memset(&stru_3D8140, 0, sizeof(stru_3D8140));
		memset(&stru_3D8190, 0, sizeof(stru_3D8190));
		memset(&stru_3D81E0, 0, sizeof(stru_3D81E0));

		s_main_stack.Initialize();

		for (auto& character : s_main_scene.m_characters)
		{
			static_cast<CSceneData&>(character).Initialize();
			character.Initialize();
		}

		for (auto& camera : s_main_scene.m_cameras)
		{
			static_cast<CSceneData&>(camera).Initialize();
			camera.Initialize();
		}

		for (auto& message : s_main_scene.m_messages)
		{
			static_cast<CSceneData&>(message).Initialize();
			message.Initialize();
		}

		s_main_scene.m_mds_list_set.Initialize();

		new (&s_main_scene.m_fire_raster) mgCTexture;

		for (auto& unk_var : s_main_scene.m_fire_raster.m_unk_field_70)
		{
			memset(&unk_var, 0, sizeof(unk_var));
		}

		s_main_scene.m_fire_raster.Initialize();

		for (auto& sky : s_main_scene.m_skies)
		{
			static_cast<CSceneData&>(sky).Initialize();
			sky.Initialize();
		}

		for (auto& gameobj : s_main_scene.m_gameobjs)
		{
			static_cast<CSceneData&>(gameobj).Initialize();
			static_cast<CSceneCharacter&>(gameobj).Initialize();
			gameobj.Initialize();
		}

		for (auto& effect : s_main_scene.m_effects)
		{
			static_cast<CSceneData&>(effect).Initialize();
			effect.Initialize();
		}

		s_main_scene.m_fade_in_out.Initialize();
		s_main_scene.m_scn_loadmap_info.Initialize();
		memset(&s_main_scene.m_scene_event_data, 0, sizeof(s_main_scene.m_scene_event_data));

		for (auto& villager_data : s_main_scene.m_villager_manager.m_villager_data)
		{
			villager_data.Initialize();
		}

		s_main_scene.m_villager_manager.Initialize();

		for (auto& bgm_info : s_main_scene.m_bgm_info)
		{
			bgm_info.m_stack.Initialize();
		}

		s_main_scene.m_unk_field_9DD0.Initialize();
		s_main_scene.m_unk_field_A450.Initialize();
		s_main_scene.m_unk_field_C4A0.Initialize();
		s_main_scene.m_unk_field_E4E0.Initialize();
		s_main_scene.m_unk_field_10510.Initialize();

		s_main_scene.m_loop_se_manager.Initialize();

		s_main_scene.InitAllData();

		stru_1DEA0B0.Initialize();
		stru_1E017E0.Initialize();

		for (auto& edit_data : stru_1E03434)
		{
			new (&edit_data) CEditData;
		}

		new (&stru_1E1EAB0) CUserDataManager;
		stru_1E64250.Initialize();
		new (&stru_1E658D0) CMenuSystemData;

		for (auto& texture : stru_1E672B0)
		{
			new (&texture) mgCTexture;
		}

		new (&stru_1E67390) ClsMes;
	}
}

// 00190840
CFont* GetDebugFont()
{
	log_trace("{}", __func__);

	return &s_debug_font;
}

// 001908F0
mgCMemory* GetMainStack()
{
	log_trace("{}", __func__);

	return &s_main_stack;
}

// 00190CB0
void MainLoop()
{
	log_trace("{}", __func__);

	todo;
}
