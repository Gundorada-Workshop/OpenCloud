#pragma once
#include "common/debug.h"
#include "common/types.h"

#include "script/file.h"
#include "script/bytecode.h"
#include "script/stack.h"

// ~ 00186AE0 - 00188880

struct RS_CALLDATA 
{
  // 0
  script::instruction* m_return_address{ nullptr };
  // 4
  script::stack_data* m_function_stack_frame{ nullptr };
  // 8
  script::func_data_entry* m_last_funcdata{ nullptr };
};

using ext_func_t = std::function<bool(script::stack_data*, int)>;

struct RS_TAG_PARAM
{
  ext_func_t m_func;
  s32 m_id;
};

class CRunScript
{
public:
  // 00186D40
  void DeleteProgram();
  // 001870F0
  void load(script::header* prog_header, script::stack_data* stack_buf, usize n_stack_buf, RS_CALLDATA* call_stack_buf, usize n_call_stack_buf);
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
  void push(script::stack_data data);
  // 00186DD0
  void push_int(int data);
  // 00186E20
  void push_str(char* data);
  // 00186E70
  void push_ptr(script::stack_data* data);
  // 00186EC0
  void push_float(float data);
  // 00186F10
  script::stack_data pop();
  // 00186F30
  script::instruction* call_func(script::func_data_entry* func, script::instruction* return_address);
  // 00187020
  script::instruction* ret_func();
  // 00187050
  void ext(script::stack_data* stack_data, s32 i);
  // 001873C0
  void exe(script::instruction* code);

  // 0
  s32 m_script_version{ 1 }; // UNUSED?
  // 4
  usize m_n_ext_func{ 0 };
  // 8
  ext_func_t* m_ext_func{ nullptr };
  // C
  usize m_n_stack_buf{ 0 }; // UNUSED?
  // 10
  script::stack_data* m_stack_bottom{ nullptr };
  // 14
  script::stack_data* m_stack_current{ nullptr };
  // 18
  script::stack_data* m_stack_top{ nullptr };
  // 1C
  // These are what "pointer" stackdata point to
  script::stack_data* m_global_variables{ nullptr };
  // 20
  usize m_n_calldata{}; // UNUSED?
  // 24
  RS_CALLDATA* m_calldata_bottom{ nullptr };
  // 28
  RS_CALLDATA* m_calldata_current{ nullptr };
  // 2C
  RS_CALLDATA* m_calldata_top{ nullptr };
  // 30
  script::stack_data* m_function_stack_frame{ nullptr };
  // 34
  script::func_data_entry* m_current_funcdata{ nullptr };
  // 38
  script::instruction* m_vmcode{ nullptr };
  // 40
  bool m_skip_flag{ false };
  // 44
  script::header* m_prog_header{ nullptr };
  // 48
  // pointer to just misc. script data, such as strings, vmcode, etc.; instructions provide
  // an offset to this address
  u32 m_script_data{ 0 };
  // 4C
  script::stack_data m_last_return_value{}; // UNUSED?
  // 50
  s32 m_unk_field_50{}; // UNUSED? (incremented in exe case 28, but doesn't seem to be used elsewhere)
};
