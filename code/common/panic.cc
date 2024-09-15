#include "common/panic.h"
#include "common/console.h"
#include "common/platform.h"
#include "common/backtrace.h"

#if PLATFORM_OS_WINDOWS
#include <Windows.h>
#include <DbgHelp.h>
#elif PLATFORM_OS_LINUX
#include <execinfo.h>
#include <signal.h>
#endif

namespace common
{
  void panic(std::string_view msg)
  {
    console::write("The application has panicked and needs to exit\n");
    console::write_format("{}\n", msg);

    print_trace(50);

    #if PLATFORM_OS_WINDOWS
      if (IsDebuggerPresent())
      {
        DebugBreak();
      }

      TerminateProcess(GetCurrentProcess(), 0xDEADBEEF);
    #elif PLATFORM_OS_LINUX
      #if defined(SIGTRAP)
        raise(SIGTRAP);
      #endif

      kill(getpid(), SIGKILL);
    #endif
  }
}