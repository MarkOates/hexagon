
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/Selection.hpp>

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::Selection selection;
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, selection__is_a_constructor_arg_and_has_a_getter)
{
   std::vector<CodeRange> code_range = { CodeRange{4, 5, 10, 6} };
   Hexagon::AdvancedCodeEditor::Selection selection(code_range);

   EXPECT_EQ(code_range, selection.get_code_ranges());
}
