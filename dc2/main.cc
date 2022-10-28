#include <Windows.h>
#include <cstdlib>

#include "MainLoop.h"

INT WINAPI WinMain(_In_ HINSTANCE /*hInstance*/, _In_opt_ HINSTANCE /*hPrevInstance*/,
  _In_ LPSTR /*lpCmdLine*/, _In_ INT /*nCmdShow*/)

{
  MainLoop();

  return EXIT_SUCCESS;
}
