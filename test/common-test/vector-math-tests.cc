#include <gtest/gtest.h>

#include "graph/vector.h"

TEST(VectorFloatMath, ShouldCalculateUnitVector)
{
  vec3 v{ 1.0f, 1.0f, 1.0f };

  auto res = graph::norm(v);

  EXPECT_FLOAT_EQ(res.data.a[0], 0.57735f);
  EXPECT_FLOAT_EQ(res.data.a[1], 0.57735f);
  EXPECT_FLOAT_EQ(res.data.a[2], 0.57735f);
}

TEST(VectorFloatMath, ShouldCalculateCrossProduct)
{
  vec3 v0{ 1.0f, 2.0f, 6.0f };
  vec3 v1{ 4.0f, 5.0f, 3.0f };

  auto res = graph::cross(v0, v1);

  EXPECT_FLOAT_EQ(res.data.a[0], -24.0f);
  EXPECT_FLOAT_EQ(res.data.a[1],  21.0f);
  EXPECT_FLOAT_EQ(res.data.a[2], -3.0f);
}

TEST(VectorFloatMath, ShouldCalculateMagnitude)
{
  vec3 v0{ -2.0f, 2.0f, 5.0f };

  EXPECT_FLOAT_EQ(graph::mag(v0), 5.744563f);
}

TEST(VectorFloatMath, ShouldCalculateDistance)
{
  vec3 v0{ -1.0f, 3.0f, 6.0f };
  vec3 v1{ 1.0f, 1.0f, 1.0f };

  EXPECT_FLOAT_EQ(graph::dist(v0, v1), 5.744563f);
}

TEST(VectorFloatMath, ShouldCalculateDotProduct)
{
  vec3 v0{ 1.0f, 2.0f, 3.0f };
  vec3 v1{ 1.0f, 5.0f, 7.0f };

  EXPECT_FLOAT_EQ(graph::dot(v0, v1), 32.0f);
}

TEST(VectorFloatMath, ShouldCalculateMax)
{
  vec3 v0{ 0.0f, 8.0f, 3.0f };
  vec3 v1{ 1.0f, 5.0f, 7.0f };

  const auto max = graph::max(v0, v1);

  EXPECT_FLOAT_EQ(max.data.a[0], 1.0f);
  EXPECT_FLOAT_EQ(max.data.a[1], 8.0f);
  EXPECT_FLOAT_EQ(max.data.a[2], 7.0f);

  vec3 v2{ 100.0f, 1.0f, 10.0f };

  const auto max_ilist = graph::max({ v0, v1, v2 });

  EXPECT_FLOAT_EQ(max_ilist.data.a[0], 100.0f);
  EXPECT_FLOAT_EQ(max_ilist.data.a[1], 8.0f);
  EXPECT_FLOAT_EQ(max_ilist.data.a[2], 10.0f);
}

TEST(VectorFloatMath, ShouldCalculateMin)
{
  vec3 v0{ 0.0f, 8.0f, 3.0f };
  vec3 v1{ 1.0f, 5.0f, 7.0f };

  const auto min = graph::min(v0, v1);

  EXPECT_FLOAT_EQ(min.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(min.data.a[1], 5.0f);
  EXPECT_FLOAT_EQ(min.data.a[2], 3.0f);

  vec3 v2{ 100.0f, 1.0f, 10.0f };

  const auto min_ilist = graph::min({ v0, v1, v2 });

  EXPECT_FLOAT_EQ(min_ilist.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(min_ilist.data.a[1], 1.0f);
  EXPECT_FLOAT_EQ(min_ilist.data.a[2], 3.0f);
}

TEST(VectorFloatMath, ShouldCalculateMinMax)
{
  vec3 v0{ 0.0f, 8.0f, 3.0f };
  vec3 v1{ 1.0f, 5.0f, 7.0f };

  const auto minmax = graph::minmax(v0, v1);

  const auto& min = minmax.first;
  const auto& max = minmax.second;

  EXPECT_FLOAT_EQ(min.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(min.data.a[1], 5.0f);
  EXPECT_FLOAT_EQ(min.data.a[2], 3.0f);

  EXPECT_FLOAT_EQ(max.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(max.data.a[1], 5.0f);
  EXPECT_FLOAT_EQ(max.data.a[2], 3.0f);

  vec3 v2{ 100.0f, 1.0f, 10.0f };

  const auto minmax_ilist = graph::minmax({ v0, v1, v2 });

  const auto& min_ilist = minmax_ilist.first;
  const auto& max_ilist = minmax_ilist.second;

  EXPECT_FLOAT_EQ(max_ilist.data.a[0], 100.0f);
  EXPECT_FLOAT_EQ(max_ilist.data.a[1], 8.0f);
  EXPECT_FLOAT_EQ(max_ilist.data.a[2], 10.0f);

  EXPECT_FLOAT_EQ(min_ilist.data.a[0], 0.0f);
  EXPECT_FLOAT_EQ(min_ilist.data.a[1], 1.0f);
  EXPECT_FLOAT_EQ(min_ilist.data.a[2], 3.0f);
}