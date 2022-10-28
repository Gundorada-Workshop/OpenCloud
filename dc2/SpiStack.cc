#include "SpiStack.h"

char* GetStackString(SPI_STACK* stack)
{
  if(stack->data_type != SPI_DATA_TYPE_STR)
  {
    return NULL;
  }

  return stack->as_string;
}

int GetStackInt(SPI_STACK* stack)
{
  switch (stack->data_type)
  {
  case SPI_DATA_TYPE_INT:
    return stack->as_integer;
  case SPI_DATA_TYPE_FLT:
    return static_cast<int>(stack->as_float);
  }

  return 0;
}

float GetStackFloat(SPI_STACK* stack)
{
  switch(stack->data_type)
  {
    case SPI_DATA_TYPE_INT:
      return static_cast<float>(stack->as_integer);
    case SPI_DATA_TYPE_FLT:
      return stack->as_float;
  }

  return 0.0f;
}

void spiGetStackVector(float v[3], SPI_STACK* stack)
{
  v[0] = GetStackFloat(stack);
  v[1] = GetStackFloat(++stack);
  v[2] = GetStackFloat(++stack);
}
