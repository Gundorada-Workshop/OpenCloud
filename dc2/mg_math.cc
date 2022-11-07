#include "common/log.h"
#include "mg_math.h"

set_log_channel("mg_math");

// 00130B60
float mgAngleInterpolate(float f12, float f13, float f14, bool b)
{
  log_trace("{}({}, {}, {}, {})", __func__, f12, f13, f14, b);

  float f1 = f13 - f12;
  if (f1 > DEGREES_TO_RADIANS(180.0f))
  {
    f1 = DEGREES_TO_RADIANS(360.0f) - f1;
  }
  if (f1 <= DEGREES_TO_RADIANS(-180.0f))
  {
    f1 = DEGREES_TO_RADIANS(360.0f) + f1;
  }

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

  float f0 = f12 + f2;
  if (f0 > DEGREES_TO_RADIANS(-180.0f))
  {
    f0 -= DEGREES_TO_RADIANS(360.0f);
  }
  if (f0 <= DEGREES_TO_RADIANS(180.0f))
  {
    f0 += DEGREES_TO_RADIANS(360.0f);
  }

  return f0;
}