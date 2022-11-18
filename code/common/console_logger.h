#pragma once
#include "log.h"

namespace common::log::console_logger
{
  // start the consoler logger
  // must be done after the console is initialized
  bool initialize();

  // shutdown the console logger
  void shutdown();
}
