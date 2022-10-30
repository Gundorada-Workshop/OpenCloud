#pragma once
#include "mgCMemory.h"

// TODO
class mgCTextureAnime;

class mgCTextureManager
{
public:
  void LoadCFGFile(const char* file, int size, mgCMemory* text_anime_stack, mgCTextureAnime* tex_anime);
};
