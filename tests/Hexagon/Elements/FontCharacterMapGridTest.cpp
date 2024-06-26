
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <Hexagon/Elements/FontCharacterMapGrid.hpp>
#include <allegro5/allegro_image.h> // for al_save_bitmap to png

TEST(Hexagon_Elements_FontCharacterMapGridTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::FontCharacterMapGrid font_character_map_grid;
}

TEST(Hexagon_Elements_FontCharacterMapGridTest, initialize__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::FontCharacterMapGrid text_mesh;
   ASSERT_THROW_GUARD_ERROR(
      text_mesh.initialize(),
      "Hexagon::Elements::FontCharacterMapGrid::initialize",
      "al_is_system_installed()"
   );
}


TEST(Hexagon_Elements_FontCharacterMapGridTest, initialize__without_a_valid_font__raises_an_error)
{
   al_init();
   Hexagon::Elements::FontCharacterMapGrid text_mesh;
   ASSERT_THROW_GUARD_ERROR(
      text_mesh.initialize(),
      "Hexagon::Elements::FontCharacterMapGrid::initialize",
      "font"
   );
   al_uninstall_system();
}


TEST(Hexagon_Elements_FontCharacterMapGridTest, initialize__returns_true)
{
   al_init();
   ALLEGRO_FONT *font = al_create_builtin_font();
   Hexagon::Elements::FontCharacterMapGrid font_character_map_grid(font);

   ASSERT_EQ(true, font_character_map_grid.initialize());

   al_destroy_font(font);
   al_uninstall_system();
}


TEST(Hexagon_Elements_FontCharacterMapGridTest, initialize__will_populate_the_character_uv_mapping)
{
   al_init();
   ALLEGRO_FONT *font = al_create_builtin_font();
   Hexagon::Elements::FontCharacterMapGrid font_character_map_grid(font);

   font_character_map_grid.initialize();

   ALLEGRO_BITMAP *result = font_character_map_grid.get_created_character_map_bitmap();
   ASSERT_NE(nullptr, result);

   std::map<char, std::tuple<float, float, float, float>> some_expected_mappings = {
      { 'a', {8.0f, 48.0f, 16.0f, 56.0f} },
      { ';', {88.0f, 24.0f, 96.0f, 32.0f} },
   };
   std::map<char, std::tuple<float, float, float, float>> created_mapping =
      font_character_map_grid.get_character_uv_mapping();

   ASSERT_EQ(256, created_mapping.size());

   for (auto &some_expected_mapping : some_expected_mappings)
   {
      char character = some_expected_mapping.first;
      bool exists = created_mapping.find(character) != created_mapping.end();
      if (exists)
      {
         std::tuple<float, float, float, float> expected_mapping = some_expected_mapping.second;
         std::tuple<float, float, float, float> actual_mapping = created_mapping[character];
         EXPECT_EQ(expected_mapping, actual_mapping);
      }
   }

   al_destroy_font(font);
   al_uninstall_system();
}


TEST(Hexagon_Elements_FontCharacterMapGridTest, initialize__if_called_more_than_once__will_throw_an_error)
{
   al_init();
   ALLEGRO_FONT *font = al_create_builtin_font();
   Hexagon::Elements::FontCharacterMapGrid font_character_map_grid(font);

   ASSERT_EQ(true, font_character_map_grid.initialize());
   ASSERT_THROW_GUARD_ERROR(
      font_character_map_grid.initialize(),
      "Hexagon::Elements::FontCharacterMapGrid::initialize",
      "(!initialized)"
   );
}


TEST(Hexagon_Elements_FontCharacterMapGridTest,
   get_created_character_map_bitmap__before_initialize_is_called__will_throw_an_error)
{
   Hexagon::Elements::FontCharacterMapGrid font_character_map_grid;

   ASSERT_THROW_GUARD_ERROR(
      font_character_map_grid.get_created_character_map_bitmap(),
      "Hexagon::Elements::FontCharacterMapGrid::get_created_character_map_bitmap",
      "initialized"
   );
}


TEST(Hexagon_Elements_FontCharacterMapGridTest, character_uv_mapping__is_empty_by_default)
{
   Hexagon::Elements::FontCharacterMapGrid font_character_map_grid;
   EXPECT_EQ(true, font_character_map_grid.get_character_uv_mapping().empty());
}


TEST(Hexagon_Elements_FontCharacterMapGridTest,
   get_created_character_map_bitmap__will_return_the_created_character_map_bitmap)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::Elements::FontCharacterMapGrid font_character_map_grid(font);

   ASSERT_EQ(true, font_character_map_grid.initialize());

   ALLEGRO_BITMAP *result = font_character_map_grid.get_created_character_map_bitmap();
   ASSERT_NE(nullptr, result);

   al_draw_bitmap(result, 0, 0, 0);
   al_flip_display();

   al_init_image_addon();
   EXPECT_EQ(true, al_save_bitmap("/Users/markoates/Repos/hexagon/tmp/FontCharacterMapGridTest.png", result));

   //sleep(2);

   al_destroy_font(font);
   al_destroy_display(display);
   al_uninstall_system();
}


