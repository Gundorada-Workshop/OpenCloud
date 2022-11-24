#include <Windows.h>
#include <Xinput.h>
#include <intrin.h>

#include <mutex>

#include "common/log.h"
#include "common/bits.h"
#include "common/dynamic_library.h"

#include "host/xinput_pad_handler.h"

set_log_channel("xinput");

namespace host
{
  // xinput entry point
  static common::dynamic_library s_xinput{"xinput1_4.dll"};

  // function pointer types
  using pfn_xinput_get_state               = std::add_pointer_t<DWORD(DWORD, XINPUT_STATE*)>;
  using pfn_xinput_set_state               = std::add_pointer_t<DWORD(DWORD, XINPUT_VIBRATION*)>;
  using pfn_xinput_get_capabilities        = std::add_pointer_t<DWORD(DWORD, DWORD, XINPUT_CAPABILITIES*)>;
  using pfn_xinput_get_audio_device_ids    = std::add_pointer_t<DWORD(DWORD, LPWSTR, UINT*, LPWSTR, UINT*)>;
  using pfn_xinput_get_battery_information = std::add_pointer_t<DWORD(DWORD, BYTE, XINPUT_BATTERY_INFORMATION*)>;
  using pfn_xinput_get_keystroke           = std::add_pointer_t<DWORD(DWORD, DWORD, PXINPUT_KEYSTROKE)>;

  // function pointers
  static pfn_xinput_get_state               s_xinput_get_state{ nullptr };
  static pfn_xinput_set_state               s_xinput_set_state{ nullptr };
  static pfn_xinput_get_capabilities        s_xinput_get_capabilities{ nullptr };
  static pfn_xinput_get_audio_device_ids    s_xinput_get_audio_device_ids{ nullptr };
  static pfn_xinput_get_battery_information s_xinput_get_battery_information{ nullptr };
  static pfn_xinput_get_keystroke           s_xinput_get_keystroke{ nullptr };

  static constexpr u32 left_trigger_button_id = 1 << 16;
  static constexpr u32 right_trigger_button_id = 1 << 17;

  static std::unordered_map<u32, pad_handler::buttons> s_default_international_mapping =
  {
    { XINPUT_GAMEPAD_DPAD_UP,        pad_handler::buttons::dpad_up },
    { XINPUT_GAMEPAD_DPAD_DOWN,      pad_handler::buttons::dpad_down },
    { XINPUT_GAMEPAD_DPAD_LEFT,      pad_handler::buttons::dpad_left },
    { XINPUT_GAMEPAD_DPAD_RIGHT,     pad_handler::buttons::dpad_right },
    { XINPUT_GAMEPAD_START,          pad_handler::buttons::start },
    { XINPUT_GAMEPAD_BACK,           pad_handler::buttons::select },
    { XINPUT_GAMEPAD_LEFT_THUMB,     pad_handler::buttons::l3 },
    { XINPUT_GAMEPAD_RIGHT_THUMB,    pad_handler::buttons::r3 },
    { XINPUT_GAMEPAD_LEFT_SHOULDER,  pad_handler::buttons::l1 },
    { XINPUT_GAMEPAD_RIGHT_SHOULDER, pad_handler::buttons::r1 },
    { XINPUT_GAMEPAD_A,              pad_handler::buttons::cross },
    { XINPUT_GAMEPAD_B,              pad_handler::buttons::circle },
    { XINPUT_GAMEPAD_X,              pad_handler::buttons::square },
    { XINPUT_GAMEPAD_Y,              pad_handler::buttons::triangle },
    { left_trigger_button_id,        pad_handler::buttons::l2 },
    { right_trigger_button_id,       pad_handler::buttons::r2 }
  };

  static std::unordered_map<u32, pad_handler::buttons> s_default_japanese_mapping =
  {
    { XINPUT_GAMEPAD_DPAD_UP,        pad_handler::buttons::dpad_up },
    { XINPUT_GAMEPAD_DPAD_DOWN,      pad_handler::buttons::dpad_down },
    { XINPUT_GAMEPAD_DPAD_LEFT,      pad_handler::buttons::dpad_left },
    { XINPUT_GAMEPAD_DPAD_RIGHT,     pad_handler::buttons::dpad_right },
    { XINPUT_GAMEPAD_START,          pad_handler::buttons::start },
    { XINPUT_GAMEPAD_BACK,           pad_handler::buttons::select },
    { XINPUT_GAMEPAD_LEFT_THUMB,     pad_handler::buttons::l3 },
    { XINPUT_GAMEPAD_RIGHT_THUMB,    pad_handler::buttons::r3 },
    { XINPUT_GAMEPAD_LEFT_SHOULDER,  pad_handler::buttons::l1 },
    { XINPUT_GAMEPAD_RIGHT_SHOULDER, pad_handler::buttons::r1 },
    { XINPUT_GAMEPAD_A,              pad_handler::buttons::circle },
    { XINPUT_GAMEPAD_B,              pad_handler::buttons::cross },
    { XINPUT_GAMEPAD_X,              pad_handler::buttons::square },
    { XINPUT_GAMEPAD_Y,              pad_handler::buttons::triangle },
    { left_trigger_button_id,        pad_handler::buttons::l2 },
    { right_trigger_button_id,       pad_handler::buttons::r2 }
  };

  xinput_pad_handler::xinput_pad_handler()
    : m_mapping{ s_default_international_mapping }
  {
  };

  xinput_pad_handler::~xinput_pad_handler() = default;

  static bool load_xinput_library()
  {
    s_xinput_get_state = s_xinput.load_pfn_type<pfn_xinput_get_state>("XInputGetState");
    if (!s_xinput_get_state)
    {
      log_error("Failed to load XInputGetState");

      return false;
    }

    // TODO: ordinal get state for home button
    s_xinput_set_state = s_xinput.load_pfn_type<pfn_xinput_set_state>("XInputSetState");
    if (!s_xinput_set_state)
    {
      log_error("Failed to load XInputSetState");

      return false;
    }

    // these aren't required
    s_xinput_get_capabilities        = s_xinput.load_pfn_type<pfn_xinput_get_capabilities>("XInputGetCapabilities");
    s_xinput_get_audio_device_ids    = s_xinput.load_pfn_type<pfn_xinput_get_audio_device_ids>("XInputGetAudioDeviceIds");
    s_xinput_get_battery_information = s_xinput.load_pfn_type<pfn_xinput_get_battery_information>("XInputGetBatteryInformation");
    s_xinput_get_keystroke           = s_xinput.load_pfn_type<pfn_xinput_get_keystroke>("XInputGetKeystroke");

    return true;
  }

  std::unique_ptr<pad_handler> xinput_pad_handler::create()
  {
    if (!load_xinput_library())
      return nullptr;

    return std::make_unique<xinput_pad_handler>();
  }

  bool xinput_pad_handler::poll()
  {
    XINPUT_STATE state;
    if (s_xinput_get_state(0, &state) != ERROR_SUCCESS)
      return false;

    const auto left_thumb_x = deadzone(state.Gamepad.sThumbLX, static_cast<SHORT>(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
    const auto left_thumb_y = deadzone(state.Gamepad.sThumbLY, static_cast<SHORT>(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));

    const auto right_thumb_x = deadzone(state.Gamepad.sThumbRX, static_cast<SHORT>(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
    const auto right_thumb_y = deadzone(state.Gamepad.sThumbRY, static_cast<SHORT>(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));

    const auto left_trigger  = deadzone(state.Gamepad.bLeftTrigger,  static_cast<BYTE>(XINPUT_GAMEPAD_TRIGGER_THRESHOLD));
    const auto right_trigger = deadzone(state.Gamepad.bRightTrigger, static_cast<BYTE>(XINPUT_GAMEPAD_TRIGGER_THRESHOLD));

    axis left_axis =
    {
      .x = normalize(left_thumb_x),
      .y = normalize(left_thumb_y)
    };

    axis right_axis =
    {
      .x = normalize(right_thumb_x),
      .y = normalize(right_thumb_y)
    };

    axis trigger =
    {
      .x = normalize(left_trigger),
      .y = normalize(right_trigger)
    };

    auto xinput_buttons = state.Gamepad.wButtons;
    buttons current_buttons{ };

    while (xinput_buttons)
    {
      auto lsb = common::bits::lsb(xinput_buttons);

      current_buttons |= m_mapping[lsb];
      xinput_buttons &= ~(lsb);
    }

    // we have to treat r2 and l2 as special
    // in game these are not triggers but buttons
    if (trigger.x)
      current_buttons |= m_mapping[left_trigger_button_id];

    if (trigger.y)
      current_buttons |= m_mapping[right_trigger_button_id];

    // critical section
    {
      std::lock_guard<std::mutex> lk(m_input_mutex);

      m_current_button_buffer ^= 1;

      m_button_buffers[m_current_button_buffer] = current_buttons;

      m_right_stick_axis = std::move(right_axis);
      m_left_stick_axis  = std::move(left_axis);
      m_trigger_axis     = std::move(trigger);
    }

    return true;
  }
}
