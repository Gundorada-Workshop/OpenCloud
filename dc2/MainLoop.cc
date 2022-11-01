#include <string>
#include "common/debug.h"
#include "CScene.h"
#include "MainLoop.h"
#include "mgCMemory.h"

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
		memset(&stru_3D8070, 0, sizeof(stru_3D8070));

		s_debug_font.Initialize();

		memset(&stru_3D8140, 0, sizeof(stru_3D8140));
		memset(&stru_3D8190, 0, sizeof(stru_3D8190));
		memset(&stru_3D81E0, 0, sizeof(stru_3D81E0));

		s_main_stack.Initialize();

		for (int i = 0; i < s_main_scene.m_n_characters; ++i)
		{
			s_main_scene.m_characters[i].Initialize();
		}

		for (int i = 0; i < s_main_scene.m_n_cameras; ++i)
		{
			s_main_scene.m_cameras[i].Initialize();
		}

		for (int i = 0; i < s_main_scene.m_n_messages; ++i)
		{
			s_main_scene.m_messages[i].Initialize();
		}

		// 00373694
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
