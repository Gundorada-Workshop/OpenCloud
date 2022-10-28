#include "CGamePad.h"

#include <cmath>

// 0014aef0
static int AxisCalibration(int axis)
{
  // dead zone
  if(std::abs(axis - 128) < 50)
    return 0;

  if((axis - 128) < 1)
    return ((axis - 78) * 128) / 78;

  return ((axis - 177) * 128) / 78;
}

float CGamePad::GetRXf()
{
  return static_cast<float>(GetRX()) / 128.0f;
}

float CGamePad::GetRYf()
{
  return static_cast<float>(GetRY()) / 128.0f;
}

float CGamePad::GetLXf()
{
  return static_cast<float>(GetLX()) / 128.0f;
}

float CGamePad::GetLYf()
{
  return static_cast<float>(GetLY()) / 128.0f;
}
