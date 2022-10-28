#include "CScriptInterpreter.h"

// 00147300
static bool CheckChar(char ch)
{
  return ch != '\r' && ch != '\n' && ch != '\t' && ch != ' ';
}

CScriptInterpreter::CScriptInterpreter()
{
  // TODO
}

void CScriptInterpreter::Run()
{
  while(GetNextTAG(1) > -1) { }
}

unsigned int CScriptInterpreter::hash(char* str)
{
  unsigned int out = 0;

  while(*str != '\0')
  {
    char ch = *str;

    out = (out * 256 + ch) % 0x65 & 0xFF;

    str++;
  }

  return out;
}
