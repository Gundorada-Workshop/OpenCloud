#if defined(_WIN32)
    #include <Windows.h>
#elif defined(__linux__)
    #include <time.h>
#else
    static_assert(false, "clock.cc is not implemented for this operating system");
#endif

#include <mutex>
#include <list>

#include "common/clock.h"
#include "common/debug.h"

namespace common::time
{
  // we can check for 0 because the WIN32 API gurentees non-zero unless < XP
  // not something we need to worry about
  // make it thread local so each thread has it's own copy, though
  static thread_local cycles_type s_cached_cycles_per_second{ 0 };

  cycles_type current_cycle_count()
  {
    #if defined(_WIN32)
    // NOTE: on systems XP+ this never fails and count is never 0
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);

    return count.QuadPart;
    #elif defined(__linux__)
    timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC_RAW, &ts))
      debug::panic("Failed to get time!");
    return (u64)ts.tv_nsec + (u64)1E9 * (u64)ts.tv_sec;
    #else
    static_assert(false, "Not implemented");
    #endif
  }

  cycles_type cycles_per_second()
  {
    // this value is the same from reboot
    // so there is no sense in querying the OS for it more than once
    if (!s_cached_cycles_per_second)
    {
      #if defined(_WIN32)
      // NOTE: on systems XP+ this never fails and freq is never 0
      LARGE_INTEGER freq;
      QueryPerformanceFrequency(&freq);

      s_cached_cycles_per_second = freq.QuadPart;
      #elif defined(__linux__)
      return (u64)1E9;
      #else
      static_assert(false, "Not implemented");
      #endif
    }

    return s_cached_cycles_per_second;
  }

  seconds_type cycles_to_seconds(cycles_type cycles)
  {
    return static_cast<seconds_type>(cycles) / static_cast<seconds_type>(current_cycle_count());
  }

  cycles_type seconds_to_cycles(seconds_type seconds)
  {
    return static_cast<cycles_type>(seconds * cycles_per_second());
  }

  stopwatch::stopwatch()
  {
    start();
  }

  void stopwatch::start()
  {
    reset();

    m_start_cycle = current_cycle_count();
    m_started = true;
  }

  void stopwatch::stop()
  {
    if (m_started)
      m_end_cycle = current_cycle_count();
    m_started = false;
  }

  void stopwatch::reset()
  {
    m_started = false;
    m_start_cycle = 0;
    m_end_cycle = 0;
  }

  cycles_type stopwatch::delta_cycles()
  {
    if (m_started)
      return current_cycle_count() - m_start_cycle;

    return m_end_cycle - m_start_cycle;
  }

  seconds_type stopwatch::delta_seconds()
  {
    const auto cycles = delta_cycles();

    return cycles_to_seconds(cycles);
  }
}
