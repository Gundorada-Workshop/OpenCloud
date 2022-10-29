#pragma once
#include "common/types.h"
#include "SpiStack.h"

class CScriptInterpreter
{
public:
  // 001469f0
  CScriptInterpreter();

  // 001467b0
  void SetTag(const SPI_TAG_PARAM* param)
  {
    // TODO
  }

  void SetScript(const char* script, sint script_size)
  {
    // TODO
  }

  // 00146720
  void Run();

  // 00146590
  sint GetNextTAG(sint)
  {
    return 0; // TODO
  }

  // 00146760
  sint hash(char* str);
};
