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