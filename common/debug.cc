#include <vector>
#include <limits>

#if defined(_WIN32)
#include <Windows.h>
#include <DbgHelp.h>
#endif

#include "types.h"
#include "console.h"
#include "debug.h"

namespace common::debug
{
#if defined(_WIN32)
  static std::vector<std::string> backtrace(uint depth)
  {
    const auto process = GetCurrentProcess();
    const auto thread = GetCurrentThread();

    // https://learn.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-rtlcapturecontext
    // get the caller context
    CONTEXT context = {};
    RtlCaptureContext(&context);

    STACKFRAME64 frame = {};

    // instruction pointer
    frame.AddrPC.Offset = context.Rip;
    frame.AddrPC.Mode = ADDRESS_MODE::AddrModeFlat;

    // stack pointer
    frame.AddrStack.Offset = context.Rsp;
    frame.AddrStack.Mode = ADDRESS_MODE::AddrModeFlat;

    // base pointer
    frame.AddrFrame.Offset = context.Rbp;
    frame.AddrFrame.Mode = ADDRESS_MODE::AddrModeFlat;

    // https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-syminitialize
    // we don't need a symbol directory, working dir is already in the search
    SymInitializeW(process, NULL, true);

    // https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-symsetoptions
    // load line numbers
    SymSetOptions(SYMOPT_LOAD_LINES);

    // we need a buffer of at least struct size + max name size
    constexpr auto ALLOC_SIZE = sizeof(SYMBOL_INFOW) + (sizeof(TCHAR) * 256);

    // we'll reuse it instead of allocing/freeing in a loop
    auto symbols = reinterpret_cast<SYMBOL_INFOW*>(LocalAlloc(LPTR, ALLOC_SIZE));
    if (symbols == NULL)
    {
      return {};
    }

    symbols->SizeOfStruct = sizeof(SYMBOL_INFOW);
    symbols->MaxNameLen = 256;

    std::vector<std::string> out;

    // pop off the top
    // https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-stackwalk64
    while (StackWalk64(IMAGE_FILE_MACHINE_AMD64, process, thread, &frame, &context, NULL,
                          SymFunctionTableAccess64, SymGetModuleBase64, NULL) && depth--)
    {
      DWORD64 unused;
      // https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-symfromaddr
      SymFromAddrW(process, frame.AddrPC.Offset, &unused, symbols);

      if (symbols->NameLen)
      {
        auto name = strings::to_utf8({ symbols->Name, symbols->NameLen });

        IMAGEHLP_LINEW64 line_info = {};
        line_info.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

        DWORD unused2;
        if (SymGetLineFromAddrW64(process, frame.AddrPC.Offset, &unused2, &line_info))
        {
          // note: null terminated
          auto path = strings::to_utf8({ line_info.FileName });

          if (name && path)
          {
            auto formatted = strings::format("{}:{} {}", *path, line_info.LineNumber, *name);

            out.push_back(std::move(formatted));
          }

          // got all the info we need
          continue;
        }

        if (name)
          out.push_back(std::move(*name));

        // didn't get extra symbol info (line number, etc)
        // but we got at name at least
        continue;
      }

      // we didn't get anything other than an addr
      out.push_back(strings::format("{:x}", frame.AddrPC.Offset));
    }

    LocalFree(symbols);

    return out;
  }
#endif

  void print_trace(uint depth)
  {
    const auto bt = backtrace(depth);

    for (const auto& line : bt)
    {
      console::write_format("{}\n", line);
    }
  }

  void runtime_assert(std::string_view msg)
  {
    console::write("ASSERTION FAILURE!!!\n");
    console::write_format("{}\n", msg);

    print_trace(50);

#if defined(_WIN32)
    if (IsDebuggerPresent() && console::prompt("Would you like to start debugging?"))
      DebugBreak();
#endif
  }

  void panic(std::string_view msg)
  {
    console::write("PANIC!!!\n");
    console::write_format("{}\n", msg);

#if defined(_WIN32)
    if (IsDebuggerPresent())
      DebugBreak();

    TerminateProcess(GetCurrentProcess(), 0xDEADBEEF);
#endif
  }
}
