#pragma once

namespace host::console_logger
{
  // start the consoler logger
  // must be done after the console is initialized
  bool initialize();

  // shutdown the console logger
  void shutdown();
}
