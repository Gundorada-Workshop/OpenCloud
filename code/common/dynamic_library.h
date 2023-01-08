#pragma once
#include <string_view>
#include <memory>

#include "common/types.h"

namespace common
{
  class dynamic_library
  {
  public:
    // don't open anything yet
    dynamic_library();

    dynamic_library(const dynamic_library&) = delete;
    dynamic_library(dynamic_library&&) = delete;

    // create a new dynamic lib
    dynamic_library(std::string_view name);

    // calls close
    ~dynamic_library();

    // open a library (if not already open)
    bool open(std::string_view name);

    // close the library
    void close();

    // type unsafe load function
    void* load_pfn(std::string_view name);

    // type safe load function
    template<typename T>
    T load_pfn_type(std::string_view name)
    {
      return reinterpret_cast<T>(load_pfn(name));
    }
    
  private:
    class impl;

    std::unique_ptr<impl> m_impl;
  };
}
