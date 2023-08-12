#pragma once
#include <string_view>

namespace version
{
  std::string_view branch();
  std::string_view revision();
}