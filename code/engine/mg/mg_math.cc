#include <array>

#include "common/math.h"
#include "common/log.h"

#include "engine/mg/mg_math.h"

set_log_channel("mg_math");

using namespace common;

// 0037FD40
static std::array<f32, 1024> SinTable{ };
// 00376504
constexpr static f32 sin_table_unit_1 = static_cast<f32>(SinTable.size()) / math::pi2();

// 0012F1C0
//ivec4 mgFtoI4(const vec4& v)
//{
//  ivec4 result;
//  for (usize i = 0; i < 4; ++i)
//  {
//    result[i] = static_cast<s32>(v[i] * 16.0f);
//  }
//  return result;
//}

// 0012F1D0
//mgVu0FBOX8 mgCreateBox8(const vec4& max_corner, const vec4& min_corner)
//{
//  log_trace("{}({}, {})", __func__, max_corner, min_corner);
//
//  auto& c1 = max_corner;
//  auto& c2 = min_corner;
//
//  return mgVu0FBOX8 {
//    vec4{ c2.x, c2.y, c2.z, 1.0f },
//    vec4{ c1.x, c2.y, c2.z, 1.0f },
//    vec4{ c2.x, c1.y, c2.z, 1.0f },
//    vec4{ c1.x, c1.y, c2.z, 1.0f },
//    vec4{ c2.x, c2.y, c1.z, 1.0f },
//    vec4{ c1.x, c2.y, c1.z, 1.0f },
//    vec4{ c2.x, c1.y, c1.z, 1.0f },
//    vec4{ c1.x, c1.y, c1.z, 1.0f },
//  };
//}
//
//mgVu0FBOX8 mgCreateBox8(const vec4& max_corner, const vec3& min_corner)
//{
//  return mgCreateBox8(max_corner.xyz, min_corner.xyz);
//}
//
//mgVu0FBOX8 mgCreateBox8(const vec3& max_corner, const vec4& min_corner)
//{
//  return mgCreateBox8(max_corner, min_corner.xyz);
//}
//
//mgVu0FBOX8 mgCreateBox8(const vec3& max_corner, const vec3& min_corner)
//{
//  return mgCreateBox8(vec4{ max_corner, 1.0f }, vec4{ min_corner.xyz, 1.0f });
//}

// 0012F250
//bool mgClipBoxVertex(const vec4& p, const vec4& max_corner, const vec4& min_corner)
//{
//  log_trace("{}({}, {}, {})", __func__, p, max_corner, min_corner);
//
//  return
//    p.x <= max_corner.x &&
//    p.y <= max_corner.y &&
//    p.z <= max_corner.z &&
//    p.x >= min_corner.x &&
//    p.y >= min_corner.y &&
//    p.z >= min_corner.z;
//}

//bool mgClipBoxVertex(const vec4& point, const mgVu0FBOX& box)
//{
//  return mgClipBoxVertex(point, box.corners[0], box.corners[1]);
//}

// 0012F290
//bool mgClipBox(const vec4& max_corner1, const vec4& min_corner1, const vec4& max_corner2, const vec4& min_corner2)
//{
//  log_trace("{}({}, {}, {}, {})", __func__, max_corner1, min_corner1, max_corner2, min_corner2);
//
//  return
//    min_corner1.x <= max_corner2.x &&
//    min_corner1.y <= max_corner2.y &&
//    min_corner1.z <= max_corner2.z &&
//    max_corner1.x >= min_corner2.x &&
//    max_corner1.y >= min_corner2.y &&
//    max_corner1.z >= min_corner2.z;
//}

//bool mgClipBox(const mgVu0FBOX& box1, const mgVu0FBOX& box2)
//{
//  return mgClipBox(box1.corners[0], box1.corners[1], box2.corners[0], box2.corners[1]);
//}

// 0012F2E0
//bool mgClipBoxW(const vec4& max_corner1, const vec4& min_corner1, const vec4& max_corner2, const vec4& min_corner2)
//{
//  log_trace("{}({}, {}, {}, {})", __func__, max_corner1, min_corner1, max_corner2, min_corner2);
//
//  return
//    min_corner1.x <= max_corner2.x &&
//    min_corner1.y <= max_corner2.y &&
//    min_corner1.w <= max_corner2.w &&
//    max_corner1.x >= min_corner2.x &&
//    max_corner1.y >= min_corner2.y &&
//    max_corner1.w >= min_corner2.w;
//}

//bool mgClipBoxW(const mgVu0FBOX& box1, const mgVu0FBOX& box2)
//{
//  return mgClipBoxW(box1.corners[0], box1.corners[1], box2.corners[0], box2.corners[1]);
//}

// 0012F330
//bool mgClipInBox(const vec4& max_corner1, const vec4& min_corner1, const vec4& max_corner2, const vec4& min_corner2)
//{
//  log_trace("{}({}, {}, {}, {})", __func__, max_corner1, min_corner1, max_corner2, min_corner2);
//
//    return 
//      min_corner1.x >= min_corner2.x &&
//      min_corner1.y >= min_corner2.y &&
//      min_corner1.z >= min_corner2.z &&
//      max_corner1.x <= max_corner2.x &&
//      max_corner1.y <= max_corner2.y &&
//      max_corner1.z <= max_corner2.z;
//}

//bool mgClipInBox(const mgVu0FBOX& box1, const mgVu0FBOX& box2)
//{
//  return mgClipInBox(box1.corners[0], box1.corners[1], box2.corners[0], box2.corners[1]);
//}

// 0012F380
//bool mgClipInBoxW(const vec4& max_corner1, const vec4& min_corner1, const vec4& max_corner2, const vec4& min_corner2)
//{
//  log_trace("{}({}, {}, {}, {})", __func__, max_corner1, min_corner1, max_corner2, min_corner2);
//
//  return
//    min_corner1.x >= min_corner2.x &&
//    min_corner1.y >= min_corner2.y &&
//    min_corner1.w >= min_corner2.w &&
//    max_corner1.x <= max_corner2.x &&
//    max_corner1.y <= max_corner2.y &&
//    max_corner1.w <= max_corner2.w;
//}

//bool mgClipInBoxW(const mgVu0FBOX& box1, const mgVu0FBOX& box2)
//{
//  return mgClipInBoxW(box1.corners[0], box1.corners[1], box2.corners[0], box2.corners[1]);
//}

// 0012F540
//void mgBoxMaxMin(mgVu0FBOX& lhs, const mgVu0FBOX& rhs)
//{
//  log_trace("{}({}, {})", __func__, fmt::ptr(&lhs), fmt::ptr(&rhs));
//
//  lhs.corners[0] = glm::max(lhs.corners[0], glm::max(lhs.corners[1], glm::max(rhs.corners[0], rhs.corners[1])));
//  lhs.corners[1] = glm::min(lhs.corners[0], glm::min(lhs.corners[1], glm::min(rhs.corners[0], rhs.corners[1])));
//}

// 0012F580
//vec3 mgPlaneNormal(const vec3& v1, const vec3& v2, const vec3& v3)
//{
//  log_trace("{}({}, {}, {})", __func__, v1, v2, v3);
//
//  auto temp1 = v2 - v1;
//  auto temp2 = v3 - v1;
//  
//  return math::vector_outer_product(temp1, temp2);
//}

// 0012F5B0
//f32 mgDistPlanePoint(const vec3& v1, const vec3& v2, const vec3& v3)
//{
//  log_trace("{}({}, {})", __func__, v1, v2);
//
//  return math::vector_dot_product(v1, v3 - v2);
//}

// 0012F5F0
//f32 mgDistLinePoint(const vec3& v1, const vec3& v2, const vec3& v3, vec3& v4_dest)
//{
//  log_trace("{}({}, {}, {}, {})", __func__, v1, v2, v3, fmt::ptr(&v4_dest));
//
//  auto var_40 = v2 - v1;
//  auto var_30 = v3 - v1;
//  auto var_10 = var_30 - var_40;
//  f32 f20 = mgDistVector(var_10);
//  f20 *= f20;
//  f32 f0 = math::negate(math::vector_dot_product(var_40, var_10));
//  f32 f12 = f0 / f20;
//
//  if (f12 >= 0.0f && f12 <= 1.0f)
//  {
//    auto var_20 = var_10 * f12;
//    var_20 += var_40;
//    v4_dest = var_20 + v1;
//    return mgDistVector(var_20);
//  }
//
//  f20 = mgDistVector(v1, v2);
//  f32 f21 = mgDistVector(v1, v3);
//
//  if (f20 < f21)
//  {
//    v4_dest = v2;
//    return f20;
//  }
//  else
//  {
//    v4_dest = v3;
//    return f21;
//  }
//}

// 0012F760
//f32 mgReflectionPlane(const vec3& v1, const vec3& v2, const vec3& v3, vec3& v4_dest)
//{
//  log_trace("{}({}, {}, {}, {})", __func__, v1, v2, v3, fmt::ptr(&v4_dest));
//
//  f32 result = mgDistPlanePoint(v1, v2, v3) * 2.0f;
//  v4_dest = v2 - v3 - (v1 * -result);
//  return result;
//}

// 0012F7F0
//usize mgIntersectionSphereLine0(const vec3& line_start, const vec3& line_end, vec3* intersections, f32 radius)
//{
//  log_trace("{}({}, {}, {}, {})", __func__, line_start, line_end, fmt::ptr(intersections), radius);
//
//  // We take in a normalized line, such that sphere's origin is at 0,0,0, relative to the lines.
//  // The line is normalized in mgIntersectionSphereLine.
//
//  // 0012F7F0 - 0012F828
//  auto distance = line_end - line_start;
//  // 0012F828 - 0012F834
//  f32 f20 = mgDistVector2(distance);
//  // 0012F834 - 0012F844
//  f32 f21 = math::vector_dot_product(distance, line_start);
//  // 0012F844 - 0012F854
//  f32 f0 = mgDistVector2(line_start) - (radius * radius);
//
//  // 0012F854 - 0012F85C
//  // NOTE: another way of thinking about these 2 instructions:
//  // ACC = f21 * f21
//  // f22 = ACC - (f20 * f0)
//  f32 f22 = (f21 * f21) - (f20 * f0);
//
//  // 0012F864 - 0012F87C
//  if (f22 < 0.0f)
//  {
//    return 0;
//  }
//
//  // 0012F888 - 0012F88C
//  usize n_intersections = 0;
//
//  // 0012F87C - 0012F884 (f22 is moved into f12 before previous branch)
//  f0 = sqrtf(f22);
//  // 0012F884 - 0012F888
//  float f2 = -f21;
//  // 0012F88C - 0012F894
//  float f12 = (f2 - f0) / f20;
//  // 0012F894 - 0012F8A0
//  f20 = (f0 + f2) / f20;
//
//  // 0012F8A0 - 0012F8D0
//  vec3 intersection_dist;
//  if (f12 >= 0.0f && f12 <= 1.0f)
//  {
//    // 0012F8D0 - 0012F8D8
//    intersection_dist = distance * f12;
//    // 0012F8D8 - 0012F8E8
//    intersections[0] = line_start + intersection_dist;
//    // 0012F8E8 - 0012F8EC
//    ++n_intersections;
//  }
//
//  // 0012F8EC - 0012F904
//  if (f22 == 0.0f)
//  {
//    return 1;
//  }
//
//  // 0012F90C - 0012F938
//  if (f20 < 0.0f || f20 > 1.0f)
//  {
//    return n_intersections;
//  }
//
//  // 0012F938 - 0012F944
//  intersection_dist = distance * f20;
//  // 0012F948 - 0012F958
//  intersections[n_intersections] = line_start + intersection_dist;
//  // 0012F958 - 0012F95C
//  ++n_intersections;
//
//  // 0012F95C -
//  return n_intersections;
//}

// 0012F990
//usize mgIntersectionSphereLine(const vec4& sphere, const vec3& line_start, const vec3& line_end, vec3* intersections)
//{
//  log_trace("{}({}, {}, {})", __func__, line_start, line_end, fmt::ptr(intersections));
//
//  // NOTE: Sphere is a vec4 with xyz representing its 3D origin, and w representing its radius)
//
//  float radius = sphere.w;
//
//  auto start_normal = line_start - sphere.xyz;
//  auto end_normal = line_end - sphere.xyz;
//
//  usize n_intersections = mgIntersectionSphereLine0(start_normal, end_normal, intersections, radius);
//
//  for (int i = 0; i < n_intersections; ++i)
//  {
//    intersections[i] += vec3{ sphere.xyz };
//  }
//  return n_intersections;
//}

// 0012FA50
//bool mgIntersectionPoint_line_poly3(const vec3& v1, const vec3& v2, const vec3& v3, const vec3& v4, const vec3& v5, const vec3& v6, vec3& v7_dest)
//{
//  log_trace("{}({}, {}, {}, {}, {}, {}, {})", __func__, v1, v2, v3, v4, v5, v6, v7_dest);
//
//  auto var_40 = v2 - v1;
//  auto var_30 = v3 - v1;
//  auto var_20 = v4 - v1;
//  auto var_10 = v5 - v1;
//  f32 f1 = math::vector_dot_product(v6, var_30);
//  f32 f0 = math::vector_dot_product(v6, var_40);
//
//  if (f0 == 0.0f)
//  {
//    return false;
//  }
//
//  v7_dest = var_40 * (f1 / f0) + v1;
//  return mgCheckPointPoly3_XYZ(v7_dest, v3, v4, v5, v6);
//}

// 0012FB70
//bool mgCheckPointPoly3_XYZ(const vec3& v1, const vec3& v2, const vec3& v3, const vec3& v4, const vec3& v5)
//{
//  log_trace("{}({}, {}, {}, {}, {})", __func__, v1, v2, v3, v4, v5);
//
//  auto var_90 = v1 - v2;
//  auto var_80 = v1 - v3;
//  auto var_70 = v1 - v4;
//  auto var_60 = v3 - v2;
//  auto var_50 = v4 - v3;
//  auto var_40 = v2 - v4;
//  auto var_30 = math::vector_outer_product(var_60, var_90);
//  auto var_20 = math::vector_outer_product(var_50, var_80);
//  auto var_10 = math::vector_outer_product(var_40, var_70);
//
//  f32 f20 = math::vector_dot_product(var_30, v5);
//  f32 f21 = math::vector_dot_product(var_20, v5);
//  f32 f0 = math::vector_dot_product(var_10, v5);
//
//  return 
//    (f20 >= 0.0f && f21 >= 0.0f && f0 >= 0.0f) ||
//    (f20 <= 0.0f && f21 <= 0.0f && f0 <= 0.0f);
//}

// 0012FD10
//uint mgCheckPointPoly3_XZ(const vec3& v1, const vec3& v2, const vec3& v3, const vec3& v4)
//{
//  log_trace("{}({}, {}, {}, {})", __func__, v1, v2, v3, v4);
//
//  return Check_Point_Poly3(v1.x, v1.z, v2.x, v2.z, v3.x, v3.z, v4.x, v4.z);
//}

// 0012FD40
uint Check_Point_Poly3(f32 aa, f32 ab, f32 ba, f32 bb, f32 ca, f32 cb, f32 da, f32 db)
{
  log_trace("{}({}, {}, {}, {}, {}, {}, {}, {})", __func__, aa, ab, ba, ab, ca, cb, da, db);

  if (aa < std::min({ ba, ca, da }))
  {
    return 0;
  }

  if (aa > std::max({ ba, ca, da }))
  {
    return 0;
  }

  if (ab < std::min({ bb, cb, db }))
  {
    return 0;
  }

  if (ab > std::max({ bb, cb, db }))
  {
    return 0;
  }

  f32 f6 = (ca - ba) * (ab - bb) - (cb - bb) * (aa - ba);
  f32 f4 = (da - ca) * (ab - cb) - (db - cb) * (aa - ca);
  f32 f1 = (ba - da) * (ab - db) - (bb - db) * (aa - da);

  if (f6 == 0.0f)
  {
    return 2;
  }

  if (f4 == 0.0f)
  {
    return 3;
  }

  if (f1 == 0.0f)
  {
    return 4;
  }

  if (
    (f6 > 0.0f && f4 > 0.0f && f1 > 0.0f) ||
    (f6 < 0.0f && f4 < 0.0f && f1 < 0.0f)
    )
  {
    return 1;
  }
  return 0;
}

// 001302D0
//matrix4 mgInverseMatrix(const matrix4& mat)
//{
//  log_trace("{}({})", __func__, fmt::ptr(&mat));
//
//  // Hopefully this is right - Souzooka
//
//  // First, we want a matrix of the 3x3 submatrix of mat from (0, 0) until (3, 3)
//  matrix3 inverse = glm::inverse(
//    matrix3 {
//      mat[0].xyz,
//      mat[1].xyz,
//      mat[2].xyz 
//    }
//  );
//  
//  // Now, we have to convert our inverse into a 4x4 matrix. For the first three rows,
//  // 0 will be used for the w component. But what's going to be in the fourth row?
//  // According to game code, the final result should end up being something like this.
//  // NOTE: The w component of the fourth row is always 1.0f
//  return {
//    vec4{ inverse[0], 0.0f },
//    vec4{ inverse[1], 0.0f },
//    vec4{ inverse[2], 0.0f },
//    vec4{ -(inverse * mat[3]), 1.0f}
//  };
//}

// 001303D0
//matrix4 mgRotMatrixX(f32 rotation)
//{
//  log_trace("{}({})", __func__, rotation);
//
//  matrix4 mat = mgUnitMatrix();
//
//  f32 f = cosf(rotation);
//  mat[2].z = f;
//  mat[1].y = f;
//
//  f = sinf(rotation);
//  mat[1].z = f;
//  mat[2].y = -f;
//  return mat;
//}

// 00130430
//matrix4 mgRotMatrixY(f32 rotation)
//{
//  log_trace("{}({})", __func__, rotation);
//
//  matrix4 mat = mgUnitMatrix();
//
//  f32 f = cosf(rotation);
//  mat[2].z = f;
//  mat[0].x = f;
//
//  f = sinf(rotation);
//  mat[0].z = -f;
//  mat[2].x = f;
//  return mat;
//}

// 00130490
//matrix4 mgRotMatrixZ(f32 rotation)
//{
//  log_trace("{}({})", __func__, rotation);
//
//  matrix4 mat = mgUnitMatrix();
//
//  f32 f = cosf(rotation);
//  mat[1].y = f;
//  mat[0].x = f;
//
//  f = sinf(rotation);
//  mat[0].y = f;
//  mat[1].x = -f;
//  return mat;
//}

// 001304F0
//matrix4 mgRotMatrixXYZ(const vec3& rotation)
//{
//  log_trace("{}({})", __func__, rotation);
//
//  matrix4 rotX = mgRotMatrixX(rotation.x);
//  matrix4 rotY = mgRotMatrixY(rotation.y);
//  matrix4 rotZ = mgRotMatrixZ(rotation.z);
//
//  return MulMatrix3(rotZ, rotY, rotX);
//}

// 00130550
//matrix4 mgCreateMatrixPY(const vec4& v, f32 f)
//{
//  log_trace("{}({}, {})", __func__, v, f);
//
//  matrix4 result = mgUnitMatrix();
//  result = glm::rotate(result, f, { 0, 1, 0 });
//
//  result[3] = v;
//  result[3].w = 1.0f;
//  return result;
//}

// 001305B0
//matrix4 mgLookAtMatrixZ(const vec3& v)
//{
//  log_trace("{}({})", __func__, v);
//
//  auto var_60 = mgUnitMatrix();
//  auto var_A0 = var_60;
//  auto var_20 = common::math::vector_normalize(v);
//  auto var_10 = var_20;
//  var_10.y = 0.0f;
//  f32 f0 = mgDistVector(var_10);
//  f32 f1 = 1.0f;
//  f32 f2 = 0.0f;
//
//  if (f0 == 0.0f)
//  {
//    var_A0[1].y = 1.0f;
//  }
//  else
//  {
//    f2 = var_20.x / f0;
//    f1 = var_20.z / f0;
//    var_A0[1].y = f0;
//  }
//
//  var_A0[2].z = f0;
//  var_60[0].z = -f2;
//  var_60[2].x = f2;
//  var_60[0].x = f1;
//  var_60[2].z = f1;
//  var_A0[2].y = var_20.y;
//  var_A0[1].z = -var_20.y;
//  return mgMulMatrix(var_60, var_A0);
//}

// 00130690
//matrix4 mgShadowMatrix(const vec3& v1, const vec3& v2, const vec3& v3)
//{
//  log_trace("{}({}, {}, {})", __func__, v1, v2, v3);
//
//  vec3 var_10{ v3 };
//  vec3 var_20{ v2 };
//  vec3 var_30{ v1 };
//  matrix4 result;
//
//  f32 f0 = math::vector_dot_product(var_10, var_20);
//  if (f0 == 0.0f)
//  {
//    var_20.x *= 0.9f;
//    var_20.y *= 0.9f;
//    var_20.z *= 0.9f;
//    f0 = math::vector_dot_product(var_10, var_20);
//  }
//
//  f0 = 1.0f / f0;
//  f32 f20 = var_10.x * f0;
//  f32 f21 = var_10.y * f0;
//  f32 f22 = var_10.z * f0;
//  var_30 = math::vector_normalize(var_30);
//
//  f32 f1 = (f20 * var_30.x) + (f21 * var_30.y) + (f22 * var_30.z);
//  f32 f8 = -1.0f / f1;
//
//  result[0].x = f8 * ((f20 * var_30.x) - f1);
//  result[0].y = f8 * f20 * var_30.y;
//  result[0].z = f8 * f20 * var_30.z;
//  result[0].w = 0.0f;
//
//  result[1].x = f8 * f21 * var_30.x;
//  result[1].y = f8 * ((f21 * var_30.y) - f1);
//  result[1].z = f8 * f21 * var_30.z;
//  result[1].w = 0.0f;
//
//  result[2].x = f8 * f22 * var_30.x;
//  result[2].y = f8 * f22 * var_30.y;
//  result[2].z = f8 * ((f22 * var_30.z) - f1);
//  result[2].w = 0.0f;
//  
//  result[3].x = f8 * -var_30.x;
//  result[3].y = f8 * -var_30.y;
//  result[3].z = f8 * -var_30.z;
//  result[3].w = f8 * -f1;
//  
//  return result;
//}

// 001308A0
//void mgApplyMatrixN(vec4* vecs_dest, const matrix4& mat, const vec4* vecs, usize n)
//{
//  log_trace("{}({}, {}, {}, {})", __func__, fmt::ptr(vecs_dest), fmt::ptr(&mat), fmt::ptr(vecs), n);
//
//  for (usize i = 0; i < n; ++i)
//  {
//    vecs_dest[i] = mat * vecs[i];
//  }
//}

// 001308F0
//void mgApplyMatrixN_MaxMin(vec4* vecs_dest, const matrix4& mat, const vec4* vecs, usize n, vec4& max_dest, vec4& min_dest)
//{
//  log_trace("{}({}, {}, {}, {}, {})", __func__, fmt::ptr(vecs_dest), fmt::ptr(&mat), fmt::ptr(vecs), n, fmt::ptr(&max_dest), fmt::ptr(&min_dest));
//
//  assert_msg(n != 0, "{}(n = 0) is invalid", __func__);
//
//  vec4 max = vec4{ common::constants::f32_min };
//  vec4 min = vec4{ common::constants::f32_max };
//
//  for (usize i = 0; i < n; ++i)
//  {
//    vecs_dest[i] = mat * vec4{ vecs[i].xyz, 1.0f };
//    max = glm::max(max, vecs_dest[i]);
//    min = glm::min(min, vecs_dest[i]);
//  }
//
//  max_dest = max;
//  min_dest = min;
//}

// 00130980
//void mgVectorMinMaxN(vec4& max_dest, vec4& min_dest, const vec4* vecs, usize n)
//{
//  log_trace("{}({}, {}, {}, {})", __func__, fmt::ptr(&max_dest), fmt::ptr(&min_dest), fmt::ptr(vecs), n);
//
//  assert_msg(n != 0, "{}(n = 0) is invalid", __func__);
//
//  vec4 max = vec4{ common::constants::f32_min };
//  vec4 min = vec4{ common::constants::f32_max };
//
//  for (usize i = 0; i < n; ++i)
//  {
//    max = glm::max(max, vecs[i]);
//    min = glm::min(min, vecs[i]);
//  }
//
//  max_dest = max;
//  min_dest = min;
//}

// 001309E0
//void mgApplyMatrix(vec4& max_dest, vec4& min_dest, const matrix4& mat, const vec4& max_corner, const vec4& min_corner)
//{
//  log_trace("{}({}, {}, {}, {}, {})", __func__, fmt::ptr(&max_dest), fmt::ptr(&min_dest), fmt::ptr(&mat), max_corner, min_corner);
//
//  auto var_80 = mgCreateBox8(max_corner, min_corner);
//  mgApplyMatrixN_MaxMin(var_80.vertices.data(), mat, var_80.vertices.data(), var_80.vertices.size(), max_dest, min_dest);
//}

// 00130A50
//vec3 mgVectorInterpolate(const vec3& lhs, const vec3& rhs, f32 t, bool b)
//{
//  log_trace("{}({}, {}, {}, {})", __func__, lhs, rhs, t, b);
//
//  auto delta = rhs - lhs;
//  if (b)
//  {
//    // NOTE: apparently this is dead code, nothing calls this fn with true
//    return { 
//      lhs.x + (delta.x / t),
//      lhs.y + (delta.y / t),
//      lhs.z + (delta.z / t)
//    };
//  }
//
//  if (mgDistVector(delta) < t)
//  {
//    return rhs;
//  }
//
//  delta = math::vector_normalize(delta);
//  delta *= t;
//  return lhs + delta;
//}

// 00130B60
f32 mgAngleInterpolate(f32 f12, f32 f13, f32 f14, bool b)
{
  log_trace("{}({}, {}, {}, {})", __func__, f12, f13, f14, b);

  f32 f1 = mgAngleClamp(f13 - f12);

  if (!b)
  {
    if (fabsf(f1) < f14)
    {
      return f13;
    }
  }

  f32 f2 = 0.0f;

  if (b)
  {
    f2 = f1 / f14;
  }
  else
  {
    if (f1 < 0.0f)
    {
      if (f14 < f1)
      {
        return f13;
      }
      f2 -= f14;
    }

    if (f1 > 0.0f)
    {
      if (f14 > f1)
      {
        return f13;
      }
      f2 += f14;
    }
  }

  return mgAngleClamp(f12 + f2);
}

// 00130D10
s32 mgAngleCmp(f32 f12, f32 f13, f32 f14)
{
  log_trace("{}({}, {}, {})", __func__, f12, f13, f14);

  f32 n = f12 - f13;
  if (n == 0.0f)
  {
    return 0;
  }

  n = mgAngleClamp(n);

  if (n > f14)
  {
    return 1;
  }
  if (n < -f14)
  {
    return -1;
  }
  return 0;
}

// 00130DD0
f32 mgAngleLimit(f32 f)
{
  log_trace("{}({})", __func__, f);

  if (math::negate(math::pi()) <= f && f < math::pi())
  {
    return f;
  }

  f -= truncf(f / math::pi2()) * math::pi2();
  return mgAngleClamp(f);
}

// 00130EE0
f32 mgRnd()
{
  log_trace("{}()", __func__);

  return rand() / static_cast<f32>(constants::s32_max);
}

// 00130F20
// for when you want a rand that returns [-6, 6] but really biases towards 0
// for whatever reason
f32 mgNRnd()
{
  f32 f = 0;
  for (int i = 0; i < 12; ++i)
  {
    f += mgRnd();
  }
  return f - 6.0f;
}

// 00130FB0
void mgCreateSinTable()
{
  log_trace("{}()", __func__);

  f32 sin_table_num = static_cast<f32>(SinTable.size());

  for (usize i = 0; i < SinTable.size(); ++i)
  {
    SinTable[i] = sinf(static_cast<f32>(i) * math::pi2() / sin_table_num);
  }
}

// 00131050
f32 mgSinf(f32 f)
{
  log_trace("{}({})", __func__, f);

  f32 sign = static_cast<f32>(copysign(1, f));

  ssize index = static_cast<ssize>(fabsf(f) * sin_table_unit_1);
  index = abs(index) % SinTable.size();
  return SinTable[index] * sign;
}

// 001310F0
f32 mgCosf(f32 f)
{
  log_trace("{}({})", __func__, f);

  return mgSinf(f + math::deg_to_rad(90.0f));
}
