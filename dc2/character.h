#pragma once
#include "mg_frame.h"
#include "mg_memory.h"
#include "object.h"

// ~ 0016A140 - 0017C240

// TODO THIS FILE
class CCharacter2 : public CObjectFrame {};
class CActionChara : public CCharacter2 {};
class CDACollision {};

class CDynamicAnime
{
public:
  void Load(const char* script, int script_size, mgCFrame* frame, mgCMemory* stack);
  void NewVertexTable(int, mgCMemory* stack);
  void NewBoundingBoxTable(int, mgCMemory* stack);
  void NewCollisionTable(int, mgCMemory* stack);
};
