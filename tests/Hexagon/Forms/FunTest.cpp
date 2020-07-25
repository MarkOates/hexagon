
#include <gtest/gtest.h>

#include <Hexagon/Forms/Fun.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

TEST(Hexagon_Forms_FunTest, can_be_created_without_blowing_up)
{
   Hexagon::Forms::Fun fun;
}

TEST(Hexagon_Forms_FunTest, run__returns_the_expected_response)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_BITMAP *render_surface = al_create_bitmap(16 * 80, 9 * 80);
   al_set_target_bitmap(render_surface);

   Hexagon::Forms::Fun fun;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, fun.run());

   al_uninstall_system();
}
