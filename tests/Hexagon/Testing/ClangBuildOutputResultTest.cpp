
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
   // TODO
}


