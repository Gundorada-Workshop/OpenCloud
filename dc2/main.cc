#include <Windows.h>
#include <cstdlib>

#include "common/console.h"
#include "common/log.h"

#include "MainLoop.h"
#include "SInit.h"

set_log_channel("WINMAIN");

INT WINAPI WinMain(_In_ HINSTANCE /*hInstance*/, _In_opt_ HINSTANCE /*hPrevInstance*/,
  _In_ LPSTR /*lpCmdLine*/, _In_ INT /*nCmdShow*/)

{
  log_info("Starting");

  // start the console
  // todo: report message box to user
  if (!common::console::initialize())
    return EXIT_FAILURE;

  // metrowerks has some weird static initialization thing
  // we don't, so we do that here
  StaticInitializers::Init();

  // the main loop
  MainLoop();

  // free the console
  common::console::shutdown();

  return EXIT_SUCCESS;
}
