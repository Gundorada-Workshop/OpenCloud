#include "common/platform.h"

#if PLATFORM_OS_WINDOWS
#include <Windows.h>
#include <DbgHelp.h>
#elif PLATFORM_OS_LINUX
#include <execinfo.h>
#include <signal.h>
#endif

#include "common/assert.h"
#include "common/console.h"
#include "common/backtrace.h"

namespace common
{
  void rassert(std::string_view msg)
  {
    console::write("The application experienced an assertion\n");
    console::write_format("{}\n", msg);

    print_trace(50);

    #if PLATFORM_OS_WINDOWS
    if (IsDebuggerPresent() && console::prompt("Would you like to start debugging?"))
    {
      DebugBreak();
    }
    #elif PLATFORM_OS_LINUX
      #if defined(SIGTRAP)
        raise(SIGTRAP);
      #endif
    #else
      #error Unsupported platform
    #endif
  }
}