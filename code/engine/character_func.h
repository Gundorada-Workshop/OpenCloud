#pragma once
#include "engine/run_script.h"
#include "engine/mg/mg_lib.h"

class CActionChara;
struct RUN_SCRIPT_ENV;

struct ACTION_INFO
{
  CActionChara* m_chara{ nullptr };
  mgCCameraFollow* m_camera{ nullptr };
  RUN_SCRIPT_ENV* m_script_env{ nullptr };
};

// 01F0D430
extern ACTION_INFO action_info;

// 002D20D0
bool SetActionScript(CRunScript* run_script, char* rs_program, mgCMemory* stack);

// 002D2160
void SetActionExtendTable();
