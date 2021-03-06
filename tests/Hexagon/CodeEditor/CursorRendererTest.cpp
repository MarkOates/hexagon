
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/CursorRenderer.hpp>

#include <allegro5/allegro_color.h>
static void EXPECT_COLOR_EQ(const ALLEGRO_COLOR &color1, const ALLEGRO_COLOR &color2)
{
   EXPECT_EQ(color1.r, color2.r);
   EXPECT_EQ(color1.g, color2.g);
   EXPECT_EQ(color1.b, color2.b);
   EXPECT_EQ(color1.a, color2.a);
}

#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Timer.hpp>

TEST(Hexagon_CodeEditor_CursorRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::CursorRenderer cursor_renderer;
}

TEST(Hexagon_CodeEditor_CursorRendererTest, color__has_a_getter_with_the_default_value)
{
   Hexagon::CodeEditor::CursorRenderer cursor_renderer;
   ALLEGRO_COLOR expected_color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
   ALLEGRO_COLOR actual_color = cursor_renderer.get_color();

   EXPECT_COLOR_EQ(expected_color, actual_color);
}

TEST(Hexagon_CodeEditor_CursorRendererTest, render__will_not_blow_up)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_BITMAP *surface_render = al_create_bitmap(1280, 720); // (vec2d(16, 9) * 80);
   al_set_target_bitmap(surface_render);

   Hexagon::CodeEditor::CursorRenderer cursor_renderer;
   cursor_renderer.render();

   al_destroy_bitmap(surface_render);
   al_uninstall_system();
}

TEST(Hexagon_CodeEditor_CursorRendererTest,
   DISABLED__render__will_execute_in_under_the_expected_time)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_BITMAP *surface_render = al_create_bitmap(1280, 720); // (vec2d(16, 9) * 80);
   al_set_target_bitmap(surface_render);

   Hexagon::CodeEditor::CursorRenderer cursor_renderer;
   AllegroFlare::Timer timer;
   timer.start();
   cursor_renderer.render();
   timer.pause();

   ASSERT_LT(timer.get_elapsed_time_microseconds(), 100);

   al_destroy_bitmap(surface_render);
   al_uninstall_system();
}

