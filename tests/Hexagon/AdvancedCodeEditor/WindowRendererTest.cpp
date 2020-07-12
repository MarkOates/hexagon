
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/WindowRenderer.hpp>

#include <allegro5/allegro.h>

TEST(Hexagon_AdvancedCodeEditor_WindowRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::WindowRenderer window_renderer;
}

TEST(Hexagon_AdvancedCodeEditor_WindowRendererTest, render__returns_the_expected_response)
{
   al_init();

   Hexagon::AdvancedCodeEditor::WindowRenderer window_renderer;
   window_renderer.render();

   al_uninstall_system();

   SUCCEED();
}
