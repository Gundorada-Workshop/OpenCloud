#include "SpiStack.h"

char* spiGetStackString(SPI_STACK* stack)
{
  if(stack->data_type != SPI_DATA_TYPE_STR)
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
  switch(stack->data_type)
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
