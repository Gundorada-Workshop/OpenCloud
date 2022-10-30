#pragma once
#include "mgCMemory.h"

// todo
class mgCFrame;

class CDynamicAnime
{
public:
  void Load(const char* script, int script_size, mgCFrame* frame, mgCMemory* stack);
};
