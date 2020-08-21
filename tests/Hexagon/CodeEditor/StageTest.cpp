
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/Stage.hpp>

TEST(Hexagon_CodeEditor_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::Stage stage;
}

TEST(Hexagon_CodeEditor_StageTest, code_editor_char_count__when_empty__returns_the_expected_number_of_characers)
{
   Hexagon::CodeEditor::Stage stage;
   ASSERT_EQ(0, stage.code_editor_char_count());
}

TEST(Hexagon_CodeEditor_StageTest, code_editor_char_count__with_empty_line__returns_the_expected_character_count)
{
   Hexagon::CodeEditor::Stage stage;
   stage.get_code_editor_ref().set_initial_content("");
   ASSERT_EQ(0, stage.code_editor_char_count());
}

TEST(Hexagon_CodeEditor_StageTest, code_editor_char_count__with_empty_lines__includes_newlines_in_character_count)
{
   Hexagon::CodeEditor::Stage stage;
   stage.get_code_editor_ref().set_initial_content(std::vector<std::string>({ "", "", "" }));
   ASSERT_EQ(2, stage.code_editor_char_count());
}

