#pragma once
#include "engine/run_script.h"
#include "engine/mg/mg_lib.h"

class CScene;
class CActiveMonster;

// These two are initialized by CMonsterMan::RunScript
// and should refer to the current active scene and active monster
// 0037735C
extern CScene* nowScene;
// 00377360
extern CActiveMonster* nowMonster;

// 001E7BB0
bool SetMonsterScript(CRunScript* run_script, char* rs_program, mgCMemory* stack);

// 001E7C40
void SetMonsterExtendTable();
