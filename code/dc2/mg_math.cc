#include "common/log.h"

#include "dc2/mg_math.h"

set_log_channel("mg_math");

// 0012F1D0
mgVu0FBOX8 mgCreateBox8(const vec4& c1, const vec4& c2)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(&c1), fmt::ptr(&c2));

  // TODO: Check if this produces better code with swizzling.
  mgVu0FBOX8 result;

  result.vertices[0] = c2;
  result.vertices[1] = c2;
  result.vertices[2] = c2;
  result.vertices[3] = c2;
  result.vertices[4] = c1;
  result.vertices[5] = c1;
  result.vertices[6] = c1;
  result.vertices[7] = c1;

  result.vertices[1].x = c1.x;
  result.vertices[2].y = c1.y;
  result.vertices[3].z = c1.z;
  result.vertices[4].x = c2.x;
  result.vertices[5].y = c2.y;
  result.vertices[6].z = c2.z;
  return result;
}

// 0012F250
bool mgClipBoxVector(const vec4& v1, const vec4& v2, const vec4& v3)
{
  log_trace("{}({}, {}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2), fmt::ptr(&v3));

  todo;
  return false;
}

// 0012F290
bool mgClipBox(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4)
{
  log_trace("{}({}, {}, {}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2), fmt::ptr(&v3), fmt::ptr(&v4));

  todo;
  return false;
}

// 0012F2E0
bool mgClipBoxW(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4)
{
  log_trace("{}({}, {}, {}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2), fmt::ptr(&v3), fmt::ptr(&v4));

  todo;
  return false;
}

// 0012F330
bool mgClipInBox(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4)
{
  log_trace("{}({}, {}, {}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2), fmt::ptr(&v3), fmt::ptr(&v4));

  todo;
  return false;
}

// 0012F380
bool mgClipInBoxW(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4)
{
  log_trace("{}({}, {}, {}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2), fmt::ptr(&v3), fmt::ptr(&v4));

  todo;
  return false;
}

// 0012F410
vec4 mgNormalizeVector(const vec4& v, float scale)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(&v), scale);

  return glm::normalize(v) * scale;
}

// 00130B60
f32 mgAngleInterpolate(f32 f12, f32 f13, f32 f14, bool b)
{
  log_trace("{}({}, {}, {}, {})", __func__, f12, f13, f14, b);

  f32 f1 = mgAngleClamp(f13 - f12);

  if (!b)
  {
    if (fabsf(f1) < f14)
    {
      return f13;
    }
  }

  f32 f2 = 0.0f;

  if (b)
  {
    f2 = f1 / f14;
  }
  else
  {
    if (f1 < 0.0f)
    {
      if (f14 < f1)
      {
        return f13;
      }
      f2 -= f14;
    }

    if (f1 > 0.0f)
    {
      if (f14 > f1)
      {
        return f13;
      }
      f2 += f14;
    }
  }

  return mgAngleClamp(f12 + f2);
}

// 00130D10
s32 mgAngleCmp(f32 f12, f32 f13, f32 f14)
{
  log_trace("{}({}, {}, {})", __func__, f12, f13, f14);

  f32 n = f12 - f13;
  if (n == 0.0f)
  {
    return 0;
  }

  n = mgAngleClamp(n);

  if (n > f14)
  {
    return 1;
  }
  if (n < -f14)
  {
    return -1;
  }
  return 0;
}

// 00130DD0
f32 mgAngleLimit(f32 f)
{
  log_trace("{}({})", __func__, f);

  if (common::negate(common::pi()) <= f && f < common::pi())
  {
    return f;
  }

  f -= truncf(f / common::pi2()) * common::pi2();
  return mgAngleClamp(f);
}

// 00130EE0
f32 mgRnd()
{
  log_trace("{}()", __func__);

  return rand() / static_cast<f32>(std::numeric_limits<s32>::max());
}

// 00130F20
// for when you want a rand that returns [-6, 6] but really biases towards 0
// for whatever reason
f32 mgNRnd()
{
  f32 f = 0;
  for (int i = 0; i < 12; ++i)
  {
    f += mgRnd();
  }
  return f - 6.0f;
}
