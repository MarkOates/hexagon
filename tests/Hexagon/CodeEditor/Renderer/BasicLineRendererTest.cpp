
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/Renderer/BasicLineRenderer.hpp>

TEST(Hexagon_CodeEditor_Renderer_BasicLineRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::Renderer::BasicLineRenderer basic_line_renderer;
}

TEST(Hexagon_CodeEditor_Renderer_BasicLineRendererTest, run__returns_the_expected_response)
{
   Hexagon::CodeEditor::Renderer::BasicLineRenderer basic_line_renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, basic_line_renderer.run());
}
