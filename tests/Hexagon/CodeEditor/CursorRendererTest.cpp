
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/CursorRenderer.hpp>

TEST(Hexagon_CodeEditor_CursorRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::CursorRenderer cursor_renderer;
}

TEST(Hexagon_CodeEditor_CursorRendererTest, run__returns_the_expected_response)
{
   Hexagon::CodeEditor::CursorRenderer cursor_renderer;
   //std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, cursor_renderer.run());
}
