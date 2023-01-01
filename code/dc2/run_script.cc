#include "common/bits.h"
#include "common/log.h"

#include "dc2/run_script.h"

set_log_channel("run_script");

using namespace script::rs;

// 00186AE0
void runerror(const char* msg);
// 00186B20
void stkoverflow();
void stkunderflow();
// 00186B30
s32 chk_int(stack_data data, func_data_entry* func_data);
// 00186BD0
void divby0error();
// 00186BE0
void modby0error();
// 00186BF0
void print(stack_data* data, usize amount);
// 00186B90
bool is_true(stack_data data);

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
    stkoverflow();
}

// 00186D80
void CRunScript::push(script::rs::stack_data data)
{
  log_trace("CRunScript::{}({})", __func__, data);

  check_stack();

  *m_stack_current = std::move(data);

  ++m_stack_current;
}

// 00186DD0
void CRunScript::push_int(int data)
{
  log_trace("CRunScript::{}({})", __func__, data);

  check_stack();

  m_stack_current->type = stack_data_type::_int;
  m_stack_current->_int = data;

  ++m_stack_current;
}

// 00186E20
void CRunScript::push_str(char* data)
{
  log_trace("CRunScript::{}({})", __func__, data);

  check_stack();

  m_stack_current->type = stack_data_type::_str;
  m_stack_current->_str = data;

  ++m_stack_current;
}

// 00186E70
void CRunScript::push_ptr(stack_data* data)
{
  log_trace("CRunScript::{}({})", __func__, fmt::ptr(data));

  m_stack_current->type = stack_data_type::_ptr;
  m_stack_current->_ptr = data;

  ++m_stack_current;
}

// 00186E70
void CRunScript::push_float(f32 data)
{
  log_trace("CRunScript::{}({})", __func__, data);

  m_stack_current->type = stack_data_type::_flt;
  m_stack_current->_flt = data;

  ++m_stack_current;
}

// 00186F10
stack_data CRunScript::pop()
{
  log_trace("CRunScript::{}()", __func__);

  --m_stack_current;

  check_stack();

  return *(m_stack_current + 1);
}

// 00186F30
instruction* CRunScript::call_func(func_data_entry* func, instruction* return_address)
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
  m_function_stack_frame = m_stack_current -= func->argument_count;

  // now create space on the stack for the function's variables
  m_stack_current = m_function_stack_frame + func->stack_byte_count;

  m_current_funcdata = func;

  // Increment the call stack
  ++m_calldata_current;

  // Zero-Initialize our function stack frame (but not the arguments!)
  stack_data* locals = m_function_stack_frame + func->argument_count;
  memset(locals, 0, sizeof(stack_data) * (func->stack_byte_count - func->argument_count));

  // Check for stack overflow
  check_stack();

  // Now return the address of the start of the function
  return reinterpret_cast<instruction*>(static_cast<uptr>(m_script_data) + static_cast<uptr>(func->code_start_byte_offset));
}

// 00187020
instruction* CRunScript::ret_func()
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
void CRunScript::ext(stack_data* stack_data, s32 stack_count)
{
  log_trace("CRunScript::{}({}, {})", __func__, *stack_data, stack_count);

  // First item of stack_data should be the extension function ID.
  s32 call_index = stack_data->_int;

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
void CRunScript::load(header* prog_header, stack_data* stack_buf, usize n_stack_buf, RS_CALLDATA* call_stack_buf, usize n_call_stack_buf)
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
  m_script_data = prog_header->data_start_byte_offset;

  if (strncmp(m_prog_header->magic, "SB2", 3) == 0)
  {
    // The 2nd version of a RUN SCRIPT script, so we've got *fancy* global variables!!!
    m_script_version = 2;

    // Allocate space for global variables; these are variables that "pointer" stack data can directly reference.
    m_global_variables = m_stack_bottom;
    m_stack_bottom += prog_header->global_variable_count;
    m_n_stack_buf -= prog_header->global_variable_count;

    // Zero-initialize global variables
    memset(m_global_variables, 0, sizeof(stack_data) * prog_header->global_variable_count);
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
    return -1;

  // Initialize our stacks
  m_stack_current = m_stack_bottom;
  m_calldata_current = m_calldata_bottom;

  // And now we'll want to try and find our program
  m_current_funcdata = nullptr;
  if (program_id < 0)
  {
    // Not sure what this is for? Script version 1 maybe? Doesn't seem valid for SB2...
    m_current_funcdata = reinterpret_cast<func_data_entry*>(reinterpret_cast<uptr>(m_prog_header) + static_cast<uptr>(m_prog_header->unk0));
  }
  else
  {
    func_table_entry* func_list = reinterpret_cast<func_table_entry*>(reinterpret_cast<uptr>(m_prog_header) + static_cast<uptr>(m_prog_header->header_byte_count));
    for (usize i = 0; i < m_prog_header->function_count; ++i)
    {
      if (static_cast<s32>(func_list[i].id) == program_id)
      {
        m_current_funcdata = reinterpret_cast<func_data_entry*>(static_cast<uptr>(func_list[i].function_data_byte_offset));
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
  m_function_stack_frame = m_stack_current - m_current_funcdata->argument_count;

  // Then allocate some new space for the rest of the frame
  m_stack_current = m_function_stack_frame + m_current_funcdata->stack_byte_count;

  // Check for an overflow
  check_stack();

  // Memset our function stack frame (but not the arguments)
  stack_data* locals = m_function_stack_frame + m_current_funcdata->argument_count;
  memset(locals, 0, sizeof(stack_data) * (m_current_funcdata->stack_byte_count - m_current_funcdata->argument_count));

  // Now let's run the program
  m_program_terminated = false;
  m_skip_flag = false;
  m_unk_field_50 = 0;

  instruction* code = reinterpret_cast<instruction*>( // bet Rust won't let you do this
    // header
    reinterpret_cast<uptr>(m_prog_header) + 
    // data offset
    static_cast<uptr>(m_prog_header->data_start_byte_offset) + 
    // code
    static_cast<uptr>(m_current_funcdata->code_start_byte_offset)
  );

  exe(code);

  return static_cast<sint>(!m_program_terminated);
}

// 00187360
bool CRunScript::check_program(s32 program_id)
{
  log_trace("CRunScript::{}({})", __func__, program_id);

  func_table_entry* func_entries = reinterpret_cast<func_table_entry*>(reinterpret_cast<uptr>(m_prog_header) + static_cast<uptr>(m_prog_header->header_byte_count));

  for (u32 i = 0; i < m_prog_header->function_count; ++i)
  {
    if (static_cast<s32>(func_entries[i].id) == program_id)
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
void CRunScript::exe(instruction* code)
{
  log_trace("CRunScript::{}({})", __func__, fmt::ptr(code));

  m_vmcode = code;

  while (true)
  {
    switch (m_vmcode->opcode)
    {
      case opcode::_push_stack: // 00187414
      {
        const auto& encoding = code->load_store_relative;

        switch (code->load_store_relative.mode)
        {
          case address_mode::frame_relative: // 187468
            push(m_function_stack_frame[encoding.address]);
            break;
          case address_mode::frame_offset: // 1874B4
          {
            const auto offset = chk_int(pop(), m_current_funcdata);

            push(m_function_stack_frame[encoding.address + offset]);
            break;
          }
          case address_mode::data_offset: // 1874FC
          {
            const auto offset = chk_int(pop(), m_current_funcdata);

            push(*(m_function_stack_frame[encoding.address]._ptr + offset));
            break;
          }
          case address_mode::frame_relative_flt: // 187548
          {
            // 187548
            m_function_stack_frame[encoding.address].type = stack_data_type::_flt;
            push(m_function_stack_frame[encoding.address]);
            break;
          }
          case address_mode::frame_offset_flt: // 1875C8
          {
            const auto offset = chk_int(pop(), m_current_funcdata);

            auto data = &m_function_stack_frame[encoding.address];
            (data + offset)->type = stack_data_type::_flt;

            push(*data);
            break;
          }
          case address_mode::data_offset_flt: // 187630
          {
            const auto offset = chk_int(pop(), m_current_funcdata);

            auto data = &m_function_stack_frame[encoding.address];
            (data->_ptr + offset)->type = stack_data_type::_flt;

            push(*data);
            break;
          }
          case address_mode::global_relative: // 18748C SB2 only!
            push(m_global_variables[encoding.address]);
            break;
          case address_mode::global_relative_flt: // 187588 SB2 only!
          {
            auto data = m_global_variables[encoding.address];
            data.type = stack_data_type::_flt;

            push(data);
            break;
          }
          default:
            break;
        }
        break;
      }
      case opcode::_push_ptr:
      {
        const auto& encoding = code->load_store_relative;

        // 001876A0
        switch (code->load_store_relative.mode)
        {
          case address_mode::frame_relative: // 1876F0
          case address_mode::frame_relative_flt: // 1877C0
            push_ptr(m_function_stack_frame + encoding.address);
            break;
          case address_mode::frame_offset: // 187730
          case address_mode::frame_offset_flt: // 187800
          {
            const auto offset = chk_int(pop(), m_current_funcdata) * sizeof(stack_data);

            push_ptr(
              reinterpret_cast<stack_data*>(reinterpret_cast<uptr>(m_function_stack_frame + encoding.address) + offset)
            );
            break;
          }
          case address_mode::data_offset: // 187774
          case address_mode::data_offset_flt: // 187844
          {
            const auto offset = chk_int(pop(), m_current_funcdata) * sizeof(stack_data);

            push_ptr(
              reinterpret_cast<stack_data*>(reinterpret_cast<uptr>((m_function_stack_frame + encoding.address)->_ptr) + offset)
            );
            break;
          }
          case address_mode::global_relative: // 187710
          case address_mode::global_relative_flt: // 1877E0
          {
            push_ptr(
              reinterpret_cast<stack_data*>(reinterpret_cast<uptr>(m_global_variables) + (encoding.address * sizeof(stack_data)))
            );
            break;
          }
          default:
            break;
        }
        break;
      }
      case opcode::_push: // 001878E8
      {
        const auto& encoding = code->load_store_immediate;

        switch (encoding.type)
        {
        case value_data_type::_int:
          push_int(encoding.data._int);
          break;
        case value_data_type::_flt:
          push_float(encoding.data._flt);
          break;
        case value_data_type::_str:
          push_str(reinterpret_cast<char*>(static_cast<uptr>(m_script_data) + static_cast<uptr>(encoding.data._str)));
          break;
        default:
          break;
        }
        break;
      }
      case opcode::_pop: // 00187958
        pop();
        break;
      case opcode::_deref: // 00187890
      {
        // NOTE: an intermediate variable, var_130, is used here, but I don't think it's necessary
        auto val = pop();
        auto ptr = pop();

        ptr._ptr->type = val.type;
        ptr._ptr = val._ptr;

        push(val);
        break;
      }
      case opcode::_add: // 00187D00
      {
        const auto rhs = pop();
        const auto lhs = pop();

        if (lhs.type == stack_data_type::_int && rhs.type == stack_data_type::_int)
          push_int(lhs._int + rhs._int);
        else if (lhs.type == stack_data_type::_flt && rhs.type == stack_data_type::_flt)
          push_float(lhs._flt + rhs._flt);
        else if (lhs.type == stack_data_type::_flt && rhs.type == stack_data_type::_int)
          push_float(lhs._flt + rhs._int);
        else if (lhs.type == stack_data_type::_int && rhs.type == stack_data_type::_flt)
          push_float(lhs._int + rhs._flt);
        else
          unreachable_code;

        break;
      }
      case opcode::_sub: // 00187E30
      {
        const auto rhs = pop();
        const auto lhs = pop();

        if (lhs.type == stack_data_type::_int && rhs.type == stack_data_type::_int)
          push_int(lhs._int - rhs._int);
        else if (lhs.type == stack_data_type::_flt && rhs.type == stack_data_type::_flt)
          push_float(lhs._flt - rhs._flt);
        else if (lhs.type == stack_data_type::_flt && rhs.type == stack_data_type::_int)
          push_float(lhs._flt - rhs._int);
        else if (lhs.type == stack_data_type::_int && rhs.type == stack_data_type::_flt)
          push_float(lhs._int - rhs._flt);
        else
          unreachable_code;

        break;
      }
      case opcode::_mul: // 00187F60
      {
        const auto rhs = pop();
        const auto lhs = pop();

        if (lhs.type == stack_data_type::_int && rhs.type == stack_data_type::_int)
          push_int(lhs._int * rhs._int);
        else if (lhs.type == stack_data_type::_flt && rhs.type == stack_data_type::_flt)
          push_float(lhs._flt * rhs._flt);
        else if (lhs.type == stack_data_type::_flt && rhs.type == stack_data_type::_int)
          push_float(lhs._flt * rhs._int);
        else if (lhs.type == stack_data_type::_int && rhs.type == stack_data_type::_flt)
          push_float(lhs._int * rhs._flt);
        else
          unreachable_code;

        break;
      }
      case opcode::_div: // 00188090
      {
        const auto rhs = pop();
        const auto lhs = pop();

        if (rhs._int == 0)
          divby0error();

        if (lhs.type == stack_data_type::_int && rhs.type == stack_data_type::_int)
          push_int(lhs._int / rhs._int);
        else if (lhs.type == stack_data_type::_flt && rhs.type == stack_data_type::_flt)
          push_float(lhs._flt / rhs._flt);
        else if (lhs.type == stack_data_type::_flt && rhs.type == stack_data_type::_int)
          push_float(lhs._flt / rhs._int);
        else if (lhs.type == stack_data_type::_int && rhs.type == stack_data_type::_flt)
          push_float(lhs._int / rhs._flt);
        else
          unreachable_code;

        break;
      }
      case opcode::_mod: // 00188208
      {
        const auto rhs = pop();
        const auto lhs = pop();
        
        // error handling (not int / div by 0)
        chk_int(rhs, m_current_funcdata);
        chk_int(lhs, m_current_funcdata);

        if (rhs._int == 0)
          modby0error();
        
        push_int(lhs._int % rhs._int);

        break;
      }
      case opcode::_neg: // 00188300
      {
        const auto lhs = pop();

        if (lhs.type == stack_data_type::_int)
          push_int(-lhs._int);
        else if (lhs.type == stack_data_type::_flt)
          push_float(-lhs._flt);
        else
          unreachable_code;

        break;
      }
      case opcode::_itof: // 00188550
      {
        const auto lhs = pop();

        if (lhs.type == stack_data_type::_int)
          push_float(static_cast<f32>(lhs._int));
        else if (lhs.type == stack_data_type::_flt)
          push_float(lhs._flt);
        else
          unreachable_code;

        break;
      }
      case opcode::_ftoi: // 001885E0
      {
        const auto lhs = pop();

        if (lhs.type == stack_data_type::_int)
          push_int(lhs._int);
        else if (lhs.type == stack_data_type::_flt)
          push_int(static_cast<s32>(lhs._flt));
        else
          unreachable_code;

        break;
      }
      case opcode::_cmp: // 00187A38
      {
        const auto& encoding = code->comparison;

        const auto rhs = pop();
        const auto lhs = pop();

        if (lhs.type == stack_data_type::_int && rhs.type == stack_data_type::_int)
        {
          const s32 lVal = lhs._int;
          const s32 rVal = rhs._int;

          switch (encoding.function)
          {
            case comparision_function::_eq:
              push_int(lVal == rVal);
              break;
            case comparision_function::_ne:
              push_int(lVal != rVal);
              break;
            case comparision_function::_lt:
              push_int(lVal < rVal);
              break;
            case comparision_function::_le:
              push_int(lVal <= rVal);
              break;
            case comparision_function::_gt:
              push_int(lVal > rVal);
              break;
            case comparision_function::_ge:
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

          if (lhs.type == stack_data_type::_int)
            lVal = static_cast<f32>(lhs._int);
          else if (lhs.type == stack_data_type::_flt)
            lVal = lhs._flt;
          else
            panicf("RUNTIME ERROR at _CMP: lhs is not number");

          if (rhs.type == stack_data_type::_int)
            rVal = static_cast<f32>(rhs._int);
          else if (rhs.type == stack_data_type::_flt)
            rVal = rhs._flt;
          else
            panicf("RUNTIME ERROR at _CMP: rhs is not number");

          switch (encoding.function)
          {
            case comparision_function::_eq:
              push_int(lVal == rVal);
              break;
            case comparision_function::_ne:
              push_int(lVal != rVal);
              break;
            case comparision_function::_lt:
              push_int(lVal < rVal);
              break;
            case comparision_function::_le:
              push_int(lVal <= rVal);
              break;
            case comparision_function::_gt:
              push_int(lVal > rVal);
              break;
            case comparision_function::_ge:
              push_int(lVal >= rVal);
              break;
            default:
              break;
          }
        }
        break;
      }
      case opcode::_ret: // 0018871C
      {
        const auto return_value = pop();

        if (m_calldata_current == m_calldata_bottom)
        {
          // The callstack has been completely unwound, stop execution.
          push(return_value);

          m_last_return_value = std::move(return_value);
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
      case opcode::_jmp: // 00187968
      {
        const auto& encoding = code->jump;

        if (!m_skip_flag)
          m_vmcode = reinterpret_cast<instruction*>(static_cast<uptr>(m_script_data) + encoding.address);

        break;
      }
      case opcode::_bf: // 001879E0
      {
        const auto& encoding = code->conditional_branch;

        if (!m_skip_flag && !is_true(pop()))
        {
          if (encoding.restore_flag == test_flag_mode::preserve)
            push_int(false);

          m_vmcode = reinterpret_cast<instruction*>(static_cast<uptr>(m_script_data) + encoding.address);
        }

        break;
      }
      case opcode::_bt: // 00187988
      {
        const auto& encoding = code->conditional_branch;

        if (!m_skip_flag && is_true(pop()))
        {
          if (encoding.restore_flag == test_flag_mode::preserve)
            push_int(true);

          m_vmcode = reinterpret_cast<instruction*>(static_cast<uptr>(m_script_data) + encoding.address);
        }

        break;
      }
      case opcode::_call: // 001886F0
      {
        const auto& encoding = code->jump;

        func_data_entry* fn = reinterpret_cast<func_data_entry*>(static_cast<uptr>(m_script_data) + encoding.address);
        
        // call_func returns the address of the code at the start of the function;
        // we have to decrement it once, since the loop will increment it at the end.
        m_vmcode = call_func(fn, code) - 1;
        break;
      }
      case opcode::_print: // 00188670
      {
        const auto& encoding = code->single_integer;

        m_stack_current -= encoding.value;
        print(m_stack_current, encoding.value);
        break;
      }
      case opcode::_ext: // 0018869C
      {
        const auto& encoding = code->single_integer;

        m_stack_current -= encoding.value;

        if (!m_skip_flag)
          ext(m_stack_current, encoding.value);

        break;
      }
      case opcode::_yld: // 001887A8
      {
        if (!m_skip_flag)
        {
          m_vmcode += 1;
          return;
        }

        break;
      }
      case opcode::_and: // 00188270
      {
        const auto rhs = pop();
        const auto lhs = pop();

        const auto rVal = chk_int(rhs, m_current_funcdata);
        const auto lVal = chk_int(lhs, m_current_funcdata);

        push_int(lVal & rVal);

        break;
      }
      case opcode::_or: // 001882B8
      {
        const auto rhs = pop();
        const auto lhs = pop();

        const auto rVal = chk_int(rhs, m_current_funcdata);
        const auto lVal = chk_int(lhs, m_current_funcdata);

        push_int(lVal | rVal);

        break;
      }
      case opcode::_not: // 001884D8
      {
        const auto stack_data = pop();

        if (stack_data.type != stack_data_type::_int)
          panicf("RUNTIME ERROR: Operand is not an integer!");

        const auto value = common::bits::to_bool(stack_data._int);

        push_int(value);

        break;
      }
      case opcode::_exit: // 001886DC
        m_program_terminated = true;
        m_vmcode = nullptr;

        return;
      case opcode::_unk0: // 001887BC
        ++m_unk_field_50;

        if (!m_skip_flag)
          break;

        m_skip_flag = false;
        m_vmcode += 1;

        return;
      case opcode::_sin: // 00188398
      {
        const auto lhs = pop();

        f32 result;
        switch (lhs.type)
        {
        case stack_data_type::_int:
          result = sinf(static_cast<f32>(lhs._int));
          break;
        case stack_data_type::_flt:
          result = sinf(lhs._flt);
          break;
        default:
          panicf("RUNTIME ERROR at _SIN: operand is not a number");
        }

        push_float(result);

        break;
      }
      case opcode::_cos: // 00188438
      {
        const auto lhs = pop();

        f32 result;
        switch (lhs.type)
        {
        case stack_data_type::_int:
          result = cosf(static_cast<f32>(lhs._int));
          break;
        case stack_data_type::_flt:
          result = cosf(lhs._flt);
          break;
        default:
          panicf("RUNTIME ERROR at _COS: operand is not a number");
        }

        push_float(result);

        break;
      }
      case opcode::_end:
      case opcode::_unk1:
      default: // 00187C08
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
s32 chk_int(stack_data data, func_data_entry* func_data)
{
  if (data.type != stack_data_type::_int)
    panicf("RUNTIME ERROR: operand is not integer\n");

  return data._int;
}

// 00186B90
bool is_true(stack_data data)
{
  if (data.type == stack_data_type::_int)
    return common::bits::to_bool(data._int);

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
void print(stack_data* data, usize amount)
{
  for (; amount > 0; --amount)
  {
    log_info("print_stack_value: {}", *data);
    ++data;
  }
}
