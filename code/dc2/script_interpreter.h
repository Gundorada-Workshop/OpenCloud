#pragma once
#include <functional>

#include "common/debug.h"
#include "common/log.h"
#include "common/types.h"

// ~ 00146290 - 00147450

enum SPI_STACK_DATA_TYPE
{
  SPI_DATA_TYPE_STR = 0,
  SPI_DATA_TYPE_INT = 1,
  SPI_DATA_TYPE_FLT = 2,
  SPI_DATA_TYPE_INVALID = -1,
};

struct input_str
{
  // 0
  char* m_string{};
  // 4
  s32 m_length{};
  // 8
  s32 m_position{};

  inline void back()
  {
    m_position = std::max(m_position - 1, 0);
  }

  inline bool get(char* dest)
  {
    *dest = m_string[m_position];
    ++m_position;
    return m_position <= m_length;
  }

  // 00146290
  bool GetLine(std::string& line_dest, const std::string line_sep = "\r\n");
};

struct SPI_STACK
{
  SPI_STACK_DATA_TYPE data_type;
  // I don't actually know what type this is
  // but it's 4 bytes and casts to these types
  // so a union of those types seems like an idea
  union
  {
    sint as_integer;
    char* as_string;
    f32 as_float;
  };
};

template<>
struct fmt::formatter<SPI_STACK> : fmt::formatter<std::string_view>
{
  template<typename FormatContext>
  auto format(const SPI_STACK& stack_data, FormatContext& ctx)
  {
    if (stack_data.data_type == SPI_DATA_TYPE_INT)
    {
      return fmt::format_to(ctx.out(), "{}", stack_data.as_integer);
    }
    if (stack_data.data_type == SPI_DATA_TYPE_FLT)
    {
      return fmt::format_to(ctx.out(), "{}", stack_data.as_float);
    }
    if (stack_data.data_type == SPI_DATA_TYPE_STR)
    {
      return fmt::format_to(ctx.out(), "{}", stack_data.as_string);
    }
    return fmt::format_to(ctx.out(), "INVALID STACK DATA!!");
  }
};

struct SPI_TAG_PARAM
{
  const char* tag_name;
  std::function<bool(SPI_STACK*, int)> func;
};

// 00146470
// Get an string off the stack
char* spiGetStackString(SPI_STACK* stack);
// 001463e0
// Get an integer off the stack
sint spiGetStackInt(SPI_STACK* stack);
// 00146430
// Get a float off the stack
f32 spiGetStackFloat(SPI_STACK* stack);
// 001464a0
// Get a vec3 off the stack
void spiGetStackVector(vec3 v, SPI_STACK* stack);

#define trace_script_call(stack, count) do { log_trace("{}({}, {})", __func__, fmt::ptr(stack), count); } while (0)

struct SPI_TAG_HASH
{
  SPI_TAG_HASH* m_next_hash;
  const char* m_tag_name;
  usize m_index;
};

class CScriptInterpreter
{
public:

  void SetScript(const char* script, sint script_size)
  {
    // TODO
  }

  // 00146500
  void PushStack(SPI_STACK stack_item);

  // 00146590
  sint GetNextTAG(sint)
  {
    return 0; // TODO
  }

  // 001466F0
  void SetStack(SPI_STACK* stack, ssize stack_size);

  // 00146700
  void SetStringBuff(char* buff, ssize buff_size);

  // 00146720
  void Run();

  // 00146760
  sint hash(const char* str);

  // 001467B0
  void SetTag(const SPI_TAG_PARAM* param);

  // 00146980
  void SetScript(char* script, usize script_len);

  // 00146C70
  sint GetArgs();

  // 00147080
  bool SearchCommand(ssize* command_index_dest);


  // 0
  input_str m_input_str{};
  // C
  ssize m_stack_curr{};
  // 10
  ssize m_n_stack{};
  // 14
  SPI_STACK* m_stack{};
  // 18
  ssize m_n_string_buff{};
  // 1C
  char* m_string_buff_curr{};
  // 20
  char* m_string_buff{};
  // 24
  bool m_binary_script{};
  // 28
  ssize m_n_tag_param{};
  // 2C
  const SPI_TAG_PARAM* m_tag_param{ nullptr };
  // 30
  std::array<SPI_TAG_HASH*, 101>* m_p_hash_list;
  // 40
  std::array<SPI_TAG_HASH*, 101> m_hash_list;
  // 1E0
  std::array<SPI_TAG_HASH, 128> m_hash_buff;

  // ?

  // SIZE 0xED0
};
