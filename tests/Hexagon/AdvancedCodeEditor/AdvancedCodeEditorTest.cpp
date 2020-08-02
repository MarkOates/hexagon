
#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
   std::vector<std::pair<int, int>> expected_lines_below_current_line = {
      { 0, 8 }, { 1, 8 }, { 2, 8 }, { 3, 8 }, { 4, 8 }, { 5, 8 }, { 6, 8 }, { 7, 8 }, { 8, 8 }, { 9, 8 }, { 10, 8 },
      { 11, 8 }, { 12, 8 }, { 13, 8 }, { 14, 8 }, { 15, 8 }, { 16, 8 }, { 17, 8 }, { 18, 8 }, { 19, 8 }, { 20, 8 },
      { 21, 8 }, { 22, 8 }, { 23, 8 }, { 24, 8 }, { 25, 8 }, { 26, 8 }, { 27, 8 }, { 28, 8 }, { 29, 8 }, { 30, 8 },
   };
   std::vector<std::pair<int, int>> actual = advanced_code_editor.get_dirty_cells();
   ASSERT_THAT(expected_characters_from_current_line, IsSubsetOf(actual));
   ASSERT_THAT(expected_lines_below_current_line, IsSubsetOf(actual));
}

