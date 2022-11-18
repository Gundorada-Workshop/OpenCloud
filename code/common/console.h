#pragma once
#include <fmt/core.h>
#include "strings.h"

namespace common::console
{
  // start the console
  bool initialize();

  // shutdown the console
  // needs to be called before exit (windows)
  void shutdown();

  // write to the console
  void write(std::string_view msg);

  // same as write but with a new line
  inline void writeln(std::string_view msg)
  {
    write(msg);
    write("\n");
  }

  // same as write but accepts format arguments
  template<typename ...Args>
  void write_format(fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    const std::string msg = common::strings::format(fmtstr, std::forward<Args>(args)...);

    write(msg);
  }

  // same as write_format but with a new line
  template<typename ...Args>
  void writeln_format(fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    write_format(fmtstr, std::forward<Args>(args)...);
    write("\n");
  }

  // write an error to the console
  void write_error(std::string_view msg);

  // read user input
  std::string read();

  // ask the user yes/no question
  // return true if yes and false if no
  bool prompt(std::string_view question);
}
