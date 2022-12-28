#include "common/bits.h"
#include "common/log.h"

#include "dc2/run_script.h"

set_log_channel("run_script");

// 00186AE0
void runerror(const char* msg);
// 00186B20
void stkoverflow();
void stkunderflow();
// 00186B30
s32 chk_int(RS_STACKDATA stack_data, funcdata* func_data);
// 00186BD0
void divby0error();
// 00186BE0
void modby0error();
// 00186BF0
void print(RS_STACKDATA* stack_data, usize amount);
// 00186B90
bool is_true(RS_STACKDATA stack_data);

// 00186D40
void CRunScript::DeleteProgram()
{
  log_trace("CRunScript::{}()", __func__);

  m_program_terminated = false;
  m_skip_flag = false;
  m_prog_header = nullptr;
}

// 00186D50
void CRunScript::check_stack() const
{
  log_trace("CRunScript::{}()", __func__);

  if (m_stack_current >= m_stack_top)
  {
    stkoverflow();
  }
}

// 00186D80
void CRunScript::push(RS_STACKDATA data)
{
  log_trace("CRunScript::{}({})", __func__, data);

  check_stack();

  *m_stack_current = data;
  ++m_stack_current;
}

// 00186DD0
void CRunScript::push_int(int data)
{
  log_trace("CRunScript::{}({})", __func__, data);

  check_stack();

  stackdata_t stack_data;
  stack_data.i = data;
  m_stack_current->m_data_type = EStackDataType::Int;
  m_stack_current->m_data = stack_data;
  ++m_stack_current;
}

// 00186E20
void CRunScript::push_str(char* data)
{
  log_trace("CRunScript::{}({})", __func__, data);

  check_stack();

  stackdata_t stack_data;
  stack_data.s = data;
  m_stack_current->m_data_type = EStackDataType::String;
  m_stack_current->m_data = stack_data;
  ++m_stack_current;
}

// 00186E70
void CRunScript::push_ptr(RS_STACKDATA* data)
{
  log_trace("CRunScript::{}({})", __func__, fmt::ptr(data));

  stackdata_t stack_data;
  stack_data.p = data;
  m_stack_current->m_data_type = EStackDataType::Pointer;
  m_stack_current->m_data = stack_data;
  ++m_stack_current;
}

// 00186E70
void CRunScript::push_float(float data)
{
  log_trace("CRunScript::{}({})", __func__, data);

  stackdata_t stack_data;
  stack_data.f = data;
  m_stack_current->m_data_type = EStackDataType::Float;
  m_stack_current->m_data = stack_data;
  ++m_stack_current;
}

// 00186F10
RS_STACKDATA CRunScript::pop()
{
  log_trace("CRunScript::{}()", __func__);

  --m_stack_current;

  check_stack();

  return *(m_stack_current + 1);
}

// 00186F30
vmcode_t* CRunScript::call_func(funcdata* func, vmcode_t* return_address)
{
  log_trace("CRunScript::{}({}, {})", __func__, fmt::ptr(func), fmt::ptr(return_address));

  if (m_calldata_current >= m_calldata_top)
  {
    panicf("CRunScript: Function call stack overflow!");
  }

  // Set up our call information
  m_calldata_current->m_return_address = return_address;
  m_calldata_current->m_last_funcdata = m_current_funcdata;
  m_calldata_current->m_function_stack_frame = m_function_stack_frame;
  
  // function stack frame starts before the current stack, if there are any arguments provided to the function
  m_function_stack_frame = m_stack_current -= func->m_arity;

  // now create space on the stack for the function's variables
  m_stack_current = m_function_stack_frame + func->m_function_stack_size;

  m_current_funcdata = func;

  // Increment the call stack
  ++m_calldata_current;

  // Zero-Initialize our function stack frame (but not the arguments!)
  RS_STACKDATA* locals = m_function_stack_frame + func->m_arity;
  memset(locals, 0, sizeof(RS_STACKDATA) * (func->m_function_stack_size - func->m_arity));

  // Check for stack overflow
  check_stack();

  // Now return the address of the start of the function
  return reinterpret_cast<vmcode_t*>(static_cast<uptr>(m_script_data) + static_cast<uptr>(func->m_vmcode));
}

// 00187020
vmcode_t* CRunScript::ret_func()
{
  log_trace("CRunScript::{}()", __func__);

  // Rewind the call stack
  --m_calldata_current;

  // Now the current call stack item has all of the information to restore the machine state
  m_function_stack_frame = m_calldata_current->m_function_stack_frame;
  m_current_funcdata = m_calldata_current->m_last_funcdata;
  return m_calldata_current->m_return_address;
}

// 00187050
void CRunScript::ext(RS_STACKDATA* stack_data, s32 stack_count)
{
  log_trace("CRunScript::{}({}, {})", __func__, *stack_data, stack_count);

  // First item of stack_data should be the extension function ID.
  s32 call_index = stack_data->m_data.i;

  if (call_index < 0 || m_n_ext_func <= call_index)
  {
    log_warn("Not found ext {}", call_index);
    return;
  }

  ext_func_t fn = m_ext_func[call_index];

  if (fn == nullptr)
  {
    log_warn("Not found ext {}", call_index);
    return;
  }

  // NOTE: the first item on the stack is the extension function ID,
  // So we ignore that when passing the stack pointer/count to the extension function.
  if (!fn(stack_data + 1, stack_count - 1))
  {
    log_warn("Illegal function call ext {}", call_index);
    return;
  }
  return;
}

// 001870F0
void CRunScript::load(RS_PROG_HEADER* prog_header, RS_STACKDATA* stack_buf, usize n_stack_buf, RS_CALLDATA* call_stack_buf, usize n_call_stack_buf)
{
  log_trace("CRunScript::{}({}, {}, {}, {}, {})", __func__, fmt::ptr(prog_header), fmt::ptr(stack_buf), n_stack_buf, fmt::ptr(call_stack_buf), n_call_stack_buf);

  // Datastack
  m_stack_bottom = stack_buf;
  m_n_stack_buf = n_stack_buf;

  // Callstack
  m_calldata_bottom = call_stack_buf;
  m_n_calldata = n_call_stack_buf;

  // Tops of stacks
  m_stack_top = m_stack_bottom + n_stack_buf;
  m_calldata_top = m_calldata_bottom + m_n_calldata;

  m_prog_header = prog_header;
  m_script_data = prog_header->m_script_data;

  if (strncmp(m_prog_header->m_tag, "SB2", 3) == 0)
  {
    // The 2nd version of a RUN SCRIPT script, so we've got *fancy* global variables!!!
    m_script_version = 2;

    // Allocate space for global variables; these are variables that "pointer" stack data can directly reference.
    m_global_variables = m_stack_bottom;
    m_stack_bottom += prog_header->m_n_global_variables;
    m_n_stack_buf -= prog_header->m_n_global_variables;

    // Zero-initialize global variables
    memset(m_global_variables, 0, sizeof(RS_STACKDATA) * prog_header->m_n_global_variables);
  }
}

// 001871D0
void CRunScript::ext_func(ext_func_t* ext_func, usize length)
{
  log_trace("CRunScript::{}({}, {})", __func__, fmt::ptr(ext_func), length);

  m_ext_func = ext_func;
  m_n_ext_func = length;
}

// 001871E0
void CRunScript::resume()
{
  log_trace("CRunScript::{}()", __func__);

  if (m_vmcode != nullptr)
  {
    exe(m_vmcode);
  }
}

// 00187210
sint CRunScript::run(s32 program_id)
{
  log_trace("CRunScript::{}({})", __func__, program_id);

  if (m_prog_header == nullptr)
  {
    return -1;
  }

  // Initialize our stacks
  m_stack_current = m_stack_bottom;
  m_calldata_current = m_calldata_bottom;

  // And now we'll want to try and find our program
  m_current_funcdata = nullptr;
  if (program_id < 0)
  {
    // Not sure what this is for? Script version 1 maybe? Doesn't seem valid for SB2...
    m_current_funcdata = reinterpret_cast<funcdata*>(reinterpret_cast<uptr>(m_prog_header) + static_cast<uptr>(m_prog_header->m_unk_field_4));
  }
  else
  {
    funcentry* func_list = reinterpret_cast<funcentry*>(reinterpret_cast<uptr>(m_prog_header) + static_cast<uptr>(m_prog_header->m_func_table));
    for (usize i = 0; i < m_prog_header->m_n_func_table; ++i)
    {
      if (func_list[i].m_program_id == program_id)
      {
        m_current_funcdata = reinterpret_cast<funcdata*>(static_cast<uptr>(func_list[i].m_funcdata));
        break;
      }
    }
  }

  if (m_current_funcdata == nullptr)
  {
    log_warn("Couldn't find program {}", program_id);
    return -1;
  }

  // Set up our function stacks
  // First, grab some previously allocated space for any arguments
  m_function_stack_frame = m_stack_current - m_current_funcdata->m_arity;

  // Then allocate some new space for the rest of the frame
  m_stack_current = m_function_stack_frame + m_current_funcdata->m_function_stack_size;

  // Check for an overflow
  check_stack();

  // Memset our function stack frame (but not the arguments)
  RS_STACKDATA* locals = m_function_stack_frame + m_current_funcdata->m_arity;
  memset(locals, 0, sizeof(RS_STACKDATA) * (m_current_funcdata->m_function_stack_size - m_current_funcdata->m_arity));

  // Now let's run the program
  m_program_terminated = false;
  m_skip_flag = false;
  m_unk_field_50 = 0;
  vmcode_t* code = reinterpret_cast<vmcode_t*>( // bet Rust won't let you do this
    // header
    reinterpret_cast<uptr>(m_prog_header) + 
    // data offset
    static_cast<uptr>(m_prog_header->m_script_data) + 
    // code
    static_cast<uptr>(m_current_funcdata->m_vmcode)
  );
  exe(code);

  return static_cast<sint>(!m_program_terminated);
}

// 00187360
bool CRunScript::check_program(s32 program_id)
{
  log_trace("CRunScript::{}({})", __func__, program_id);

  funcentry* func_entries = reinterpret_cast<funcentry*>(reinterpret_cast<uptr>(m_prog_header) + static_cast<uptr>(m_prog_header->m_func_table));

  for (u32 i = 0; i < m_prog_header->m_n_func_table; ++i)
  {
    if (func_entries[i].m_program_id == program_id)
    {
      return true;
    }
  }

  return false;
}

// 001873B0
void CRunScript::skip()
{
  log_trace("CRunScript::{}()", __func__);

  m_skip_flag = true;
  resume();
}

// 001873C0
void CRunScript::exe(vmcode_t* code)
{
  log_trace("CRunScript::{}({})", __func__, fmt::ptr(code));

  m_vmcode = code;

  while (true)
  {
    using enum EStackDataType;

    switch (m_vmcode->m_instruction)
    {
      case 1:
      {
        // 00187414
        switch (code->m_op2)
        {
          case 0x1:
          {
            // 187468
            push(m_function_stack_frame[code->m_op1]);
            break;
          }
          case 0x2:
          {
            // 1874B4
            sint offset = chk_int(pop(), m_current_funcdata);
            push(m_function_stack_frame[code->m_op1 + offset]);
            break;
          }
          case 0x4:
          {
            // 1874FC
            sint offset = chk_int(pop(), m_current_funcdata);
            push(*(m_function_stack_frame[code->m_op1].m_data.p + offset));
            break;
          }
          case 0x8:
          {
            // 187548
            m_function_stack_frame[code->m_op1].m_data_type = Float;
            push(m_function_stack_frame[code->m_op1]);
            break;
          }
          case 0x10:
          {
            // 1875C8
            sint offset = chk_int(pop(), m_current_funcdata);
            auto data = &m_function_stack_frame[code->m_op1];
            (data + offset)->m_data_type = Float;
            push(*data);
            break;
          }
          case 0x20:
          {
            // 187630
            sint offset = chk_int(pop(), m_current_funcdata);
            auto data = &m_function_stack_frame[code->m_op1];
            (data->m_data.p + offset)->m_data_type = Float;
            push(*data);
            break;
          }
          case 0x40:
          {
            // 18748C
            // SB2 only!
            push(m_global_variables[code->m_op1]);
            break;
          }
          case 0x200:
          {
            // 187588
            // SB2 only!
            auto data = m_global_variables[code->m_op1];
            data.m_data_type = Float;
            push(data);
            break;
          }
          default:
            break;
        }
        break;
      }
      case 2:
      {
        // 001876A0
        switch (code->m_op2)
        {
          case 0x1:
          {
            // 1876F0
            // Same as 0x8?
            push_ptr(m_function_stack_frame + code->m_op1);
            break;
          }
          case 0x2:
          {
            // 187730
            // Same as 0x10?
            sint offset = chk_int(pop(), m_current_funcdata) * sizeof(RS_STACKDATA);
            push_ptr(
              reinterpret_cast<RS_STACKDATA*>(reinterpret_cast<uptr>(m_function_stack_frame + code->m_op1) + offset)
            );
            break;
          }
          case 0x4:
          {
            // 187774
            // Same as 0x20?
            sint offset = chk_int(pop(), m_current_funcdata) * sizeof(RS_STACKDATA);
            push_ptr(
              reinterpret_cast<RS_STACKDATA*>(reinterpret_cast<uptr>((m_function_stack_frame + code->m_op1)->m_data.p) + offset)
            );
            break;
          }
          case 0x8:
          {
            // 1877C0
            push_ptr(m_function_stack_frame + code->m_op1);
            break;
          }
          case 0x10:
          {
            // 187800
            sint offset = chk_int(pop(), m_current_funcdata) * sizeof(RS_STACKDATA);
            push_ptr(
              reinterpret_cast<RS_STACKDATA*>(reinterpret_cast<uptr>(m_function_stack_frame + code->m_op1) + offset)
            );
            break;
          }
          case 0x20:
          {
            // 187844
            sint offset = chk_int(pop(), m_current_funcdata) * sizeof(RS_STACKDATA);
            push_ptr(
              reinterpret_cast<RS_STACKDATA*>(reinterpret_cast<uptr>((m_function_stack_frame + code->m_op1)->m_data.p) + offset)
            );
            break;
          }
          case 0x40:
          {
            // 187710
            // SB2 only!
            // ... same as 0x200?
            push_ptr(
              reinterpret_cast<RS_STACKDATA*>(reinterpret_cast<uptr>(m_global_variables) + (code->m_op1 * sizeof(RS_STACKDATA)))
            );
            break;
          }
          case 0x200:
            // 1877E0
            // SB2 only!
            push_ptr(
              reinterpret_cast<RS_STACKDATA*>(reinterpret_cast<uptr>(m_global_variables) + (code->m_op1 * sizeof(RS_STACKDATA)))
            );
            break;
          default:
            break;
        }
        break;
      }
      case 3:
        // 001878E8
        // _PUSH
        switch (code->m_op1)
        {
          case 1:
            push_int(code->m_op2);
            break;
          case 2:
            push_float(std::bit_cast<float>(code->m_op2));
            break;
          case 3:
            push_str(reinterpret_cast<char*>(static_cast<uptr>(m_script_data) + static_cast<uptr>(code->m_op2)));
            break;
          default:
            break;
        }
        break;
      case 4:
        // 00187958
        // _POP
        pop();
        break;
      case 5:
      {
        // 00187890
        // _DEREF_WRITE
        // NOTE: an intermediate variable, var_130, is used here, but I don't think it's necessary
        auto val = pop();
        auto ptr = pop();
        ptr.m_data.p->m_data_type = val.m_data_type;
        ptr.m_data.p->m_data = val.m_data;
        push(val);
        break;
      }
      case 6:
      {
        // 00187D00
        // _ADD
        auto rhs = pop();
        auto lhs = pop();

        if (lhs.m_data_type == Int && rhs.m_data_type == Int)
        {
          push_int(lhs.m_data.i + rhs.m_data.i);
        }
        else if (lhs.m_data_type == Float && rhs.m_data_type == Float)
        {
          push_float(lhs.m_data.f + rhs.m_data.f);
        }
        else if (lhs.m_data_type == Float && rhs.m_data_type == Int)
        {
          push_float(lhs.m_data.f + rhs.m_data.i);
        }
        else if (lhs.m_data_type == Int && rhs.m_data_type == Float)
        {
          push_float(lhs.m_data.i + rhs.m_data.f);
        }
        else
        {
          panicf("RUNTIME ERROR at _ADD: {}: operand is not number", m_current_funcdata->m_function_name);
        }

        break;
      }
      case 7:
      {
        // 00187E30
        // _SUB
        auto rhs = pop();
        auto lhs = pop();

        if (lhs.m_data_type == Int && rhs.m_data_type == Int)
        {
          push_int(lhs.m_data.i - rhs.m_data.i);
        }
        else if (lhs.m_data_type == Float && rhs.m_data_type == Float)
        {
          push_float(lhs.m_data.f - rhs.m_data.f);
        }
        else if (lhs.m_data_type == Float && rhs.m_data_type == Int)
        {
          push_float(lhs.m_data.f - rhs.m_data.i);
        }
        else if (lhs.m_data_type == Int && rhs.m_data_type == Float)
        {
          push_float(lhs.m_data.i - rhs.m_data.f);
        }
        else
        {
          panicf("RUNTIME ERROR at _SUB: {}: operand is not number", m_current_funcdata->m_function_name);
        }

        break;
      }
      case 8:
      {
        // 00187F60
        // _MUL
        auto rhs = pop();
        auto lhs = pop();

        if (lhs.m_data_type == Int && rhs.m_data_type == Int)
        {
          push_int(lhs.m_data.i * rhs.m_data.i);
        }
        else if (lhs.m_data_type == Float && rhs.m_data_type == Float)
        {
          push_float(lhs.m_data.f * rhs.m_data.f);
        }
        else if (lhs.m_data_type == Float && rhs.m_data_type == Int)
        {
          push_float(lhs.m_data.f * rhs.m_data.i);
        }
        else if (lhs.m_data_type == Int && rhs.m_data_type == Float)
        {
          push_float(lhs.m_data.i * rhs.m_data.f);
        }
        else
        {
          panicf("RUNTIME ERROR at _MUL: {}: operand is not number", m_current_funcdata->m_function_name);
        }

        break;
      }
      case 9:
      {
        // 00188090
        // _DIV
        auto rhs = pop();
        if (rhs.m_data.i == 0) divby0error();
        auto lhs = pop();

        if (lhs.m_data_type == Int && rhs.m_data_type == Int)
        {
          push_int(lhs.m_data.i / rhs.m_data.i);
        }
        else if (lhs.m_data_type == Float && rhs.m_data_type == Float)
        {
          push_float(lhs.m_data.f / rhs.m_data.f);
        }
        else if (lhs.m_data_type == Float && rhs.m_data_type == Int)
        {
          push_float(lhs.m_data.f / rhs.m_data.i);
        }
        else if (lhs.m_data_type == Int && rhs.m_data_type == Float)
        {
          push_float(lhs.m_data.i / rhs.m_data.f);
        }
        else
        {
          panicf("RUNTIME ERROR at _DIV: {}: operand is not number", m_current_funcdata->m_function_name);
        }

        break;
      }
      case 10:
      {
        // 00188208
        // _MOD
        auto rhs = pop();
        
        // error handling (not int / div by 0)
        chk_int(rhs, m_current_funcdata);
        if (rhs.m_data.i == 0)
        {
          modby0error();
        }

        auto lhs = pop();
        chk_int(lhs, m_current_funcdata);
        
        push_int(lhs.m_data.i % rhs.m_data.i);

        break;
      }
      case 11:
      {
        // 00188300
        // _NEGATE
        auto lhs = pop();
        if (lhs.m_data_type == EStackDataType::Int)
        {
          push_int(-lhs.m_data.i);
        }
        else if (lhs.m_data_type == EStackDataType::Float)
        {
          push_float(-lhs.m_data.f);
        }
        else
        {
          panicf("RUNTIME ERROR at _NEGATE: {}: operand is not a number", m_current_funcdata->m_function_name);
        }
        break;
      }
      case 12:
      {
        // 00188550
        // _ITOF
        auto lhs = pop();
        if (lhs.m_data_type == EStackDataType::Int)
        {
          push_float(static_cast<float>(lhs.m_data.i));
        }
        else if (lhs.m_data_type == EStackDataType::Float)
        {
          push_float(lhs.m_data.f);
        }
        else
        {
          panicf("RUNTIME ERROR at _ITOF: {}: operand is not a number", m_current_funcdata->m_function_name);
        }
        break;
      }
      case 13:
      {
        // 001885E0
        // _FTOI
        auto lhs = pop();
        if (lhs.m_data_type == EStackDataType::Int)
        {
          push_int(lhs.m_data.i);
        }
        else if (lhs.m_data_type == EStackDataType::Float)
        {
          push_int(static_cast<s32>(lhs.m_data.f));
        }
        else
        {
          panicf("RUNTIME ERROR at _FTOI: {}: operand is not a number", m_current_funcdata->m_function_name);
        }
        break;
      }
      case 14:
      {
        // 00187A38
        // _CMP
        auto rhs = pop();
        auto lhs = pop();

        if (lhs.m_data_type == EStackDataType::Int && rhs.m_data_type == EStackDataType::Int)
        {
          s32 lVal = lhs.m_data.i;
          s32 rVal = rhs.m_data.i;

          switch (static_cast<ECompare>(code->m_op1))
          {
            case ECompare::EQ:
              push_int(lVal == rVal);
              break;
            case ECompare::NE:
              push_int(lVal != rVal);
              break;
            case ECompare::LT:
              push_int(lVal < rVal);
              break;
            case ECompare::LTE:
              push_int(lVal <= rVal);
              break;
            case ECompare::GT:
              push_int(lVal > rVal);
              break;
            case ECompare::GTE:
              push_int(lVal >= rVal);
              break;
            default:
              break;
          }
        }
        else
        {
          f32 lVal;
          f32 rVal;

          if (lhs.m_data_type == EStackDataType::Float && rhs.m_data_type == EStackDataType::Float)
          {
            lVal = lhs.m_data.f;
            rVal = rhs.m_data.f;
          }
          else if (lhs.m_data_type == EStackDataType::Int && rhs.m_data_type == EStackDataType::Float)
          {
            lVal = static_cast<f32>(lhs.m_data.i);
            rVal = rhs.m_data.f;
          }
          else if (lhs.m_data_type == EStackDataType::Float && rhs.m_data_type == EStackDataType::Int)
          {
            lVal = lhs.m_data.f;
            rVal = static_cast<f32>(rhs.m_data.i);
          }
          else
          {
            panicf("RUNTIME ERROR at _CMP: {}: operand is not number\n", m_current_funcdata->m_function_name);
          }

          switch (static_cast<ECompare>(code->m_op1))
          {
            case ECompare::EQ:
              push_int(lVal == rVal);
              break;
            case ECompare::NE:
              push_int(lVal != rVal);
              break;
            case ECompare::LT:
              push_int(lVal < rVal);
              break;
            case ECompare::LTE:
              push_int(lVal <= rVal);
              break;
            case ECompare::GT:
              push_int(lVal > rVal);
              break;
            case ECompare::GTE:
              push_int(lVal >= rVal);
              break;
            default:
              break;
          }
        }
        break;
      }
      case 15:
      {
        // 0018871C
        // _RET
        auto return_value = pop();

        if (m_calldata_current == m_calldata_bottom)
        {
          // The callstack has been completely unwound, stop execution.
          m_last_return_value = return_value.m_data;
          push(return_value);
          m_program_terminated = true;
        }
        else
        {
          // Return to the last function on the call stack.
          m_stack_current = m_function_stack_frame;
          m_vmcode = ret_func();
          push(return_value);
        }

        break;
      }
      case 16:
      {
        // 00187968
        // _JMP
        if (!m_skip_flag)
        {
          m_vmcode = reinterpret_cast<vmcode_t*>(
            static_cast<uptr>(m_script_data) + code->m_op1
          );
          continue;
        }
        break;
      }
      case 17:
      {
        // 001879E0
        // _BF
        if (!m_skip_flag && !is_true(pop()))
        {
          if (code->m_op2)
          {
            push_int(false);
          }
          m_vmcode = reinterpret_cast<vmcode_t*>(
            static_cast<uptr>(m_script_data) + code->m_op1
          );
          continue;
        }
        break;
      }
      case 18:
      {
        // 00187988
        // _BT
        if (!m_skip_flag && is_true(pop()))
        {
          if (code->m_op2)
          {
            push_int(true);
          }
          m_vmcode = reinterpret_cast<vmcode_t*>(
            static_cast<uptr>(m_script_data) + code->m_op1
          );
          continue;
        }
        break;
      }
      case 19:
      {
        // 001886F0
        // _CALL
        funcdata* fn = reinterpret_cast<funcdata*>(
          static_cast<uptr>(m_script_data) + code->m_op2
        );
        
        // call_func returns the address of the code at the start of the function;
        // we have to decrement it once, since the loop will increment it at the end.
        m_vmcode = call_func(fn, code) - 1;
        break;
      }
      case 20:
      {
        // 00188670
        // _PRINT
        usize amount = code->m_op1;
        m_stack_current -= amount;
        print(m_stack_current, amount);
        break;
      }
      case 21:
        // 0018869C
        // _EXT
        m_stack_current -= code->m_op1;

        if (!m_skip_flag)
        {
          ext(m_stack_current, code->m_op1);
        }

        break;
      case 23:
      {
        // 001887A8
        // _YIELD
        if (!m_skip_flag)
        {
          m_vmcode += 1;
          return;
        }
        break;
      }
      case 24:
      {
        // 00188270
        // _AND
        auto rhs = pop();
        auto rVal = chk_int(rhs, m_current_funcdata);
        auto lhs = pop();
        auto lVal = chk_int(lhs, m_current_funcdata);
        push_int(lVal & rVal);
        break;
      }
      case 25:
      {
        // 001882B8
        // _OR
        auto rhs = pop();
        auto rVal = chk_int(rhs, m_current_funcdata);
        auto lhs = pop();
        auto lVal = chk_int(lhs, m_current_funcdata);
        push_int(lVal | rVal);
        break;
      }
      case 26:
      {
        // 001884D8
        // _NOT

        auto stack_data = pop();
        if (stack_data.m_data_type != Int)
        {
          panicf("RUNTIME ERROR: {}: Operand is not an integer!", m_current_funcdata->m_function_name);
        }

        push_int(!common::bits::to_bool(stack_data.m_data.i));
        break;
      }
      case 27:
        // 001886DC
        // _EXIT
        m_program_terminated = true;
        m_vmcode = nullptr;
        return;
      case 28:
        // 001887BC
        ++m_unk_field_50;
        if (!m_skip_flag)
        {
          break;
        }
        m_skip_flag = false;
        m_vmcode += 1;
        return;
      case 29:
      {
        // 00188398
        // _SIN
        auto lhs = pop();
        if (lhs.m_data_type == Int)
        {
          push_float(sinf(static_cast<f32>(lhs.m_data.i)));
        }
        else if (lhs.m_data_type == Float)
        {
          push_float(sinf(lhs.m_data.f));
        }
        else
        {
          panicf("RUNTIME ERROR at _SIN: {}: operand is not a number", m_current_funcdata->m_function_name);
        }
        break;
      }
      case 30:
      {
        // 00188438
        // _COS
        auto lhs = pop();
        if (lhs.m_data_type == Int)
        {
          push_float(cosf(static_cast<f32>(lhs.m_data.i)));
        }
        else if (lhs.m_data_type == Float)
        {
          push_float(cosf(lhs.m_data.f));
        }
        else
        {
          panicf("RUNTIME ERROR at _COS: {}: operand is not a number", m_current_funcdata->m_function_name);
        }
        break;
      }
      case 0:
      case 22:
      default:
        // 00187C08
        // nop
        break;
    }

    m_vmcode += 1;
  }
}

// 00186AE0
void runerror(const char* msg)
{
  log_trace("{}()", __func__);

  panicf("RUNTIME ERROR: {}\n", msg);
}

// 00186B20
void stkoverflow()
{
  log_trace("{}()", __func__);

  runerror("stack overflow");
}

void stkunderflow()
{
  log_trace("{}()", __func__);

  runerror("stack underflow");
}

// 00186B30
s32 chk_int(RS_STACKDATA stack_data, funcdata* func_data)
{
  if (stack_data.m_data_type != EStackDataType::Int)
  {
    panicf("RUNTIME ERROR: {}: operand is not integer\n", func_data->m_function_name);
  }
  return stack_data.m_data.i;
}

// 00186B90
bool is_true(RS_STACKDATA stack_data)
{
  if (stack_data.m_data_type == EStackDataType::Int)
  {
    return stack_data.m_data.i != 0;
  }
  return true;
}

// 00186BD0
void divby0error()
{
  log_trace("{}()", __func__);

  runerror("Divide by 0");
}

// 00186BE0
void modby0error()
{
  log_trace("{}()", __func__);

  runerror("Modulo by 0");
}

// 00186BF0
void print(RS_STACKDATA* stack_data, usize amount)
{
  for (; amount > 0; --amount)
  {
    log_info("print_stack_value: {}", *stack_data);
    ++stack_data;
  }
}

// 00188820
s32 rsGetStackInt(RS_STACKDATA* stack_data)
{
  if (stack_data->m_data_type == EStackDataType::Float)
  {
    return static_cast<int>(stack_data->m_data.f);
  }
  return stack_data->m_data.i;
}

// 00188860
void rsSetStack(RS_STACKDATA* stack_data, s32 value)
{
  if (stack_data->m_data_type == EStackDataType::Pointer)
  {
    stack_data->m_data.p->m_data.i = value;
  }
}
