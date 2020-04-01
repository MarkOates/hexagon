
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <allegro5/allegro.h>

#include <Hexagon/Powerbar/Renderer.hpp>

TEST(Hexagon_Powerbar_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::Powerbar::Renderer renderer;
}

TEST(Hexagon_Powerbar_RendererTest, render__with_a_nullptr_powerbar_throws_an_error)
{
   Hexagon::Powerbar::Renderer renderer;

   std::string expected_error_message = "[Hexagon/Powerbar/Renderer error:] cannot \"render\" with a nullptr powerbar";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_Powerbar_RendererTest, render__with_a_nullptr_font_throws_an_error)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(600, 320);
   Hexagon::Powerbar::Powerbar powerbar;

   Hexagon::Powerbar::Renderer renderer(display, &powerbar);

   std::string expected_error_message = "[Hexagon/Powerbar/Renderer error:] cannot \"render\" with a nullptr font";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}
TEST(Hexagon_Powerbar_RendererTest, render__draws_the_powerbar)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(600, 320);
   ALLEGRO_FONT *font = al_create_builtin_font();
   Hexagon::Powerbar::Powerbar powerbar;

   Hexagon::Powerbar::Renderer renderer(display, &powerbar, font);
   renderer.render();

   al_flip_display();

   sleep(1);

   al_destroy_display(display);
   al_uninstall_system();
}
