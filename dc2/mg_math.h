#pragma once
#include <numbers>
#include "common/types.h"

// ~ 0012F1C0 - 00131110

constexpr float M_PI_F = std::numbers::pi_v<float>;
constexpr float M_2PI_F = M_PI_F * 2;

// Converts degrees to radians
#define DEGREES_TO_RADIANS(x) \
  x * M_PI_F/180.0f

// Converts radians to degrees
#define RADIANS_TO_DEGREES(x) \
  x * 180.0f/M_PI_F

// Clamps an angle to (-pi, +pi] radians.
// (Only valid for floats within (-2pi, +2pi].
// Use mgAngleLimit if your float is not within that range.)
inline float mgAngleClamp(float x)
{
  if (x > DEGREES_TO_RADIANS(180.0f))
  {
    return x - DEGREES_TO_RADIANS(360.0f);
  }
  if (x <= DEGREES_TO_RADIANS(-180.0f))
  {
    return x + DEGREES_TO_RADIANS(360.0f);
  }
}

// 00130B60
float mgAngleInterpolate(float f1, float f2, float f3, bool b);

// 00130D10
s32 mgAngleCmp(float f1, float f2, float f3);

// 00130DD0
float mgAngleLimit(float f);

// 00130EE0
float mgRnd();

// 00130F20
// for when you want a rand that returns [-6, 6] but really biases towards 0
// for whatever reason
float mgNRnd();