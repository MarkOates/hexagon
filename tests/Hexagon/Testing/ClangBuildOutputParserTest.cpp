
#include <gtest/gtest.h>

#include <Hexagon/Testing/ClangBuildOutputParser.hpp>


#define TEST_FIXTURE_BUILD_DUMP_FOLDER "/Users/markoates/Repos/hexagon/tests/fixtures/data/builds/dumps/"
#define DUPLICATE_TEST_NAME \
         (TEST_FIXTURE_BUILD_DUMP_FOLDER "build_dump_with_duplicate_test_name.txt")


#include <fstream>
std::string file_get_contents(std::string filename)
{
   std::ifstream file(filename.c_str());
   std::string input = "";
   if (!file) return "";
   char ch;
   while (file.get(ch)) input.append(1, ch);
   if (!file.eof()) return ""; // strange error
   file.close();
   return input;
}


TEST(Hexagon_Testing_ClangBuildOutputParserTest, can_be_created_without_blowing_up)
{
   Hexagon::Testing::ClangBuildOutputParser clang_build_output_parser;
}


TEST(Hexagon_Testing_ClangBuildOutputParserTest, parse__DEV)
{
   std::string test_build_dump_with_duplicate_object_test_names = file_get_contents(DUPLICATE_TEST_NAME);
   Hexagon::Testing::ClangBuildOutputParser clang_build_output_parser;

   clang_build_output_parser.parse();

   EXPECT_EQ(true, clang_build_output_parser.get_error_messages_during_parsing().empty());
}


