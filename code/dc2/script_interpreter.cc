#include "common/log.h"

#include "dc2/script_interpreter.h"

set_log_channel("script_interpreter");

static bool SkipSpace(input_str& str);
static bool CheckChar(char ch);
static void PreProcess(input_str& str);

char* spiGetStackString(SPI_STACK* stack)
{
  if (stack->data_type != SPI_DATA_TYPE_STR)
  {
    return NULL;
  }

  return stack->as_string;
}

sint spiGetStackInt(SPI_STACK* stack)
{
  switch (stack->data_type)
  {
    case SPI_DATA_TYPE_INT:
      return stack->as_integer;
    case SPI_DATA_TYPE_FLT:
      return static_cast<sint>(stack->as_float);
  }

  return 0;
}

f32 spiGetStackFloat(SPI_STACK* stack)
{
  switch (stack->data_type)
  {
    case SPI_DATA_TYPE_INT:
      return static_cast<f32>(stack->as_integer);
    case SPI_DATA_TYPE_FLT:
      return stack->as_float;
  }

  return 0.0f;
}

void spiGetStackVector(vec3 v, SPI_STACK* stack)
{
  v[0] = spiGetStackFloat(stack);
  v[1] = spiGetStackFloat(++stack);
  v[2] = spiGetStackFloat(++stack);
}

// 00146290
bool input_str::GetLine(std::string& line_dest, const std::string line_sep)
{
  log_trace("input_str::{}({}, {})", __func__, fmt::ptr(&line_dest), line_sep);

  while (memcmp(&m_string[m_position], line_sep.data(), line_sep.length()) != 0)
  {
    char c;
    if (!get(&c))
    {
      return false;
    }
    line_dest += c;
  }

  m_position += line_sep.size();
  return true;
}

// 00147280
static bool SkipSpace(input_str& str)
{
  for (; str.m_position < str.m_length; ++str.m_position)
  {
    if (CheckChar(str.m_string[str.m_position]))
    {
      break;
    }
  }

  return str.m_position < str.m_length;
}

// 00147300
static bool CheckChar(char ch)
{
  return ch != '\r' && ch != '\n' && ch != '\t' && ch != ' ';
}

// 00147350
static void PreProcess(input_str& str)
{
  for (int i = 0; i < str.m_length; ++i)
  {
    if (str.m_string[i] == '/' && str.m_string[i + 1] == '/')
    {
      // Remove same line comment
      for (; i < str.m_length; ++i)
      {
        if (str.m_string[i] == '\n' || str.m_string[i] == '\r')
        {
          break;
        }

        str.m_string[i] = ' ';
      }
    }

    if (str.m_string[i] == '/' && str.m_string[i + 1] == '*')
    {
      // Remove multi-line comment
      for (; i < str.m_length; ++i)
      {
        if (str.m_string[i] == '*' && str.m_string[i + 1] == '/')
        {
          // remove end of comment marker
          str.m_string[i] = ' ';
          str.m_string[i + 1] = ' ';
          break;
        }

        str.m_string[i] = ' ';
      }
    }
  }
}

void CScriptInterpreter::Run()
{
  while(GetNextTAG(1) > -1) { }
}

sint CScriptInterpreter::hash(char* str)
{
  sint out = 0;

  while(*str != '\0')
  {
    char ch = *str;

    out = (out * 256 + ch) % 0x65 & 0xFF;

    str++;
  }

  return out;
}
