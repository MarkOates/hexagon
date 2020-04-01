
#include <gtest/gtest.h>

#include <allegro5/allegro.h>

#include <Hexagon/Powerbar/Renderer.hpp>

TEST(Hexagon_Powerbar_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::Powerbar::Renderer renderer;
}

TEST(Hexagon_Powerbar_RendererTest, render__draws_the_powerbar)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(600, 320);

   Hexagon::Powerbar::Renderer renderer(display);
   renderer.render();

   al_flip_display();

   al_destroy_display(display);
   al_uninstall_system();
}
