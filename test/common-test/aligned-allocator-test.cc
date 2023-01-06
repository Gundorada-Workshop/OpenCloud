#include <gtest/gtest.h>

#include <vector>

#include "common/types.h"
#include "common/aligned_allocator.h"

TEST(AlignedAllocator, ShouldWorkWithVectors)
{
  std::vector<sint, common::simd_allocator<sint>> test;

  test.push_back(10);

  EXPECT_EQ(test[0], 10);
}