
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/LineRenderBin.hpp>

TEST(Hexagon_CodeEditor_LineRenderBinTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::LineRenderBin line_render_bin;
}

TEST(Hexagon_CodeEditor_LineRenderBinTest, run__returns_the_expected_response)
{
   Hexagon::CodeEditor::LineRenderBin line_render_bin;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, line_render_bin.run());
}
