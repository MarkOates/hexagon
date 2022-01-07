
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/Selection.hpp>

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::Selection selection;
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, selection__is_a_constructor_arg_and_has_a_getter)
{
   std::vector<CodeRange> code_ranges = { CodeRange{4, 5, 10, 6} };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   EXPECT_EQ(code_ranges, selection.get_code_ranges());
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest,
   find_next_from__with_no_code_ranges__returns_the_cursor_location_that_was_passed_location)
{
   std::vector<CodeRange> empty_code_ranges = {};
   Hexagon::AdvancedCodeEditor::Selection selection(empty_code_ranges);
   ASSERT_EQ(CodePoint(32, 87), selection.find_next_from(32, 87));
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_next_from__finds_the_next_selection)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange{2, 0, 3, 0},
      CodeRange{3, 8, 4, 8},
      CodeRange{9, 19, 10, 19},
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   ASSERT_EQ(CodePoint(2, 0), selection.find_next_from(0, 0)); // on the same line
   ASSERT_EQ(CodePoint(3, 8), selection.find_next_from(4, 0)); // on a subsequent line
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest,
   find_next_from__when_at_an_existing_selections_start__finds_the_next_selection)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange{2, 0, 3, 0},
      CodeRange{3, 8, 4, 8},
      CodeRange{9, 19, 10, 19},
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   ASSERT_EQ(CodePoint(3, 8), selection.find_next_from(2, 0)); // on the same line
   ASSERT_EQ(CodePoint(9, 19), selection.find_next_from(3, 8)); // on a subsequent line
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_next_from__when_beyond_the_last_selection__does_nothing)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange{2, 0, 3, 0},
      CodeRange{3, 8, 4, 8},
      CodeRange{9, 19, 10, 19},
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   ASSERT_EQ(CodePoint(10, 19), selection.find_next_from(10, 19)); // on the same line
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_previous_from__finds_the_previous_selection)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange{2, 0, 3, 0},
      CodeRange{3, 8, 4, 8},
      CodeRange{9, 19, 10, 19},
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   ASSERT_EQ(CodePoint(2, 0), selection.find_previous_from(4, 0)); // on the same line
   ASSERT_EQ(CodePoint(2, 0), selection.find_previous_from(4, 7)); // on a subsequent line
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_previous_from__when_at_a_selection_start__finds_the_previous_selection)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_previous_from__when_before_the_first_selection__does_nothing)
{
   // TODO
}


