
#include <gtest/gtest.h>

#include <Hexagon/Testing/ClangBuildOutputResult.hpp>


TEST(Hexagon_Testing_ClangBuildOutputResultTest, can_be_created_without_blowing_up)
{
   Hexagon::Testing::ClangBuildOutputResult clang_build_output_result;
}


TEST(Hexagon_Testing_ClangBuildOutputResultTest,
   build_from_message_line__on_a_line_that_is_not_in_the_expected_format__will_throw_an_error)
{
   // TODO
}


TEST(Hexagon_Testing_ClangBuildOutputResultTest,
   build_from_message_line__will_parse_the_expected_values_from_the_message_line)
{
   std::string message_line = "tests/Hexagon/Testing/ClangBuildOutputParserTest.cpp:63:66: error: "
                              "'NUM_WARNINGS_ERRORS_GENERATED_REGEX' is a private member of "
                              "'Hexagon::Testing::ClangBuildOutputParser'";

   Hexagon::Testing::ClangBuildOutputResult built = 
      Hexagon::Testing::ClangBuildOutputResult::build_from_message_line(message_line);

   EXPECT_EQ(message_line, built.get_message_line());
   EXPECT_EQ(63, built.get_line_num());
   EXPECT_EQ(66, built.get_column_num());
   EXPECT_EQ("error", built.get_type());
}


