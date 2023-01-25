#pragma once
#include <functional>
#include <mutex>
#include <limits>
#include <type_traits>
#include <unordered_map>

#include "common/macros.h"
#include "common/types.h"

namespace host
{
  class pad_handler
  {
  public:
    // ctor
    pad_handler() = default;

    // dtor
    virtual ~pad_handler() = default;

  public:
    enum class buttons : u32
    {
      none       = 0,
      dpad_up    = 1 << 0,
      dpad_down  = 1 << 1,
      dpad_left  = 1 << 2,
      dpad_right = 1 << 3,
      start      = 1 << 4,
      select     = 1 << 5,
      home       = 1 << 6,
      l3         = 1 << 7,
      r3         = 1 << 8,
      l1         = 1 << 9,
      r1         = 1 << 10,
      triangle   = 1 << 11,
      cross      = 1 << 12,
      square     = 1 << 13,
      circle     = 1 << 14,
      l2         = 1 << 15,
      r2         = 1 << 16
    };

    enum class analog : u32
    {
      // TODO: Check if these properly align with the values in analog_table @ 0x3353E0
      left_horizonal = 1,
      left_vertical = 2,
      right_horizontal = 3,
      right_vertical = 4,
    };

    // These values come from pad_table @ 0x3351B0
    // TODO: Names
    enum class button_action
    {
      _0 = 0,
      _1 = 1,
      _2 = 2,
      _3 = 3,
      _4 = 4,
      _5 = 5,
      _6 = 6,
      _7 = 7,
      _8 = 8,
      _9 = 9,
      _10 = 10,
      _11 = 11,
      _12 = 12,
      _13 = 13,
      _14 = 14,
      _15 = 15,
      _16 = 16,
      _17 = 17,
      _18 = 18,
      _19 = 19,
      _20 = 20,
      _21 = 21,
      _22 = 22,
      _23 = 23,
      _24 = 24,
      _50 = 50,
      _51 = 51,
      _52 = 52,
      _53 = 53,
      _54 = 54,
      _55 = 55,
      _56 = 56,
      _100 = 100,
      _101 = 101,
      _102 = 102,
      _103 = 103,
      _104 = 104,
      _105 = 105,
      _106 = 106,
      _107 = 107,
      _108 = 108,
      _109 = 109,
      _120 = 120,
      _121 = 121,
      _122 = 122,
    };

    // These values come from pad_table @ 0x3351B0
    // TODO: Names
    enum class analog_action
    {
      _0 = 0,
      _1 = 1,
      _2 = 2,
      _3 = 3,
      _4 = 4,
      _5 = 5,
      _6 = 6,
      _7 = 7,
    };

    struct axis
    {
      f32 x{ 0.0f };
      f32 y{ 0.0f };
    };

    // pull for input
    virtual bool poll() = 0;

    // get the current button buffer
    inline buttons current_buttons()
    {
      return m_buttons;
    }

    // get the right stick values
    inline axis right_stick_axis()
    {
      return m_right_stick_axis;
    }

    // get the left stick values
    axis left_stick_axis()
    {
      return m_left_stick_axis;
    }

    // get the value of the triggers
    axis trigger_axis()
    {
      return m_trigger_axis;
    }

    /*
    * These functions provide an abstraction by allowing the programmer to register
    * raw inputs for a particular action the player may perform, then get the value
    * of the inputs by checking the action.
    *
    * For example, a simple usage may look something like this:
    *
    * pad_handler.register_button_action("photo-take", buttons::square);
    * ...
    * pad_handler.update_actions(); // handled in host_interface_base's start_game_frame
    * ...
    * if (pad_handler.check_button_action("photo_take"))
    * {
    *   // The user is pressing the button associated with taking a photo
    * }
    * else
    * {
    *   // The user is not pressing the button associated with taking a photo
    * }
    *
    * Note that the second argument for register_button_action need not necessarily be buttons::square,
    * but could come from some other source like a settings file. Therefore,
    * the action "photo-take" could be associated with any number of arbitrary
    * inputs, but the programmer does not have to worry about the raw inputs.
    *
    * NOTE: This MVP is designed only for gamepads, at the moment.
    */

    // Clear all input actions
    void clear_actions();

    // Register a button action which corresponds to an input
    void register_button_action(const button_action btn_action, buttons button, std::function<void(bool pressed)> callback = nullptr);
    void register_button_action(const button_action btn_action, const std::vector<buttons>& input_buttons, std::function<void(bool pressed)> callback = nullptr);

    // TODO: Unregistering (this one commit is getting too large anyways)

    // TODO:
    /*
    // Register an analog action which corresponds to an input
    void register_analog_action(const std::string_view& action, ... axis);
    */

    // Set a callback for a button action
    void set_button_action_callback(const button_action btn_action, std::function<void(bool pressed)> callback);

    // Set a callback for an analog action
    void set_analog_action_callback(const analog_action ana_action, std::function<void(f32 axis)> callback);

    // Check the value of a button action
    bool check_button_action(const button_action action);

    // Check the value of an analog action
    f32 check_analog_action(const analog_action ana_action);

    // Updates the values of actions
    void update_actions();

    // Handles action callbacks outside of a critical section
    void do_action_callbacks();

  protected:
    template<typename T>
    constexpr f32 normalize(T val)
    {
      static constexpr f32 max = static_cast<f32>(std::numeric_limits<T>::max());
      return static_cast<f32>(val) / max;
    }

    template<typename T>
    constexpr T deadzone(T val, T strength)
    {
      using signed_type = std::make_signed_t<T>;

      if (std::abs(val) < strength)
        return 0;

      return val;
    }

  protected:
    struct action_button
    {
      // last value; used to determine if the "pressed" state has changed for an action
      bool m_value{ false };
      buttons m_input_key{ buttons::none };
      std::function<void(bool pressed)> m_callback{ nullptr };
    };

    struct action_analog
    {
      f32 m_value{ 0.0f };
      // TODO: axis representation, need to do some digging in the game to match up values
      // TODO: Consider callback behavior for analog inputs; should it be called every update?
      std::function<void(f32 axis)> m_callback{ nullptr };
    };

    // TODO: Currently, callbacks are processed in arbitrary order. This may be an issue
    // if you want to process inputs in a set order, for example directional buttons before the confirm
    // button inside of a menu. If we needed to correct this issue, something we could try doing
    // is assigning an optional callback priority to each action, then sorting deferred callbacks
    // by their priority.

    struct action_button_callback
    {
      bool m_value{ false };
      std::function<void(bool pressed)> m_callback{ nullptr };
    };

    struct action_analog_callback
    {
      f32 m_value{ 0.0f };
      std::function<void(f32 axis)> m_callback{ nullptr };
    };

  protected:
    buttons m_buttons;

    axis m_right_stick_axis{ };
    axis m_left_stick_axis{ };
    axis m_trigger_axis{ };

    // Mapping of individual actions to raw inputs
    std::unordered_map<button_action, action_button> m_button_actions{ };
    std::unordered_map<analog_action, action_analog> m_analog_actions{ };

    // Queued callbacks (called outside critical section to avoid deadlocks)
    std::vector<action_button_callback> m_button_action_callbacks{ };
    std::vector<action_analog_callback> m_analog_action_callbacks{ };
  };
}

IMPLEMENT_ENUM_CLASS_BITWISE_OPERATORS(host::pad_handler::buttons);
