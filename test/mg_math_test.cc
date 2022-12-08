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

TEST(mgMathTest, mgDistPlanePoint)
{
  vec3 v1;
  vec3 v2;
  vec3 v3;
  f32 f_actual;
  f32 f_expected;

  v1 = { 1, 2, 3 };
  v2 = { 30, 20, 10 };
  v3 = { 5, 6, 7 };
  f_expected = -62.0f;
  f_actual = mgDistPlanePoint(v1, v2, v3);
  EXPECT_FLOAT_EQ(f_actual, f_expected);
}

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

TEST(mgMathTest, mgReflectionPlane)
{
  vec3 v1;
  vec3 v2;
  vec3 v3;
  vec3 v4_actual;
  vec3 v4_expected;
  f32 f_actual;
  f32 f_expected;

  v1 = { 1, 2, 3 };
  v2 = { 30, 20, 10 };
  v3 = { 5, 6, 7 };
  v4_expected = { -99, -234, -369 };
  f_expected = -124.0f;
  f_actual = mgReflectionPlane(v1, v2, v3, v4_actual);
  EXPECT_FLOAT_EQ(f_actual, f_expected);
  for (usize i = 0; i < 3; ++i)
  {
    EXPECT_FLOAT_EQ(v4_actual[i], v4_expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, v4_actual[i], v4_expected[i]) << std::endl;
  }
}


/* TODO: Fix this test
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
*/

TEST(mgMathTest, mgIntersectionPoint_line_poly3)
{
  vec3 v1;
  vec3 v2;
  vec3 v3;
  vec3 v4;
  vec3 v5;
  vec3 v6;
  vec3 v7_actual;
  vec3 v7_expected;
  bool result_expected;
  bool result_actual;

  v1 = { -34.91, 137.98, 159.12 };
  v2 = { -34.91, 103.98, 159.12 };
  v3 = { -0.43, 104.20, 159.78 };
  v4 = { 60.26, 104.20, 148.0 };
  v5 = { -61, 104.2, -147.7 };
  v6 = { 0, 19372.44, 0 };
  result_expected = false;
  result_actual = mgIntersectionPoint_line_poly3(v1, v2, v3, v4, v5, v6, v7_actual);
  EXPECT_EQ(result_actual, result_expected);

  v1 = { -39.55, 138.2, 150.26 };
  v2 = { -39.55, 104.20, 150.26 };
  v3 = { -60.74, 104.2, 148.27 };
  v4 = { -0.43, 104.2, 159.78 };
  v5 = { -112.92, 104.2, -113.57 };
  v6 = { 0, 15193.65, 0 };
  v7_expected = { -39.55, 104.2, 150.26 };
  result_expected = true;
  result_actual = mgIntersectionPoint_line_poly3(v1, v2, v3, v4, v5, v6, v7_actual);
  EXPECT_EQ(result_actual, result_expected);
  for (usize i = 0; i < 3; ++i)
  {
    EXPECT_FLOAT_EQ(v7_actual[i], v7_expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, v7_actual[i], v7_expected[i]) << std::endl;
  }
}

TEST(mgMathTest, mgCheckPointPoly3_XYZ)
{
  vec3 v1;
  vec3 v2;
  vec3 v3;
  vec3 v4;
  vec3 v5;

  v1 = { -21, 104.2, 157.75 };
  v2 = { -0.43, 104.2, 159.78 };
  v3 = { 60.26, 104.2, 148.0 };
  v4 = { -61, 104.2, -147.7 };
  v5 = { 0, 19372.44, 0 };
  EXPECT_EQ(mgCheckPointPoly3_XYZ(v1, v2, v3, v4, v5), 0);

  v1 = { -93.30, 109, 220.76 };
  v2 = { -169.71, 180, 169.71 };
  v3 = { -91.84, 180, 221.73 };
  v4 = { -91.84, 104, 221.73 };
  v5 = { 3953.93, 0, -5917.48 };
  EXPECT_EQ(mgCheckPointPoly3_XYZ(v1, v2, v3, v4, v5), 1);
}

TEST(mgMathTest, mgCheckPointPoly3_XZ)
{
  vec3 v1;
  vec3 v2;
  vec3 v3;
  vec3 v4;

  v1 = { 0, 0, 229.5 };
  v2 = { 40, 0, 240.0 };
  v3 = { 320, 0, -320 };
  v4 = { 0, 0, -320 };
  EXPECT_EQ(mgCheckPointPoly3_XZ(v1, v2, v3, v4), 0);

  v1 = { 3.57794, 0, 223.712f };
  v2 = { -320, 0, -320 };
  v3 = { -40, 0, 240 };
  v4 = { 40, 0, 240 };
  EXPECT_EQ(mgCheckPointPoly3_XZ(v1, v2, v3, v4), 1);

  v1 = { -7.19, 0, -161.47f };
  v2 = { -21.84, 0, -165.73 };
  v3 = { -21.84, 0, -165.73 };
  v4 = { -1.71, 0, -113.71 };
  EXPECT_EQ(mgCheckPointPoly3_XZ(v1, v2, v3, v4), 2);

  v1 = { -7.19, 0, -161.47f };
  v2 = { -1.71, 0, -113.71 };
  v3 = { -21.84, 0, -165.73 };
  v4 = { -21.84, 0, -165.73 };
  EXPECT_EQ(mgCheckPointPoly3_XZ(v1, v2, v3, v4), 3);

  v1 = { -7.19, 0, -161.47f };
  v2 = { -1.71, 0, -113.71 };
  v3 = { -21.84, 0, -165.73 };
  v4 = { -1.71, 0, -113.71 };
  EXPECT_EQ(mgCheckPointPoly3_XZ(v1, v2, v3, v4), 4);
}

TEST(mgMathTest, mgDistVector)
{
  EXPECT_FLOAT_EQ(mgDistVector({ -2.0f, 2.0f, 5.0f }), 5.744563f);
  EXPECT_FLOAT_EQ(mgDistVector({ -2.0f, 2.0f, 5.0f }, { 20.0f, 20.0f, 20.0f }), 32.140316f);
}

TEST(mgMathTest, mgDistVectorXZ)
{
  EXPECT_FLOAT_EQ(mgDistVectorXZ({ -2.0f, 2.0f, 5.0f }), 5.385165f);
}

TEST(mgMathTest, mgDistVector2)
{
  EXPECT_FLOAT_EQ(mgDistVector2({ -2.0f, 2.0f, 5.0f }), 33.0f);
  EXPECT_FLOAT_EQ(mgDistVector2({ -2.0f, 2.0f, 5.0f }, { 20.0f, 20.0f, 20.0f }), 1032.9999f);
}

TEST(mgMathTest, mgDistVectorXZ2)
{
  EXPECT_FLOAT_EQ(mgDistVectorXZ2({ -2.0f, 2.0f, 5.0f }, { 20.0f, 20.0f, 20.0f }), 709.0f);
}

TEST(mgMathTest, mgMulMatrix)
{
  matrix4 m1;
  matrix4 m2;
  matrix4 expected;
  matrix4 actual;
  m1 = {
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16
  };
  m2 = {
    17, 18, 19, 20,
    21, 22, 23, 24,
    25, 26, 27, 28,
    29, 30, 31, 32
  };
  expected = {
    538, 612, 686, 760,
    650, 740, 830, 920,
    762, 868, 974, 1080,
    874, 996, 1118, 1240
  };
  actual = mgMulMatrix(m1, m2);

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      EXPECT_FLOAT_EQ(actual[i][j], expected[i][j]) <<
        common::strings::format("Component {},{}: Actual: {}, Expected: {}", i, j, actual[i][j], expected[i][j]) << std::endl;
    }
  }
}

TEST(mgMathTest, mgInverseMatrix)
{
  matrix4 m1 = {
    2, -2, 2, 2,
    0.5, 2, 2, 2,
    -2, 1, 1, 2,
    1, 2, -2, -2
  };
  matrix4 expected = {
    0, 8/36.0f, -16/36.0f, 0,
    -9/36.0f, 12/36.0f, -6/36.0f, 0,
    9/36.0f, 4/36.0f, 10/36.0f, 0,
    1.0f, -24/36.0f, 48/36.0f, 1
  };
  auto actual = mgInverseMatrix(m1);

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      EXPECT_FLOAT_EQ(actual[i][j], expected[i][j]) <<
        common::strings::format("Component {},{}: Actual: {}, Expected: {}", i, j, actual[i][j], expected[i][j]) << std::endl;
    }
  }
}

TEST(mgMathTest, mgRotMatrixX)
{
  f32 scalar = common::math::deg_to_rad(60.0f);
  matrix4 expected = {
    1, 0, 0, 0,
    0, 0.5, 0.86602545f, 0,
    0, -0.86602545f, 0.5, 0,
    0, 0, 0, 1
  };
  auto actual = mgRotMatrixX(scalar);

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      EXPECT_FLOAT_EQ(actual[i][j], expected[i][j]) <<
        common::strings::format("Component {},{}: Actual: {}, Expected: {}", i, j, actual[i][j], expected[i][j]) << std::endl;
    }
  }
}

TEST(mgMathTest, mgRotMatrixY)
{
  f32 scalar = common::math::deg_to_rad(60.0f);
  matrix4 expected = {
    0.5, 0, -0.86602545f, 0,
    0, 1, 0, 0,
    0.86602545f, 0, 0.5, 0,
    0, 0, 0, 1
  };
  auto actual = mgRotMatrixY(scalar);

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      EXPECT_FLOAT_EQ(actual[i][j], expected[i][j]) <<
        common::strings::format("Component {},{}: Actual: {}, Expected: {}", i, j, actual[i][j], expected[i][j]) << std::endl;
    }
  }
}

TEST(mgMathTest, mgRotMatrixZ)
{
  f32 scalar = common::math::deg_to_rad(60.0f);
  matrix4 expected = {
    0.5, 0.86602545f, 0, 0,
    -0.86602545f, 0.5, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };
  auto actual = mgRotMatrixZ(scalar);

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      EXPECT_FLOAT_EQ(actual[i][j], expected[i][j]) <<
        common::strings::format("Component {},{}: Actual: {}, Expected: {}", i, j, actual[i][j], expected[i][j]) << std::endl;
    }
  }
}

TEST(mgMathTest, mgRotMatrixXYZ)
{
  vec3 rot = { common::math::deg_to_rad(60.0f), common::math::deg_to_rad(60.0f), common::math::deg_to_rad(60.0f) };
  matrix4 expected = {
    0.25, 0.43301269f, -0.86602545f, 0,
    -0.058012694f, 0.8995191f, 0.4330127f, 0,
    0.96650636f, -0.058012694f, 0.25, 0,
    0, 0, 0, 1
  };
  auto actual = mgRotMatrixXYZ(rot);

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      EXPECT_FLOAT_EQ(actual[i][j], expected[i][j]) <<
        common::strings::format("Component {},{}: Actual: {}, Expected: {}", i, j, actual[i][j], expected[i][j]) << std::endl;
    }
  }
}

TEST(mgMathTest, mgCreateMatrixPY)
{
  f32 rot = common::math::deg_to_rad(60.0f);
  vec4 w = { 2.0, 3.0, 4.0, 5.0 };
  matrix4 expected = {
    0.5, 0, -0.86602545, 0,
    0, 1, 0, 0,
    0.86602545, 0, 0.5, 0,
    2, 3, 4, 1
  };
  auto actual = mgCreateMatrixPY(w, rot);

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      EXPECT_FLOAT_EQ(actual[i][j], expected[i][j]) <<
        common::strings::format("Component {},{}: Actual: {}, Expected: {}", i, j, actual[i][j], expected[i][j]) << std::endl;
    }
  }
}

TEST(mgMathTest, mgLookAtMatrixZ)
{
  vec3 look_at = { 10, 20, 30 };
  matrix4 expected = {
    0.948683, 0, -0.31622773, 0,
    -0.16903083, 0.84515429, -0.50709254, 0,
    0.26726124, 0.53452247, 0.801784, 0,
    0, 0, 0, 1
  };
  auto actual = mgLookAtMatrixZ(look_at);

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      EXPECT_FLOAT_EQ(actual[i][j], expected[i][j]) <<
        common::strings::format("Component {},{}: Actual: {}, Expected: {}", i, j, actual[i][j], expected[i][j]) << std::endl;
    }
  }
}

TEST(mgMathTest, mgShadowMatrix)
{
  vec3 v1 = { 10, 20, 30 };
  vec3 v2 = { 40, 50, 60 };
  vec3 v3 = { 0, 1, 0 };
  matrix4 expected = {
    1, 0, 0, 0,
    -0.5, 0, -1.5, 0,
    0, 0, 1, 0,
    25, 50, 75, 1
  };
  auto actual = mgShadowMatrix(v1, v2, v3);

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      EXPECT_FLOAT_EQ(actual[i][j], expected[i][j]) <<
        common::strings::format("Component {},{}: Actual: {}, Expected: {}", i, j, actual[i][j], expected[i][j]) << std::endl;
    }
  }
}

TEST(mgMathTest, mgVectorMinMaxN)
{
  vec4 v[] = {
    vec4{ 1, 2, 3, 4 },
    vec4{ 4, 3, 2, 1 },
  };
  vec4 max_expected = { 4, 3, 3, 4 };
  vec4 min_expected = { 1, 2, 2, 1 };
  vec4 max_actual;
  vec4 min_actual;
  mgVectorMinMaxN(max_actual, min_actual, v, std::size(v));

  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_FLOAT_EQ(max_actual[i], max_expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, max_actual[i], max_expected[i]) << std::endl;
  }
  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_FLOAT_EQ(min_actual[i], min_expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, min_actual[i], min_expected[i]) << std::endl;
  }
}

TEST(mgMathTest, mgApplyMatrix)
{
  vec4 min_corner = { 10, 20, 30, 1 };
  vec4 max_corner = { 40, 50, 60, 1 };
  matrix4 m = {
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16
  };
  vec4 max_expected = { 843, 994, 1145, 1296 };
  vec4 min_expected = { 393, 454, 515, 576 };
  vec4 max_actual;
  vec4 min_actual;

  mgApplyMatrix(max_actual, min_actual, m, max_corner, min_corner);

  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_FLOAT_EQ(max_actual[i], max_expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, max_actual[i], max_expected[i]) << std::endl;
  }
  for (usize i = 0; i < 4; ++i)
  {
    EXPECT_FLOAT_EQ(min_actual[i], min_expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, min_actual[i], min_expected[i]) << std::endl;
  }
}

TEST(mgMathTest, mgApplyMatrixN)
{
  vec4 v[] = {
    vec4 {1, 2, 3, 4},
    vec4 {5, 6, 7, 8}
  };
  matrix4 m = {
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16
  };
  vec4 v_actual[std::size(v)];
  vec4 v_expected[] = {
    vec4 {90.0f, 100.0f, 110.0f, 120.0f},
    vec4 {202.0f, 228.0f, 254.0f, 280.0f},
  };

  mgApplyMatrixN(v_actual, m, v, std::size(v));

  for (usize i = 0; i < std::size(v); ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      EXPECT_FLOAT_EQ(v_actual[i][j], v_expected[i][j]) <<
        common::strings::format("Component {},{}: Actual: {}, Expected: {}", i, j, v_actual[i][j], v_expected[i][j]) << std::endl;
    }
  }
}

TEST(mgMathTest, mgVectorInterpolate)
{
  vec3 lhs = { 10, 20, 30 };
  vec3 rhs = { 50, 50, 50 };
  f32 t = 0.75f;
  vec3 expected = { 10.557086f, 20.417814f, 30.278543f };
  vec3 actual = mgVectorInterpolate(lhs, rhs, t, false);

  for (usize i = 0; i < 3; ++i)
  {
    EXPECT_FLOAT_EQ(actual[i], expected[i]) <<
      common::strings::format("Component {}: Actual: {}, Expected: {}", i, actual[i], expected[i]) << std::endl;
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