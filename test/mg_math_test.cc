#include <gtest/gtest.h>

#include "dc2/mg_math.h"

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
  EXPECT_FLOAT_EQ(mgAngleLimit(DEGREES_TO_RADIANS(0.0f)), DEGREES_TO_RADIANS(0.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(DEGREES_TO_RADIANS(90.0f)), DEGREES_TO_RADIANS(90.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(DEGREES_TO_RADIANS(-90.0f)), DEGREES_TO_RADIANS(-90.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(DEGREES_TO_RADIANS(225.0f)), DEGREES_TO_RADIANS(-135.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(DEGREES_TO_RADIANS(-225.0f)), DEGREES_TO_RADIANS(135.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(DEGREES_TO_RADIANS(270.0f)), DEGREES_TO_RADIANS(-90.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(DEGREES_TO_RADIANS(-270.0f)), DEGREES_TO_RADIANS(90.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(DEGREES_TO_RADIANS(1100.0f)), DEGREES_TO_RADIANS(20.0f));
  EXPECT_FLOAT_EQ(mgAngleLimit(DEGREES_TO_RADIANS(-1100.0f)), DEGREES_TO_RADIANS(-20.0f));
}