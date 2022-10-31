#pragma once
#include "common/types.h"

// 0012F230
// Clears a vector to 0.0f.
extern inline void mgZeroVector(vec4& v);

// 0012F240
// Same as mgZeroVector?
extern inline void mgZeroVectorW(vec4& v);

// 0012F3D0
// Adds the components of other to dest
extern inline void mgAddVector(vec4& dest, vec4& other);

// 0012F3F0
// Subtracts the components of other from dest
extern inline void mgSubVector(vec4& dest, vec4& other);

// 0012FFD0
// Calculates the distance between 3D XYZ points in v1 and (0, 0, 0).
extern inline float mgDistVector(vec4& v1);

// 00130060
// Calculates the distance between 3D XYZ points in both vectors.
extern inline float mgDistVector(vec4& v1, vec4& v2);