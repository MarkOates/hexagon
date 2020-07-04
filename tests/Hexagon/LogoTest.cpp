
#include <gtest/gtest.h>

#include <Hexagon/Logo.hpp>

TEST(Hexagon_LogoTest, can_be_created_without_blowing_up)
{
   Hexagon::Logo logo;
}

TEST(Hexagon_LogoTest, render__draws_the_expected_graphic)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   ALLEGRO_FONT *font = al_create_builtin_font();

   float x = al_get_display_width(display)/2.0f;
   float y = al_get_display_height(display)/2.0f;
   float radius = 100;
   Hexagon::Logo logo(x, y, radius, font, Hexagon::Logo::default_color(), 2.0f);
   logo.render();

   al_flip_display();
   //sleep(2);

   al_destroy_display(display);
   al_uninstall_system();
}

