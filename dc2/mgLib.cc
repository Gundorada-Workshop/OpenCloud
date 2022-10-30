#include "mgLib.h"
#include "common/types.h"

void mgZeroVector(vec4& v)
{
    for (float& f : v)
    {
        f = 0.0f;
    }
}