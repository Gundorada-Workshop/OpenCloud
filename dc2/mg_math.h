#pragma once
#include <numbers>

// ~ 0012F1C0 - 00131110

constexpr float M_PI_F = std::numbers::pi_v<float>;

#define DEGREES_TO_RADIANS(x) \
  x * M_PI_F/180.0f

#define RADIANS_TO_DEGREES(x) \
  x * 180.0f/M_PI_F