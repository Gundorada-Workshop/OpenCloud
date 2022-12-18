#pragma once
#include "dc2/run_script.h"
#include "dc2/mg/mg_lib.h"

// 001E7BB0
bool SetMonsterScript(CRunScript* run_script, char* rs_program, mgCMemory* stack);

// 001E7C40
void SetMonsterExtendTable();
