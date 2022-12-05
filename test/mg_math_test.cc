#include <gtest/gtest.h>

#include "common/math.h"
#include "common/strings.h"
#include "common/types.h"

#include "dc2/mg/mg_math.h"

TEST(mgMathTest, mgFtoI4)
{
  vec4 input;
  ivec4 expected;
  ivec4 actual;

  input = { 274.067f, 251.886f, std::bit_cast<f32>(0x4c9ee441), 130.923f };

  // NOTE: These are actually fixed point 28,4 numbers
  expected = { 4385, 4030, 1332879488, 2094 };
  actual = mgFtoI4(input);

  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_EQ(actual[i], expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual[i], expected[i]) << std::endl;
  }
}

TEST(mgMathTest, mgCreateBox8)
{
  vec3 corner1;
  vec3 corner2;
  mgVu0FBOX8 expected;
  mgVu0FBOX8 actual;

  corner1 = { 160.0f, 400.0f, 160.0f };
  corner2 = { -160.0f, -20.0f, -160.0f };
  expected = {
    vec4{ -160.0f, -20.0f, -160.0f, 1.0f },
    vec4{ 160.0f, -20.0f, -160.0f, 1.0f },
    vec4{ -160.0f, 400.0f, -160.0f, 1.0f },
    vec4{ 160.0f, 400.0f, -160.0f, 1.0f },
    vec4{ -160.0f, -20.0f, 160.0f, 1.0f },
    vec4{ 160.0f, -20.0f, 160.0f, 1.0f },
    vec4{ -160.0f, 400.0f, 160.0f, 1.0f },
    vec4{ 160.0f, 400.0f, 160.0f, 1.0f },
  };
  actual = mgCreateBox8(corner1, corner2);

  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      EXPECT_FLOAT_EQ(actual.vertices[i][j], expected.vertices[i][j]) <<
        common::strings::format(
          "Component {},{}: Actual: {}, Expected: {}", i, j, actual.vertices[i][j], expected.vertices[i][j]
        ) << std::endl;
    }
  }
}

TEST(mgMathTest, mgClipBoxVertex)
{
  vec4 c1;
  vec4 c2;
  vec4 p;
  c1 = { 20.0f, 40.0f, 60.0f, 1.0f };
  c2 = { -20.0f, -40.0f, -60.0f, 1.0f };
  p = { 10.0f, 30.0f, 50.0f, 1.0f };
  EXPECT_TRUE(mgClipBoxVertex(p, c1, c2));

  c1 = { 20.0f, 40.0f, 60.0f, 1.0f };
  c2 = { -20.0f, -40.0f, -60.0f, 1.0f };
  p = { -10.0f, -30.0f, -50.0f, 1.0f };
  EXPECT_TRUE(mgClipBoxVertex(p, c1, c2));

  c1 = { 20.0f, 40.0f, 60.0f, 1.0f };
  c2 = { -20.0f, -40.0f, -60.0f, 1.0f };
  p = { 30.0f, 30.0f, 50.0f, 1.0f };
  EXPECT_FALSE(mgClipBoxVertex(p, c1, c2));

  c1 = { 20.0f, 40.0f, 60.0f, 1.0f };
  c2 = { -20.0f, -40.0f, -60.0f, 1.0f };
  p = { 10.0f, 50.0f, 50.0f, 1.0f };
  EXPECT_FALSE(mgClipBoxVertex(p, c1, c2));

  c1 = { 20.0f, 40.0f, 60.0f, 1.0f };
  c2 = { -20.0f, -40.0f, -60.0f, 1.0f };
  p = { 10.0f, 30.0f, 70.0f, 1.0f };
  EXPECT_FALSE(mgClipBoxVertex(p, c1, c2));
}

TEST(mgMathTest, mgClipBox)
{
  vec4 c1;
  vec4 c2;
  vec4 c3;
  vec4 c4;
  c1 = { 480.0f, 400.0f, 3360.0f, 1.0f };
  c2 = { 160.0f, -20.0f, 3040.0f, 1.0f };
  c3 = { 469.797f, 40.0f, 3219.31f, 1.0f };
  c4 = { 389.797f, -40.0f, 3139.31f, 1.0f };
  EXPECT_TRUE(mgClipBox(c1, c2, c3, c4));

  c1 = { 480.0f, 400.0f, 3360.0f, 1.0f };
  c2 = { 160.0f, -20.0f, 3040.0f, 1.0f };
  c3 = { 469.797f, 40.0f, 3219.31f, 1.0f };
  c4 = { 389.797f, -40.0f, 3139.31f, 1.0f };
  EXPECT_TRUE(mgClipBox(c1, c2, c3, c4));

  c1 = { 800.0f, 400.f, 3360.0f, 1.0f };
  c2 = { 480.0f, -20.0f, 3040.0f, 1.0f };
  c3 = { 468.422f, 40.0f, 3219.31f, 1.0f };
  c4 = { 389.797f, -40.0f, 3139.31f, 1.0f };
  EXPECT_FALSE(mgClipBox(c1, c2, c3, c4));

  c1 = { 800.0f, 400.f, 3360.0f, 1.0f };
  c2 = { 460.0f, 60.0f, 3040.0f, 1.0f };
  c3 = { 468.422f, 40.0f, 3219.31f, 1.0f };
  c4 = { 389.797f, -40.0f, 3139.31f, 1.0f };
  EXPECT_FALSE(mgClipBox(c1, c2, c3, c4));

  c1 = { 800.0f, 400.f, 3360.0f, 1.0f };
  c2 = { 460.0f, -20.0f, 3340.0f, 1.0f };
  c3 = { 468.422f, 40.0f, 3219.31f, 1.0f };
  c4 = { 389.797f, -40.0f, 3139.31f, 1.0f };
  EXPECT_FALSE(mgClipBox(c1, c2, c3, c4));
}

TEST(mgMathTest, mgClipBoxW)
{
  vec4 c1;
  vec4 c2;
  vec4 c3;
  vec4 c4;
  c1 = { 480.0f, 400.0f, 1.0f, 3360.0f };
  c2 = { 160.0f, -20.0f, 1.0f, 3040.0f };
  c3 = { 469.797f, 40.0f, 1.0f, 3219.31f };
  c4 = { 389.797f, -40.0f, 1.0f, 3139.31f };
  EXPECT_TRUE(mgClipBoxW(c1, c2, c3, c4));

  c1 = { 480.0f, 400.0f, 1.0f, 3360.0f };
  c2 = { 160.0f, -20.0f, 1.0f, 3040.0f };
  c3 = { 469.797f, 40.0f, 1.0f, 3219.31f };
  c4 = { 389.797f, -40.0f, 1.0f, 3139.31f };
  EXPECT_TRUE(mgClipBoxW(c1, c2, c3, c4));

  c1 = { 800.0f, 400.f, 1.0f, 3360.0f };
  c2 = { 480.0f, -20.0f, 1.0f, 3040.0f };
  c3 = { 468.422f, 40.0f, 1.0f, 3219.31f };
  c4 = { 389.797f, -40.0f, 1.0f, 3139.31f };
  EXPECT_FALSE(mgClipBoxW(c1, c2, c3, c4));

  c1 = { 800.0f, 400.f, 1.0f, 3360.0f };
  c2 = { 460.0f, 60.0f, 1.0f, 3040.0f };
  c3 = { 468.422f, 40.0f, 1.0f, 3219.31f };
  c4 = { 389.797f, -40.0f, 1.0f, 3139.31f };
  EXPECT_FALSE(mgClipBoxW(c1, c2, c3, c4));

  c1 = { 800.0f, 400.f, 1.0f, 3360.0f };
  c2 = { 460.0f, -20.0f, 1.0f, 3340.0f };
  c3 = { 468.422f, 40.0f, 1.0f, 3219.31f };
  c4 = { 389.797f, -40.0f, 1.0f, 3139.31f };
  EXPECT_FALSE(mgClipBoxW(c1, c2, c3, c4));
}

TEST(mgMathTest, mgClipInBox)
{
  vec4 c1;
  vec4 c2;
  vec4 c3;
  vec4 c4;
  c1 = { 738.834f, 221.569f, 398.365f, 1.0f };
  c2 = { -11.2427f, -40.1354f, 131.28f, 1.0f };
  c3 = { 2047.0f, 2047.0f, 50000.0f, 1.0f };
  c4 = { -2047.0f, -2047.0f, 5.0f, 1.0f };
  EXPECT_TRUE(mgClipInBox(c1, c2, c3, c4));

  c1 = { 738.834f, 221.569f, 398.365f, 1.0f };
  c2 = { -3011.2427f, -40.1354f, 131.28f, 1.0f };
  c3 = { 2047.0f, 2047.0f, 50000.0f, 1.0f };
  c4 = { -2047.0f, -2047.0f, 5.0f, 1.0f };
  EXPECT_FALSE(mgClipInBox(c1, c2, c3, c4));

  c1 = { 3738.834f, 221.569f, 398.365f, 1.0f };
  c2 = { -11.2427f, -40.1354f, 131.28f, 1.0f };
  c3 = { 2047.0f, 2047.0f, 50000.0f, 1.0f };
  c4 = { -2047.0f, -2047.0f, 5.0f, 1.0f };
  EXPECT_FALSE(mgClipInBox(c1, c2, c3, c4));

  c1 = { 738.834f, 2221.569f, 398.365f, 1.0f };
  c2 = { -11.2427f, -40.1354f, 131.28f, 1.0f };
  c3 = { 2047.0f, 2047.0f, 50000.0f, 1.0f };
  c4 = { -2047.0f, -2047.0f, 5.0f, 1.0f };
  EXPECT_FALSE(mgClipInBox(c1, c2, c3, c4));

  c1 = { 738.834f, 221.569f, 398.365f, 1.0f };
  c2 = { -11.2427f, -3040.1354f, 131.28f, 1.0f };
  c3 = { 2047.0f, 2047.0f, 50000.0f, 1.0f };
  c4 = { -2047.0f, -2047.0f, 5.0f, 1.0f };
  EXPECT_FALSE(mgClipInBox(c1, c2, c3, c4));

  c1 = { 738.834f, 221.569f, 60398.365f, 1.0f };
  c2 = { -11.2427f, -40.1354f, 131.28f, 1.0f };
  c3 = { 2047.0f, 2047.0f, 50000.0f, 1.0f };
  c4 = { -2047.0f, -2047.0f, 5.0f, 1.0f };
  EXPECT_FALSE(mgClipInBox(c1, c2, c3, c4));

  c1 = { 738.834f, 221.569f, 398.365f, 1.0f };
  c2 = { -11.2427f, -40.1354f, -131.28f, 1.0f };
  c3 = { 2047.0f, 2047.0f, 50000.0f, 1.0f };
  c4 = { -2047.0f, -2047.0f, 5.0f, 1.0f };
  EXPECT_FALSE(mgClipInBox(c1, c2, c3, c4));
}

TEST(mgMathTest, mgClipInBoxW)
{
  vec4 c1;
  vec4 c2;
  vec4 c3;
  vec4 c4;
  c1 = { 738.834f, 221.569f, 1.0f, 398.365f };
  c2 = { -11.2427f, -40.1354f, 1.0f, 131.28f };
  c3 = { 2047.0f, 2047.0f, 1.0f, 50000.0f };
  c4 = { -2047.0f, -2047.0f, 1.0f, 5.0f };
  EXPECT_TRUE(mgClipInBoxW(c1, c2, c3, c4));

  c1 = { 738.834f, 221.569f, 1.0f, 398.365f };
  c2 = { -3011.2427f, -40.1354f, 1.0f, 131.28f };
  c3 = { 2047.0f, 2047.0f, 1.0f, 50000.0f };
  c4 = { -2047.0f, -2047.0, 1.0f, 5.0f };
  EXPECT_FALSE(mgClipInBoxW(c1, c2, c3, c4));

  c1 = { 3738.834f, 221.569f, 1.0f, 398.365f };
  c2 = { -11.2427f, -40.1354f, 1.0f, 131.28f };
  c3 = { 2047.0f, 2047.0f, 1.0f, 50000.0f };
  c4 = { -2047.0f, -2047.0f, 1.0f, 5.0f };
  EXPECT_FALSE(mgClipInBoxW(c1, c2, c3, c4));

  c1 = { 738.834f, 2221.569f, 1.0f, 398.365f };
  c2 = { -11.2427f, -40.1354f, 1.0f, 131.28f };
  c3 = { 2047.0f, 2047.0, 1.0f, 50000.0f };
  c4 = { -2047.0f, -2047.0f, 1.0f, 5.0f };
  EXPECT_FALSE(mgClipInBoxW(c1, c2, c3, c4));

  c1 = { 738.834f, 221.569f, 1.0f, 398.365f };
  c2 = { -11.2427f, -3040.1354f, 1.0f, 131.28f };
  c3 = { 2047.0f, 2047.0f, 1.0f, 50000.0f };
  c4 = { -2047.0f, -2047.0f, 1.0f, 5.0 };
  EXPECT_FALSE(mgClipInBoxW(c1, c2, c3, c4));

  c1 = { 738.834f, 221.569f, 1.0f, 60398.365f };
  c2 = { -11.2427f, -40.1354f, 1.0f, 131.28f };
  c3 = { 2047.0f, 2047.0f, 1.0f, 50000.0f };
  c4 = { -2047.0f, -2047.0f, 1.0f, 5.0f };
  EXPECT_FALSE(mgClipInBoxW(c1, c2, c3, c4));

  c1 = { 738.834f, 221.569f, 1.0f, 398.365f };
  c2 = { -11.2427f, -40.1354f, 1.0f, -131.28f };
  c3 = { 2047.0f, 2047.0f, 1.0f, 50000.0f };
  c4 = { -2047.0f, -2047.0f, 1.0f, 5.0f };
  EXPECT_FALSE(mgClipInBoxW(c1, c2, c3, c4));
}

TEST(mgMathTest, mgAddVector)
{
  vec4 v1{ 1, 2, 3, 4 };
  vec4 v2{ 2, 4, 6, 8 };
  vec4 expected{ 3, 6, 9, 12 };

  mgAddVector(v1, v2);
  EXPECT_EQ(v1, expected);
}

TEST(mgMathTest, mgSubVector)
{
  vec4 v1{ 2, 4, 6, 8 };
  vec4 v2{ 1, 2, 3, 4 };
  vec4 expected{ 1, 2, 3, 4 };

  mgSubVector(v1, v2);
  EXPECT_EQ(v1, expected);
}

TEST(mgMathTest, mgNormalizeVector)
{
  vec3 v1;
  f32 scalar;
  vec3 expected;
  vec3 actual;

  v1 = { 10, 0, 0 };
  scalar = 2;
  expected = { 2, 0, 0 };
  actual = mgNormalizeVector(v1, scalar);
  for (usize i = 0; i < 3; ++i)
  {
    EXPECT_FLOAT_EQ(actual[i], expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual[i], expected[i]) << std::endl;
  }

  v1 = { 5, 5, 5 };
  scalar = 6;
  expected = { 0.5773502691896257 * scalar, 0.5773502691896257 * scalar, 0.5773502691896257 * scalar };
  actual = mgNormalizeVector(v1, scalar);
  for (usize i = 0; i < 3; ++i)
  {
    EXPECT_FLOAT_EQ(actual[i], expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual[i], expected[i]) << std::endl;
  }
}

TEST(mgMathTest, mgVectorMin)
{
  vec4 v1;
  vec4 v2;
  vec4 v3;
  vec4 v4;
  vec4 expected;
  vec4 actual;

  // 2 vectors
  v1 = { 1, 2, 3, 4 };
  v2 = { 4, 3, 2, 1 };
  expected = { 1, 2, 2, 1 };
  actual = mgVectorMin(v1, v2);
  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_FLOAT_EQ(actual[i], expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual[i], expected[i]) << std::endl;
  }

  // 4 vectors
  v1 = { 1, 5, 9, 11 };
  v2 = { 11, 9, 5, 1 };
  v3 = { 2, 4, 8, 10 };
  v4 = { 10, 8, 4, 2 };
  expected = { 1, 4, 4, 1 };
  actual = mgVectorMin(v1, v2, v3, v4);
  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_FLOAT_EQ(actual[i], expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual[i], expected[i]) << std::endl;
  }
}

TEST(mgMathTest, mgVectorMaxMin)
{
  vec4 v1;
  vec4 v2;
  vec4 v3;
  vec4 v4;
  vec4 expected_max;
  vec4 expected_min;
  vec4 actual_max;
  vec4 actual_min;

  // 2 vectors
  v1 = { 1, 2, 3, 4 };
  v2 = { 4, 3, 2, 1 };
  expected_max = { 4, 3, 3, 4 };
  expected_min = { 1, 2, 2, 1 };
  mgVectorMaxMin(actual_max, actual_min, v1, v2);
  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_FLOAT_EQ(actual_max[i], expected_max[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual_max[i], expected_max[i]) << std::endl;
  }
  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_FLOAT_EQ(actual_min[i], expected_min[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual_min[i], expected_min[i]) << std::endl;
  }

  // 3 vectors
  v1 = { 1, 5, 9, 11 };
  v2 = { 11, 9, 5, 1 };
  v3 = { 2, 4, 8, 10 };
  expected_max = { 11, 9, 9, 11 };
  expected_min = { 1, 4, 5, 1 };
  mgVectorMaxMin(actual_max, actual_min, v1, v2, v3);
  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_FLOAT_EQ(actual_max[i], expected_max[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual_max[i], expected_max[i]) << std::endl;
  }
  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_FLOAT_EQ(actual_min[i], expected_min[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual_min[i], expected_min[i]) << std::endl;
  }

  // 4 vectors
  v1 = { 1, 5, 9, 11 };
  v2 = { 11, 9, 5, 1 };
  v3 = { 2, 4, 8, 10 };
  v4 = { 10, 8, 4, 2 };
  expected_max = { 11, 9, 9, 11 };
  expected_min = { 1, 4, 4, 1 };
  mgVectorMaxMin(actual_max, actual_min, v1, v2, v3, v4);
  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_FLOAT_EQ(actual_max[i], expected_max[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual_max[i], expected_max[i]) << std::endl;
  }
  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_FLOAT_EQ(actual_min[i], expected_min[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual_min[i], expected_min[i]) << std::endl;
  }
}

TEST(mgMathTest, mgBoxMaxMin)
{
  mgVu0FBOX b1;
  mgVu0FBOX b2;
  mgVu0FBOX expected;

  b1 = {
    3, 4, 5, 6,
    2, 3, 4, 5
  };
  b2 = {
    4, 3, 2, 1,
    3, 2, 1, 0
  };
  expected = {
    4, 4, 5, 6,
    2, 2, 1, 0
  };
  mgBoxMaxMin(b1, b2);
  for (usize i = 0; i < b1.corners.size(); ++i)
  {
    for (usize j = 0; j < 4; ++j)
    {
      EXPECT_FLOAT_EQ(b1.corners[i][j], expected.corners[i][j]) <<
        common::strings::format("Component {},{}: Actual: {}, Expected: {}", i, j, b1.corners[i][j], expected.corners[i][j]) << std::endl;
    }
  }
}

TEST(mgMathTest, mgPlaneNormal)
{
  vec3 v1;
  vec3 v2;
  vec3 v3;
  vec3 expected;
  vec3 actual;

  // TODO: Find and confirm better values to test here
  // approx. (float converter not accurate enough :()
  // v1 = { 3167.05f, 435.044f, -1.12291f };
  // v2 = { 3178.58f, 444.944f, -1.12291f };
  // v3 = { 3178.58f, 444.944f, 14.1226f };
  // expected = { 150.935f, -175.837f, 0.0f };
  v1 = { std::bit_cast<f32>(0x4545F0C7), std::bit_cast<f32>(0x43D9859F), std::bit_cast<f32>(0xBF8FBB9A) };
  v2 = { std::bit_cast<f32>(0x4546A951), std::bit_cast<f32>(0x43DE78DB), std::bit_cast<f32>(0xBF8FBB9A) };
  v3 = { std::bit_cast<f32>(0x4546A951), std::bit_cast<f32>(0x43DE78DB), std::bit_cast<f32>(0x4161F651) };
  expected = { std::bit_cast<f32>(0x4316EF5D), std::bit_cast<f32>(0xC32FD663), 0.0f };
  actual = mgPlaneNormal(v1, v2, v3);
  for (usize i = 0; i < 3; ++i)
  {
    EXPECT_FLOAT_EQ(actual[i], expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual[i], expected[i]) << std::endl;
  }
}

// TODO: mgDistPlanePoint test

TEST(mgMathTest, mgDistLinePoint)
{
  vec3 v1;
  vec3 v2;
  vec3 v3;
  vec3 v4_actual;
  vec3 v4_expected;
  f32 f_actual;
  f32 f_expected;

  v1 = { 383.5f, 55.75f, 3293.0f };
  v2 = { 429.75f, 0.00012207f, 3179.0f };
  v3 = { 429.75f, 16.0f, 3179.0f };
  v4_expected = { 429.75f, 16.0f, 3179.0f };
  f_expected = 129.286972f;
  f_actual = mgDistLinePoint(v1, v2, v3, v4_actual);
  EXPECT_FLOAT_EQ(f_actual, f_expected);
  for (usize i = 0; i < 3; ++i)
  {
    EXPECT_FLOAT_EQ(v4_actual[i], v4_expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, v4_actual[i], v4_expected[i]) << std::endl;
  }
}

// TODO: mgReflectionPlane

TEST(mgMathTest, mgIntersectionSphereLine)
{
  vec4 sphere;
  vec3 line_start;
  vec3 line_end;
  vec3 intersections_expected[2];
  vec3 intersections_actual[2];
  usize n_intersections_expected;
  usize n_intersections_actual;

  // 0 intersections
  sphere = { 731.094f, 0.0f, 3859.55f, 4.0f };
  line_start = { 480.0f, 0.0f, 3680.0f };
  line_end = { 480.0f, 0.0f, 3920.0f };
  n_intersections_expected = 0;
  n_intersections_actual = mgIntersectionSphereLine(sphere, line_start, line_end, intersections_actual);
  EXPECT_EQ(n_intersections_actual, n_intersections_expected);

  // 2 intersections
  sphere = { 2118.67f, 0.0f, 10.0f, 4.0f };
  line_start = { 2117.42f, 0.0f, 14.1226f };
  line_end = { 2118.67f, 0.0f, -1.12291f };
  n_intersections_expected = 2;
  intersections_expected[0] = vec3 { 2117.42f, 0.0f, 13.799f };
  intersections_expected[1] = vec3 { 2117.42f, 0.0f, 6.20098f };
  n_intersections_actual = mgIntersectionSphereLine(sphere, line_start, line_end, intersections_actual);
  EXPECT_EQ(n_intersections_actual, n_intersections_expected);
  for (usize i = 0; i < 2; ++i)
  {
    for (usize j = 0; j < 3; ++j)
    {
      EXPECT_FLOAT_EQ(intersections_actual[i][j], intersections_expected[i][j]) <<
        common::strings::format("Component {},{}: Actual: {}, Expected: {}", i,j, intersections_actual[i][j], intersections_expected[i][j]) << std::endl;
    }
  }
}

TEST(mgMathTest, mgAngleInterpolate)
{
  EXPECT_FLOAT_EQ(mgAngleInterpolate(-0.078987f, 2.387641f, 0.3f, false), 0.221013f);
  EXPECT_FLOAT_EQ(mgAngleInterpolate(0.221013f, 2.418880f, 0.3f, false), 0.521013f);
  EXPECT_FLOAT_EQ(mgAngleInterpolate(0.f, 0.f, 4.f, true), 0.f);
  EXPECT_FLOAT_EQ(mgAngleInterpolate(-0.76f, -0.76f, 8.f, true), -0.76f);
  EXPECT_FLOAT_EQ(mgAngleInterpolate(-2.184873f, 4.098312f, 2.f, true), -2.184873f);
}

TEST(mgMathTest, mgAngleCmp)
{
  EXPECT_EQ(mgAngleCmp(1.343752, 1.343500, 0.785398), 0);
}

TEST(mgMathTest, mgAngleLimit)
{
  EXPECT_FLOAT_EQ(mgAngleLimit(math::deg_to_rad(0.0f)), math::deg_to_rad(0.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(math::deg_to_rad(90.0f)), math::deg_to_rad(90.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(math::deg_to_rad(-90.0f)), math::deg_to_rad(-90.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(math::deg_to_rad(225.0f)), math::deg_to_rad(-135.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(math::deg_to_rad(-225.0f)), math::deg_to_rad(135.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(math::deg_to_rad(270.0f)), math::deg_to_rad(-90.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(math::deg_to_rad(-270.0f)), math::deg_to_rad(90.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(math::deg_to_rad(1100.0f)), math::deg_to_rad(20.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(math::deg_to_rad(-1100.0f)), math::deg_to_rad(-20.0f));
}