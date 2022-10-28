#include "CGamePad.h"

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
