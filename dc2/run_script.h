#pragma once
#include "common/types.h"

// ~ 00186AE0 - 00188880

struct vmcode_t
{
  u32 instruction;
  u32 op1;
  u32 op2;
};

class CRunScript
{
private:
  // 001873C0
  void exe(vmcode_t* code);
  
  // 38
  vmcode_t* m_vmcode{ nullptr };
};