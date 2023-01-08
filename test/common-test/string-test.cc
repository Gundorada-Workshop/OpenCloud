#include <gtest/gtest.h>

#include "common/strings.h"

TEST(Strings, ShouldConvertToUppercaseUTF8)
{
  constexpr std::string_view test =
  {
    "test"
  };

  EXPECT_EQ(common::strings::uppercase(test), "TEST");
}

TEST(Strings, ShouldConvertToUppercaseUTF16)
{
  constexpr std::wstring_view test =
  {
    L"test"
  };

  EXPECT_EQ(common::strings::uppercase(test), L"TEST");
}

TEST(Strings, ShouldConvertToLowercaseUTF8)
{
  constexpr std::string_view test =
  {
    "TEST"
  };

  EXPECT_EQ(common::strings::lowercase(test), "test");
}

TEST(Strings, ShouldConvertToLowercaseUTF16)
{
  constexpr std::wstring_view test =
  {
    L"TEST"
  };

  EXPECT_EQ(common::strings::lowercase(test), L"test");
}