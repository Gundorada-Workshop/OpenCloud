#include "CGamePad.h"

#include <cmath>

// 0014aef0
static sint AxisCalibration(sint axis)
{
  // dead zone
  if(std::abs(axis - 128) < 50)
    return 0;

  if((axis - 128) < 1)
    return ((axis - 78) * 128) / 78;

  return ((axis - 177) * 128) / 78;
}

sint CGamePad::GetRX()
{
  return 0; // TODO
}

sint CGamePad::GetRY()
{
  return 0; // TODO
}

sint CGamePad::GetLX()
{
  return 0; // TODO
}

sint CGamePad::GetLY()
{
  return 0; // TODO
}

f32 CGamePad::GetRXf()
{
  return static_cast<f32>(GetRX()) / 128.0f;
}

f32 CGamePad::GetRYf()
{
  return static_cast<f32>(GetRY()) / 128.0f;
}

f32 CGamePad::GetLXf()
{
  return static_cast<f32>(GetLX()) / 128.0f;
}

f32 CGamePad::GetLYf()
{
  return static_cast<f32>(GetLY()) / 128.0f;
}
