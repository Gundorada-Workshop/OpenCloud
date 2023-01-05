#include <gtest/gtest.h>

#include "graph/vector.h"
#include "graph/_vector/_vector_math.h"

using namespace graph;

TEST(VectorFloatMath, ShouldCalculateUnitVector)
{
  vector<f32, 3> v{ 1.0f, 1.0f, 1.0f };

  auto res = vector_normalize(v);

  EXPECT_FLOAT_EQ(res.data.a[0], 0.57735f);
  EXPECT_FLOAT_EQ(res.data.a[1], 0.57735f);
  EXPECT_FLOAT_EQ(res.data.a[2], 0.57735f);
}

TEST(VectorFloatMath, ShouldCalculateCrossProduct)
{
  vector<f32, 3> v0{ 1.0f, 2.0f, 6.0f };
  vector<f32, 3> v1{ 4.0f, 5.0f, 3.0f };

  auto res = vector_cross_product(v0, v1);

  EXPECT_FLOAT_EQ(res.data.a[0], -24.0f);
  EXPECT_FLOAT_EQ(res.data.a[1],  21.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], -3.0f);
}

TEST(VectorFloatMath, ShouldCalculateMagnitude)
{
  vector<f32, 3> v0{ -2.0f, 2.0f, 5.0f };

  EXPECT_FLOAT_EQ(vector_magnitude(v0), 5.744563f);
}

TEST(VectorFloatMath, ShouldCalculateDistance)
{
  vector<f32, 3> v0{ -1.0f, 3.0f, 6.0f };
  vector<f32, 3> v1{ 1.0f, 1.0f, 1.0f };

  EXPECT_FLOAT_EQ(vector_distance(v0, v1), 5.744563f);
}

TEST(VectorFloatMath, ShouldCalculateDotProduct)
{
  vector<f32, 3> v0{ 1.0f, 2.0f, 3.0f };
  vector<f32, 3> v1{ 1.0f, 5.0f, 7.0f };

  EXPECT_FLOAT_EQ(vector_dot_product(v0, v1), 32.0f);
}

TEST(VectorFloatMath, ShouldCalculateMax)
{
  vector<f32, 3> v0{ 0.0f, 8.0f, 3.0f };
  vector<f32, 3> v1{ 1.0f, 5.0f, 7.0f };

  const auto max = vector_max(v0, v1);

  EXPECT_FLOAT_EQ(max.data.a[0], 1.0f);
  EXPECT_FLOAT_EQ(max.data.a[1], 8.0f);
  EXPECT_FLOAT_EQ(max.data.a[2], 7.0f);

  vector<f32, 3> v2{ 100.0f, 1.0f, 10.0f };

  const auto max_ilist = vector_max({ v0, v1, v2 });

  EXPECT_FLOAT_EQ(max_ilist.data.a[0], 100.0f);
  EXPECT_FLOAT_EQ(max_ilist.data.a[1], 8.0f);
  EXPECT_FLOAT_EQ(max_ilist.data.a[2], 10.0f);
}

TEST(VectorFloatMath, ShouldCalculateMin)
{
  vector<f32, 3> v0{ 0.0f, 8.0f, 3.0f };
  vector<f32, 3> v1{ 1.0f, 5.0f, 7.0f };

  const auto min = vector_min(v0, v1);

  EXPECT_FLOAT_EQ(min.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(min.data.a[1], 5.0f);
  EXPECT_FLOAT_EQ(min.data.a[2], 3.0f);

  vector<f32, 3> v2{ 100.0f, 1.0f, 10.0f };

  const auto min_ilist = vector_min({ v0, v1, v2 });

  EXPECT_FLOAT_EQ(min_ilist.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(min_ilist.data.a[1], 1.0f);
  EXPECT_FLOAT_EQ(min_ilist.data.a[2], 3.0f);
}

TEST(VectorFloatMath, ShouldCalculateMinMax)
{
  vector<f32, 3> v0{ 0.0f, 8.0f, 3.0f };
  vector<f32, 3> v1{ 1.0f, 5.0f, 7.0f };

  const auto minmax = vector_minmax(v0, v1);

  const auto& min = minmax.first;
  const auto& max = minmax.second;

  EXPECT_FLOAT_EQ(min.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(min.data.a[1], 5.0f);
  EXPECT_FLOAT_EQ(min.data.a[2], 3.0f);

  EXPECT_FLOAT_EQ(max.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(max.data.a[1], 5.0f);
  EXPECT_FLOAT_EQ(max.data.a[2], 3.0f);

  vector<f32, 3> v2{ 100.0f, 1.0f, 10.0f };

  const auto minmax_ilist = vector_minmax({ v0, v1, v2 });

  const auto& min_ilist = minmax_ilist.first;
  const auto& max_ilist = minmax_ilist.second;

  EXPECT_FLOAT_EQ(max_ilist.data.a[0], 100.0f);
  EXPECT_FLOAT_EQ(max_ilist.data.a[1], 8.0f);
  EXPECT_FLOAT_EQ(max_ilist.data.a[2], 10.0f);

  EXPECT_FLOAT_EQ(min_ilist.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(min_ilist.data.a[1], 1.0f);
  EXPECT_FLOAT_EQ(min_ilist.data.a[2], 3.0f);
}