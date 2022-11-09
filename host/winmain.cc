#include <Windows.h>
#include <cstdlib>

#include "common/console.h"
#include "common/log.h"
#include "common/console_logger.h"

#include "mainloop.h"
#include "sinit.h"

set_log_channel("WINMAIN");

INT WINAPI WinMain(_In_ HINSTANCE /*hInstance*/, _In_opt_ HINSTANCE /*hPrevInstance*/,
  _In_ LPSTR /*lpCmdLine*/, _In_ INT /*nCmdShow*/)

{
  log_trace("WinMain()");

  // start the console
  // todo: report message box to user
  if (!common::console::initialize())
    return EXIT_FAILURE;

  common::log::console_logger::initialize();

  log_info("Starting");

  // metrowerks has some weird static initialization thing
  // we don't, so we do that here
  StaticInitializers::Init();

  // the main loop
  MainLoop();

  // free the console
  common::log::console_logger::shutdown();
  common::console::shutdown();

  return EXIT_SUCCESS;
}
