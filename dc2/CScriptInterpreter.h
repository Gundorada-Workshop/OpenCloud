#pragma once
#include "Types.h"
#include "SpiStack.h"

class CScriptInterpreter
{
public:
  // 001469f0
  CScriptInterpreter();

  // 001467b0
  void SetTag(SPI_TAG_PARAM* param);

  void SetScript(char* script, sint script_size);

  // 00146720
  void Run();

  // 00146590
  sint GetNextTAG(sint);

  // 00146760
  sint hash(char* str);
};
