
#include <gtest/gtest.h>

#include <Hexagon/Elements/FontedTextGrid.hpp>

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
   sleep(3);


   fonted_text_grid.destroy();

   al_destroy_font(font);
   al_uninstall_system();

   SUCCEED();
}

