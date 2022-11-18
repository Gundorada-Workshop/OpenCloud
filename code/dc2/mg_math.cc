#include "common/log.h"

#include "dc2/mg_math.h"

set_log_channel("mg_math");

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
