#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>

TEST(Hexagon_AdvancedCodeEditor_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::Renderer renderer;
}

TEST(Hexagon_AdvancedCodeEditor_RendererTest, render__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::Renderer renderer;
   renderer.render();
   SUCCEED();
}
