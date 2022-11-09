#pragma once
#include "common/types.h"

// ~ 00186AE0 - 00188880

struct vmcode_t
{
  u32 instruction;
  u32 op1;
  u32 op2;
};

namespace EStackDataType
{
  enum EStackDataType : u8
  {
    Int = 0,
    Float = 1,
    String = 2,
    Pointer = 3
  };
}

struct RS_STACKDATA;

union stackdata_t
{
  s32 i;
  float f;
  char* s;
  RS_STACKDATA* p;
};

struct RS_STACKDATA
{
  EStackDataType::EStackDataType m_data_type;
  stackdata_t m_data;
};

class CRunScript
{
private:
  // 00186B20
  void stkoverflow() const;
  // 00186D50
  void check_stack() const;
  // 00186D80
  void push(RS_STACKDATA data);
  // 00186DD0
  void push_int(int data);
  // 00186E20
  void push_str(char* data);
  // 00186E70
  void push_ptr(RS_STACKDATA* data);
  // 00186EC0
  void push_float(float data);
  // 00186F10
  RS_STACKDATA pop();
  // 001873C0
  void exe(vmcode_t* code);
  
  // 14
  RS_STACKDATA* m_stack_current;
  // 18
  RS_STACKDATA* m_stack_top;
  // 38
  vmcode_t* m_vmcode{ nullptr };
};