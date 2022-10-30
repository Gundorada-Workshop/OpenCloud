#pragma once
#include "mgCMemory.h"

class CDngFloorManager
{
public:
  void RelationGlid();
  void AnalyzeFile(const char* script, int script_size, mgCMemory* tree_stack);
};
