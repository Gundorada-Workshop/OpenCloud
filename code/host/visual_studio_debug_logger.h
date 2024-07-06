#pragma once

namespace host::visual_studio_debug_logger
{
  // start the consoler logger
  // must be done after the console is initialized
  bool initialize();

  // shutdown the console logger
  void shutdown();
}