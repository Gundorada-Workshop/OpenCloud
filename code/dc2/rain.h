#pragma once
#include "common/types.h"

class CRipple
{
public:
  enum class StepResult
  {
    Finished = -1,
    NotBirthed = 0,
    Playing = 1,
  };

  // 00281510
  s32 Birth(const vec3& position);
  // 00281590
  StepResult Step();
  // 002815E0
  void Draw();

  // 0
  bool m_birthed{ false };
  // 10
  vec3 m_position{ 0.0f, 0.0f, 0.0f };
  // 20
  f32 m_scale{ 0.0f };
  // 24
  f32 m_frame{ 0.0f };
  // 28
  f32 m_frame_max{ 0.0f };
};

class CParticle
{
public:
  enum class StepResult
  {
    Finished = -1,
    NotBirthed = 0,
    Playing = 1,
  };

  // 002819E0
  bool Birth(const vec3& v1, const vec3& v2);
  // 00281A60
  CParticle::StepResult Step();
  // 00281B10
  void Draw();

  // 0
  bool m_birthed{ false };
  // 10
  vec3 m_unk_field_10{ 0.0f, 0.0f, 0.0f };
  // 20
  vec3 m_unk_field_20{ 0.0f, 0.0f, 0.0f };
  // 30
  vec3 m_unk_field_30{ 0.0f, 0.0f, 0.0f };
  // 40
  f32 m_unk_field_40{ 0.0f };
};

class CRainDrop
{
public:
  enum class StepResult
  {
    Finished = -1,
    NotBirthed = 0,
    Playing = 1,
  };

  // 00281D20
  bool Birth(sint i);
  // 00281E90
  CRainDrop::StepResult Step();
  // 00281F60
  void Draw();

  // 0
  unk32 m_unk_field_0{ 0 };
  // 4
  unk32 m_unk_field_4{ 0 };
  // 10
  std::array<vec3, 8> m_unk_field_10{ vec3{0.0f, 0.0f, 0.0f} };
  // 90
  vec3 m_unk_field_90{ 0.0f, 0.0f, 0.0f };
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

  // 002821F0
  void ParticleBirth(const vec3& v, sint i);

  // 002822D0
  void Stop();

  // 002822E0
  void Start();

  // 002823E0
  void Step();

  // 002829E0
  void Draw();
};

