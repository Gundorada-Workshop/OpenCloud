// SPDX-License-Identifier: MIT

#pragma once
#include "common/types.h"

namespace common
{
  template<typename type>
  constexpr auto to_underlying(type t) -> std::underlying_type_t<type>
  {
    return static_cast<std::underlying_type_t<type>>(t);
  }
}