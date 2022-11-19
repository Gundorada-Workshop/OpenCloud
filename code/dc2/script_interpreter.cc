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

// 00146500
void CScriptInterpreter::PushStack(SPI_STACK stack_item)
{
  log_trace("CScriptInterpreter::{}({})", __func__, stack_item);

  if (m_stack_curr >= m_n_stack)
  {
    log_warn("SPI stack over!!\n");
    return;
  }

  m_stack[m_stack_curr] = stack_item;
  ++m_stack_curr;
}

// 001466F0
void CScriptInterpreter::SetStack(SPI_STACK* stack, ssize stack_size)
{
  log_trace("CScriptInterpreter::{}({}, {})", __func__, fmt::ptr(stack), stack_size);

  m_stack = stack;
  m_n_stack = stack_size;

  m_stack_curr = 0;
}

// 00146700
void CScriptInterpreter::SetStringBuff(char* buff, ssize buff_size)
{
  log_trace("CScriptInterpreter::{}({}, {})", __func__, fmt::ptr(buff), buff_size);

  m_string_buff = buff;
  m_n_string_buff = buff_size;

  m_string_buff_curr = m_string_buff;
}

// 00146720
void CScriptInterpreter::Run()
{
  log_trace("CScriptInterpreter::{}()", __func__);

  while(GetNextTAG(1) >= 0) { }
}

// 00146760
sint CScriptInterpreter::hash(const char* str)
{
  log_trace("CScriptInterpreter::{}({})", __func__, str);

  sint out = 0;

  while(*str != '\0')
  {
    char ch = *str;

    out = (out * 256 + ch) % 0x65 & 0xFF;

    str++;
  }

  return out;
}

// 001467B0
void CScriptInterpreter::SetTag(const SPI_TAG_PARAM* param)
{
  log_trace("CScriptInterpreter::{}({})", __func__, fmt::ptr(param));

  m_tag_param = param;
  m_n_tag_param = 0;

  while (m_tag_param[m_n_tag_param].tag_name != nullptr &&
    m_tag_param[m_n_tag_param].tag_name[0] != '\0')
  {
    ++m_n_tag_param;
  }

  m_p_hash_list = nullptr;

  if (m_n_tag_param >= m_hash_buff.size())
  {
    return;
  }

  m_p_hash_list = &m_hash_list;

  for (int i = 0; i < m_p_hash_list[0].size(); ++i)
  {
    m_p_hash_list[0][i] = 0;
  }

  for (int i = 0; i < m_n_tag_param; ++i)
  {
    m_hash_buff[i].m_next_hash = nullptr;
    m_hash_buff[i].m_tag_name = m_tag_param[i].tag_name;
    // for lookup in m_tag_param for the associated function later
    m_hash_buff[i].m_index = i;

    uint hash_val = hash(m_tag_param[i].tag_name);

    // check to see if there's already any items stored at this index
    if (m_p_hash_list[0][hash_val] == nullptr)
    {
      // Nope; just store the hash here
      m_p_hash_list[0][hash_val] = &m_hash_buff[i];
    }
    else
    {
      // find and store the hash at the end of the list of hashes
      SPI_TAG_HASH* hash = m_p_hash_list[0][hash_val];
      for (; hash->m_next_hash != nullptr; hash = hash->m_next_hash) {}

      hash->m_next_hash = &m_hash_buff[i];
    }
  }
}

// 00146980
void CScriptInterpreter::SetScript(char* script, usize script_len)
{
  log_trace("CScriptInterpreter::{}({}, {})", __func__, script, script_len);

  m_input_str.m_string = script;
  m_input_str.m_length = script_len;
  m_input_str.m_position = 0;

  m_stack_curr = 0;

  constexpr char bin_prefix[] = "BIN";
  m_binary_script = strncmp(script, bin_prefix, std::size(bin_prefix) - 1) == 0;

  if (m_binary_script)
  {
    m_input_str.m_position += std::size(bin_prefix);
  }
  else
  {
    PreProcess(m_input_str);
  }
}

// 00146C70
sint CScriptInterpreter::GetArgs()
{
  log_trace("CScriptInterpreter::{}()", __func__);

  // NOTE: There's a SkipSpace here, but it's done at the beginning of the loop anyways

  bool args_not_terminated = true;
  sint n_args = 0;
  char arg_buf[0x100];
  sint arg_buf_index = 0;
  SPI_STACK parsed_arg;

  while (args_not_terminated)
  {
    // 146CB8
    if (!SkipSpace(m_input_str))
    {
      return n_args;
    }

    // 146CD0
    bool string_arg = false;
    char last_read;

    while (true)
    {
      // 146CD4
      if (!m_input_str.get(&last_read))
      {
        return n_args;
      }

      // 146CF4
      string_arg = string_arg || (last_read == '"');

      if (string_arg)
      {
        // NOTE: There's a special case where more than one character is read,
        // probably for shift-jis, at 00146D20; we probably don't have to worry about that

        if (last_read == '\\')
        {
          // An escape character! We'll want to expend the next character,
          // if it is a quotation, so it doesn't count as the end of the string.

          char next_char;
          if (!m_input_str.get(&next_char) || next_char != '"')
          {
            // End of string or not a quotation; back up
            m_input_str.back();
          }
          else
          {
            // Record the next character, not the escape character
            last_read = next_char;
          }
        }
      }

      if (string_arg || (last_read != ',' && last_read != ';'))
      {
        // 146DD8
        arg_buf[arg_buf_index++] = last_read;
        continue;
      }
      else if (last_read == ';')
      {
        args_not_terminated = false;
      }
      break;
    }

    // 146DEC
    if (arg_buf_index == 0 && last_read == ';')
    {
      return n_args;
    }

    // 146E00
    arg_buf[arg_buf_index] = '\0';
    ++n_args;

    SPI_STACK_DATA_TYPE arg_type = SPI_DATA_TYPE_INT;
    sint quote_count = 0;
    bool bad_number_chars = false;
    bool arg_invalid = false;

    if (arg_buf[0] == '"')
    {
      ++quote_count;
    }

    if (arg_buf[arg_buf_index - 1] == '"')
    {
      arg_buf[arg_buf_index - 1] = '\0';
      ++quote_count;
    }

    // NOTE: arg_buf_index moves from s2 -> s0
    for (arg_buf_index = 0; arg_buf[arg_buf_index] != '\0'; ++arg_buf_index)
    {
      // 146E54
      if (quote_count != 0)
      {
        continue;
      }

      char c = arg_buf[arg_buf_index];
      if (c == '.')
      {
        arg_type = SPI_DATA_TYPE_FLT;
      }

      if (CheckChar(c))
      {
        // 146E90
        if (c != '-' && c != '.' && c < '0' && c > '9')
        {
          bad_number_chars = true;
        }
      }

      // 146EBC
      if (!CheckChar(c))
      {
        arg_buf[arg_buf_index] = '\0';
        break;
      }
    }

    // 146EF4
    if (quote_count == 2)
    {
      arg_type = SPI_DATA_TYPE_STR;
    }

    // 146F08
    if ((bad_number_chars && arg_type != SPI_DATA_TYPE_STR) || arg_buf_index == 0)
    {
      arg_invalid = true;
    }

    parsed_arg.data_type = arg_type;

    // 146F2C
    if (arg_invalid)
    {
      parsed_arg.data_type = SPI_DATA_TYPE_INVALID;
      parsed_arg.as_integer = 0;
    }

    // 146F44
    switch (arg_type)
    {
      // 146F50
      case SPI_DATA_TYPE_STR:
      {
        uint str_len = strlen(&arg_buf[1]);

        if (m_string_buff_curr + str_len + 1 >= m_string_buff + m_n_string_buff)
        {
          log_warn("SPI string buffer over!!");
        }
        else
        {
          parsed_arg.as_string = m_string_buff_curr;
          strcpy(m_string_buff_curr, &arg_buf[1]);
        }
        break;
      }
      // 146FD0
      case SPI_DATA_TYPE_INT:
        parsed_arg.as_integer = atoi(arg_buf);
        break;
      // 146FF0
      case SPI_DATA_TYPE_FLT:
        parsed_arg.as_float = static_cast<f32>(atof(arg_buf));
        break;
      default:
        break;
    }

    PushStack(parsed_arg);
  }

  return n_args;
}

// 00147080
bool CScriptInterpreter::SearchCommand(ssize* command_index_dest)
{
  log_trace("CScriptInterpreter::{}({})", __func__, fmt::ptr(command_index_dest));

  if (m_binary_script)
  {
    if (m_input_str.m_position >= m_input_str.m_length)
    {
      return false;
    }

    // lh $v1, 0($v1)
    s16 index = m_input_str.m_string[m_input_str.m_position] |
      (m_input_str.m_string[m_input_str.m_position + 1] << 8);
    *command_index_dest = index;
    m_input_str.m_position += 2;

    return index >= 0;
  }

  if (!SkipSpace(m_input_str))
  {
    return false;
  }

  char command_buff[0x100];
  usize command_buff_index = 0;

  char c;
  while (true)
  {
    if (!m_input_str.get(&c))
    {
      return false;
    }

    if (!CheckChar(c) || c == ';')
    {
      break;
    }

    command_buff[command_buff_index++] = c;
  }

  if (c == ';')
  {
    m_input_str.back();
  }

  command_buff[command_buff_index] = '\0';
  if (command_buff[0] < 'A' || command_buff[0] > 'Z')
  {
    // 147190
    // ?
    *command_index_dest = -1;
    return true;
  }

  if (m_p_hash_list == nullptr)
  {
    // Huh, no hash list? Was the provided tag list too large to store?
    // We'll do an unhashed look up on the provided tag list.

    for (int i = 0; i < m_n_tag_param; ++i)
    {
      if (strcmp(m_tag_param[m_n_tag_param].tag_name, command_buff) == 0)
      {
        *command_index_dest = i;
        return true;
      }
    }
  }
  else
  {
    // We've got a hash list, so we can do a faster look up.
    uint hash_val = hash(command_buff);
    auto hash = m_p_hash_list[0][hash_val];

    for (auto hash = m_p_hash_list[0][hash_val]; hash != nullptr; hash = hash->m_next_hash)
    {
      if (strcmp(command_buff, hash->m_tag_name) == 0)
      {
        *command_index_dest = hash->m_index;
        return true;
      }
    }
  }

  // 147250
  // ?
  *command_index_dest = -1;
  return true;
}