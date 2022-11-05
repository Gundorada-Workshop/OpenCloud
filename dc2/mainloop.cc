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
Language::Language LanguageCode;

// 003D8070
static SDebugInfo DebugInfo;
// 003D8090
static CFont Font;
// 003D8140
static SInitArg InitArg;
// 003D8190
static SInitArg NextInitArg;
// 003D81E0
static SInitArg PrevInitArg;
// 003D8230
// FIXME: 0x1A000000 bytes (26MB) in PS2. Might need to adjust slightly for windows.
// Bumped up to 40MB (0x28000000) on Windows (to adjust for slightly bigger datatypes)
static alignas(16) char main_buffer[0x28000000];
// 01DD8230
static mgCMemory MainBuffer;
// 01DD8260
static CScene MainScene;
// 01DE87B0
static char SystemSeBuff[0x1900];
// 01DEA0B0
static mgCMemory SystemSeStack;
// 01E017E0
static mgCMemory InfoStack;
// 01E01810
static CSaveData SaveData;

// FIXME: The following are part of CSaveData (01E01810) and need to be folded in
// 01E03434
static std::array<CEditData, 5> stru_1E03434;
// 01E1EAB0
static CUserDataManager stru_1E1EAB0;
// 01E64250
static CQuestData stru_1E64250;
// 01E658D0
static CMenuSystemData stru_1E658D0;

// 01E67180
static mgCMemory MenuBuffer;
// 01E672B0
static std::array<mgCTexture, 2> FontTex;
// 01E67390
static ClsMes PauseMes;

namespace MainLoop_SInit
{
	// 00373580
	void SInit()
	{
		log_trace("SInit()");

		memset(&DebugInfo, 0, sizeof(DebugInfo));

		Font.Initialize();

		memset(&InitArg, 0, sizeof(InitArg));
		memset(&NextInitArg, 0, sizeof(NextInitArg));
		memset(&PrevInitArg, 0, sizeof(PrevInitArg));

		MainBuffer.Initialize();

		for (auto& character : MainScene.m_characters)
		{
			character.CSceneData::Initialize();
			character.Initialize();
		}

		for (auto& camera : MainScene.m_cameras)
		{
			camera.CSceneData::Initialize();
			camera.Initialize();
		}

		for (auto& message : MainScene.m_messages)
		{
			message.CSceneData::Initialize();
			message.Initialize();
		}

		MainScene.m_mds_list_set.Initialize();

		new (&MainScene.m_fire_raster) mgCTexture;

		for (auto& unk_var : MainScene.m_fire_raster.m_unk_field_70)
		{
			memset(&unk_var, 0, sizeof(unk_var));
		}

		MainScene.m_fire_raster.Initialize();

		for (auto& sky : MainScene.m_skies)
		{
			sky.CSceneData::Initialize();
			sky.Initialize();
		}

		for (auto& gameobj : MainScene.m_gameobjs)
		{
			gameobj.CSceneData::Initialize();
			gameobj.CSceneCharacter::Initialize();
			gameobj.Initialize();
		}

		for (auto& effect : MainScene.m_effects)
		{
			effect.CSceneData::Initialize();
			effect.Initialize();
		}

		MainScene.m_fade_in_out.Initialize();
		MainScene.m_scn_loadmap_info.Initialize();
		memset(&MainScene.m_scene_event_data, 0, sizeof(MainScene.m_scene_event_data));

		for (auto& villager_data : MainScene.m_villager_manager.m_villager_data)
		{
			villager_data.Initialize();
		}

		MainScene.m_villager_manager.Initialize();

		for (auto& bgm_info : MainScene.m_bgm_info)
		{
			bgm_info.m_stack.Initialize();
		}

		MainScene.m_unk_field_9DD0.Initialize();
		MainScene.m_unk_field_A450.Initialize();
		MainScene.m_unk_field_C4A0.Initialize();
		MainScene.m_unk_field_E4E0.Initialize();
		MainScene.m_unk_field_10510.Initialize();

		MainScene.m_loop_se_manager.Initialize();

		MainScene.InitAllData();

		SystemSeStack.Initialize();
		InfoStack.Initialize();

		for (auto& edit_data : stru_1E03434)
		{
			new (&edit_data) CEditData;
		}

		new (&stru_1E1EAB0) CUserDataManager;
		stru_1E64250.Initialize();
		new (&stru_1E658D0) CMenuSystemData;

		for (auto& texture : FontTex)
		{
			new (&texture) mgCTexture;
		}

		new (&PauseMes) ClsMes;
	}
}

// 00190840
CFont* GetDebugFont()
{
	log_trace("{}()", __func__);

	return &Font;
}

// 001908F0
mgCMemory* GetMainStack()
{
	log_trace("{}()", __func__);

	return &MainBuffer;
}

// 00190CB0
void MainLoop()
{
	log_trace("{}()", __func__);

	todo;
}
