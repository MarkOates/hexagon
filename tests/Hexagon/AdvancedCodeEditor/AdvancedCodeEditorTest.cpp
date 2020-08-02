
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/AdvancedCodeEditor.hpp>

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
   split_lines__on_a_line_number_that_is_out_of_bounds__does_nothing_and_returns_false)
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
   delete_character__will_set_the_characters_changed_in_last_action_with_the_expected_values)
{
   std::vector<std::string> lines;
   Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
   advanced_code_editor.set_content(FIXTURE_PASSAGE);

   advanced_code_editor.cursor_move_to(7, 2);
   ASSERT_EQ(true, advanced_code_editor.delete_character());

   std::vector<std::pair<int, int>> expected = {
      { 7, 2 },  { 8, 2 },  { 9, 2 },  { 10, 2 }, { 11, 2 }, { 12, 2 }, { 13, 2 }, { 14, 2 }, { 15, 2 },
      { 16, 2 }, { 17, 2 }, { 18, 2 }, { 19, 2 }, { 20, 2 },
   };
   std::vector<std::pair<int, int>> actual = advanced_code_editor.get_characters_changed_in_last_action();
   ASSERT_EQ(expected, actual);
}

