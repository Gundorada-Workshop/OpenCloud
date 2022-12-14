#include <gtest/gtest.h>

#include "graph/vector.h"

TEST(VectorFloat, ShouldConstructFromScalarConstexpr)
{
  constexpr vec4 v4{ 200.0f };
  constexpr vec3 v3{ 300.0f };
  constexpr vec2 v2{ 400.0f };

  EXPECT_FLOAT_EQ(v4.data.a[0], 200.0f);
  EXPECT_FLOAT_EQ(v4.data.a[1], 200.0f);
  EXPECT_FLOAT_EQ(v4.data.a[2], 200.0f);
  EXPECT_FLOAT_EQ(v4.data.a[3], 200.0f);

  EXPECT_FLOAT_EQ(v3.data.a[0], 300.0f);
  EXPECT_FLOAT_EQ(v3.data.a[1], 300.0f);
  EXPECT_FLOAT_EQ(v3.data.a[2], 300.0f);

  EXPECT_FLOAT_EQ(v2.data.a[0], 400.0f);
  EXPECT_FLOAT_EQ(v2.data.a[1], 400.0f);
}

TEST(VectorFloat, ShouldConstructFromScalar)
{
  vec4 v4{ 200.0f };
  vec3 v3{ 300.0f };
  vec2 v2{ 400.0f };

  EXPECT_FLOAT_EQ(v4.data.a[0], 200.0f);
  EXPECT_FLOAT_EQ(v4.data.a[1], 200.0f);
  EXPECT_FLOAT_EQ(v4.data.a[2], 200.0f);
  EXPECT_FLOAT_EQ(v4.data.a[3], 200.0f);

  EXPECT_FLOAT_EQ(v3.data.a[0], 300.0f);
  EXPECT_FLOAT_EQ(v3.data.a[1], 300.0f);
  EXPECT_FLOAT_EQ(v3.data.a[2], 300.0f);

  EXPECT_FLOAT_EQ(v2.data.a[0], 400.0f);
  EXPECT_FLOAT_EQ(v2.data.a[1], 400.0f);
}

TEST(VectorFloat, ShouldConstructFromTwoElements)
{
  vec4 v4{ 200.0f, 100.0f };
  vec3 v3{ 300.0f, 400.0f };
  vec2 v2{ 400.0f, 300.0f };

  EXPECT_FLOAT_EQ(v4.data.a[0], 200.0f);
  EXPECT_FLOAT_EQ(v4.data.a[1], 100.0f);
  EXPECT_FLOAT_EQ(v4.data.a[2], 200.0f);
  EXPECT_FLOAT_EQ(v4.data.a[3], 100.0f);

  EXPECT_FLOAT_EQ(v3.data.a[0], 300.0f);
  EXPECT_FLOAT_EQ(v3.data.a[1], 400.0f);
  EXPECT_FLOAT_EQ(v3.data.a[2], 300.0f);

  EXPECT_FLOAT_EQ(v2.data.a[0], 400.0f);
  EXPECT_FLOAT_EQ(v2.data.a[1], 300.0f);
}

TEST(VectorFloat, ShouldConstructFromThreeElements)
{
  vec4 v4{ 200.0f, 100.0f, 800.0f };
  vec3 v3{ 300.0f, 400.0f, 800.0f };

  EXPECT_FLOAT_EQ(v4.data.a[0], 200.0f);
  EXPECT_FLOAT_EQ(v4.data.a[1], 100.0f);
  EXPECT_FLOAT_EQ(v4.data.a[2], 800.0f);
  EXPECT_FLOAT_EQ(v4.data.a[3], 1.0f);

  EXPECT_FLOAT_EQ(v3.data.a[0], 300.0f);
  EXPECT_FLOAT_EQ(v3.data.a[1], 400.0f);
  EXPECT_FLOAT_EQ(v3.data.a[2], 800.0f);
}

TEST(VectorFloat, ShouldConstructFromFourElements)
{
  vec4 v4{ 200.0f, 100.0f, 800.0f, 7.0f };

  EXPECT_FLOAT_EQ(v4.data.a[0], 200.0f);
  EXPECT_FLOAT_EQ(v4.data.a[1], 100.0f);
  EXPECT_FLOAT_EQ(v4.data.a[2], 800.0f);
  EXPECT_FLOAT_EQ(v4.data.a[3], 7.0f);
}

TEST(VectorFloat, ShouldAccessIndividualElements)
{
  vec4 v4{ 200.0f, 100.0f, 800.0f, 7.0f };

  EXPECT_FLOAT_EQ(v4.x(), 200.0f);
  EXPECT_FLOAT_EQ(v4.y(), 100.0f);
  EXPECT_FLOAT_EQ(v4.z(), 800.0f);
  EXPECT_FLOAT_EQ(v4.w(), 7.0f);
}

TEST(VectorFloat, ShouldSwizzle4Elements)
{
  vec4 v4{ 200.0f, 100.0f, 800.0f, 7.0f };

  auto res = v4.xxxx();

  EXPECT_FLOAT_EQ(res.data.a[0], 200.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 200.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 200.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 200.0f);

  res = v4.yyyy();

  EXPECT_FLOAT_EQ(res.data.a[0], 100.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 100.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 100.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 100.0f);

  res = v4.zzzz();

  EXPECT_FLOAT_EQ(res.data.a[0], 800.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 800.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 800.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 800.0f);

  res = v4.wwww();

  EXPECT_FLOAT_EQ(res.data.a[0], 7.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 7.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 7.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 7.0f);

  res = v4.zywx();

  EXPECT_FLOAT_EQ(res.data.a[0], 800.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 100.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 7.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 200.0f);
}

TEST(VectorFloat, ShouldSwizzle3Elements)
{
  vec4 v4{ 200.0f, 100.0f, 800.0f, 7.0f };

  auto res = v4.xxx();

  EXPECT_FLOAT_EQ(res.data.a[0], 200.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 200.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 200.0f);

  res = v4.yyy();

  EXPECT_FLOAT_EQ(res.data.a[0], 100.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 100.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 100.0f);

  res = v4.zzz();

  EXPECT_FLOAT_EQ(res.data.a[0], 800.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 800.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 800.0f);

  res = v4.www();

  EXPECT_FLOAT_EQ(res.data.a[0], 7.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 7.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 7.0f);

  res = v4.zyw();

  EXPECT_FLOAT_EQ(res.data.a[0], 800.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 100.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 7.0f);
}

TEST(VectorFloat, ShouldSwizzle2Elements)
{
  vec4 v4{ 200.0f, 100.0f, 800.0f, 7.0f };

  auto res = v4.xx();

  EXPECT_FLOAT_EQ(res.data.a[0], 200.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 200.0f);

  res = v4.yy();

  EXPECT_FLOAT_EQ(res.data.a[0], 100.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 100.0f);

  res = v4.zz();

  EXPECT_FLOAT_EQ(res.data.a[0], 800.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 800.0f);

  res = v4.ww();

  EXPECT_FLOAT_EQ(res.data.a[0], 7.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 7.0f);

  res = v4.zy();

  EXPECT_FLOAT_EQ(res.data.a[0], 800.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 100.0f);
}

TEST(VectorFloat, ShouldAddByVector)
{
  const vec4 v1{ 0.0f, 1.0f, 2.0f, 3.0f };
  const vec4 v2{ 3.0f, 2.0f, 1.0f, 0.0f };

  auto res = v1 + v2;

  EXPECT_FLOAT_EQ(res.data.a[0], 3.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 3.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 3.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 3.0f);

  res += vec4{ 10.0f, 10.0f, 10.0f, 10.0f };

  EXPECT_FLOAT_EQ(res.data.a[0], 13.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 13.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 13.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 13.0f);
}

TEST(VectorFloat, ShouldIncrement)
{
  vec4 v1{ 0.0f, 0.0f, 0.0f, 0.0f };

  v1++;

  EXPECT_FLOAT_EQ(v1.data.a[0], 1.0f);
  EXPECT_FLOAT_EQ(v1.data.a[1], 1.0f);
  EXPECT_FLOAT_EQ(v1.data.a[2], 1.0f);
  EXPECT_FLOAT_EQ(v1.data.a[3], 1.0f);

  ++v1;

  EXPECT_FLOAT_EQ(v1.data.a[0], 2.0f);
  EXPECT_FLOAT_EQ(v1.data.a[1], 2.0f);
  EXPECT_FLOAT_EQ(v1.data.a[2], 2.0f);
  EXPECT_FLOAT_EQ(v1.data.a[3], 2.0f);
}

TEST(VectorFloat, ShouldDecrement)
{
  vec4 v1{ 2.0f, 2.0f, 2.0f, 2.0f };

  v1--;

  EXPECT_FLOAT_EQ(v1.data.a[0], 1.0f);
  EXPECT_FLOAT_EQ(v1.data.a[1], 1.0f);
  EXPECT_FLOAT_EQ(v1.data.a[2], 1.0f);
  EXPECT_FLOAT_EQ(v1.data.a[3], 1.0f);

  --v1;

  EXPECT_FLOAT_EQ(v1.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(v1.data.a[1], 0.0f);
  EXPECT_FLOAT_EQ(v1.data.a[2], 0.0f);
  EXPECT_FLOAT_EQ(v1.data.a[3], 0.0f);
}

TEST(VectorFloat, ShouldAddByScalar)
{
  const vec4 v1{ 0.0f, 1.0f, 2.0f, 3.0f };

  auto res = v1 + 5.0f;

  EXPECT_FLOAT_EQ(res.data.a[0], 5.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 6.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 7.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 8.0f);

  res += 10.0f;

  EXPECT_FLOAT_EQ(res.data.a[0], 15.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 16.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 17.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 18.0f);
}

TEST(VectorFloat, ShouldSubtractByVector)
{
  const vec4 v1{ 0.0f, 1.0f, 2.0f, 3.0f };
  const vec4 v2{ 3.0f, 2.0f, 1.0f, 0.0f };

  auto res = v1 - v2;

  EXPECT_FLOAT_EQ(res.data.a[0], -3.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], -1.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 1.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 3.0f);

  res -= vec4{ 10.0f, 10.0f, 1.0f, 3.0f };

  EXPECT_FLOAT_EQ(res.data.a[0], -13.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], -11.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 0.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 0.0f);
}

TEST(VectorFloat, ShouldSubtractByScalar)
{
  const vec4 v1{ 0.0f, 1.0f, 2.0f, 3.0f };

  auto res = v1 - 10.0f;

  EXPECT_FLOAT_EQ(res.data.a[0], -10.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], -9.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], -8.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], -7.0f);

  res -= 10.0f;

  EXPECT_FLOAT_EQ(res.data.a[0], -20.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], -19.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], -18.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], -17.0f);
}

TEST(VectorFloat, ShouldMultiplyByVector)
{
  const vec4 v1{ 0.0f, 1.0f, 2.0f, 3.0f };
  const vec4 v2{ 3.0f, 2.0f, 1.0f, 0.0f };

  auto res = v1 * v2;

  EXPECT_FLOAT_EQ(res.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 2.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 2.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 0.0f);

  res *= vec4{ 2.0f, 2.0f, 2.0f, 2.0f };

  EXPECT_FLOAT_EQ(res.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 4.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 4.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 0.0f);
}

TEST(VectorFloat, ShouldMultiplyByScalar)
{
  const vec4 v1{ 0.0f, 1.0f, 2.0f, 3.0f };

  auto res = v1 * 5.0f;

  EXPECT_FLOAT_EQ(res.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 5.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 10.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 15.0f);

  res *= 2.0f;

  EXPECT_FLOAT_EQ(res.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 10.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 20.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 30.0f);
}

TEST(VectorFloat, ShouldDivideByVector)
{
  const vec4 v1{ 3.0f, 10.0f, 2.0f, 9.0f };
  const vec4 v2{ 3.0f, 2.0f,  1.0f, 3.0f };

  auto res = v1 / v2;

  EXPECT_FLOAT_EQ(res.data.a[0], 1.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 5.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 2.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 3.0f);

  res /= vec4{ 2.0f, 2.0f, 2.0f, 3.0f };

  EXPECT_FLOAT_EQ(res.data.a[0], 0.5f);
  EXPECT_FLOAT_EQ(res.data.a[1], 2.5f);
  EXPECT_FLOAT_EQ(res.data.a[2], 1.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 1.0f);
}

TEST(VectorFloat, ShouldDivideByScalar)
{
  const vec4 v1{ 3.0f, 6.0f, 12.0f, 9.0f };

  auto res = v1 / 3.0f;

  EXPECT_FLOAT_EQ(res.data.a[0], 1.0f);
  EXPECT_FLOAT_EQ(res.data.a[1], 2.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 4.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 3.0f);

  res /= vec4{ 2.0f, 2.0f, 2.0f, 3.0f };

  EXPECT_FLOAT_EQ(res.data.a[0], 0.5f);
  EXPECT_FLOAT_EQ(res.data.a[1], 1.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], 2.0f);
  EXPECT_FLOAT_EQ(res.data.a[3], 1.0f);
}

TEST(VectorUnsignedInteger, ShouldConstructFromScalarConstexpr)
{
  constexpr uvec4 v4{ 200u };
  constexpr uvec3 v3{ 300u };
  constexpr uvec2 v2{ 400u };

  EXPECT_EQ(v4.data.a[0], 200u);
  EXPECT_EQ(v4.data.a[1], 200u);
  EXPECT_EQ(v4.data.a[2], 200u);
  EXPECT_EQ(v4.data.a[3], 200u);

  EXPECT_EQ(v3.data.a[0], 300u);
  EXPECT_EQ(v3.data.a[1], 300u);
  EXPECT_EQ(v3.data.a[2], 300u);

  EXPECT_EQ(v2.data.a[0], 400u);
  EXPECT_EQ(v2.data.a[1], 400u);
}

TEST(VectorUnsignedInteger, ShouldConstructFromScalar)
{
  uvec4 v4{ 200u };
  uvec3 v3{ 300u };
  uvec2 v2{ 400u };

  EXPECT_EQ(v4.data.a[0], 200u);
  EXPECT_EQ(v4.data.a[1], 200u);
  EXPECT_EQ(v4.data.a[2], 200u);
  EXPECT_EQ(v4.data.a[3], 200u);

  EXPECT_EQ(v3.data.a[0], 300u);
  EXPECT_EQ(v3.data.a[1], 300u);
  EXPECT_EQ(v3.data.a[2], 300u);

  EXPECT_EQ(v2.data.a[0], 400u);
  EXPECT_EQ(v2.data.a[1], 400u);
}

TEST(VectorSignedInteger, ShouldConstructFromScalarConstexpr)
{
  constexpr ivec4 v4{ -200 };
  constexpr ivec3 v3{ -300 };
  constexpr ivec3 v2{ -400 };

  EXPECT_EQ(v4.data.a[0], -200);
  EXPECT_EQ(v4.data.a[1], -200);
  EXPECT_EQ(v4.data.a[2], -200);
  EXPECT_EQ(v4.data.a[3], -200);

  EXPECT_EQ(v3.data.a[0], -300);
  EXPECT_EQ(v3.data.a[1], -300);
  EXPECT_EQ(v3.data.a[2], -300);

  EXPECT_EQ(v2.data.a[0], -400);
  EXPECT_EQ(v2.data.a[1], -400);
}

TEST(VectorSignedInteger, ShouldConstructFromScalar)
{
  ivec4 v4{ -200 };
  ivec3 v3{ -300 };
  ivec2 v2{ -400 };

  EXPECT_EQ(v4.data.a[0], -200);
  EXPECT_EQ(v4.data.a[1], -200);
  EXPECT_EQ(v4.data.a[2], -200);
  EXPECT_EQ(v4.data.a[3], -200);

  EXPECT_EQ(v3.data.a[0], -300);
  EXPECT_EQ(v3.data.a[1], -300);
  EXPECT_EQ(v3.data.a[2], -300);

  EXPECT_EQ(v2.data.a[0], -400);
  EXPECT_EQ(v2.data.a[1], -400);
}