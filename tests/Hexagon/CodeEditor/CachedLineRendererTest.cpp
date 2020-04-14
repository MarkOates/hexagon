
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/CachedLineRenderer.hpp>

TEST(Hexagon_CodeEditor_CachedLineRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::CachedLineRenderer cached_line_renderer;
}

TEST(Hexagon_CodeEditor_CachedLineRendererTest, run__returns_the_expected_response)
{
   Hexagon::CodeEditor::CachedLineRenderer cached_line_renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, cached_line_renderer.run());
}
