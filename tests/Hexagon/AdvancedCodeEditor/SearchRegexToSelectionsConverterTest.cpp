
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/SearchRegexToSelectionsConverter.hpp>

TEST(Hexagon_AdvancedCodeEditor_SearchRegexToSelectionsConverterTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::SearchRegexToSelectionsConverter search_regex_to_selections_converter;
}

TEST(Hexagon_AdvancedCodeEditor_SearchRegexToSelectionsConverterTest,
   convert__will_create_the_expected_selections)
{
   std::string search_regex_string = "foobar";
   std::vector<std::string> lines = {};
   Hexagon::AdvancedCodeEditor::SearchRegexToSelectionsConverter converter(search_regex_string, lines);

   std::vector<CodeRange> expected = converter.convert();
   std::vector<CodeRange> actual = {};
 
   EXPECT_EQ(expected, actual);
}

