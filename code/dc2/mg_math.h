#pragma once
#include <array>
#include <numbers>

#include "common/types.h"
#include "common/math.h"

#include "glm/glm.hpp"

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

// 0012F1C0
inline ivec4 mgFtoI4(const vec4& v)
{
  return glm::floatBitsToInt(v);
}

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

// 0012F230
inline void mgZeroVector(vec4& v)
{
  v = { 0, 0, 0, 0 };
}

// 0012F240
inline void mgZeroVectorW(vec4& v)
{
  v = { 0, 0, 0, 1 };
}

// 0012F250
bool mgClipBoxVector(const vec4& v1, const vec4& v2, const vec4& v3);

// 0012F290
bool mgClipBox(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4);

// 0012F2E0
bool mgClipBoxW(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4);

// 0012F330
bool mgClipInBox(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4);

// 0012F380
bool mgClipInBoxW(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4);

// 0012F3D0
inline void mgAddVector(vec4& lhs, const vec4& rhs)
{
  lhs += rhs;
}

// 0012F3F0
inline void mgSubVector(vec4& lhs, const vec4& rhs)
{
  lhs -= rhs;
}

// 0012F410
vec4 mgNormalizeVector(const vec4& v, float scale);

// 0012F460
inline vec4 mgVectorMin(const vec4& lhs, const vec4& rhs)
{
  return glm::min(lhs, rhs);
}

// 0012F480
inline vec4 mgVectorMin(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4)
{
  // what?
  return glm::min(v1, glm::min(v2, glm::min(v3, v4)));
}

// 0012F4B0
inline void mgVectorMaxMin(vec4& max_dest, vec4& min_dest, const vec4& lhs, const vec4& rhs)
{
  // ez pz
  max_dest = glm::max(lhs, rhs);
  min_dest = glm::min(lhs, rhs);
}

// 0012F4D0
inline void mgVectorMaxMin(vec4& max_dest, vec4& min_dest, const vec4& v1, const vec4& v2, const vec4& v3)
{
  // oh, wait
  max_dest = glm::max(v1, glm::max(v2, v3));
  min_dest = glm::min(v1, glm::min(v2, v3));
}

// 0012F500
inline void mgVectorMaxMin(vec4& max_dest, vec4& min_dest, const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4)
{
  // I'm trapped in a function overload, aren't I?
  max_dest = glm::max(v1, glm::max(v2, glm::max(v3, v4)));
  min_dest = glm::min(v1, glm::min(v2, glm::min(v3, v4)));
}

// 0012F540
void mgBoxMaxMin(mgVu0FBOX& lhs, const mgVu0FBOX& rhs);

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
