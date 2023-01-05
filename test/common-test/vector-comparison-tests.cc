#include <gtest/gtest.h>

#include "graph/vector.h"
#include "graph/_vector/_vector_math.h"

using namespace graph;

TEST(VectorFloatCompare, ShouldCompareEqual)
{
  vector<f32, 3> v0{ 0.0f, 10.0f, 20.0f };
  vector<f32, 3> v1{ 10.0f, 20.0f, 10.0f };

  const auto mask0 = v0 == v1;

  EXPECT_TRUE(!std::isnan(mask0.data.a[0]));
  EXPECT_TRUE(!std::isnan(mask0.data.a[1]));
  EXPECT_TRUE(!std::isnan(mask0.data.a[2]));

  vector<f32, 3> v2{ 10.0f, 10.0f, 10.0f };
  vector<f32, 3> v3{ 10.0f, 20.0f, 10.0f };

  const auto mask1 = v2 == v3;

  EXPECT_TRUE(std::isnan(mask1.data.a[0]));
  EXPECT_TRUE(!std::isnan(mask1.data.a[1]));
  EXPECT_TRUE(std::isnan(mask1.data.a[2]));
}
TEST(VectorFloatCompare, ShouldCompareLessThan)
{
  vector<f32, 3> v0{ 0.0f, 10.0f, 20.0f };
  vector<f32, 3> v1{ 10.0f, 20.0f, 10.0f };

  const auto mask = v0 < v1;

  EXPECT_TRUE(std::isnan(mask.data.a[0]));
  EXPECT_TRUE(std::isnan(mask.data.a[1]));
  EXPECT_TRUE(!std::isnan(mask.data.a[2]));
}

TEST(VectorFloatCompare, ShouldCompareLessThanEqual)
{
  vector<f32, 3> v0{ 0.0f, 20.0f, 20.0f };
  vector<f32, 3> v1{ 10.0f, 20.0f, 10.0f };

  const auto mask = v0 <= v1;

  EXPECT_TRUE(std::isnan(mask.data.a[0]));
  EXPECT_TRUE(std::isnan(mask.data.a[1]));
  EXPECT_TRUE(!std::isnan(mask.data.a[2]));
}

TEST(VectorFloatCompare, ShouldCompareGreaterThan)
{
  vector<f32, 3> v0{ 0.0f, 10.0f, 20.0f };
  vector<f32, 3> v1{ 10.0f, 20.0f, 10.0f };

  const auto mask = v0 > v1;

  EXPECT_TRUE(!std::isnan(mask.data.a[0]));
  EXPECT_TRUE(!std::isnan(mask.data.a[1]));
  EXPECT_TRUE(std::isnan(mask.data.a[2]));
}

TEST(VectorFloatCompare, ShouldCompareGreaterThanEqual)
{
  vector<f32, 3> v0{ 0.0f, 20.0f, 20.0f };
  vector<f32, 3> v1{ 10.0f, 20.0f, 10.0f };

  const auto mask = v0 >= v1;

  EXPECT_TRUE(!std::isnan(mask.data.a[0]));
  EXPECT_TRUE(std::isnan(mask.data.a[1]));
  EXPECT_TRUE(std::isnan(mask.data.a[2]));
}

TEST(VectorFloatCompare, ShouldCompareAny)
{
  vector<f32, 3> v0{ 0.0f, 10.0f, 20.0f };
  vector<f32, 3> v1{ 10.0f, 20.0f, 10.0f };

  const auto mask0 = v0 < v1;

  EXPECT_TRUE(vector_any(mask0));

  vector<f32, 3> v2{ 100.0f, 100.0f, 200.0f };
  vector<f32, 3> v3{ 10.0f, 20.0f, 10.0f };

  const auto mask1 = v2 < v3;

  EXPECT_FALSE(vector_any(mask1));
}

TEST(VectorFloatCompare, ShouldCompareAll)
{
  vector<f32, 3> v0{ 0.0f, 0.0f, 0.0f };
  vector<f32, 3> v1{ 10.0f, 20.0f, 10.0f };

  const auto mask0 = v0 < v1;

  EXPECT_TRUE(vector_all(mask0));

  vector<f32, 3> v2{ 0.0f, 100.0f, 0.0f };
  vector<f32, 3> v3{ 10.0f, 20.0f, 10.0f };

  const auto mask1 = v2 < v3;

  EXPECT_FALSE(vector_all(mask1));
}