#include <gtest/gtest.h>

#include "graph/vector.h"

TEST(VectorFloatCompare, ShouldCompareEqual)
{
  vec3 v0{ 0.0f, 10.0f, 20.0f };
  vec3 v1{ 10.0f, 20.0f, 10.0f };

  const auto mask0 = v0 == v1;

  EXPECT_TRUE(!std::isnan(mask0.data.a[0]));
  EXPECT_TRUE(!std::isnan(mask0.data.a[1]));
  EXPECT_TRUE(!std::isnan(mask0.data.a[2]));

  vec3 v2{ 10.0f, 10.0f, 10.0f };
  vec3 v3{ 10.0f, 20.0f, 10.0f };

  const auto mask1 = v2 == v3;

  EXPECT_TRUE(std::isnan(mask1.data.a[0]));
  EXPECT_TRUE(!std::isnan(mask1.data.a[1]));
  EXPECT_TRUE(std::isnan(mask1.data.a[2]));
}
TEST(VectorFloatCompare, ShouldCompareLessThan)
{
  vec3 v0{ 0.0f, 10.0f, 20.0f };
  vec3 v1{ 10.0f, 20.0f, 10.0f };

  const auto mask = v0 < v1;

  EXPECT_TRUE(std::isnan(mask.data.a[0]));
  EXPECT_TRUE(std::isnan(mask.data.a[1]));
  EXPECT_TRUE(!std::isnan(mask.data.a[2]));
}

TEST(VectorFloatCompare, ShouldCompareLessThanEqual)
{
  vec3 v0{ 0.0f, 20.0f, 20.0f };
  vec3 v1{ 10.0f, 20.0f, 10.0f };

  const auto mask = v0 <= v1;

  EXPECT_TRUE(std::isnan(mask.data.a[0]));
  EXPECT_TRUE(std::isnan(mask.data.a[1]));
  EXPECT_TRUE(!std::isnan(mask.data.a[2]));
}

TEST(VectorFloatCompare, ShouldCompareGreaterThan)
{
  vec3 v0{ 0.0f, 10.0f, 20.0f };
  vec3 v1{ 10.0f, 20.0f, 10.0f };

  const auto mask = v0 > v1;

  EXPECT_TRUE(!std::isnan(mask.data.a[0]));
  EXPECT_TRUE(!std::isnan(mask.data.a[1]));
  EXPECT_TRUE(std::isnan(mask.data.a[2]));
}

TEST(VectorFloatCompare, ShouldCompareGreaterThanEqual)
{
  vec3 v0{ 0.0f, 20.0f, 20.0f };
  vec3 v1{ 10.0f, 20.0f, 10.0f };

  const auto mask = v0 >= v1;

  EXPECT_TRUE(!std::isnan(mask.data.a[0]));
  EXPECT_TRUE(std::isnan(mask.data.a[1]));
  EXPECT_TRUE(std::isnan(mask.data.a[2]));
}

TEST(VectorFloatCompare, ShouldCompareAny)
{
  vec3 v0{ 0.0f, 10.0f, 20.0f };
  vec3 v1{ 10.0f, 20.0f, 10.0f };

  const auto mask0 = v0 < v1;

  EXPECT_TRUE(any(mask0));

  vec3 v2{ 100.0f, 100.0f, 200.0f };
  vec3 v3{ 10.0f, 20.0f, 10.0f };

  const auto mask1 = v2 < v3;

  EXPECT_FALSE(any(mask1));
}

TEST(VectorFloatCompare, ShouldCompareAll)
{
  vec3 v0{ 0.0f, 0.0f, 0.0f };
  vec3 v1{ 10.0f, 20.0f, 10.0f };

  const auto mask0 = v0 < v1;

  EXPECT_TRUE(all(mask0));

  vec3 v2{ 0.0f, 100.0f, 0.0f };
  vec3 v3{ 10.0f, 20.0f, 10.0f };

  const auto mask1 = v2 < v3;

  EXPECT_FALSE(all(mask1));
}