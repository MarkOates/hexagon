
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Elements/SubBitmapCharacterMap.hpp>
#include <allegro5/allegro_color.h> // for al_color_name
#include <allegro5/allegro_image.h> // for al_save_bitmap to png

TEST(Hexagon_Elements_SubBitmapCharacterMapTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::SubBitmapCharacterMap font_character_map_grid;
}

TEST(Hexagon_Elements_SubBitmapCharacterMapTest, initialize__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::SubBitmapCharacterMap text_mesh;
   std::string expected_error_message =
      "SubBitmapCharacterMap::initialize: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(text_mesh.initialize(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_Elements_SubBitmapCharacterMapTest, initialize__without_a_valid_font__raises_an_error)
{
   al_init();
   Hexagon::Elements::SubBitmapCharacterMap text_mesh;
   std::string expected_error_message = "SubBitmapCharacterMap::initialize: error: guard \"font\" not met";
   ASSERT_THROW_WITH_MESSAGE(text_mesh.initialize(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}

TEST(Hexagon_Elements_SubBitmapCharacterMapTest, create__with_valid_arguments__returns_a_bitmap)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   al_clear_to_color(al_color_name("black"));
   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::Elements::SubBitmapCharacterMap font_character_map_grid(font);
   font_character_map_grid.initialize();

   ALLEGRO_BITMAP *result = font_character_map_grid.get_surface();
   ASSERT_NE(nullptr, result);

   al_init_image_addon();
   al_draw_bitmap(result, 0, 0, 0);
   al_flip_display();
   EXPECT_EQ(true, al_save_bitmap("/Users/markoates/Repos/hexagon/tmp/SubBitmapCharacterMapTest.png", result));

   //sleep(2);

   al_destroy_font(font);
   al_destroy_display(display);
   al_uninstall_system();
}

