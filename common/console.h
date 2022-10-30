#pragma once
#include <fmt/core.h>
#include "strings.h"

namespace common::console
{
  bool initialize();
  void shutdown();

  void write(std::string_view msg);

  // variadic std::format forward
  template<typename ...Args>
  void write_format(fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    const std::string msg = common::strings::format(fmtstr, std::forward<Args>(args)...);

    write(msg);
  }

  void write_error(std::string_view msg);

  std::string read();

  // ask the user yes/no question
  // return true if yes and false if no
  bool prompt(std::string_view question);
}
