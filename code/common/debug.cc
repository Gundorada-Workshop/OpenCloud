#include <vector>
#include <limits>

#if defined(_WIN32)
#include <Windows.h>
#include <DbgHelp.h>
#elif defined(__linux__)
#include <execinfo.h>
#include <signal.h>
#endif

#include "common/types.h"
#include "common/console.h"
#include "common/debug.h"

namespace common::debug
{
  static std::vector<std::string> backtrace(uint depth)
  {
    std::vector<std::string> out;

  #if defined(_WIN32)
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
        auto name = strings::wstring_to_utf8_or_none({ symbols->Name, symbols->NameLen });

        IMAGEHLP_LINEW64 line_info = {};
        line_info.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

        DWORD unused2;
        if (SymGetLineFromAddrW64(process, frame.AddrPC.Offset, &unused2, &line_info))
        {
          // note: null terminated
          auto path = strings::wstring_to_utf8_or_none({ line_info.FileName });
          name = strings::format("{}:{} {}", path, line_info.LineNumber, name);
        }

        out.push_back(std::move(name));

        // didn't get extra symbol info (line number, etc)
        // but we got at name at least
        continue;
      }

      // we didn't get anything other than an addr
      out.push_back(strings::format("{:x}", frame.AddrPC.Offset));
    }

    LocalFree(symbols);

  #elif defined(__linux__)
    // Extract the backtrace to the requested depth
    // Note that this doesn't give particularly useful results without
    // the -rdynamic linker option
    std::vector<void*> frame_stack{ depth };
    ::backtrace(frame_stack.data(), depth);
    char** symbols;
    symbols = ::backtrace_symbols(frame_stack.data(), depth); // Warning: uses malloc() under the hood, requires free()
    
    // Convert to std::string
    for (uint i = 0; i < depth; ++i)
    {
      out.emplace_back(symbols[i]);
    }
    
    // Cleaning up after backtrace_symbols
    free(symbols);
  #endif

    return out;
  }

  void print_trace(uint depth)
  {
    const auto bt = backtrace(depth);

    for (const auto& line : bt)
      console::write_format("{}\n", line);
  }

  void runtime_assert(std::string_view msg)
  {
    console::write("ASSERTION FAILURE!!!\n");
    console::write_format("{}\n", msg);

    print_trace(50);

    #if defined(_WIN32)
      if (IsDebuggerPresent() && console::prompt("Would you like to start debugging?"))
       DebugBreak();
    #elif defined(__linux__)
      #if defined(SIGTRAP)
        raise(SIGTRAP);
      #endif
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
    #elif defined(__linux__)
      #if defined(SIGTRAP)
        raise(SIGTRAP);
      #endif
      kill(getpid(), SIGKILL);
    #endif
  }
}
