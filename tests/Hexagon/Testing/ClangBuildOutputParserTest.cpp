
#include <gtest/gtest.h>

#include <Hexagon/Testing/ClangBuildOutputParser.hpp>


#define TEST_FIXTURE_BUILD_DUMP_FOLDER "/Users/markoates/Repos/hexagon/tests/fixtures/data/builds/dumps/"


TEST(Hexagon_Testing_ClangBuildOutputParserTest, can_be_created_without_blowing_up)
{
   Hexagon::Testing::ClangBuildOutputParser clang_build_output_parser;
}


TEST(Hexagon_Testing_ClangBuildOutputParserTest, parse__DEV)
{
   //build_dump_with_duplicate_test_name.txt
   Hexagon::Testing::ClangBuildOutputParser clang_build_output_parser;
}


