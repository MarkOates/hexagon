
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

