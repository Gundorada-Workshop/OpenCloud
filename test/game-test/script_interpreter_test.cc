#include <string>

#include <gtest/gtest.h>

#include "dc2/script_interpreter.h"

class input_strTest : public ::testing::Test {
protected:
  void SetUp() override {
    new (&input) input_str();
  }

  input_str input{};
};

TEST_F(input_strTest, GetLine)
{
  char buf[0x1000];
  strcpy_s(buf, sizeof(buf) / sizeof(char), "\
WEPNUM 112;\r\n\
WEP 36,32;\r\n\
WEP_ST 8,10;\r\n\
WEP_ST_L 20,19;\r\n\
WEP_ST2 2,0,0,0, 5 ,0,0,0;\r\n\
WEP_ST2_L 19,19,19,19,19,19,19,19;\r\n\
WEP_SPE 1,0,0,2,0;\r\n\
WEP_BUILD 2,90,0;\r\n\
");
  input.m_string = buf;
  input.m_position = 0;
  input.m_length = input.m_string.length();

  std::string line1;
  std::string line2;
  std::string line3;
  std::string line4;
  std::string line5;
  std::string line6;
  std::string line7;
  std::string line8;
  std::string line9;

  EXPECT_TRUE(input.GetLine(line1));
  EXPECT_TRUE(input.GetLine(line2));
  EXPECT_TRUE(input.GetLine(line3));
  EXPECT_TRUE(input.GetLine(line4));
  EXPECT_TRUE(input.GetLine(line5));
  EXPECT_TRUE(input.GetLine(line6));
  EXPECT_TRUE(input.GetLine(line7));
  EXPECT_TRUE(input.GetLine(line8));
  EXPECT_FALSE(input.GetLine(line9));

  EXPECT_EQ("WEPNUM 112;", line1);
  EXPECT_EQ("WEP 36,32;", line2);
  EXPECT_EQ("WEP_ST 8,10;", line3);
  EXPECT_EQ("WEP_ST_L 20,19;", line4);
  EXPECT_EQ("WEP_ST2 2,0,0,0, 5 ,0,0,0;", line5);
  EXPECT_EQ("WEP_ST2_L 19,19,19,19,19,19,19,19;", line6);
  EXPECT_EQ("WEP_SPE 1,0,0,2,0;", line7);
  EXPECT_EQ("WEP_BUILD 2,90,0;", line8);
}

static bool spi_test1_bool;
static sint spi_test1_sint;
static float spi_test1_float;
static std::string spi_test1_string;

static bool TEST1(SPI_STACK* stack, int stack_count)
{
  spi_test1_bool = static_cast<bool>(spiGetStackInt(stack++));
  spi_test1_sint = spiGetStackInt(stack++);
  spi_test1_float = spiGetStackFloat(stack++);
  spi_test1_string = std::string(spiGetStackString(stack++));
  return true;
}

static sint spi_test2_sint;

static bool TEST2(SPI_STACK* stack, int stack_count)
{
  spi_test2_sint = spiGetStackInt(stack++);
  return true;
}

static const SPI_TAG_PARAM test_tag[] =
{
  "TEST1",  TEST1,
  "TEST2",  TEST2,
  NULL, nullptr
};

class CScriptInterpreterTest : public ::testing::Test {
protected:

};

TEST_F(CScriptInterpreterTest, Run)
{
  char buf[0x1000];
  strcpy_s(buf, sizeof(buf) / sizeof(char), "\
TEST1 1, 200, 735.2, \"HELLO WORLD!\";\r\n\
TEST2 400;\r\n\
");
  
  CScriptInterpreter script_interpreter{};
  script_interpreter.SetScript(buf, strlen(buf));
  script_interpreter.SetTag(test_tag);
  script_interpreter.Run();

  EXPECT_TRUE(spi_test1_bool);
  EXPECT_EQ(spi_test1_sint, 200);
  EXPECT_FLOAT_EQ(spi_test1_float, 735.2);
  EXPECT_EQ(spi_test1_string, "HELLO WORLD!");
  EXPECT_EQ(spi_test2_sint, 400);
}

TEST_F(CScriptInterpreterTest, ShouldIgnoreSpecialCharactersInStrings)
{
  char buf[0x1000];
  strcpy_s(buf, sizeof(buf) / sizeof(char), "\
TEST1 0, 123, 3.14, \"Hallo! ,;\\\" whoops that shouldn't break the script either\";\r\n\
");

  CScriptInterpreter script_interpreter{};
  script_interpreter.SetScript(buf, strlen(buf));
  script_interpreter.SetTag(test_tag);
  script_interpreter.Run();

  EXPECT_FALSE(spi_test1_bool);
  EXPECT_EQ(spi_test1_sint, 123);
  EXPECT_FLOAT_EQ(spi_test1_float, 3.14);
  EXPECT_EQ(spi_test1_string, "Hallo! ,;\" whoops that shouldn't break the script either");
}

TEST_F(CScriptInterpreterTest, ShouldIgnoreComments)
{
  char buf[0x1000];
  strcpy_s(buf, sizeof(buf) / sizeof(char), "\
//Hi, here's my first script!\r\n\
//Look at this \"TEST2 555;\" command, it should set a variable to 555\r\n\
TEST2 555;\r\n\
/*\r\n\
  And this command is a bit more complicated, but it should set \r\n\
  multiple variables, if everything works correctly. \r\n\
*/\r\n\
TEST1 0, 123, 3.14, \"Is this thing working?\";\r\n\
");

  CScriptInterpreter script_interpreter{};
  script_interpreter.SetScript(buf, strlen(buf));
  script_interpreter.SetTag(test_tag);
  script_interpreter.Run();

  EXPECT_EQ(spi_test2_sint, 555);

  EXPECT_FALSE(spi_test1_bool);
  EXPECT_EQ(spi_test1_sint, 123);
  EXPECT_FLOAT_EQ(spi_test1_float, 3.14);
  EXPECT_EQ(spi_test1_string, "Is this thing working?");
}

TEST_F(CScriptInterpreterTest, ShouldConvertFromShiftJIS)
{
  char buf[0x1000];
  strcpy_s(buf, sizeof(buf) / sizeof(char), 
    "TEST1 0, 123, 3.14, \"\x32\x8F\xCD\x82\xA9\x82\xE7\";\r\n"
);

  CScriptInterpreter script_interpreter{};
  script_interpreter.SetScript(buf, strlen(buf));
  script_interpreter.SetTag(test_tag);
  script_interpreter.Run();

  EXPECT_FALSE(spi_test1_bool);
  EXPECT_EQ(spi_test1_sint, 123);
  EXPECT_FLOAT_EQ(spi_test1_float, 3.14);
  EXPECT_EQ(spi_test1_string, "2章から");
}

TEST_F(CScriptInterpreterTest, ShouldNotConvertWhenUTF8EncodingSpecified)
{
  char buf[0x1000];
  strcpy_s(buf, sizeof(buf) / sizeof(char),
    "// This is a comment\r\n"
    "\r\n"
    "encoding utf-8;\r\n"
    "TEST1 1, 124, 3.15, \"これはＵTF8がなくてはならない\";\r\n"
  );

  CScriptInterpreter script_interpreter{};
  script_interpreter.SetScript(buf, strlen(buf));
  script_interpreter.SetTag(test_tag);
  script_interpreter.Run();

  EXPECT_TRUE(spi_test1_bool);
  EXPECT_EQ(spi_test1_sint, 124);
  EXPECT_FLOAT_EQ(spi_test1_float, 3.15);
  EXPECT_EQ(spi_test1_string, "これはＵTF8がなくてはならない");
}
