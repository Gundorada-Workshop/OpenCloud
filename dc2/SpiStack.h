#pragma once
#include <functional>
#include "common/types.h"

enum SPI_STACK_DATA_TYPE
{
  SPI_DATA_TYPE_STR = 0,
  SPI_DATA_TYPE_INT = 1,
  SPI_DATA_TYPE_FLT = 2,
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
char* GetStackString(SPI_STACK* stack);
// 001463e0
// Get an integer off the stack
sint GetStackInt(SPI_STACK* stack);
// 00146430
// Get a float off the stack
f32 GetStackFloat(SPI_STACK* stack);
// 001464a0
// Get a vec3 off the stack
void spiGetStackVector(vec3 v, SPI_STACK* stack);
