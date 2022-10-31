#pragma once
#include "common/types.h"

// 001070E0
// Adds lhs and rhs, and stores the result in dest.
extern inline void sceVu0AddVector(vec4& dest, vec4& lhs, vec4& rhs);

// 001070F8
// Subtracts rhs from lhs, and stores the result in dest.
extern inline void sceVu0SubVector(vec4& dest, vec4& lhs, vec4& rhs);

// 00107110
// Multiplies lhs and rhs, and stores the result in dest.
extern inline void sceVu0MulVector(vec4& dest, vec4& lhs, vec4& rhs);

// 00107128
// Multiplies every component of vector by scale; result stored in dest.
extern inline void sceVu0ScaleVector(vec4& dest, vec4& vector, float scale);

// 00107170
// Copies the value of source vec4 into dest vec4
extern inline void sceVu0CopyVector(vec4& dest, vec4& source);

// 00107180
// Copies the value of source matrix4 into dest matrix4
extern inline void sceVu0CopyMatrix(matrix4& dest, matrix4& source);

// 001071A8
// Probably shouldn't use this, likely not needed and clunky
extern inline void sceVu0FTOI4Vector(vec4& dest, vec4& source);

// 001071C8
// Probably shouldn't use this, likely not needed and clunky
extern inline void sceVu0ITOF4Vector(vec4& dest, vec4& source);

// 00107A58
// Multiplies the X, Y, Z components of vector by scale; result stored in dest.
extern inline void sceVu0ScaleVectorXYZ(vec4& dest, vec4& vector, float scale);