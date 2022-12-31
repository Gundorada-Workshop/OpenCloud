#include <Windows.h>

#include "common/dynamic_library.h"
#include "common/strings.h"
#include "common/synchro.h"

namespace common::synchro
{
  static dynamic_library s_kernel32_lib{ "kernel32.dll" };

  sint current_thread_id()
  {
    return GetCurrentThreadId();
  }

  void set_current_thread_name(std::string_view name)
  {
    using pfn_set_thread_description = decltype(&SetThreadDescription);

    static auto p_set_thread_description = s_kernel32_lib.load_pfn_type<pfn_set_thread_description>("SetThreadDescription");
    if (!p_set_thread_description)
      return;

    auto wname = strings::utf8_to_wstring_or_panic(name);

    p_set_thread_description(GetCurrentThread(), wname.c_str());
  }

  void sleep_current_thread(uint ms)
  {
    Sleep(ms);
  }
}