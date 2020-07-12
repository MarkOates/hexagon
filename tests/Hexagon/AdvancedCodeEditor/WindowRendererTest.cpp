
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/WindowRenderer.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

TEST(Hexagon_AdvancedCodeEditor_WindowRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::WindowRenderer window_renderer;
}

TEST(Hexagon_AdvancedCodeEditor_WindowRendererTest, render__returns_the_expected_response)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_BITMAP *render_surface = al_create_bitmap(800, 400);
   al_set_target_bitmap(render_surface);

   Hexagon::AdvancedCodeEditor::WindowRenderer window_renderer;
   window_renderer.render();

   al_uninstall_system();

   SUCCEED();
}
