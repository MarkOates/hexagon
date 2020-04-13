
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/Renderer/AdvancedLineRenderer.hpp>

#include <allegro5/allegro.h>

TEST(Hexagon_CodeEditor_Renderer_AdvancedLineRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::Renderer::AdvancedLineRenderer basic_line_renderer;
}

TEST(Hexagon_CodeEditor_Renderer_AdvancedLineRendererTest, render__will_render_the_text_as_expected)
{
   al_init();
   Hexagon::CodeEditor::Renderer::AdvancedLineRenderer basic_line_renderer;
   //basic_line-
   al_uninstall_system();
}

