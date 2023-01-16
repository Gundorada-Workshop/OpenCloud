#pragma once
#include <unordered_map>
#include <vector>

#include "common/types.h"

#include "host/pad_handler.h"

/*
* CPadControl creates an abstraction by allowing the programmer to register
* raw inputs for a particular action the player may perform, then get the value
* of the inputs by checking the action.
* 
* For example, a simple usage may look something like this:
* 
* PadCtrl.RegisterBtn("photo-take", SQUARE);
* ...
* PadCtrl.Update();
* ...
* if (PadCtrl.Btn("photo_take"))
* {
*   // The user is pressing the button associated with taking a photo
* }
* else
* {
*   // The user is not pressing the button associated with taking a photo
* }
* 
* Note that the second argument for RegisterBtn need not necessarily be SQUARE,
* but could come from some other source like a settings file. Therefore,
* the action "photo-take" could be associated with any number of arbitrary
* inputs, but the programmer does not have to worry about the raw inputs.
* 
* NOTE: This MVP is designed only for gamepads, at the moment.
*/

enum class EPadAxis
{
  _1 = 1,
  _2 = 2,
  _3 = 3,
  _4 = 4,
};

struct PAD_ANALOG
{
  f32 m_value{ 0.0f };
  EPadAxis m_input_axis{};
};

struct PAD_BUTTON
{
  bool m_value{ false };
  host::pad_handler::buttons m_input_key{};
};

class CPadControl
{
public:

  // 002ED3E0
  void Reset();

  // 002ED460
  void RegisterBtn(const std::string_view& action_name, host::pad_handler::buttons btn1, host::pad_handler::buttons btn2 = host::pad_handler::buttons::none);

  // 002ED4A0
  void RegisterAnalog(const std::string_view& action_name, EPadAxis axis);

  // 002ED4E0
  bool Btn(const std::string_view& action_name);

  // 002ED520
  f32 Analog(const std::string_view& action_name);

  // 002ED550
  void Update();

private:
  std::unordered_map<std::string, PAD_BUTTON> m_buttons{};
  std::unordered_map<std::string, PAD_ANALOG> m_analog{};
};

extern std::unique_ptr<CPadControl> PadCtrl = std::make_unique<CPadControl>();
