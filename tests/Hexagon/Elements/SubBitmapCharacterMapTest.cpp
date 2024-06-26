
#include <gtest/gtest.h>

#include <Hexagon/Elements/SubBitmapCharacterMap.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <allegro5/allegro_color.h> // for al_color_name
#include <allegro5/allegro_image.h> // for al_save_bitmap to png

TEST(Hexagon_Elements_SubBitmapCharacterMapTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::SubBitmapCharacterMap sub_bitmap_character_map;
}

TEST(Hexagon_Elements_SubBitmapCharacterMapTest, initialize__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::SubBitmapCharacterMap sub_bitmap_character_map;
   EXPECT_THROW_GUARD_ERROR(
      sub_bitmap_character_map.initialize(),
      "Hexagon::Elements::SubBitmapCharacterMap::initialize",
      "al_is_system_installed()"
   );
}

TEST(Hexagon_Elements_SubBitmapCharacterMapTest, initialize__without_a_valid_font__raises_an_error)
{
   al_init();
   Hexagon::Elements::SubBitmapCharacterMap sub_bitmap_character_map;
   EXPECT_THROW_GUARD_ERROR(
      sub_bitmap_character_map.initialize(),
      "Hexagon::Elements::SubBitmapCharacterMap::initialize",
      "font"
   );
   al_uninstall_system();
}

TEST(Hexagon_Elements_SubBitmapCharacterMapTest, create__with_valid_arguments__creates_the_bitmap_surface)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   al_clear_to_color(al_color_name("black"));
   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::Elements::SubBitmapCharacterMap sub_bitmap_character_map(font);
   sub_bitmap_character_map.initialize();

   ALLEGRO_BITMAP *result = sub_bitmap_character_map.get_surface();
   ASSERT_NE(nullptr, result);

   al_init_image_addon();
   al_draw_bitmap(result, 0, 0, 0);
   al_flip_display();
   EXPECT_EQ(true, al_save_bitmap("/Users/markoates/Repos/hexagon/tmp/SubBitmapCharacterMapTest.png", result));

   al_destroy_font(font);
   al_destroy_display(display);
   al_uninstall_system();
}

