
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

   al_destroy_font(font);
   al_uninstall_system();

   SUCCEED();
}
