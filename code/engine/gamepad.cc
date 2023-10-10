#include <cmath>

#include "common/debug.h"
#include "common/macros.h"
#include "common/log.h"

#include "engine/gamepad.h"

set_log_channel("gamepad");

// 003D76E0
CGamePad GamePad;
// 003D7B60
CPadControl PadCtrl;

// 0014a930
void CGamePad::Update()
{
  log_trace("CGamePad::Update()");

  todo;
}

// 0014aef0
MAYBE_UNUSED static sint AxisCalibration(sint axis)
{
  log_trace("AxisCalibration({})", axis);

  // dead zone
  if(std::abs(axis - 128) < 50)
    return 0;

  if((axis - 128) < 1)
    return ((axis - 78) * 128) / 78;

  return ((axis - 177) * 128) / 78;
}

sint CGamePad::GetRX()
{
  log_trace("GetRX()");

  todo;

  return 0; // TODO
}

sint CGamePad::GetRY()
{
  log_trace("GetRY()");

  todo;

  return 0; // TODO
}

sint CGamePad::GetLX()
{
  log_trace("GetLX()");

  todo;

  return 0; // TODO
}

sint CGamePad::GetLY()
{
  log_trace("GetRY()");

  todo;

  return 0; // TODO
}

f32 CGamePad::GetRXf()
{
  log_trace("GetRXf()");

  return static_cast<f32>(GetRX()) / 128.0f;
}

f32 CGamePad::GetRYf()
{
  log_trace("GetRYf()");

  return static_cast<f32>(GetRY()) / 128.0f;
}

f32 CGamePad::GetLXf()
{
  log_trace("GetLXf()");

  return static_cast<f32>(GetLX()) / 128.0f;
}

f32 CGamePad::GetLYf()
{
  log_trace("GetLYf()");

  return static_cast<f32>(GetLY()) / 128.0f;
}

// 002ED4E0
bool CPadControl::Btn(MAYBE_UNUSED int button)
{
  log_trace("CPadControl::Btn({})", button);

  todo;
  return false;
}

// 002ED550
void CPadControl::Update(MAYBE_UNUSED CGamePad* game_pad)
{
  log_trace("CPadControl::Update({})", fmt::ptr(game_pad));

  todo;
}