#pragma once
#include "dc2/run_script.h"
#include "dc2/mg/mg_lib.h"

// 002D20D0
bool SetActionScript(CRunScript* run_script, char* rs_program, mgCMemory* stack);

// 002D2160
void SetActionExtendTable();
