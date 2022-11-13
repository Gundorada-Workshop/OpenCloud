#pragma once
#include "common/debug.h"
#include "common/types.h"

// ~ 00186AE0 - 00188880

struct vmcode_t
{
  u32 m_instruction;
  u32 m_op1;
  u32 m_op2;
};

static_assert(sizeof(vmcode_t) == 0xC, "needs to be 0xC for interpreter to function correctly");

struct RS_CALLDATA {};
struct RS_PROG_HEADER {};

struct funcdata
{
  // 4
  char *m_function_name;
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

namespace ECompare
{
  enum ECompare : u8
  {
    EQ = 0,
    NE = 1,
    LT = 2,
    LTE = 3,
    GT = 4,
    GTE = 5
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

typedef s32(ext_func_t)(RS_STACKDATA*, s32);

template<>
struct fmt::formatter<RS_STACKDATA> : fmt::formatter<std::string_view>
{
  template<typename FormatContext>
  auto format(const RS_STACKDATA& stack_data, FormatContext& ctx)
  {
    if (stack_data.m_data_type == EStackDataType::Int)
    {
      return fmt::format_to(ctx.out(), "{}", stack_data.m_data.i);
    }
    if (stack_data.m_data_type == EStackDataType::Float)
    {
      return fmt::format_to(ctx.out(), "{}", stack_data.m_data.f);
    }
    if (stack_data.m_data_type == EStackDataType::String)
    {
      return fmt::format_to(ctx.out(), "{}", stack_data.m_data.s);
    }
    return fmt::format_to(ctx.out(), "{}", fmt::ptr(stack_data.m_data.p));
  }
};

class CRunScript
{
private:
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
  // 00187020
  vmcode_t* ret_func();
  // 00187050
  void ext(RS_STACKDATA* stack_data, s32 i);
  // 001873C0
  void exe(vmcode_t* code);

  // 0
  bool m_unk_field_0{ true };
  // 4
  usize m_n_ext_func{};
  // 8
  ext_func_t** m_ext_func{ nullptr };
  // C
  _DWORD m_unk_field_C{};
  // 10
  _DWORD m_unk_field_10{};
  // 14
  RS_STACKDATA* m_stack_current{};
  // 18
  RS_STACKDATA* m_stack_top{};
  // 1C
  _UNKNOWNPOINTER m_unk_field_1C{};
  // 20
  usize m_unk_field_20{};
  // 24
  _UNKNOWNPOINTER m_unk_field_24{};
  // 28
  _UNKNOWNPOINTER m_unk_field_28{};
  // 2C
  _UNKNOWNPOINTER m_unk_field_2C{};
  // 30
  RS_STACKDATA* m_unk_field_30{ nullptr };
  // 34
  funcdata* m_current_funcdata{ nullptr };
  // 38
  vmcode_t* m_vmcode{ nullptr };
  // 40
  bool m_unk_field_40{ false };
  // 44
  char* m_unk_field_44{ nullptr };
  // 48
  void* m_unk_field_48{ nullptr };
  // 4C
  stackdata_t m_unk_field_4C{};
  // 50
  s32 m_unk_field_50{};
public:
  // 00186D40
  void DeleteProgram();
  // 001871D0
  void ext_func(ext_func_t** ext_func, usize length);
  // 001871E0
  void resume();
  // 001873B0
  void skip();

  // 3C
  bool m_unk_field_3C{ false };
};

// 00188820
s32 rsGetStackInt(RS_STACKDATA* stack_data);
// 00188860
void rsSetStack(RS_STACKDATA* stack_data, s32 value);
