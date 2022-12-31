#include <Windows.h>
#include <cstdio>
#include <iostream>

#include "console.h"

namespace common::console
{
#if defined(_WIN32)
  static bool s_console_alloc{ false };

  static HANDLE s_out_handle{ NULL };
  static HANDLE s_err_handle{ NULL };
  static HANDLE s_in_handle{ NULL };

  // enables color output
  static bool enable_vt100(HANDLE handle)
  {
    DWORD mode;
    if (!GetConsoleMode(handle, &mode))
      return false;

    if (!SetConsoleMode(handle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
      return false;

    return true;
  }

  // attaches to the parent process
  static bool attach_to_parent_process()
  {
    // https://docs.microsoft.com/en-us/windows/console/attachconsole
    BOOL res = AttachConsole(ATTACH_PARENT_PROCESS);

    return static_cast<bool>(res);
  }

  // create a console
  static bool create_console()
  {
    // https://docs.microsoft.com/en-us/windows/console/allocconsole
    s_console_alloc = static_cast<bool>(AllocConsole());

    return s_console_alloc;
  }

  static void release_console()
  {
    if (s_console_alloc)
      FreeConsole();

    s_console_alloc = false;
  }

  // redirect stdio
  static bool redirect_standard_io()
  {
    std::FILE* fp;

    // https://docs.microsoft.com/en-us/windows/console/getstdhandle
    s_out_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (s_out_handle != INVALID_HANDLE_VALUE)
    {
      // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/freopen-s-wfreopen-s?view=msvc-170
      if (freopen_s(&fp, "CONOUT$", "w", stdout) != 0)
        return false;

      enable_vt100(s_out_handle);
    }

    // https://docs.microsoft.com/en-us/windows/console/getstdhandle
    s_in_handle = GetStdHandle(STD_INPUT_HANDLE);

    if (s_in_handle != INVALID_HANDLE_VALUE)
    {
      // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/freopen-s-wfreopen-s?view=msvc-170
      if (freopen_s(&fp, "CONIN$", "r", stdin) != 0)
        return false;

      enable_vt100(s_in_handle);
    }

    // https://docs.microsoft.com/en-us/windows/console/getstdhandle
    s_err_handle = GetStdHandle(STD_ERROR_HANDLE);

    if (s_err_handle != INVALID_HANDLE_VALUE)
    {
      // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/freopen-s-wfreopen-s?view=msvc-170
      if (freopen_s(&fp, "CONOUT$", "w", stderr) != 0)
        return false;

      enable_vt100(s_err_handle);
    }

    return true;
  }
#endif

  // sync with ios
  static bool sync_ios()
  {
    // sync C++ streams
    if (!std::ios::sync_with_stdio(true))
      return false;

    // wide streams
    std::wcout.clear();
    std::wcin.clear();
    std::wcerr.clear();

    // standard streams
    std::cout.clear();
    std::cerr.clear();
    std::cin.clear();

    return true;
  }

  bool initialize()
  {
#if defined(_WIN32)
    // https://docs.microsoft.com/en-us/windows/console/getstdhandle
    HANDLE old_out_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // no console currently (WinMain)
    if (!old_out_handle)
    {
      // either attach or create
      // attach when we are calling from a terminal
      // create when we are calling from the application
      if (!attach_to_parent_process() && !create_console())
        return false;

      if (!redirect_standard_io())
        return false;

      if (!sync_ios())
        return false;
    }
#endif

    return true;
  }

  void shutdown()
  {
    release_console();
  }

  void write(std::string_view msg)
  {
    const auto s = std::string{ msg };

#if defined(_WIN32)
    const auto wide = strings::utf8_to_wstring_or_none(s);
    const auto size = static_cast<DWORD>(wide.size());

    WriteConsoleW(s_out_handle, wide.c_str(), size, NULL, NULL);
#else
    fprintf(stdout, "%s", s.c_str());
#endif
  }

  void write_error(std::string_view msg)
  {
    const auto s = std::string{ msg };

#if defined(_WIN32)
    const auto wide = strings::utf8_to_wstring_or_none(s);
    const auto size = static_cast<DWORD>(wide.size());

    WriteConsoleW(s_err_handle, wide.c_str(), size, NULL, NULL);
#else
    fprintf(stderr, "%s", s.c_str());
#endif
  }

  std::string read()
  {
    std::string line;
    std::getline(std::cin, line);

    return line;
  }

  bool prompt(std::string_view question)
  {
    write_format("{} [y/n]: ", question);

    const auto res = read();

    if (res == "y" || res == "Y")
      return true;

    return false;
  }
}
