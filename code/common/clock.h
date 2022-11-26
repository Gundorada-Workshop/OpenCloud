#pragma once
#include <string_view>

#include "common/types.h"

constexpr float GAME_FPS = 29.97f;
constexpr float GAME_DT = 1.0f / GAME_FPS;
constexpr float MENU_FPS = 59.94f;
constexpr float MENU_DT = 1.0f / MENU_FPS;

namespace common::time
{
  using seconds_type = f64;
  using cycles_type = u64;

  // get current cpu counter
  cycles_type current_cycle_count();

  // get the current cpu counter frequency
  cycles_type cycles_per_second();

  // convert counter cycles to seconds
  // warning: do not use this with large cycle counts
  seconds_type cycles_to_seconds(cycles_type cycles);

  // convert seconds to cycles
  cycles_type seconds_to_cycles(seconds_type val);

  // convert from milliseconds
  constexpr seconds_type milliseconds(f64 val)
  {
    return val / 1000.0;
  }

  // convert from microseconds
  constexpr seconds_type microseconds(f64 val)
  {
    return val / 1000000.0;
  }

  // convert from nanoseconds
  constexpr seconds_type nanoseconds(f64 val)
  {
    return val / 1000000000.0;
  }

  // simple timer class
  class stopwatch
  {
  public:
    // constructs a new timer
    // calls start
    stopwatch();

  public:
    // start the timer
    void start();

    // stop the timer
    void stop();

    // reset the timer
    void reset();

    // number of cycles since start to end
    // or start to now if stop wasn't called
    cycles_type delta_cycles();

    // number of seconds since the start to end
    // or start to now if stop wasn't called
    seconds_type delta_seconds();

  private:
    // the cycle we started at
    cycles_type m_start_cycle{ 0 };

    // the cycle we ended at
    cycles_type m_end_cycle{ 0 };

    // whether the timer is started
    bool m_started{ false };
  };
}
