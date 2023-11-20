#include <gtest/gtest.h>

#include "common/types.h"

TEST(PortableBool, ShouldConvertToBool)
{
  b8 val0 = true;
  EXPECT_TRUE(val0);

  val0 = false;
  EXPECT_FALSE(val0);

  b16 val1 = true;
  EXPECT_TRUE(val1);

  val1 = false;
  EXPECT_FALSE(val1);

  b32 val2 = true;
  EXPECT_TRUE(val2);

  val2 = false;
  EXPECT_FALSE(val2);

  b64 val3 = true;
  EXPECT_TRUE(val3);

  val3 = false;
  EXPECT_FALSE(val3);
}