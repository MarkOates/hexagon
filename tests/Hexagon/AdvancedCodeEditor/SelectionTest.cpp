
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/Selection.hpp>
#include <Hexagon/Testing/Comparison/Hexagon/AdvancedCodeEditor/Selection.hpp>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


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
   EXPECT_EQ(CodePoint(32, 87), selection.find_next_from(32, 87));
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_next_from__finds_the_next_selection)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange{2, 0, 3, 0},
      CodeRange{3, 8, 4, 8},
      CodeRange{9, 19, 10, 19},
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   EXPECT_EQ(CodePoint(2, 0), selection.find_next_from(0, 0)); // on the same line
   EXPECT_EQ(CodePoint(3, 8), selection.find_next_from(4, 0)); // on a subsequent line
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

   EXPECT_EQ(CodePoint(3, 8), selection.find_next_from(2, 0)); // on the same line
   EXPECT_EQ(CodePoint(9, 19), selection.find_next_from(3, 8)); // on a subsequent line
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_next_from__when_beyond_the_last_selection__does_nothing)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange{2, 0, 3, 0},
      CodeRange{3, 8, 4, 8},
      CodeRange{9, 19, 10, 19},
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   EXPECT_EQ(CodePoint(10, 19), selection.find_next_from(10, 19)); // on the same line
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest,
   find_previous_from__with_no_code_ranges__returns_the_cursor_location_that_was_passed_location)
{
   std::vector<CodeRange> empty_code_ranges = {};
   Hexagon::AdvancedCodeEditor::Selection selection(empty_code_ranges);
   EXPECT_EQ(CodePoint(32, 87), selection.find_previous_from(32, 87));
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_previous_from__finds_the_previous_selection)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange{2, 0, 3, 0},
      CodeRange{3, 8, 4, 8},
      CodeRange{9, 19, 10, 19},
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   EXPECT_EQ(CodePoint(2, 0), selection.find_previous_from(4, 0)); // on the same line
   EXPECT_EQ(CodePoint(2, 0), selection.find_previous_from(4, 7)); // on a subsequent line
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest,
   find_previous_from__when_at_an_existing_selection_start__finds_the_previous_selection)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange{2, 0, 3, 0},
      CodeRange{3, 8, 4, 8},
      CodeRange{9, 19, 10, 19},
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   EXPECT_EQ(CodePoint(2, 0), selection.find_previous_from(3, 8)); // on the same line
   EXPECT_EQ(CodePoint(3, 8), selection.find_previous_from(9, 19)); // on a subsequent line
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest, find_previous_from__when_before_the_first_selection__does_nothing)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange{2, 1, 3, 1},
      CodeRange{3, 8, 4, 8},
      CodeRange{9, 19, 10, 19},
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   EXPECT_EQ(CodePoint(1, 0), selection.find_previous_from(1, 0)); // on the previous line
   EXPECT_EQ(CodePoint(1, 1), selection.find_previous_from(1, 1)); // on the same line
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest,
   push_down_from__will_move_code_points_down_that_are_at_or_below_a_starting_line)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange(2, 1, 3, 1),
      CodeRange(3, 8, 4, 8),
      CodeRange(9, 19, 10, 19),
      CodeRange(9, 20, 10, 20),
      CodeRange(9, 99, 10, 99),
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   selection.push_down_from(19, 3);

   std::vector<CodeRange> expected_moved_code_ranges = {
      CodeRange(2, 1, 3, 1),
      CodeRange(3, 8, 4, 8),
      CodeRange(9, 19+3, 10, 19+3),
      CodeRange(9, 20+3, 10, 20+3),
      CodeRange(9, 99+3, 10, 99+3),
   };

   EXPECT_EQ(expected_moved_code_ranges, selection.get_code_ranges());
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest,
   push_down_from__when_num_lines_to_push_down__is_negative__will_throw_an_error)
{
   // TODO
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest,
   pull_up_from__when_num_lines_to_pull_up_is_negative__will_throw_an_error)
{
   // TODO
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest,
   pull_up_from__will_move_code_points_up_that_are_at_or_below_a_starting_line)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange(2, 1, 3, 1),
      CodeRange(3, 8, 4, 8),
      CodeRange(9, 19, 10, 19),
      CodeRange(9, 20, 10, 20),
      CodeRange(9, 99, 10, 99),
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   selection.pull_up_from(19, 3);

   std::vector<CodeRange> expected_moved_code_ranges = {
      CodeRange(2, 1, 3, 1),
      CodeRange(3, 8, 4, 8),
      CodeRange(9, 19-3, 10, 19-3),
      CodeRange(9, 20-3, 10, 20-3),
      CodeRange(9, 99-3, 10, 99-3),
   };

   EXPECT_EQ(expected_moved_code_ranges, selection.get_code_ranges());
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest,
   pull_up_from__when_num_lines_to_pull_up_is_greater_than_the_number_of_available_lines_to_pull_up_will_error)
{
   Hexagon::AdvancedCodeEditor::Selection selection;
   std::string expected_message = "Selection::pull_up_from: error: guard \"(num_lines_to_pull_up <= "
                                  "starting_on_line)\" not met";
   EXPECT_THROW_WITH_MESSAGE(selection.pull_up_from(0, 1), std::runtime_error, expected_message);
   EXPECT_THROW_WITH_MESSAGE(selection.pull_up_from(10, 11), std::runtime_error, expected_message);
   EXPECT_THROW_WITH_MESSAGE(selection.pull_up_from(1, 999), std::runtime_error, expected_message);
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest,
   clear_select_lines__will_remove_ranges_that_intersect_with_the_line_indices)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange(2, 1, 3, 1),
      CodeRange(3, 8, 4, 8),
      CodeRange(9, 19, 10, 19),
      CodeRange(9, 20, 10, 20),
      CodeRange(9, 99, 10, 99),

      CodeRange(9, 108, 10, 110),
      CodeRange(9, 118, 10, 120),
      CodeRange(9, 128, 10, 130),
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);

   std::vector<int> line_indices_to_clear = { 8, 20, 108, 119, 130 };
   selection.clear_select_lines(line_indices_to_clear);

   std::vector<CodeRange> expected_result_code_ranges = {
      CodeRange(2, 1, 3, 1),
      CodeRange(9, 19, 10, 19),
      CodeRange(9, 99, 10, 99),
   };
   Hexagon::AdvancedCodeEditor::Selection expected_result_selection(expected_result_code_ranges);

   EXPECT_EQ(expected_result_selection, selection);
}


TEST(Hexagon_AdvancedCodeEditor_SelectionTest,
   clear_select_lines__will_ignore_line_indices_that_do_not_intersect_with_code_ranges)
{
   std::vector<CodeRange> code_ranges = {
      CodeRange(2, 1, 3, 1),
      CodeRange(3, 8, 4, 8),
      CodeRange(9, 19, 10, 19),
      CodeRange(9, 20, 10, 20),
      CodeRange(9, 99, 10, 99),
      CodeRange(9, 108, 10, 110),
      CodeRange(9, 118, 10, 120),
      CodeRange(9, 128, 10, 130),
   };
   Hexagon::AdvancedCodeEditor::Selection selection(code_ranges);
   std::vector<int> line_indices_to_clear = { 0, 7, 9, 18, 21, 50, 98, 107, 111, 117, 121, 127, 131, 999 };
   selection.clear_select_lines(line_indices_to_clear);

   EXPECT_EQ(code_ranges, selection.get_code_ranges());
}


