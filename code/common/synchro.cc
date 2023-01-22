#if defined(_WIN32)
    #include <Windows.h>
#elif defined(__linux__)
    #include <pthread.h>
    #include <time.h>
#else
  static_assert(false, "synchro.cc not defined for this operating system");
#endif

#include "common/debug.h"
#include "common/dynamic_library.h"
#include "common/strings.h"
#include "common/synchro.h"

namespace common::synchro
{
  #if defined(_WIN32)
  static dynamic_library s_kernel32_lib{ "kernel32.dll" };
  #endif

  sint current_thread_id()
  {
    #if defined(_WIN32)
        return GetCurrentThreadId();
    #elif defined(__linux__)
        return static_cast<sint>(pthread_self()); // Return type might need to be OS-dependent
    #else
        static_assert(false, "Not implemented");
    #endif
  }

  void set_current_thread_name(std::string_view name)
  {
    #if defined(_WIN32)
      using pfn_set_thread_description = decltype(&SetThreadDescription);

      static auto p_set_thread_description = s_kernel32_lib.load_pfn_type<pfn_set_thread_description>("SetThreadDescription");
      if (!p_set_thread_description)
        return;

      auto wname = strings::utf8_to_wstring_or_panic(name);

      p_set_thread_description(GetCurrentThread(), wname.c_str());
    #elif defined(__linux__)
      pthread_setname_np(pthread_self(), name.data());
    #else
      static_assert(false, "Not implemented");
    #endif
  }

  void sleep_current_thread(uint ms)
  {
    #if defined(_WIN32)
      Sleep(ms);
    #elif defined(__linux__)
      timespec ts;
      ts.tv_sec  = ms / 1000;
      ts.tv_nsec = (ms % 1000) * 1000000;
      nanosleep(&ts, NULL);
    #else
      static_assert(false, "Not implemented");
    #endif
  }
}