
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/AdvancedCodeEditor/AdvancedCodeEditor.hpp>

using ::testing::UnorderedElementsAreArray;
using ::testing::IsSubsetOf;

static std::string FIXTURE_PASSAGE = R"PASSAGE(       - 64 -
Act without doing;
work without effort.
Think of the small as large
and the few as many.
Confront the difficult
while it is still easy;
accomplish the great task
by a series of small acts.

The Master never reaches for the great;
thus she achieves greatness.
When she runs into a difficulty,
she stops and gives herself to it.
She doesn't cling to her own comfort;
thus problems are no problem for her.
)PASSAGE";

const std::string SONNET_TEXT = R"END(Sonnet 15

When I consider every thing that grows
Holds in perfection but a little moment.
That this huge stage presenteth nought but shows
Whereon the stars in secret influence comment.
When I perceive that men as plants increase,
Cheered and checked even by the self-same sky:
Vaunt in their youthful sap, at height decrease,
And wear their brave state out of memory.
Then the conceit of this inconstant stay,
Sets you most rich in youth before my sight,
Where wasteful time debateth with decay
To change your day of youth to sullied night,
And all in war with Time for love of you,
As he takes from you, I engraft you new.)END";

const std::string SIMPLE_PASSAGE = R"END(        - 9 -
Fill your bowl to the brim
and it will spill.
Keep sharpening your knife
and it will blunt.
Chase after money and security
and your heart will never unclench.
Care about people's approval
and you will be their prisoner.

Do your work, then step back.
The only path to serenity.)END";

const std::string PARABLE = R"END("What is this?"

"This is the union
of the before
and the after.")END";

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest, set_content__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content();
   SUCCEED();
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest, set_content__with_an_argument__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content("HELLO, WORLD!");
   SUCCEED();
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest, set_content__will_set_the_dirty_cells_with_the_expected_values)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content("Hi,\nworld!");

   std::vector<std::pair<int, int>> expected = {
      { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, { 4, 1 }, { 5, 1 },
   };
   std::vector<std::pair<int, int>> actual = advanced_code_editor.get_dirty_cells();
   ASSERT_THAT(expected, UnorderedElementsAreArray(actual));
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   set_content__will_include_previous_content_cells_in_addition_to_the_newly_set_cells)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content("Hi,\nworld!");
   advanced_code_editor.set_content("Hello,\n\nSam!");

   std::vector<std::pair<int, int>> expected = {
      { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 },
      { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, { 4, 1 }, { 5, 1 },
      { 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 },
   };
   std::vector<std::pair<int, int>> actual = advanced_code_editor.get_dirty_cells();
   ASSERT_THAT(expected, UnorderedElementsAreArray(actual));
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   cursor_jump_to_next_word__when_the_cursor_is_out_of_bounds__does_nothing_and_returns_false)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;

   advanced_code_editor.cursor_move_to(-5, -2);

   ASSERT_EQ(false, advanced_code_editor.cursor_jump_to_next_word());
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   cursor_jump_to_next_word__will_move_the_cursor_to_the_first_character_of_the_next_word_boundry)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   std::vector<int> expected_jump_points = { 5, 7, 16, 22, 28, 33 };

   advanced_code_editor.cursor_move_to(0, 2);

   for (unsigned i=0; i<expected_jump_points.size(); i++)
   {
      ASSERT_EQ(true, advanced_code_editor.cursor_jump_to_next_word());
      EXPECT_EQ(advanced_code_editor.cursor_get_x(), expected_jump_points[i]);
   }
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   cursor_jump_to_next_word_or_last_char__will_move_the_cursor_to_the_last_char)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   std::vector<int> expected_jump_points = { 5, 7, 16, 22, 28, 33, 37 };

   advanced_code_editor.cursor_move_to(0, 2);

   for (unsigned i=0; i<expected_jump_points.size(); i++)
   {
      ASSERT_EQ(true, advanced_code_editor.cursor_jump_to_next_word_or_last_char());
      EXPECT_EQ(advanced_code_editor.cursor_get_x(), expected_jump_points[i]);
   }
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   cursor_jump_to_previous_word__when_the_cursor_is_out_of_bounds__does_nothing_and_returns_false)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;

   advanced_code_editor.cursor_move_to(-5, -2);

   ASSERT_EQ(false, advanced_code_editor.cursor_jump_to_previous_word());
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   cursor_jump_to_previous_word__will_move_the_cursor_to_the_first_character_of_the_previous_word_boundry)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   std::vector<int> expected_jump_points = { 43, 39, 32, 21, 15, 10, 5, 0 };

   advanced_code_editor.cursor_move_to(45, 4);

   for (unsigned i=0; i<expected_jump_points.size(); i++)
   {
      ASSERT_EQ(true, advanced_code_editor.cursor_jump_to_previous_word());
      EXPECT_EQ(advanced_code_editor.cursor_get_x(), expected_jump_points[i]);
   }
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest, cursor_move_left__will_move_the_cursor_left_and_return_true)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   advanced_code_editor.cursor_move_to(45, 4);

   EXPECT_EQ(true, advanced_code_editor.cursor_move_left());
   EXPECT_EQ(44, advanced_code_editor.cursor_get_x());
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   cursor_move_left__will_not_move_left_if_at_or_past_the_left_edge_of_the_editor_and_return_false)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   advanced_code_editor.cursor_move_to(0, 4);

   EXPECT_EQ(false, advanced_code_editor.cursor_move_left());
   EXPECT_EQ(0, advanced_code_editor.cursor_get_x());

   advanced_code_editor.cursor_move_to(-5, 4);

   EXPECT_EQ(false, advanced_code_editor.cursor_move_left());
   EXPECT_EQ(-5, advanced_code_editor.cursor_get_x());
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest, cursor_move_up__will_move_the_cursor_up_and_return_true)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   advanced_code_editor.cursor_move_to(45, 4);

   EXPECT_EQ(true, advanced_code_editor.cursor_move_up());
   EXPECT_EQ(3, advanced_code_editor.cursor_get_y());
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   cursor_move_up__will_not_move_up_if_at_or_past_the_top_edge_of_the_editor_and_return_false)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   advanced_code_editor.cursor_move_to(45, 0);

   EXPECT_EQ(false, advanced_code_editor.cursor_move_up());
   EXPECT_EQ(0, advanced_code_editor.cursor_get_y());

   advanced_code_editor.cursor_move_to(45, -6);

   EXPECT_EQ(false, advanced_code_editor.cursor_move_up());
   EXPECT_EQ(-6, advanced_code_editor.cursor_get_y());
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest, cursor_move_down__will_move_the_cursor_down_and_will_return_true)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   advanced_code_editor.cursor_move_to(45, 5);

   EXPECT_EQ(true, advanced_code_editor.cursor_move_down());
   EXPECT_EQ(6, advanced_code_editor.cursor_get_y());
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   cursor_move_down__if_at_or_past_the_bottom_edge_of_the_editor__will_not_move_the_cursor_and_will_return_false)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   int last_line_num = advanced_code_editor.get_num_lines();
   advanced_code_editor.cursor_move_to(45, last_line_num);

   EXPECT_EQ(false, advanced_code_editor.cursor_move_down());
   EXPECT_EQ(last_line_num, advanced_code_editor.cursor_get_y());
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest, DISABLED__cursor_move_down__when_above_the_boundary__will_move_down)
{
   // TRUE
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest, DISABLED__cursor_move_up__when_below_the_boundary__will_move_up)
{
   // TRUE
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   cursor_move_to_end_of_line__will_move_the_cursor_to_the_last_character_on_the_line)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   advanced_code_editor.cursor_move_to(11, 4);
   ASSERT_EQ(true, advanced_code_editor.cursor_move_to_end_of_line());
   EXPECT_EQ(47, advanced_code_editor.cursor_get_x());

   advanced_code_editor.cursor_move_up();
   ASSERT_EQ(true, advanced_code_editor.cursor_move_to_end_of_line());
   EXPECT_EQ(39, advanced_code_editor.cursor_get_x());

   advanced_code_editor.cursor_move_up();
   ASSERT_EQ(true, advanced_code_editor.cursor_move_to_end_of_line());
   EXPECT_EQ(37, advanced_code_editor.cursor_get_x());
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   cursor_move_to_end_of_line__on_an_empty_line__will_move_the_cursor_horizontally_to_0)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   advanced_code_editor.cursor_move_to(3, 1);
   ASSERT_EQ(true, advanced_code_editor.cursor_move_to_end_of_line());
   EXPECT_EQ(0, advanced_code_editor.cursor_get_x());
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   cursor_move_to_end_of_line__when_the_cursor_is_vertically_out_of_bounds__will_move_the_cursor_horizontally_to_0)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   std::vector<std::pair<int, int>> out_of_bounds_positions = {
      { 2, -999 }, { 2, -1 }, { 5, 16 }, { 999, 999 },
   };

   for (auto &out_of_bounds_position : out_of_bounds_positions)
   {
      advanced_code_editor.cursor_move_to(out_of_bounds_position.first, out_of_bounds_position.second);
      ASSERT_EQ(true, advanced_code_editor.cursor_move_to_end_of_line());
      EXPECT_EQ(0, advanced_code_editor.cursor_get_x());
   }
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   cursor_move_to_end_of_line__when_the_cursor_is_horizontally_out_of_bounds__will_move_the_cursor_to_the_end_of_line)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   advanced_code_editor.cursor_move_to(999, 6);
   ASSERT_EQ(true, advanced_code_editor.cursor_move_to_end_of_line());
   EXPECT_EQ(43, advanced_code_editor.cursor_get_x());

   advanced_code_editor.cursor_move_to(-1, 7);
   ASSERT_EQ(true, advanced_code_editor.cursor_move_to_end_of_line());
   EXPECT_EQ(45, advanced_code_editor.cursor_get_x());

   advanced_code_editor.cursor_move_to(-999, 8);
   ASSERT_EQ(true, advanced_code_editor.cursor_move_to_end_of_line());
   EXPECT_EQ(47, advanced_code_editor.cursor_get_x());
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest, cursor_move_to_first_non_whitespace_character)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest, delete_to_end_of_line__will_remove_the_expected_characters)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   split_lines__will_split_a_single_line_to_two_sliced_at_the_cursor)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(FIXTURE_PASSAGE);

   std::vector<std::string> lines;

   lines = advanced_code_editor.get_lines();
   ASSERT_EQ(16, lines.size());

   advanced_code_editor.cursor_move_to(11, 4);
   ASSERT_EQ(true, advanced_code_editor.split_lines());

   lines = advanced_code_editor.get_lines();
   ASSERT_EQ(17, lines.size());

   std::string expected_current_line = "and the few";
   std::string actual_current_line = lines[4];
   ASSERT_EQ(expected_current_line, actual_current_line);

   std::string expected_next_line = " as many.";
   std::string actual_next_line = lines[5];
   ASSERT_EQ(expected_next_line, actual_next_line);
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   join_lines__on_a_line_number_that_is_out_of_bounds__does_nothing_and_returns_false)
{
   std::vector<std::string> original_lines, lines;
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(FIXTURE_PASSAGE);

   original_lines = advanced_code_editor.get_lines();

   int line_numbers_to_test[] = { -1, (int)(original_lines.size()+10), -10, };

   for (auto &line_number_to_test : line_numbers_to_test)
   {
      advanced_code_editor.cursor_move_to(0, line_number_to_test);

      ASSERT_EQ(false, advanced_code_editor.join_lines());

      lines = advanced_code_editor.get_lines();
      ASSERT_EQ(lines, original_lines);
   }
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   delete_line__removes_the_current_line)
{
   std::vector<std::string> lines;
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SONNET_TEXT);

   lines = advanced_code_editor.get_lines();
   EXPECT_EQ(16, lines.size());

   advanced_code_editor.cursor_set_y(9);

   ASSERT_EQ(true, advanced_code_editor.delete_line());

   lines = advanced_code_editor.get_lines();
   EXPECT_EQ(15, lines.size());
   EXPECT_EQ(9, advanced_code_editor.cursor_get_y());

   std::string expected_current_line = "Then the conceit of this inconstant stay,";
   std::string actual_current_line = lines[9];
   ASSERT_EQ(expected_current_line, actual_current_line);
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   dirty_grid_clear__will_clear_the_current_dirty_cells)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(FIXTURE_PASSAGE);

   ASSERT_EQ(401, advanced_code_editor.get_dirty_cells().size());
   advanced_code_editor.dirty_grid_clear();
   ASSERT_EQ(0, advanced_code_editor.get_dirty_cells().size());
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   delete_character__will_set_the_dirty_cells_with_the_expected_values)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(FIXTURE_PASSAGE);

   advanced_code_editor.dirty_grid_clear();

   advanced_code_editor.cursor_move_to(7, 2);
   ASSERT_EQ(true, advanced_code_editor.delete_character());

   std::vector<std::pair<int, int>> expected = {
      { 7, 2 },  { 8, 2 },  { 9, 2 },  { 10, 2 }, { 11, 2 }, { 12, 2 }, { 13, 2 }, { 14, 2 }, { 15, 2 },
      { 16, 2 }, { 17, 2 }, { 18, 2 }, { 19, 2 }, { 20, 2 },
   };
   std::vector<std::pair<int, int>> actual = advanced_code_editor.get_dirty_cells();
   ASSERT_EQ(expected, actual);
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   insert_string__on_an_empty_line_with_the_x_cursor_at_0__will_insert_the_string)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(FIXTURE_PASSAGE);
   advanced_code_editor.dirty_grid_clear();
   advanced_code_editor.cursor_move_to(0, 9);

   std::string string_to_insert = "Some text to insert";

   ASSERT_EQ(true, advanced_code_editor.insert_string(string_to_insert));

   std::vector<std::string> lines = advanced_code_editor.get_lines();

   ASSERT_EQ(string_to_insert, lines[9]);
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   insert_string__when_no_modification_happens__will_not_mark_the_content_as_modified)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   insert_string__will_mark_the_content_as_modified)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   insert_string__when_the_string_contains_newline_or_carriage_return__will_throw_an_error)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(FIXTURE_PASSAGE);

   std::string expected_error_message = "Hexagon::AdvancedCodeEditor::AdvancedCodeEditor::insert_string: error: "
                                        "Inserted string can not contain newline characters. You will need to first "
                                        "split lines and insert them via insert_lines() if you wish to insert multiple "
                                        "lines.";

   EXPECT_THROW_WITH_MESSAGE(advanced_code_editor.insert_string("\n"), std::runtime_error, expected_error_message);
   EXPECT_THROW_WITH_MESSAGE(advanced_code_editor.insert_string("\r"), std::runtime_error, expected_error_message);
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   DISABLED__TODO_add_tests_for_mutating_functions_to_ensure_content_is_modified_flag_is_set)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   insert_string__will_set_the_dirty_cells_with_the_expected_values)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(FIXTURE_PASSAGE);
   advanced_code_editor.dirty_grid_clear();

   advanced_code_editor.cursor_move_to(22, 3);
   ASSERT_EQ(true, advanced_code_editor.insert_string("VERY "));

   std::vector<std::pair<int, int>> expected = {
      { 22, 3 }, { 23, 3 }, { 24, 3 }, { 25, 3 }, { 26, 3 }, { 27, 3 }, { 28, 3 }, { 29, 3 }, { 30, 3 }, { 31, 3 }
   };
   std::vector<std::pair<int, int>> actual = advanced_code_editor.get_dirty_cells();
   ASSERT_EQ(expected, actual);
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   join_lines__will_set_the_dirty_cells_with_the_expected_values)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SIMPLE_PASSAGE);
   advanced_code_editor.dirty_grid_clear();

   advanced_code_editor.cursor_move_to(0, 7);
   advanced_code_editor.join_lines();

   // ruby shell command to generate lists
   // ruby -e "puts (0..31).to_a.collect { |i| \"{ #{i}, _ }\" }.join(', ')"

   std::vector<std::pair<int, int>> expected_characters_from_current_line = {
      {28, 7}, {29, 7}, {30, 7}, {31, 7}, {32, 7}, {33, 7}, {34, 7}, {35, 7}, {36, 7}, {37, 7}, {38, 7}, {39, 7},
      {40, 7}, {41, 7}, {42, 7}, {43, 7}, {44, 7}, {45, 7}, {46, 7}, {47, 7}, {48, 7}, {49, 7}, {50, 7}, {51, 7},
      {52, 7}, {53, 7}, {54, 7}, {55, 7}, {56, 7}, {57, 7}, {58, 7},
   };
   std::vector<std::pair<int, int>> expected_previous_cells_from_below_current_line = {
      { 0, 8 }, { 1, 8 }, { 2, 8 }, { 3, 8 }, { 4, 8 }, { 5, 8 }, { 6, 8 }, { 7, 8 }, { 8, 8 }, { 9, 8 }, { 10, 8 },
      { 11, 8 }, { 12, 8 }, { 13, 8 }, { 14, 8 }, { 15, 8 }, { 16, 8 }, { 17, 8 }, { 18, 8 }, { 19, 8 }, { 20, 8 },
      { 21, 8 }, { 22, 8 }, { 23, 8 }, { 24, 8 }, { 25, 8 }, { 26, 8 }, { 27, 8 }, { 28, 8 }, { 29, 8 }, { 30, 8 },

      { 0, 10 }, { 1, 10 }, { 2, 10 }, { 3, 10 }, { 4, 10 }, { 5, 10 }, { 6, 10 }, { 7, 10 }, { 8, 10 }, { 9, 10 },
      { 10, 10 }, { 11, 10 }, { 12, 10 }, { 13, 10 }, { 14, 10 }, { 15, 10 }, { 16, 10 }, { 17, 10 }, { 18, 10 },
      { 19, 10 }, { 20, 10 }, { 21, 10 }, { 22, 10 }, { 23, 10 }, { 24, 10 }, { 25, 10 }, { 26, 10 }, { 27, 10 },
      { 28, 10 },

      { 0, 11 }, { 1, 11 }, { 2, 11 }, { 3, 11 }, { 4, 11 }, { 5, 11 }, { 6, 11 }, { 7, 11 }, { 8, 11 }, { 9, 11 },
      { 10, 11 }, { 11, 11 }, { 12, 11 }, { 13, 11 }, { 14, 11 }, { 15, 11 }, { 16, 11 }, { 17, 11 }, { 18, 11 },
      { 19, 11 }, { 20, 11 }, { 21, 11 }, { 22, 11 }, { 23, 11 }, { 24, 11 }, { 25, 11 },
   };
   std::vector<std::pair<int, int>> expected_current_cells_from_below_current_line = {
      { 0, 9 }, { 1, 9 }, { 2, 9 }, { 3, 9 }, { 4, 9 }, { 5, 9 }, { 6, 9 }, { 7, 9 }, { 8, 9 }, { 9, 9 }, { 10, 9 },
      { 11, 9 }, { 12, 9 }, { 13, 9 }, { 14, 9 }, { 15, 9 }, { 16, 9 }, { 17, 9 }, { 18, 9 }, { 19, 9 }, { 20, 9 },
      { 21, 9 }, { 22, 9 }, { 23, 9 }, { 24, 9 }, { 25, 9 }, { 26, 9 }, { 27, 9 }, { 28, 9 },

      { 0, 10 }, { 1, 10 }, { 2, 10 }, { 3, 10 }, { 4, 10 }, { 5, 10 }, { 6, 10 }, { 7, 10 }, { 8, 10 }, { 9, 10 },
      { 10, 10 }, { 11, 10 }, { 12, 10 }, { 13, 10 }, { 14, 10 }, { 15, 10 }, { 16, 10 }, { 17, 10 }, { 18, 10 },
      { 19, 10 }, { 20, 10 }, { 21, 10 }, { 22, 10 }, { 23, 10 }, { 24, 10 }, { 25, 10 },
   };
   std::vector<std::pair<int, int>> actual = advanced_code_editor.get_dirty_cells();
   ASSERT_THAT(expected_characters_from_current_line, IsSubsetOf(actual));
   ASSERT_THAT(expected_previous_cells_from_below_current_line, IsSubsetOf(actual));
   ASSERT_THAT(expected_current_cells_from_below_current_line, IsSubsetOf(actual));

   std::vector<std::pair<int, int>> expected_cells;
   expected_cells.insert(
      expected_cells.end(),
      expected_characters_from_current_line.begin(),
      expected_characters_from_current_line.end()
   );
   expected_cells.insert(
      expected_cells.end(),
      expected_previous_cells_from_below_current_line.begin(),
      expected_previous_cells_from_below_current_line.end()
   );
   expected_cells.insert(
      expected_cells.end(),
      expected_current_cells_from_below_current_line.begin(),
      expected_current_cells_from_below_current_line.end()
   );
   std::sort(expected_cells.begin(), expected_cells.end());
   expected_cells.erase(std::unique(expected_cells.begin(), expected_cells.end()), expected_cells.end());
   ASSERT_THAT(expected_cells, UnorderedElementsAreArray(actual));
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   join_lines__if_cursor_is_outside_vertical_bounds__will_do_nothing_and_return_false)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   join_lines__if_cursor_is_inside_vertical_bounds_but_outside_horizontal_bounds__will_sill_join_lines)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   join_lines__if_cursor_is_on_the_last_line__will_do_nothing_and_return_false)
{
   // TODO
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   split_lines__will_set_the_dirty_cells_with_the_expected_cells_from_the_current_line)
{
   std::string lines = R"END(        - 9 -
Fill your bowl to the brim

and it will spill.)END";

   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(lines);
   advanced_code_editor.dirty_grid_clear();

   advanced_code_editor.cursor_move_to(14, 1);
   advanced_code_editor.split_lines();

   std::vector<std::pair<int, int>> expected = {
      { 14, 1 }, { 15, 1 }, { 16, 1 }, { 17, 1 }, { 18, 1 }, { 19, 1 }, { 20, 1 }, { 21, 1 }, { 22, 1 }, { 23, 1 },
      { 24, 1 }, { 25, 1 },
   };
   std::vector<std::pair<int, int>> actual = advanced_code_editor.get_dirty_cells();
   ASSERT_THAT(expected, IsSubsetOf(actual));
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   split_lines__will_set_the_dirty_cells_with_the_expected_cells_from_the_lines_below_the_cursor)
{
   std::string lines = R"END(        - 9 -
Fill your bowl to the brim
fam
and it will spill.)END";

   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(lines);
   advanced_code_editor.dirty_grid_clear();

   advanced_code_editor.cursor_move_to(14, 1);
   advanced_code_editor.split_lines();

   std::vector<std::pair<int, int>> expected_cells_from_before_change = {
      { 0, 2 }, { 1, 2 }, { 2, 2 },

      { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 4, 3 }, { 5, 3 }, { 6, 3 }, { 7, 3 }, { 8, 3 }, { 9, 3 }, { 10, 3 },
      { 11, 3 }, { 12, 3 }, { 13, 3 }, { 14, 3 }, { 15, 3 }, { 16, 3 }, { 17, 3 },
   };
   std::vector<std::pair<int, int>> expected_cells_from_after_change = {
      { 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, { 4, 2 }, { 5, 2 }, { 6, 2 }, { 7, 2 }, { 8, 2 }, { 9, 2 }, { 10, 2 },
      { 11, 2 },

      { 0, 3 }, { 1, 3 }, { 2, 3 },

      { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 }, { 4, 4 }, { 5, 4 }, { 6, 4 }, { 7, 4 }, { 8, 4 }, { 9, 4 }, { 10, 4 },
      { 11, 4 }, { 12, 4 }, { 13, 4 }, { 14, 4 }, { 15, 4 }, { 16, 4 }, { 17, 4 },
   };
   std::vector<std::pair<int, int>> actual = advanced_code_editor.get_dirty_cells();
   ASSERT_THAT(expected_cells_from_before_change, IsSubsetOf(actual));
   ASSERT_THAT(expected_cells_from_after_change, IsSubsetOf(actual));
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   split_lines__will_set_the_dirty_cells_with_only_the_expected_cells)
{
   std::string lines = R"END(        - 9 -
Fill your bowl to the brim

and it will spill.)END";

   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(lines);
   advanced_code_editor.dirty_grid_clear();

   advanced_code_editor.cursor_move_to(14, 1);
   advanced_code_editor.split_lines();

   std::vector<std::pair<int, int>> expected_cells_from_current_line = {
      { 14, 1 }, { 15, 1 }, { 16, 1 }, { 17, 1 }, { 18, 1 }, { 19, 1 }, { 20, 1 }, { 21, 1 }, { 22, 1 }, { 23, 1 },
      { 24, 1 }, { 25, 1 },
   };
   std::vector<std::pair<int, int>> expected_cells_from_before_change = {
      { 0, 2 }, { 1, 2 }, { 2, 2 },

      { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, { 4, 3 }, { 5, 3 }, { 6, 3 }, { 7, 3 }, { 8, 3 }, { 9, 3 }, { 10, 3 },
      { 11, 3 }, { 12, 3 }, { 13, 3 }, { 14, 3 }, { 15, 3 }, { 16, 3 }, { 17, 3 },
   };
   std::vector<std::pair<int, int>> expected_cells_from_after_change = {
      { 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, { 4, 2 }, { 5, 2 }, { 6, 2 }, { 7, 2 }, { 8, 2 }, { 9, 2 }, { 10, 2 },
      { 11, 2 },

      { 0, 3 }, { 1, 3 }, { 2, 3 },

      { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 }, { 4, 4 }, { 5, 4 }, { 6, 4 }, { 7, 4 }, { 8, 4 }, { 9, 4 }, { 10, 4 },
      { 11, 4 }, { 12, 4 }, { 13, 4 }, { 14, 4 }, { 15, 4 }, { 16, 4 }, { 17, 4 },
   };

   std::vector<std::pair<int, int>> expected_cells;
   expected_cells.insert(
      expected_cells.end(),
      expected_cells_from_current_line.begin(),
      expected_cells_from_current_line.end()
   );
   expected_cells.insert(
      expected_cells.end(),
      expected_cells_from_before_change.begin(),
      expected_cells_from_before_change.end()
   );
   expected_cells.insert(
      expected_cells.end(),
      expected_cells_from_after_change.begin(),
      expected_cells_from_after_change.end()
   );
   std::sort(expected_cells.begin(), expected_cells.end());
   expected_cells.erase(std::unique(expected_cells.begin(), expected_cells.end()), expected_cells.end());
   std::vector<std::pair<int, int>> actual = advanced_code_editor.get_dirty_cells();
   ASSERT_THAT(expected_cells, UnorderedElementsAreArray(actual));
}

TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   delete_line__will_set_the_dirty_cells_with_only_the_expected_cells)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SIMPLE_PASSAGE);
   advanced_code_editor.dirty_grid_clear();

   advanced_code_editor.cursor_move_to(0, 7);
   advanced_code_editor.delete_line();

   std::vector<std::pair<int, int>> expected_cells_from_before_change = {
      { 0, 7 }, { 1, 7 }, { 2, 7 }, { 3, 7 }, { 4, 7 }, { 5, 7 }, { 6, 7 }, { 7, 7 }, { 8, 7 }, { 9, 7 }, { 10, 7 },
      { 11, 7 }, { 12, 7 }, { 13, 7 }, { 14, 7 }, { 15, 7 }, { 16, 7 }, { 17, 7 }, { 18, 7 }, { 19, 7 }, { 20, 7 },
      { 21, 7 }, { 22, 7 }, { 23, 7 }, { 24, 7 }, { 25, 7 }, { 26, 7 }, { 27, 7 }, { 28, 7 }, { 29, 7 }, { 30, 7 },

      { 0, 8 }, { 1, 8 }, { 2, 8 }, { 3, 8 }, { 4, 8 }, { 5, 8 }, { 6, 8 }, { 7, 8 }, { 8, 8 }, { 9, 8 }, { 10, 8 },
      { 11, 8 }, { 12, 8 }, { 13, 8 }, { 14, 8 }, { 15, 8 }, { 16, 8 }, { 17, 8 }, { 18, 8 }, { 19, 8 }, { 20, 8 },
      { 21, 8 }, { 22, 8 }, { 23, 8 }, { 24, 8 }, { 25, 8 }, { 26, 8 }, { 27, 8 }, { 28, 8 }, { 29, 8 }, { 30, 8 },

      { 0, 9 }, { 1, 9 }, { 2, 9 }, { 3, 9 }, { 4, 9 }, { 5, 9 }, { 6, 9 }, { 7, 9 }, { 8, 9 }, { 9, 9 }, { 10, 9 },
      { 11, 9 }, { 12, 9 }, { 13, 9 }, { 14, 9 }, { 15, 9 }, { 16, 9 }, { 17, 9 }, { 18, 9 }, { 19, 9 }, { 20, 9 },
      { 21, 9 }, { 22, 9 }, { 23, 9 }, { 24, 9 }, { 25, 9 }, { 26, 9 }, { 27, 9 }, { 28, 9 },

      { 0, 10 }, { 1, 10 }, { 2, 10 }, { 3, 10 }, { 4, 10 }, { 5, 10 }, { 6, 10 }, { 7, 10 }, { 8, 10 }, { 9, 10 },
      { 10, 10 }, { 11, 10 }, { 12, 10 }, { 13, 10 }, { 14, 10 }, { 15, 10 }, { 16, 10 }, { 17, 10 }, { 18, 10 },
      { 19, 10 }, { 20, 10 }, { 21, 10 }, { 22, 10 }, { 23, 10 }, { 24, 10 }, { 25, 10 }, { 26, 10 }, { 27, 10 },
      { 28, 10 },

      { 0, 11 }, { 1, 11 }, { 2, 11 }, { 3, 11 }, { 4, 11 }, { 5, 11 }, { 6, 11 }, { 7, 11 }, { 8, 11 }, { 9, 11 },
      { 10, 11 }, { 11, 11 }, { 12, 11 }, { 13, 11 }, { 14, 11 }, { 15, 11 }, { 16, 11 }, { 17, 11 }, { 18, 11 },
      { 19, 11 }, { 20, 11 }, { 21, 11 }, { 22, 11 }, { 23, 11 }, { 24, 11 }, { 25, 11 },
   };
   std::vector<std::pair<int, int>> actual = advanced_code_editor.get_dirty_cells();
   ASSERT_THAT(expected_cells_from_before_change, UnorderedElementsAreArray(actual));
}


TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   insert_lines__when_any_line_contains_newline_or_carriage_return__will_throw_an_error1)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(FIXTURE_PASSAGE);

   std::string expected_error_message = "Hexagon::AdvancedCodeEditor::AdvancedCodeEditor::insert_lines() "
                                        "error: Inserted lines can not contain newline characters. "
                                        "The following lines were passed to insert_lines():\n"
                                        "=========BEGIN=========\n"
                                        "\n"
                                        "\n"
                                        "==========END=========\n";

   EXPECT_THROW_WITH_MESSAGE(advanced_code_editor.insert_lines({"\n"}), std::runtime_error, expected_error_message);
}


TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   insert_lines__when_any_line_contains_newline_or_carriage_return__will_throw_an_error2)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(FIXTURE_PASSAGE);

   std::string expected_error_message = "Hexagon::AdvancedCodeEditor::AdvancedCodeEditor::insert_lines() "
                                        "error: Inserted lines can not contain newline characters. "
                                        "The following lines were passed to insert_lines():\n"
                                        "=========BEGIN=========\n"
                                        "\r\n"
                                        "==========END=========\n";

   EXPECT_THROW_WITH_MESSAGE(advanced_code_editor.insert_lines({"\r"}), std::runtime_error, expected_error_message);
}



TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   insert_lines__will_set_the_dirty_cells_with_only_the_expected_cells)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SIMPLE_PASSAGE);
   advanced_code_editor.dirty_grid_clear();

   std::vector<std::string> lines_to_insert = {
      "These,",
      "",
      "are",
      "the lines to",
      "insert",
   };

   advanced_code_editor.cursor_move_to(0, 7);
   advanced_code_editor.insert_lines(lines_to_insert);

   std::vector<std::pair<int, int>> expected_dirty_cells = {
      { 0, 7 }, { 1, 7 }, { 2, 7 }, { 3, 7 }, { 4, 7 }, { 5, 7 }, { 6, 7 }, { 7, 7 }, { 8, 7 }, { 9, 7 }, { 10, 7 },
      { 11, 7 }, { 12, 7 }, { 13, 7 }, { 14, 7 }, { 15, 7 }, { 16, 7 }, { 17, 7 }, { 18, 7 }, { 19, 7 }, { 20, 7 },
      { 21, 7 }, { 22, 7 }, { 23, 7 }, { 24, 7 }, { 25, 7 }, { 26, 7 }, { 27, 7 },

      { 0, 8 }, { 1, 8 }, { 2, 8 }, { 3, 8 }, { 4, 8 }, { 5, 8 }, { 6, 8 }, { 7, 8 }, { 8, 8 }, { 9, 8 }, { 10, 8 },
      { 11, 8 }, { 12, 8 }, { 13, 8 }, { 14, 8 }, { 15, 8 }, { 16, 8 }, { 17, 8 }, { 18, 8 }, { 19, 8 }, { 20, 8 },
      { 21, 8 }, { 22, 8 }, { 23, 8 }, { 24, 8 }, { 25, 8 }, { 26, 8 }, { 27, 8 }, { 28, 8 }, { 29, 8 }, { 30, 8 },

      { 0, 9 }, { 1, 9 }, { 2, 9 },

      { 0, 10 }, { 1, 10 }, { 2, 10 }, { 3, 10 }, { 4, 10 }, { 5, 10 }, { 6, 10 }, { 7, 10 }, { 8, 10 }, { 9, 10 },
      { 10, 10 }, { 11, 10 }, { 12, 10 }, { 13, 10 }, { 14, 10 }, { 15, 10 }, { 16, 10 }, { 17, 10 }, { 18, 10 },
      { 19, 10 }, { 20, 10 }, { 21, 10 }, { 22, 10 }, { 23, 10 }, { 24, 10 }, { 25, 10 }, { 26, 10 }, { 27, 10 },
      { 28, 10 },

      { 0, 11 }, { 1, 11 }, { 2, 11 }, { 3, 11 }, { 4, 11 }, { 5, 11 }, { 6, 11 }, { 7, 11 }, { 8, 11 }, { 9, 11 },
      { 10, 11 }, { 11, 11 }, { 12, 11 }, { 13, 11 }, { 14, 11 }, { 15, 11 }, { 16, 11 }, { 17, 11 }, { 18, 11 },
      { 19, 11 }, { 20, 11 }, { 21, 11 }, { 22, 11 }, { 23, 11 }, { 24, 11 }, { 25, 11 },

      { 0, 12 }, { 1, 12 }, { 2, 12 }, { 3, 12 }, { 4, 12 }, { 5, 12 }, { 6, 12 }, { 7, 12 }, { 8, 12 }, { 9, 12 },
      { 10, 12 }, { 11, 12 }, { 12, 12 }, { 13, 12 }, { 14, 12 }, { 15, 12 }, { 16, 12 }, { 17, 12 }, { 18, 12 },
      { 19, 12 }, { 20, 12 }, { 21, 12 }, { 22, 12 }, { 23, 12 }, { 24, 12 }, { 25, 12 }, { 26, 12 }, { 27, 12 },

      { 0, 13 }, { 1, 13 }, { 2, 13 }, { 3, 13 }, { 4, 13 }, { 5, 13 }, { 6, 13 }, { 7, 13 }, { 8, 13 }, { 9, 13 },
      { 10, 13 }, { 11, 13 }, { 12, 13 }, { 13, 13 }, { 14, 13 }, { 15, 13 }, { 16, 13 }, { 17, 13 }, { 18, 13 },
      { 19, 13 }, { 20, 13 }, { 21, 13 }, { 22, 13 }, { 23, 13 }, { 24, 13 }, { 25, 13 }, { 26, 13 }, { 27, 13 },
      { 28, 13 }, { 29, 13 }, { 30, 13 },

      // empty row 14

      { 0, 15 }, { 1, 15 }, { 2, 15 }, { 3, 15 }, { 4, 15 }, { 5, 15 }, { 6, 15 }, { 7, 15 }, { 8, 15 }, { 9, 15 },
      { 10, 15 }, { 11, 15 }, { 12, 15 }, { 13, 15 }, { 14, 15 }, { 15, 15 }, { 16, 15 }, { 17, 15 }, { 18, 15 },
      { 19, 15 }, { 20, 15 }, { 21, 15 }, { 22, 15 }, { 23, 15 }, { 24, 15 }, { 25, 15 }, { 26, 15 }, { 27, 15 },
      { 28, 15 },

      { 0, 16 }, { 1, 16 }, { 2, 16 }, { 3, 16 }, { 4, 16 }, { 5, 16 }, { 6, 16 }, { 7, 16 }, { 8, 16 }, { 9, 16 },
      { 10, 16 }, { 11, 16 }, { 12, 16 }, { 13, 16 }, { 14, 16 }, { 15, 16 }, { 16, 16 }, { 17, 16 }, { 18, 16 },
      { 19, 16 }, { 20, 16 }, { 21, 16 }, { 22, 16 }, { 23, 16 }, { 24, 16 }, { 25, 16 },
   };
   std::vector<std::pair<int, int>> actual = advanced_code_editor.get_dirty_cells();
   ASSERT_THAT(expected_dirty_cells, UnorderedElementsAreArray(actual));
}


TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   get_select_lines__will_return_lines_by_indices)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SIMPLE_PASSAGE);
   std::map<int, std::string> expected_selected_lines = {
      { 1, "Fill your bowl to the brim" },
      { 2, "and it will spill." },
      { 4, "and it will blunt." },
      { 10, "Do your work, then step back." },
   };

   EXPECT_EQ(expected_selected_lines, advanced_code_editor.get_select_lines({1, 2, 4, 10}));
}


TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   get_select_lines__when_given_lines_outside_the_range__will_not_include_those_lines)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(SIMPLE_PASSAGE);
   std::map<int, std::string> expected_selected_lines = {};
   EXPECT_EQ(expected_selected_lines, advanced_code_editor.get_select_lines({12, 13, 999, -1}));
}


TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   replace_line__will_set_the_line_to_the_content_and_set_the_expected_dirty_cells)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(PARABLE);
   advanced_code_editor.dirty_grid_clear();

   advanced_code_editor.cursor_move_down();
   advanced_code_editor.replace_line("Is this a dream?");

   std::vector<std::string> lines = advanced_code_editor.get_lines();
   ASSERT_EQ(5, lines.size());

   EXPECT_EQ("Is this a dream?", lines[1]);

   std::vector<std::pair<int, int>> expected_dirty_cells = {
      { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, { 4, 1 }, { 5, 1 }, { 6, 1 }, { 7, 1 }, { 8, 1 }, { 9, 1 }, { 10, 1 },
      { 11, 1 }, { 12, 1 }, { 13, 1 }, { 14, 1 }, { 15, 1 },
   };
   std::vector<std::pair<int, int>> actual_dirty_cells = advanced_code_editor.get_dirty_cells();
   ASSERT_EQ(expected_dirty_cells, actual_dirty_cells);
}


TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   replace_line__when_the_line_contains_newline_or_carriage_return__will_throw_an_error)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(FIXTURE_PASSAGE);

   std::string expected_error_message = "Hexagon::AdvancedCodeEditor::AdvancedCodeEditor::replace_line() "
                                        "error: Inserted lines can not contain newline characters. "
                                        "The following lines were passed to replace_line():\n"
                                        "=========BEGIN=========\n"
                                        "\r\n"
                                        "==========END=========\n";

   EXPECT_THROW_WITH_MESSAGE(advanced_code_editor.replace_line("\r"), std::runtime_error, expected_error_message);
}


TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   set_select_lines__will_set_the_lines_to_the_content_and_set_the_expected_dirty_cells)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(PARABLE);
   advanced_code_editor.dirty_grid_clear();

   //advanced_code_editor.cursor_move_down();
   advanced_code_editor.set_select_lines({
      {1, "Is this a dream?"}
   });

   std::vector<std::string> lines = advanced_code_editor.get_lines();
   ASSERT_EQ(5, lines.size());

   EXPECT_EQ("Is this a dream?", lines[1]);

   std::vector<std::pair<int, int>> expected_dirty_cells = {
      { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, { 4, 1 }, { 5, 1 }, { 6, 1 }, { 7, 1 }, { 8, 1 }, { 9, 1 }, { 10, 1 },
      { 11, 1 }, { 12, 1 }, { 13, 1 }, { 14, 1 }, { 15, 1 },
   };
   std::vector<std::pair<int, int>> actual_dirty_cells = advanced_code_editor.get_dirty_cells();
   ASSERT_EQ(expected_dirty_cells, actual_dirty_cells);
}


TEST(Hexagon_AdvancedCodeEditor_AdvancedCodeEditorTest,
   set_select_lines__when_setting_a_line_to_a_line_index_that_does_not_exist__will_throw_an_error)
{
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(PARABLE);
   advanced_code_editor.dirty_grid_clear();

   std::map<int, std::string> lines_to_set = {
      { -1,                                     "This line will crash" },
      { advanced_code_editor.get_num_lines(),   "This line will crash" },
      { advanced_code_editor.get_num_lines()+1, "This line will crash" },
      { 9999,                                   "This line will crash" },
   };

   std::string expected_error_message = "Hexagon::AdvancedCodeEditor::AdvancedCodeEditor::set_select_lines: error: "
                     "Cannot set lines with indices less than zero or greater than the current number of "
                     "lines. If you wish to create the lines, then an alternative implementation should be "
                     "used.";

   for (auto &line_to_set : lines_to_set)
   {
      int line_num = line_to_set.first;
      EXPECT_THROW_WITH_MESSAGE(
         advanced_code_editor.set_select_lines({ {line_num, "This line will crash."} }),
         std::runtime_error,
         expected_error_message
      );
   }
}



