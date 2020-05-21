
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/CodeEditor.hpp>

TEST(Hexagon_CodeEditor_CodeEditorTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::CodeEditor code_editor;
}

TEST(Hexagon_CodeEditor_CodeEditorTest, run__returns_the_expected_response)
{
   Hexagon::CodeEditor::CodeEditor code_editor;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, code_editor.run());
}
