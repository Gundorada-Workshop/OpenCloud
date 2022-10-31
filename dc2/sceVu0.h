#pragma once
#include "common/types.h"

// 001070F8
// Subtracts v2 from v1, and stores the result in dest.
extern inline void sceVu0SubVector(vec4& dest, vec4& v1, vec4& v2);

// 00107128
// Multiplies every component of vector by scale; result stored in dest.
extern inline void sceVu0ScaleVector(vec4& dest, vec4& vector, float scale);

// 00107A58
// Multiplies the X, Y, Z components of vector by scale; result stored in dest.
extern inline void sceVu0ScaleVectorXYZ(vec4& dest, vec4& vector, float scale);