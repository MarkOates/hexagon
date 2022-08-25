
#include <gtest/gtest.h>

#include <Hexagon/Testing/ClangBuildOutputParser.hpp>


#define TEST_FIXTURE_BUILD_DUMP_FOLDER "/Users/markoates/Repos/hexagon/tests/fixtures/data/builds/dumps/"
#define DUPLICATE_TEST_NAME \
         (TEST_FIXTURE_BUILD_DUMP_FOLDER "component_test_object_1.txt")


#include <Hexagon/RegexMatcher.hpp>


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


TEST(Hexagon_Testing_ClangBuildOutputParserTest, parse__will_extract_the_num_warnings_errors_generated_line)
{
   std::string test_build_dump_with_duplicate_object_test_names = file_get_contents(DUPLICATE_TEST_NAME);
   Hexagon::Testing::ClangBuildOutputParser clang_build_output_parser(test_build_dump_with_duplicate_object_test_names);
   clang_build_output_parser.parse();
   EXPECT_EQ("3 errors generated.", clang_build_output_parser.get_num_warnings_errors_generated_line());
}


TEST(Hexagon_Testing_ClangBuildOutputParserTest, parse__will_extract_the_warnings_errors_and_notes)
{
   std::string test_build_dump_with_duplicate_object_test_names = file_get_contents(DUPLICATE_TEST_NAME);
   Hexagon::Testing::ClangBuildOutputParser clang_build_output_parser(test_build_dump_with_duplicate_object_test_names);
   clang_build_output_parser.parse();

   std::vector<Hexagon::Testing::ClangBuildOutputResult> warnings_errors_and_notes = 
      clang_build_output_parser.get_warnings_errors_and_notes();

   EXPECT_EQ(26, warnings_errors_and_notes.size());
}


TEST(Hexagon_Testing_ClangBuildOutputParserTest, NUM_WARNINGS_ERRORS_GENERATED_REGEX__will_match_valid_lines)
{
   std::vector<std::string> valid_warnings_errors_lines = {
      "2 warnings generated.",
      "1 error generated.",
      "3 errors generated.",
      "1 warning and 2 errors generated.",
      "3 warnings and 1 error generated.",
   };

   std::string regex = Hexagon::Testing::ClangBuildOutputParser::get_NUM_WARNINGS_ERRORS_GENERATED_REGEX();
   for (auto &valid_warnings_errors_line : valid_warnings_errors_lines)
   {
      RegexMatcher matcher(valid_warnings_errors_line, regex);
      std::vector<std::pair<int, int>> match_info = matcher.get_match_info();
   
      EXPECT_EQ(1, match_info.size());
   }
}


