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

class CScriptInterpreter
{
public:

  // 001467b0
  void SetTag(const SPI_TAG_PARAM* param)
  {
    // TODO
  }

  void SetScript(const char* script, sint script_size)
  {
    // TODO
  }

  // 00146720
  void Run();

  // 00146590
  sint GetNextTAG(sint)
  {
    return 0; // TODO
  }

  // 00146760
  sint hash(char* str);


  // 0
  input_str m_input_str{};
  // C
  _DWORD m_unk_field_C{};
  // 14
  _DWORD m_unk_field_14{};
  // 2C
  _DWORD m_unk_field_2C{};
};
