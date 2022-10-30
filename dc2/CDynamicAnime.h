#pragma once
#include "mg_Frame.h"
#include "mgCMemory.h"

class CDynamicAnime
{
public:
  void Load(const char* script, int script_size, mgCFrame* frame, mgCMemory* stack);
};
