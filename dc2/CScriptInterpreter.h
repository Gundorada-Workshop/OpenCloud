#pragma once
#include "SpiStack.h"

class CScriptInterpreter
{
public:
  // 001469f0
  CScriptInterpreter();

  // 001467b0
  void SetTag(SPI_TAG_PARAM* param);

  void SetScript(char* script, int script_size);

  // 00146720
  void Run();

  // 00146590
  int GetNextTAG(int);

  // 00146760
  unsigned int hash(char* str);
};
