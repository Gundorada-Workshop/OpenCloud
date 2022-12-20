#pragma once
#include "common/debug.h"
#include "common/types.h"

// ~ 00186AE0 - 00188880

struct vmcode_t
{
  // 0
  u32 m_instruction;
  // 4
  u32 m_op1;
  // 8
  u32 m_op2;
};

// we're deserializing this structure from file
static_assert(sizeof(vmcode_t) == 0xC, "needs to be 0xC for interpreter to function correctly");
static_assert(offsetof(vmcode_t, m_instruction) == 0x0);
static_assert(offsetof(vmcode_t, m_op1) == 0x4);
static_assert(offsetof(vmcode_t, m_op2) == 0x8);

struct funcdata;
struct RS_STACKDATA;

struct RS_CALLDATA 
{
  // 0
  vmcode_t* m_return_address{ nullptr };
  // 4
  RS_STACKDATA* m_function_stack_frame{ nullptr };
  // 8
  funcdata* m_last_funcdata{ nullptr };
};

struct RS_PROG_HEADER
{
  // 0
  const char m_tag[4];
  // 4
  unk32 m_unk_field_4{}; // May be used in CRunScript::Run; Hopefully never actually used ???
  // 8
  // void*
  // This is the address *AFTER* the function pointer table, and all script offsets also add this value
  // (e.g. if this is 0x40, then an instruction which loads a string at 0x3700 means the string is located
  // at 0x3740 within the file)
  u32 m_script_data{};
  // C
  // funcentry*
  u32 m_func_table{};
  // 10
  u32 m_n_func_table{};
  // 14
  unk32 m_unk_field_14{}; // Appears unused
  // 18
  u32 m_n_global_variables{};
};

// we're deserializing this structure from file
static_assert(sizeof(RS_PROG_HEADER) == 0x1C);
static_assert(offsetof(RS_PROG_HEADER, m_tag) == 0x0);
static_assert(offsetof(RS_PROG_HEADER, m_unk_field_4) == 0x4);
static_assert(offsetof(RS_PROG_HEADER, m_script_data) == 0x8);
static_assert(offsetof(RS_PROG_HEADER, m_func_table) == 0xC);
static_assert(offsetof(RS_PROG_HEADER, m_n_func_table) == 0x10);
static_assert(offsetof(RS_PROG_HEADER, m_unk_field_14) == 0x14);
static_assert(offsetof(RS_PROG_HEADER, m_n_global_variables) == 0x18);

struct funcdata
{
  // 0
  // vmcode_t*
  u32 m_vmcode{};
  // 4
  // const char*
  u32 m_function_name{};
  // 8
  u32 m_function_stack_size{};
  // C
  u32 m_arity{};
};

// we're deserializing this structure from file
static_assert(sizeof(funcdata) == 0x10);
static_assert(offsetof(funcdata, m_vmcode) == 0x0);
static_assert(offsetof(funcdata, m_function_name) == 0x4);
static_assert(offsetof(funcdata, m_function_stack_size) == 0x8);
static_assert(offsetof(funcdata, m_arity) == 0xC);

struct funcentry
{
  // 0
  u32 m_program_id{};
  // 4
  // funcdata*
  u32 m_funcdata{};
};

// we're deserializing this structure from file
static_assert(sizeof(funcentry) == 0x8);
static_assert(offsetof(funcentry, m_program_id) == 0x0);
static_assert(offsetof(funcentry, m_funcdata) == 0x4);

enum class EStackDataType : u8
{
  Int = 0,
  Float = 1,
  String = 2,
  Pointer = 3
};

enum class ECompare : u8
{
  EQ = 0,
  NE = 1,
  LT = 2,
  LTE = 3,
  GT = 4,
  GTE = 5
};

using ext_func_t = std::function<bool(RS_STACKDATA*, int)>;

struct RS_TAG_PARAM
{
  std::function<bool(RS_STACKDATA*, int)> m_func;
  s32 m_id;
};

union stackdata_t
{
  s32 i;
  float f;
  char* s;
  RS_STACKDATA* p;
};

struct RS_STACKDATA
{
  EStackDataType m_data_type;
  stackdata_t m_data;
};

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
public:
  // 00186D40
  void DeleteProgram();
  // 001870F0
  void load(RS_PROG_HEADER* prog_header, RS_STACKDATA* stack_buf, usize n_stack_buf, RS_CALLDATA* call_stack_buf, usize n_call_stack_buf);
  // 001871D0
  void ext_func(ext_func_t* ext_func, usize length);
  // 001871E0
  void resume();
  // 00187210
  sint run(s32 program_id);
  // 00187360
  bool check_program(s32 program_id);
  // 001873B0
  void skip();

  // 3C
  bool m_program_terminated{ false };
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
  // 00186F30
  vmcode_t* call_func(funcdata* func, vmcode_t* return_address);
  // 00187020
  vmcode_t* ret_func();
  // 00187050
  void ext(RS_STACKDATA* stack_data, s32 i);
  // 001873C0
  void exe(vmcode_t* code);

  // 0
  s32 m_script_version{ 1 }; // UNUSED?
  // 4
  usize m_n_ext_func{ 0 };
  // 8
  ext_func_t* m_ext_func{ nullptr };
  // C
  usize m_n_stack_buf{ 0 }; // UNUSED?
  // 10
  RS_STACKDATA* m_stack_bottom{ nullptr };
  // 14
  RS_STACKDATA* m_stack_current{ nullptr };
  // 18
  RS_STACKDATA* m_stack_top{ nullptr };
  // 1C
  // These are what "pointer" stackdata point to
  RS_STACKDATA* m_global_variables{ nullptr };
  // 20
  usize m_n_calldata{}; // UNUSED?
  // 24
  RS_CALLDATA* m_calldata_bottom{ nullptr };
  // 28
  RS_CALLDATA* m_calldata_current{ nullptr };
  // 2C
  RS_CALLDATA* m_calldata_top{ nullptr };
  // 30
  RS_STACKDATA* m_function_stack_frame{ nullptr };
  // 34
  funcdata* m_current_funcdata{ nullptr };
  // 38
  vmcode_t* m_vmcode{ nullptr };
  // 40
  bool m_skip_flag{ false };
  // 44
  RS_PROG_HEADER* m_prog_header{ nullptr };
  // 48
  // pointer to just misc. script data, such as strings, vmcode, etc.; instructions provide
  // an offset to this address
  u32 m_script_data{ 0 };
  // 4C
  stackdata_t m_unk_field_4C{}; // UNUSED?
  // 50
  s32 m_unk_field_50{}; // UNUSED? (incremented in exe case 28, but doesn't seem to be used elsewhere)
};

// 00188820
s32 rsGetStackInt(RS_STACKDATA* stack_data);
// 00188860
void rsSetStack(RS_STACKDATA* stack_data, s32 value);
