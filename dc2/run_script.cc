#include "common/log.h"
#include "run_script.h"

set_log_channel("run_script");

// 00186D40
void CRunScript::DeleteProgram()
{
  log_trace("CRunScript::{}()", __func__);

  m_unk_field_3C = false;
  m_unk_field_40 = false;
  m_unk_field_44 = nullptr;
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

// 001871D0
void CRunScript::ext_func(ext_func_t** ext_func, usize length)
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

// 001873B0
void CRunScript::skip()
{
  log_trace("CRunScript::{}()", __func__);

  m_unk_field_40 = true;
  resume();
}

// 001873C0
void CRunScript::exe(vmcode_t* code)
{
  log_trace("CRunScript::{}({})", __func__, fmt::ptr(code));

  m_vmcode = code;

  for (;; m_vmcode += 1)
  {
    using Type = EStackDataType::EStackDataType;

    switch (m_vmcode->m_instruction)
    {
      case 1:
        // 00187414
        todo;
        break;
      case 2:
        // 001876A0
        todo;
        break;
      case 3:
        // 001878E8
        todo;
        break;
      case 4:
        // 00187958
        todo;
        break;
      case 5:
        // 00187890
        todo;
        break;
      case 6:
      {
        // 00187D00
        // _ADD
        auto rhs = pop();
        auto lhs = pop();

        if (lhs.m_data_type == Type::Int && rhs.m_data_type == Type::Int)
        {
          push_int(lhs.m_data.i + rhs.m_data.i);
        }
        else if (lhs.m_data_type == Type::Float && rhs.m_data_type == Type::Float)
        {
          push_float(lhs.m_data.f + rhs.m_data.f);
        }
        else if (lhs.m_data_type == Type::Float && rhs.m_data_type == Type::Int)
        {
          push_float(lhs.m_data.f + rhs.m_data.i);
        }
        else if (lhs.m_data_type == Type::Int && rhs.m_data_type == Type::Float)
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

        if (lhs.m_data_type == Type::Int && rhs.m_data_type == Type::Int)
        {
          push_int(lhs.m_data.i - rhs.m_data.i);
        }
        else if (lhs.m_data_type == Type::Float && rhs.m_data_type == Type::Float)
        {
          push_float(lhs.m_data.f - rhs.m_data.f);
        }
        else if (lhs.m_data_type == Type::Float && rhs.m_data_type == Type::Int)
        {
          push_float(lhs.m_data.f - rhs.m_data.i);
        }
        else if (lhs.m_data_type == Type::Int && rhs.m_data_type == Type::Float)
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

        if (lhs.m_data_type == Type::Int && rhs.m_data_type == Type::Int)
        {
          push_int(lhs.m_data.i * rhs.m_data.i);
        }
        else if (lhs.m_data_type == Type::Float && rhs.m_data_type == Type::Float)
        {
          push_float(lhs.m_data.f * rhs.m_data.f);
        }
        else if (lhs.m_data_type == Type::Float && rhs.m_data_type == Type::Int)
        {
          push_float(lhs.m_data.f * rhs.m_data.i);
        }
        else if (lhs.m_data_type == Type::Int && rhs.m_data_type == Type::Float)
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

        if (lhs.m_data_type == Type::Int && rhs.m_data_type == Type::Int)
        {
          push_int(lhs.m_data.i / rhs.m_data.i);
        }
        else if (lhs.m_data_type == Type::Float && rhs.m_data_type == Type::Float)
        {
          push_float(lhs.m_data.f / rhs.m_data.f);
        }
        else if (lhs.m_data_type == Type::Float && rhs.m_data_type == Type::Int)
        {
          push_float(lhs.m_data.f / rhs.m_data.i);
        }
        else if (lhs.m_data_type == Type::Int && rhs.m_data_type == Type::Float)
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
        // 00188208
        todo;
        break;
      case 11:
        // 00188300
        todo;
        break;
      case 12:
        // 00188550
        todo;
        break;
      case 13:
        // 001885E0
        todo;
        break;
      case 14:
        // 00187A38
        todo;
        break;
      case 15:
        // 0018871C
        todo;
        break;
      case 16:
        // 00187968
        todo;
        break;
      case 17:
        // 001879E0
        todo;
        break;
      case 18:
        // 00187988
        todo;
        break;
      case 19:
        // 001886F0
        todo;
        break;
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
        todo;
        break;
      case 23:
        // 001887A8
        todo;
        break;
      case 24:
        // 00188270
        todo;
        break;
      case 25:
        // 001882B8
        todo;
        break;
      case 26:
        // 001884D8
        todo;
        break;
      case 27:
        // 001886DC
        todo;
        break;
      case 28:
        // 001887BC
        todo;
        break;
      case 29:
        // 00188398
        todo;
        break;
      case 30:
        // 00188438
        todo;
        break;
      case 0:
      case 22:
      default:
        // 00187C08
        // nop
        break;
    }
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
  if (stack_data.m_data_type != EStackDataType::Int)
  {
    return false;
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
    log_info("print_stack_value: {}", stack_data);
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
