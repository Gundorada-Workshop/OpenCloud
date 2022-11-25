#pragma once
#include <mutex>
#include <limits>
#include <type_traits>
#include <unordered_map>

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
    buttons m_buttons;

    axis m_right_stick_axis{ };
    axis m_left_stick_axis{ };
    axis m_trigger_axis{ };
  };
}

IMPLEMENT_ENUM_CLASS_BITWISE_OPERATORS(host::pad_handler::buttons);
