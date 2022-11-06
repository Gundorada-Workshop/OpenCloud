#pragma once
#include "mg_memory.h"
#include "object.h"

// ~ 0015C420 - 00168400

// FIXME: Find out where this should go
template <typename T> class CList
{
  void Initialize();
  T* pGetData();
};

// TODO THIS FILE
class CMapFlagData {};
class CPartsGroup {};
class CFuncPoint {};
struct PieceMaterial {};
class CCameraInfo {};
class CCameraDrawInfo {};
class CMapWater {};
class CMapInfo {};
class CMapLightingInfo {};
class CMapTreasureBox {};
class CMapPiece {};
class CMapSky {};
class CMapEffect_Sprite {};
class CMapEffect {};
class CMapEffectsManager {};

class CMap
{
public:
  void LoadCfgFile(const char* file, int size, mgCMemory* map_stack);
};

class CMapParts : public CObject
{
public:
  // TODO
};