#include "common/strings.h"
#include "common/debug.h"
#include "common/dynamic_library.h"

namespace common
{
  dynamic_library::dynamic_library(std::string_view name)
  {
    assert_panic(open(name));
  }

  bool dynamic_library::open(std::string_view name)
  {
    const auto wide_name = strings::utf8_to_wstring(name);

    if (!wide_name)
      panicf("Failed to convert name for dynamic library {}", name);

    HMODULE handle = LoadLibraryW(wide_name->c_str());
    if (!handle)
      return false;

    m_handle.reset(handle);

    return true;
  }

  void* dynamic_library::load_pfn(std::string_view name)
  {
    const auto string_name = std::string{ name };
    return reinterpret_cast<void*>(GetProcAddress(m_handle.get(), string_name.c_str()));
  }
}
