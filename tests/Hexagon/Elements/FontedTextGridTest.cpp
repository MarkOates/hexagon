
#include <gtest/gtest.h>

#include <Hexagon/Elements/FontedTextGrid.hpp>

#include <AllegroFlare/Timer.hpp>

TEST(Hexagon_Elements_FontedTextGridTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::FontedTextGrid fonted_text_grid;
}

TEST(Hexagon_Elements_FontedTextGridTest, initialize__does_not_blow_up)
{
   al_init();
   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::Elements::FontedTextGrid fonted_text_grid(font);
   fonted_text_grid.initialize();

   fonted_text_grid.destroy();

   al_destroy_font(font);
   al_uninstall_system();

   SUCCEED();
}

TEST(Hexagon_Elements_FontedTextGridTest, fun)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(16 * 80, 9 * 80);
   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::Elements::FontedTextGrid fonted_text_grid(font);
   fonted_text_grid.initialize();

   fonted_text_grid.set_cell_to_character_and_color('H', 0, 0);
   fonted_text_grid.set_cell_to_character_and_color('E', 1, 0);
   fonted_text_grid.set_cell_to_character_and_color('L', 2, 0);
   fonted_text_grid.set_cell_to_character_and_color('L', 3, 0);
   fonted_text_grid.set_cell_to_character_and_color('O', 4, 0);

   fonted_text_grid.draw();
   al_flip_display();
   //sleep(3);


   fonted_text_grid.destroy();

   al_destroy_font(font);
   al_uninstall_system();

   SUCCEED();
}

TEST(Hexagon_Elements_FontedTextGridTest, set_cell_to_character_and_color__executes_in_the_expected_time)
{
   al_init();
   srand(al_get_time());
   ALLEGRO_DISPLAY *display = al_create_display(16 * 80, 9 * 80);
   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::Elements::FontedTextGrid fonted_text_grid(font);
   fonted_text_grid.initialize();

   AllegroFlare::Timer timer;
   int passes = 123 * 16;
   int total_tries = 4;

   int attempts = total_tries * passes;

   for (unsigned tries=0; tries<total_tries; tries++)
   {
      timer.reset();
      timer.start();
      for (unsigned i=0; i<passes; i++)
      {
         char ch = (rand() % 96) + 32;
         int x = rand() % fonted_text_grid.get_num_columns();
         int y = rand() % fonted_text_grid.get_num_rows();

         fonted_text_grid.set_cell_to_character_and_color(ch, x, y);
      }
      timer.pause();
      //EXPECT_EQ(100, timer.get_elapsed_time_microseconds());
   }

   fonted_text_grid.draw();

   al_flip_display();

   fonted_text_grid.destroy();

   al_destroy_font(font);
   al_uninstall_system();

   SUCCEED();
}

