
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/SymbolUnderCursorMatcher.hpp>


TEST(Hexagon_AdvancedCodeEditor_SymbolUnderCursorMatcherTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::SymbolUnderCursorMatcher symbol_under_cursor_matcher;
}


TEST(Hexagon_AdvancedCodeEditor_SymbolUnderCursorMatcherTest, find_symbol_range__will)
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


