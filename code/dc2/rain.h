#pragma once
#include "common/types.h"

class CRipple
{
public:
  // 0
  unk32 m_unk_field_0{ 0 };
  // 10
  vec4 m_unk_field_10{ 0.0f, 0.0f, 0.0f, 1.0f };
  // 20
  unk32 m_unk_field_20{ 0 };
  // 24
  unk32 m_unk_field_24{ 0 };
  // 28
  unk32 m_unk_field_28{ 0 };
};

class CParticle
{
public:
  // 0
  unk32 m_unk_field_0{ 0 };
  // 10
  vec4 m_unk_field_10{ 0.0f, 0.0f, 0.0f, 1.0f };
  // 20
  vec4 m_unk_field_20{ 0.0f, 0.0f, 0.0f, 1.0f };
  // 30
  vec4 m_unk_field_30{ 0.0f, 0.0f, 0.0f, 1.0f };
  // 40
  unk32 m_unk_field_40{ 0 };
};

class CRainDrop
{
public:
  // 00282100
  CRainDrop();

  // 0
  unk32 m_unk_field_0{ 0 };
  // 4
  unk32 m_unk_field_4{ 0 };
  // 10
  std::array<vec4, 8> m_unk_field_10{};
  // 90
  vec4 m_unk_field_90{ 0.0f, 0.0f, 0.0f, 1.0f };
  // A0, A4, A8, AC
  glm::u8vec4 m_color{ 0x80, 0x80, 0x80, 0x80 };
};

class CRain
{
public:
  // 0
  bool m_unk_field_0{ 0 };
  // 4
  s32 m_char_no{ 0 };
  // 10
  std::array<CRainDrop, 100> m_unk_field_10{};
  // 44D0
  std::array<CRainDrop, 50> m_unk_field_44D0{};
  // 6730
  std::array<CParticle, 100> m_particles{};
  // 8670
  std::array<CRipple, 200> m_ripples{};

  // 00282180
  void SetCharNo(sint char_no);

  // 002822D0
  void Stop();

  // 002822E0
  void Start();
};
