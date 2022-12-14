#pragma once
#include <array>
#include <numbers>

#include "common/constants.h"
#include "common/math.h"
#include "common/types.h"

using namespace common;

// ~ 0012F1C0 - 00131110

#define VALID_INDEX(n, min, max) (n >= min && n < max)

//struct mgVu0FBOX
//{
//  // Represents the "top left" and "bottom right" corners of a 3D rectangle
//  std::array<vec4, 2> corners;
//
//  mgVu0FBOX() = default;
//
//  mgVu0FBOX(vec4 c1, vec4 c2)
//  {
//    corners[0] = c1;
//    corners[1] = c2;
//  }
//
//  mgVu0FBOX(f32 ax, f32 ay, f32 az, f32 aw, f32 bx, f32 by, f32 bz, f32 bw)
//  {
//    corners[0] = { ax, ay, az, aw };
//    corners[1] = { bx, by, bz, bw };
//  }
//};

//struct mgVu0FBOX8
//{
//  // Represents all points in a 3D rectangle
//  std::array<vec4, 8> vertices;
//};

// 0012F1C0
//ivec4 mgFtoI4(const vec4& v);

// 0012F1D0
//mgVu0FBOX8 mgCreateBox8(const vec4& max_corner, const vec4& min_corner);
//mgVu0FBOX8 mgCreateBox8(const vec4& max_corner, const vec3& min_corner);
//mgVu0FBOX8 mgCreateBox8(const vec3& max_corner, const vec4& min_corner);
//mgVu0FBOX8 mgCreateBox8(const vec3& max_corner, const vec3& min_corner);

// Clamps an angle to (-pi, +pi] radians.
// (Only valid for f32s within (-2pi, +2pi].
// Use mgAngleLimit if your f32 is not within that range.)
inline f32 mgAngleClamp(f32 x)
{
  if (x > math::deg_to_rad(180.0f))
  {
    return x - math::deg_to_rad(360.0f);
  }
  if (x <= math::deg_to_rad(-180.0f))
  {
    return x + math::deg_to_rad(360.0f);
  }
  return x;
}

// 0012F230
// Not useful to us.
// Zeros a vector.
//inline void mgZeroVector(vec4& v);

// 0012F240
// Not useful to us.
// Zeroes a vector save for w component which is set to 1
//inline void mgZeroVectorW(vec4& v);

// 0012F250
// Tests if a point is contained within a box (testing X, Y, Z)
// NOTE: the corners need to be (max, min)
//bool mgClipBoxVertex(const vec4& p, const vec4& max_corner, const vec4& min_corner);
//bool mgClipBoxVertex(const vec4& point, const mgVu0FBOX& box);

// 0012F290
// Tests if two 3D boxes overlap (checking X, Y, Z)
// NOTE: the corners need to be (max, min)
//bool mgClipBox(const vec4& max_corner1, const vec4& min_corner1, const vec4& max_corner2, const vec4& min_corner2);
//bool mgClipBox(const mgVu0FBOX& box1, const mgVu0FBOX& box2);

// 0012F2E0
// Tests if two 3D boxes overlap (checking X, Y, W (?))
// NOTE: the corners need to be (max, min)
//bool mgClipBoxW(const vec4& max_corner1, const vec4& min_corner1, const vec4& max_corner2, const vec4& min_corner2);
//bool mgClipBoxW(const mgVu0FBOX& box1, const mgVu0FBOX& box2);

// 0012F330
// Tests if the first 3D box completely contains the second 3D box (checking X, Y, Z)
// NOTE: the corners need to be (max, min)
//bool mgClipInBox(const vec4& max_corner1, const vec4& min_corner1, const vec4& max_corner2, const vec4& min_corner2);
//bool mgClipInBox(const mgVu0FBOX& box1, const mgVu0FBOX& box2);

// 0012F380
// Tests if the first 3D box completely contains the second 3D box (checking X, Y, W (?))
// NOTE: the corners need to be (max, min)
//bool mgClipInBoxW(const vec4& max_corner1, const vec4& min_corner1, const vec4& max_corner2, const vec4& min_corner2);
//bool mgClipInBoxW(const mgVu0FBOX& box1, const mgVu0FBOX& box2);

// 0012F3D0
// Not useful to us.
// Adds two vectors and stores result in lhs
//inline void mgAddVector(vec4& lhs, const vec4& rhs);

// 0012F3F0
// Not useful to us.
// Subtracts two vectors and stores result in lhs
//inline void mgSubVector(vec4& lhs, const vec4& rhs);

// 0012F410
// Not useful to us.
// Normalizes a vector
//vec3 mgNormalizeVector(const vec3& v, f32 scale);

// 0012F460
// Not useful to us.
// Finds the minimum of two vectors and stores the result in lhs
//inline vec4 mgVectorMin(const vec4& lhs, const vec4& rhs);

// 0012F480
// Not useful to us.
// Gets the minimum of 4 vectors.
//inline vec4 mgVectorMin(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4);

// 0012F4B0
// Not useful to us.
// Gets the minmax of two vectors
//inline void mgVectorMaxMin(vec4& max_dest, vec4& min_dest, const vec4& lhs, const vec4& rhs);

// 0012F4D0
// Not useful to us.
// Gets the minmax of 3 vectors
//inline void mgVectorMaxMin(vec4& max_dest, vec4& min_dest, const vec4& v1, const vec4& v2, const vec4& v3);

// 0012F500
// Not useful to us.
// Gets the minmax of 4 vectors
//inline void mgVectorMaxMin(vec4& max_dest, vec4& min_dest, const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4);

// 0012F540
//void mgBoxMaxMin(mgVu0FBOX& lhs, const mgVu0FBOX& rhs);

// 0012F580
//vec3 mgPlaneNormal(const vec3& v1, const vec3& v2, const vec3& v3);

// 0012F5B0
//f32 mgDistPlanePoint(const vec3& v1, const vec3& v2, const vec3& v3);

// 0012F5F0
//f32 mgDistLinePoint(const vec3& v1, const vec3& v2, const vec3& v3, vec3& v4_dest);

// 0012F760
//f32 mgReflectionPlane(const vec3& v1, const vec3& v2, const vec3& v3, vec3& v4_dest);

// 0012F990
//usize mgIntersectionSphereLine(const vec4& sphere, const vec3& line_start, const vec3& line_end, vec3* intersections);

// 0012FA50
//bool mgIntersectionPoint_line_poly3(const vec3& v1, const vec3& v2, const vec3& v3, const vec3& v4, const vec3& v5, const vec3& v6, vec3& v7_dest);

// 0012FB70
//bool mgCheckPointPoly3_XYZ(const vec3& v1, const vec3& v2, const vec3& v3, const vec3& v4, const vec3& v5);

// 0012FD10
//uint mgCheckPointPoly3_XZ(const vec3& v1, const vec3& v2, const vec3& v3, const vec3& v4);

// 0012FD40
//uint Check_Point_Poly3(f32 aa, f32 ab, f32 ba, f32 bb, f32 ca, f32 cb, f32 da, f32 db);

// 00130060
// Not useful to us.
// Calculates the distance between two vectors
//f32 mgDistVector(const vec3& v, const vec3& other = common::constants::vec3_zero);

// 001300A0
// Not useful to us.
// Calculates the distance between two vector xy components
//f32 mgDistVectorXZ(const vec3& v, const vec3& other = common::constants::vec3_zero);

// 001300E0
// Not useful to us.
// Calculates distance squared of two vectors
//f32 mgDistVector2(const vec3& v, const vec3& other = common::constants::vec3_zero);

// 00130110
// Not useful to us.
// Calculates the distance squared of two vector xyz components
//f32 mgDistVectorXZ2(const vec3& v, const vec3& other = common::constants::vec3_zero);

// 00130140
// Not useful to us.
// Gets a unix matrix
//matrix4 mgUnitMatrix();

// 00130160
// Not useful to us.
// Gets a zero matrix
//matrix4 mgZeroMatrix();

// 00130180
// Not useful to us.
// Multiplies 3 mats
//matrix4 MulMatrix3(const matrix4& m1, const matrix4& m2, const matrix4& m3);

// 00130250
// Not useful to us.
// Multiplies 2 mats
//matrix4 mgMulMatrix(const matrix4& lhs, const matrix4& rhs);

// 001302D0
//matrix4 mgInverseMatrix(const matrix4& mat);

// 001303D0
//matrix4 mgRotMatrixX(f32 rotation);

// 00130430
//matrix4 mgRotMatrixY(f32 rotation);

// 00130490
//matrix4 mgRotMatrixZ(f32 rotation);

// 001304F0
//matrix4 mgRotMatrixXYZ(const vec3& rotation);

// 00130550
//matrix4 mgCreateMatrixPY(const vec4& v, f32 f);

// 001305B0
//matrix4 mgLookAtMatrixZ(const vec3& v);

// 00130690
//matrix4 mgShadowMatrix(const vec3& v1, const vec3& v2, const vec3& v3);

// 001308A0
//void mgApplyMatrixN(vec4* vecs_dest, const matrix4& mat, const vec4* vecs, usize n);

// 001308F0
//void mgApplyMatrixN_MaxMin(vec4* vecs_dest, const matrix4& mat, const vec4* vecs, usize n, vec4& max_dest, vec4& min_dest);

// 00130980
//void mgVectorMinMaxN(vec4& max_dest, vec4& min_dest, const vec4* vecs, usize n);

// 001309E0
//void mgApplyMatrix(vec4& max_dest, vec4& min_dest, const matrix4& mat, const vec4& max_corner, const vec4& min_corner);

// 00130A50
//vec3 mgVectorInterpolate(const vec3& lhs, const vec3& rhs, f32 t, bool b);

// 00130B60
f32 mgAngleInterpolate(f32 f1, f32 f2, f32 f3, bool b);

// 00130D10
s32 mgAngleCmp(f32 f1, f32 f2, f32 f3);

// 00130DD0
f32 mgAngleLimit(f32 f);

// 00130EE0
f32 mgRnd();

// 00130F20
// for when you want a rand that returns [-6, 6] but really biases towards 0
// for whatever reason
f32 mgNRnd();

// 00130FB0
void mgCreateSinTable();

// 00131050
// Quick (but inaccurate) sinf call
f32 mgSinf(f32 f);

// 001310F0
// Quick (but inaccurate) cosf call
f32 mgCosf(f32 f);