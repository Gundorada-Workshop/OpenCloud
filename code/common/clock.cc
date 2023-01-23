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

namespace common::time
{
  #if defined(_WIN32)
  // we can check for 0 because the WIN32 API gurentees non-zero unless < XP
  // not something we need to worry about
  // make it thread local so each thread has it's own copy, though
  static thread_local cycles_type s_cached_cycles_per_second{ 0 };

  cycles_type current_cycle_count()
  {
    // NOTE: on systems XP+ this never fails and count is never 0
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);

    return count.QuadPart;
  }

  cycles_type cycles_per_second()
  {
    // this value is the same from reboot
    // so there is no sense in querying the OS for it more than once
    if (!s_cached_cycles_per_second)
    {
      // NOTE: on systems XP+ this never fails and freq is never 0
      LARGE_INTEGER freq;
      QueryPerformanceFrequency(&freq);

      s_cached_cycles_per_second = freq.QuadPart;
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
  #endif

  #if defined(__GNUG__) || defined(__clang__)
  seconds_type current_timestamp()
  {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);

    seconds_type out;
    return static_cast<seconds_type>(ts.tv_sec) + (1E-9)*static_cast<seconds_type>(ts.tv_nsec);
  }
  #endif

  stopwatch::stopwatch()
  {
    start();
  }

  void stopwatch::start()
  {
    reset();

    #if defined(_WIN32)
      m_start_cycle = current_cycle_count();
    #elif defined(__linux__)
      m_start_time = current_timestamp();
    #else
      static_assert(false, "Not implemented");
    #endif
    m_started = true;
  }

  void stopwatch::stop()
  {
    if (m_started)
    #if defined(_WIN32)
      m_end_cycle = current_cycle_count();
    #elif defined(__linux__)
      m_end_time = current_timestamp();
    #else
      static_assert(false, "Not implemented");
    #endif
    m_started = false;
  }

  void stopwatch::reset()
  {
    m_started = false;
    #if defined(_WIN32)
        m_start_cycle = 0;
        m_end_cycle = 0;
    #elif defined(__linux__)
        m_start_time = 0.;
        m_end_time   = 0.;
    #else
        static_assert(false, "Not implemented");
    #endif
  }

  #if defined(_WIN32)
  cycles_type stopwatch::delta_cycles()
  {
    if (m_started)
      return current_cycle_count() - m_start_cycle;

    return m_end_cycle - m_start_cycle;
  }
  #endif

  seconds_type stopwatch::delta_seconds()
  {
    #if defined(_WIN32)
        const auto cycles = delta_cycles();

        return cycles_to_seconds(cycles);
    #elif defined(__linux__)
        return m_end_time - m_start_time;
    #else
        static_assert(false, "Not Implemented");
    #endif
  }
}
