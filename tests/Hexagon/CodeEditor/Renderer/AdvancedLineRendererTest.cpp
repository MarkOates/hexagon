
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/Renderer/AdvancedLineRenderer.hpp>

TEST(Hexagon_CodeEditor_Renderer_AdvancedLineRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::Renderer::AdvancedLineRenderer advanced_line_renderer;
}

TEST(Hexagon_CodeEditor_Renderer_AdvancedLineRendererTest, run__returns_the_expected_response)
{
   Hexagon::CodeEditor::Renderer::AdvancedLineRenderer advanced_line_renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, advanced_line_renderer.run());
}
