#include "common/log.h"
#include "run_script.h"

set_log_channel("run_script");

// 00186B20
void CRunScript::stkoverflow() const
{
  log_trace("CRunScript::{}()", __func__);

  log_error("stack overflow");
  throw std::length_error("stack overflow");
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
  log_trace("CRunScript::{}(...)", __func__/*, data TODO*/);

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
  return *m_stack_current;
}

// 001873C0
void CRunScript::exe(vmcode_t* code)
{
  log_trace("CRunScript::{}({})", __func__, fmt::ptr(code));

  m_vmcode = code;

  for (;; m_vmcode += 1)
  {
    switch (m_vmcode->instruction)
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
        // 00187D00
        todo;
        break;
      case 7:
        // 00187E30
        todo;
        break;
      case 8:
        // 00187F60
        todo;
        break;
      case 9:
        // 00188090
        todo;
        break;
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
        // 00188670
        todo;
        break;
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