
#include <gtest/gtest.h>

#include <Hexagon/Forms/Fun.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

TEST(Hexagon_Forms_FunTest, can_be_created_without_blowing_up)
{
   Hexagon::Forms::Fun fun;
}

TEST(Hexagon_Forms_FunTest, draw__does_not_blow_up)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_BITMAP *render_surface = al_create_bitmap(16 * 80, 9 * 80);
   al_set_target_bitmap(render_surface);

   Hexagon::Forms::Fun fun;
   fun.draw();

   al_uninstall_system();

   SUCCEED();
}

TEST(Hexagon_Forms_FunTest, process_char_input__will_append_the_character_to_the_buffer__and_return_buffer_changed)
{
   Hexagon::Forms::Fun fun;
   std::string characters = "Hello, character input!";
   for (char character : characters)
   {
      EXPECT_EQ(1, fun.process_char_input(character));
   }
}

TEST(Hexagon_Forms_FunTest, process_char_input__for_all_char_values_up_to_the_spacebar__will_return_no_change)
{
   Hexagon::Forms::Fun fun;
   const char SPACEBAR_CHAR = 32;

   for (char character = 0; character < SPACEBAR_CHAR; character++)
   {
      if (character == 10) continue;
      EXPECT_EQ(0, fun.process_char_input(character));
   }
}

