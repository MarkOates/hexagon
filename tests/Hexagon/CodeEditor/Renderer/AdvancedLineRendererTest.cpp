
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/Renderer/BasicLineRenderer.hpp>

#include <allegro5/allegro.h>

TEST(Hexagon_CodeEditor_Renderer_BasicLineRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::Renderer::BasicLineRenderer basic_line_renderer;
}

TEST(Hexagon_CodeEditor_Renderer_BasicLineRendererTest, render__will_render_the_text_as_expected)
{
   al_init();
   Hexagon::CodeEditor::Renderer::BasicLineRenderer basic_line_renderer;
   //basic_line-
   al_uninstall_system();
}

