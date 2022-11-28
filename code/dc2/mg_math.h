#pragma once
#include <array>
#include <numbers>

#include "common/types.h"
#include "common/math.h"

// ~ 0012F1C0 - 00131110

#define VALID_INDEX(n, min, max) (n >= min && n < max)

struct mgVu0FBOX
{
  // Represents the "top left" and "bottom right" corners of a 3D rectangle
  std::array<vec4, 2> corners;
};

struct mgVu0FBOX8
{
  // Represents all points in a 3D rectangle
  std::array<vec4, 8> vertices;
};

// 0012F1D0
mgVu0FBOX8 mgCreateBox8(const vec4& c1, const vec4& c2);

// Clamps an angle to (-pi, +pi] radians.
// (Only valid for f32s within (-2pi, +2pi].
// Use mgAngleLimit if your f32 is not within that range.)
inline f32 mgAngleClamp(f32 x)
{
  if (x > common::deg_to_rad(180.0f))
  {
    return x - common::deg_to_rad(360.0f);
  }
  if (x <= common::deg_to_rad(-180.0f))
  {
    return x + common::deg_to_rad(360.0f);
  }
  return x;
}

// 00130B60
f32 mgAngleInterpolate(f32 f1, f32 f2, f32 f3, bool b);

// 00130D10
s32 mgAngleCmp(f32 f1, f32 f2, f32 f3);

// 00130DD0
f32 mgAngleLimit(f32 f);

// 00130EE0
f32 mgRnd();

// 00130F20
// for when you want a rand that returns [-6, 6] but really biases towards 0
// for whatever reason
f32 mgNRnd();
