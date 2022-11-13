#pragma once
#include <string_view>
#include <wil/resource.h>

#include "common/types.h"

namespace common
{
  class dynamic_library
  {
  public:
    // don't open anything yet
    dynamic_library() = default;

    // create a new dynamic lib
    dynamic_library(std::string_view name);

    // open a library (if not already open)
    bool open(std::string_view name);

    // type unsafe load function
    void* load_pfn(std::string_view name);

    // type safe load function
    template<typename T>
    T load_pfn_type(std::string_view name)
    {
      return reinterpret_cast<T>(load_pfn(name));
    }
    
  private:
    // native handle to the library (windows in this case)
    // TODO: linux
    wil::unique_hmodule m_handle;
  };
}
