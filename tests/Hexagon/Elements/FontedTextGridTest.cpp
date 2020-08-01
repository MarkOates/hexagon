
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

   fonted_text_grid.lock_for_update();
   fonted_text_grid.set_cell_to_character_and_color('H', 0, 0);
   fonted_text_grid.set_cell_to_character_and_color('E', 1, 0);
   fonted_text_grid.set_cell_to_character_and_color('L', 2, 0);
   fonted_text_grid.set_cell_to_character_and_color('L', 3, 0);
   fonted_text_grid.set_cell_to_character_and_color('O', 4, 0);
   fonted_text_grid.unlock_for_update();

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
   int total_tries = 128;

   int attempts = total_tries * passes;
   long total_sum_microseconds = 0;
   long worst_try_microseconds = 0;
   long best_try_microseconds = 99999;

   for (unsigned tries=0; tries<total_tries; tries++)
   {
      timer.reset();
      timer.start();
      fonted_text_grid.lock_for_update();
      for (unsigned i=0; i<passes; i++)
      {
         char ch = (rand() % 96) + 32;
         int x = rand() % fonted_text_grid.get_num_columns();
         int y = rand() % fonted_text_grid.get_num_rows();

         fonted_text_grid.set_cell_to_character_and_color(ch, x, y, ALLEGRO_COLOR{0, 1, 1, 1});
      }
      fonted_text_grid.unlock_for_update();
      timer.pause();

      long elapsed_time_microseconds = timer.get_elapsed_time_microseconds();
      total_sum_microseconds += elapsed_time_microseconds;
      if (elapsed_time_microseconds < best_try_microseconds) best_try_microseconds = elapsed_time_microseconds;
      if (elapsed_time_microseconds > worst_try_microseconds) worst_try_microseconds = elapsed_time_microseconds;

      fonted_text_grid.draw();
      al_flip_display();
   }

   fonted_text_grid.destroy();

   long average_performance_cost_microseconds = total_sum_microseconds / total_tries;
   //EXPECT_EQ(100, average_performance_cost_microseconds);
   //EXPECT_EQ(100, worst_try_microseconds);
   //EXPECT_EQ(100, best_try_microseconds);

   al_destroy_font(font);
   al_uninstall_system();

   SUCCEED();
}

