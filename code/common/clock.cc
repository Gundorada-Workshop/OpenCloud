#include <Windows.h>
#include <optional>

#include "common/clock.h"

namespace common::time
{
  // we can check for 0 because the WIN32 API gurentees non-zero unless < XP
  // not something we need to worry about
  static cycles_type s_cached_cycles_per_second{ 0 };

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
    if (!s_cached_cycles_per_second) [[unlikely]]
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
}
