#include <gtest/gtest.h>

#include "common/dictionary.h"

TEST(Dictionary, ShouldReturnValueIfFound)
{
  constexpr common::dictionary<const char*, int, 1> test_map =
  {
    { "test", 1 }
  };

  constexpr auto val = test_map.find("test");

  ASSERT_EQ(val, 1);
}

TEST(Dictionary, ShouldReturnNulloptIfNotFound)
{
  constexpr common::dictionary<const char*, int, 1> test_map =
  {
    { "test", 1 }
  };

  constexpr auto val = test_map.find("not_test");

  ASSERT_FALSE(val.has_value());
}

TEST(Dictionary, ShouldDoArrayAccess)
{
  constexpr common::dictionary<const char*, int, 2> test_map =
  {
    { "test",  1 },
    { "test2", 2 }
  };

  constexpr auto val = test_map["test2"];

  ASSERT_EQ(val, 2);
}