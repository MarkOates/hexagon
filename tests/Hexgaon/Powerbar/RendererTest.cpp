
#include <gtest/gtest.h>

#include <allegro5/allegro.h>

#include <Hexgaon/Powerbar/Renderer.hpp>

TEST(Hexgaon_Powerbar_RendererTest, can_be_created_without_blowing_up)
{
   Hexgaon::Powerbar::Renderer renderer;
}

TEST(Hexgaon_Powerbar_RendererTest, render__draws_the_powerbar)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(600, 320);

   Hexgaon::Powerbar::Renderer renderer;
   renderer.render();

   al_flip_display();

   al_destroy_display(display);
   al_uninstall_system();
}
