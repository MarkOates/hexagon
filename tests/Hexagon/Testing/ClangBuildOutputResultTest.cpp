
#include <gtest/gtest.h>

#include <Hexagon/Testing/ClangBuildOutputResult.hpp>


TEST(Hexagon_Testing_ClangBuildOutputResultTest, can_be_created_without_blowing_up)
{
   Hexagon::Testing::ClangBuildOutputResult clang_build_output_result;
}


TEST(Hexagon_Testing_ClangBuildOutputResultTest, run__returns_the_expected_response)
{
   Hexagon::Testing::ClangBuildOutputResult clang_build_output_result;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, clang_build_output_result.run());
}

