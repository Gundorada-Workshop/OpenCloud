#include "common/log.h"

#include "dc2/mg_math.h"

set_log_channel("mg_math");

// 00130B60
float mgAngleInterpolate(float f12, float f13, float f14, bool b)
{
  log_trace("{}({}, {}, {}, {})", __func__, f12, f13, f14, b);

  float f1 = mgAngleClamp(f13 - f12);

  if (!b)
  {
    if (fabsf(f1) < f14)
    {
      return f13;
    }
  }

  float f2 = 0.0f;

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
s32 mgAngleCmp(float f12, float f13, float f14)
{
  log_trace("{}({}, {}, {})", __func__, f12, f13, f14);

  float n = f12 - f13;
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
float mgAngleLimit(float f)
{
  log_trace("{}({})", __func__, f);

  if (-M_PI_F <= f && f < M_PI_F)
  {
    return f;
  }

  f -= truncf(f / M_2PI_F) * M_2PI_F;
  return mgAngleClamp(f);
}

// 00130EE0
float mgRnd()
{
  log_trace("{}()", __func__);

  return rand() / static_cast<float>(std::numeric_limits<s32>::max());
}

// 00130F20
// for when you want a rand that returns [-6, 6] but really biases towards 0
// for whatever reason
float mgNRnd()
{
  float f = 0;
  for (int i = 0; i < 12; ++i)
  {
    f += mgRnd();
  }
  return f - 6.0f;
}