
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

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_next_from__finds_the_next_selection)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_next_from__when_at_a_selection_start__finds_the_next_selection)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_next_from__when_beyond_the_last_selection__does_nothing)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_previous_from__finds_the_previous_selection)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_previous_from__when_at_a_selection_start__finds_the_previous_selection)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_previous_from__when_before_the_first_selection__does_nothing)
{
   // TODO
}


