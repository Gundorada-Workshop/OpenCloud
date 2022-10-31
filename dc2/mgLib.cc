#include <math.h>
#include "mgLib.h"
#include "common/types.h"

inline void mgZeroVector(vec4& v)
{
    for (float& f : v)
    {
        f = 0.0f;
    }
}

inline void mgZeroVectorW(vec4& v)
{
    for (float& f : v)
    {
        f = 0.0f;
    }
}

inline void mgAddVector(vec4& dest, vec4& other)
{
    for (int i = 0; i < dest.size(); ++i)
    {
        dest[i] += other[i];
    }
}

inline void mgSubVector(vec4& dest, vec4& other)
{
    for (int i = 0; i < dest.size(); ++i)
    {
        dest[i] -= other[i];
    }
}

inline float mgDistVector(vec4& v1)
{
    return sqrtf(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]);
}

inline float mgDistVector(vec4& v1, vec4& v2)
{
    float xd = (v1[0] - v2[0]);
    float yd = (v1[1] - v2[1]);
    float zd = (v1[2] - v2[2]);
    return sqrtf(xd * xd + yd * yd + zd * zd);
}