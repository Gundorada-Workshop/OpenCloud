#pragma once
#include <wil/com.h>

#include "common/helpers.h"

namespace d3d11
{
  template<typename type>
  using com_ptr = wil::com_ptr_nothrow<type>;
}
