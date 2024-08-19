#pragma once

#include "common/types.h"
#include "common/strings.h"

// Compiler
#if defined(_MSC_VER)
  #define PLATFORM_COMPILER_MSVC 1
#elif defined(__GNUC__)
  #define PLATFORM_COMPILER_GNU 1
#elif defined(__clang__)
  #define PLATFORM_COMPILER_CLANG 1
#else
  #error Unknown Compiler
#endif

// OS
// TODO Android and IOS
#if defined(_WIN32)
  #define PLATFORM_OS_WINDOWS 1
#elif defined(__linux__)
  #define PLATFORM_OS_LINUX 1
#elif defined(__FreeBSD__)
  #define PLATFORM_OS_FREEBSD 1
#elif defined(__APPLE__)
  #define PLATFORM_OS_APPLE 1
#else
  #error Unknown OS
#endif

// Arch
#if PLATFORM_COMPILER_MSVC
  #if defined(_M_X64)
    #define PLATFORM_ARCH_X64 1
  #elif defined(_M_IX86)
    #define PLATFORM_ARCH_X86 1
  #elif defined(_M_ARM64)
    #define PLATFORM_ARCH_ARM64 1
  #elif defined(_M_ARM)
    #define PLATFORM_ARCH_ARM32 1
  #else
    #error Unknown CPU Arch
  #endif
#else // GCC and Clang (others are handled above)
  #if defined(__x86_64__)
    #define PLATFORM_ARCH_X64 1
  #elif defined(__i386__)
    #define PLATFORM_ARCH_X86 1
  #elif defined(__aarch64__)
    #define PLATFORM_ARCH_ARM64 1
  #elif defined(__arm__)
    #define PLATFORM_ARCH_ARM32 1
  #else
    #error Unknown CPU Arch
  #endif
#endif

// Special case worth knowing about
#if PLATFORM_OS_APPLE && PLATFORM_ARCH_ARM64
#define PLATFORM_APPLE_SILICON 1
#endif

// wayland
#define PLATFORM_USE_WAYLAND 0

namespace common
{
  enum class os
  {
    unknown,
    windows,
    linux,
    freebsd,
    macos
  };

  enum class cpu_arch
  {
    unknown,
    x64,
    x86,
    arm64,
    arm32
  };

  enum class compiler
  {
    unknown,
    msvc,
    gnu,
    clang
  };

  constexpr os os_type()
  {
    #if PLATFORM_OS_WINDOWS
      return os::windows;
    #elif PLATFORM_OS_LINUX
      return os::linux;
    #elif PLATFORM_OS_FREEBSD
      return os::freebsd;
    #elif PLATFORM_OS_APPLE
      return os::macos;
    #else
      return os::unknown;
    #endif
  }

  constexpr cpu_arch cpu_type()
  {
    #if PLATFORM_ARCH_X64
      return cpu_arch::x64;
    #elif PLATFORM_ARCH_X86
      return cpu_arch::x86;
    #elif PLATFORM_ARCH_ARM64
      return cpu_arch::arm64;
    #elif PLATFORM_ARCH_ARM32
      return cpu_arch::arm32;
    #else
      return cpu_arch::unknown;
    #endif
  }

  constexpr compiler compiler_type()
  {
    #if PLATFORM_COMPILER_MSVC
      return compiler::msvc;
    #elif PLATFORM_COMPILER_CLANG
      return compiler::clang;
    #elif PLATFORM_COMPILER_GCC
      return compiler::gcc;
    #else
      return compiler::unknown;
    #endif
  }

  // returns a string representing the operating system by name
  constexpr std::string_view os_name()
  {
    switch (os_type())
    {
    case os::windows:
      return "Windows";
    case os::linux:
      return "Linux";
    case os::freebsd:
      return "FreeBSD";
    case os::macos:
      return "MacOS";
    default:
      break;
    }

    return "Unknown";
  }

  // returns a string representing the cpu arch by name
  constexpr std::string_view cpu_name()
  {
    switch (cpu_type())
    {
    case cpu_arch::x64:
      return "x64";
    case cpu_arch::x86:
      return "x86";
    case cpu_arch::arm64:
      return "arm64";
    case cpu_arch::arm32:
      return "arm32";
    default:
      break;
    }

    return "Unknown";
  }

  // returns a string representing the compiler by name
  constexpr std::string_view compiler_name()
  {
    switch (compiler_type())
    {
    case compiler::msvc:
      return "MSVC";
    case compiler::gnu:
      return "GCC";
    case compiler::clang:
      return "Clang";
    default:
      break;
    }

    return "Unknown";
  }
}