
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/SymbolUnderCursorMatcher.hpp>


TEST(Hexagon_AdvancedCodeEditor_SymbolUnderCursorMatcherTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher symbol_under_cursor_matcher;
}


TEST(Hexagon_AdvancedCodeEditor_SymbolUnderCursorMatcherTest,
   find_symbol_range__will_match_a_symbol_positions_under_cursor)
{
   Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher symbol_under_cursor_matcher;

   std::string code = "This::is_a_Example123_code";
   int cursor_position = 9; // Cursor is over 'i' in 'is'

   std::pair<int, int> symbol_range = symbol_under_cursor_matcher.find_symbol_range(code, cursor_position);
   int start_position = symbol_range.first;
   int end_position = symbol_range.second;

   EXPECT_EQ(0, start_position);
   EXPECT_EQ(25, end_position);
}


TEST(Hexagon_AdvancedCodeEditor_SymbolUnderCursorMatcherTest,
   find_symbol_range__when_the_cursor_is_out_of_range__will_return_NO_MATCH_FOUND)
{
   Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher symbol_under_cursor_matcher;

   std::vector<std::tuple<std::string, int, std::pair<int, int>>> test_data = {
      { "This::is_a_Example123_code", -1,  Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher::NO_MATCH_FOUND },
      { "This::is_a_Example123_code", -99, Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher::NO_MATCH_FOUND },
      { "This::is_a_Example123_code", 999, Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher::NO_MATCH_FOUND },
      { "This::is_a_Example123_code",  27, Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher::NO_MATCH_FOUND },
   };

   for (auto &test_datum : test_data)
   {
      std::string code = std::get<0>(test_datum);
      int cursor_position = std::get<1>(test_datum);
      std::pair<int, int> expected_result = std::get<2>(test_datum);

      Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher symbol_under_cursor_matcher;
      std::pair<int, int> actual_result = symbol_under_cursor_matcher.find_symbol_range(code, cursor_position);

      EXPECT_EQ(expected_result, actual_result);
   }
}


TEST(Hexagon_AdvancedCodeEditor_SymbolUnderCursorMatcherTest,
   find_symbol_range__when_the_is_over_a_valid_symbol__will_return_the_ranges_of_the_symbol)
{
   Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher symbol_under_cursor_matcher;

   std::vector<std::tuple<std::string, int, std::pair<int, int>>> test_data = {
      { "if (This::Is::A::Symbol) > ", 12, { 4, 22 } },
      //{ "This::is_a_Example123_code", -99, Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher::NO_MATCH_FOUND },
      //{ "This::is_a_Example123_code", 999, Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher::NO_MATCH_FOUND },
      //{ "This::is_a_Example123_code",  27, Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher::NO_MATCH_FOUND },
   };

   for (auto &test_datum : test_data)
   {
      std::string code = std::get<0>(test_datum);
      int cursor_position = std::get<1>(test_datum);
      std::pair<int, int> expected_result = std::get<2>(test_datum);

      Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher symbol_under_cursor_matcher;
      std::pair<int, int> actual_result = symbol_under_cursor_matcher.find_symbol_range(code, cursor_position);

      EXPECT_EQ(expected_result, actual_result);
   }
}


