#include <string>
#include "common/debug.h"
#include "common/log.h"
#include "CScene.h"
#include "MainLoop.h"
#include "mgCMemory.h"
#include "mgCTexture.h"

set_log_channel("MainLoop")

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


namespace MainLoop_SInit
{
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
			dynamic_cast<CSceneData&>(character).Initialize();
			character.Initialize();
		}

		for (auto& camera : s_main_scene.m_cameras)
		{
			dynamic_cast<CSceneData&>(camera).Initialize();
			camera.Initialize();
		}

		for (auto& message : s_main_scene.m_messages)
		{
			dynamic_cast<CSceneData&>(message).Initialize();
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
			dynamic_cast<CSceneData&>(sky).Initialize();
			sky.Initialize();
		}

		for (auto& gameobj : s_main_scene.m_gameobjs)
		{
			dynamic_cast<CSceneData&>(gameobj).Initialize();
			dynamic_cast<CSceneCharacter&>(gameobj).Initialize();
			gameobj.Initialize();
		}

		for (auto& effect : s_main_scene.m_effects)
		{
			dynamic_cast<CSceneData&>(effect).Initialize();
			effect.Initialize();
		}

		s_main_scene.m_fade_in_out.Initialize();

		// 003737AC
		todo;
	}
}

// 00190840
CFont* GetDebugFont()
{
	return &s_debug_font;
}

// 001908F0
mgCMemory* GetMainStack()
{
	return &s_main_stack;
}

// 00190CB0
void MainLoop()
{
	todo;
}
