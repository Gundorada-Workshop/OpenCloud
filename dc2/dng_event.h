#pragma once
#include "character.h"
#include "dng_main.h"
#include "event_func.h"

// ~ 0028AFC0 - 002912F0

// TODO THIS FILE
class CStartupEpisodeTitle {};
struct MessageTaskManager {};
class CRedMarkModel {};
class CTreasureBox {};
class CTreasureBoxManager {};

class CGeoStone : public CCharacter2
{
public:
	// 3C  0028BD20
	virtual void Initialize();

	// 0028BCA0
	bool CheckEvent(glm::vec4& position);
	// 0028BA80
	void GeoDraw(glm::vec4& position);
	// 0028BB70
	void DrawMiniMapSymbol(CMiniMapSymbol* mini_map_symbol);
	// 0028BBC0
	void SetFlag(bool flag);
	// 0028BC20
	void GeoStep();

	// BEGIN 0x660
  // 660
  bool m_flag{false};
  // 664
	float m_height_offset_sine{ 0.0f };
  // 668
	bool m_unk_field_668{ false };

  // ALIGNED SIZE 0x670
};

class CRandomCircle
{
public:

  // 40
  CCharacter2 m_unk_field_40;
  // SIZE 0x6A0
};