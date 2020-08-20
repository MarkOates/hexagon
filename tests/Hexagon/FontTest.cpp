
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Font.hpp>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

TEST(Hexagon_FontTest, can_be_created_without_blowing_up)
{
   Hexagon::Font font;
}

TEST(Hexagon_FontTest, font_filename__has_a_getter_and_is_set_to_default_values)
{
   Hexagon::Font font;
   ASSERT_EQ("Eurostile.ttf", font.get_font_filename());
}

TEST(Hexagon_FontTest, font_size__has_a_getter_and_is_set_to_default_values)
{
   Hexagon::Font font;
   ASSERT_EQ(-16, font.get_font_size());
}

TEST(Hexagon_FontTest, al_font__without_allegro_initialized__will_raise_an_exception)
{
   Hexagon::Font font;
   std::string expected_error_message = "Font::al_font: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(font.al_font(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_FontTest, al_font__without_the_allegro_image_addon_initialized__will_raise_an_exception)
{
   al_init();
   Hexagon::Font font;
   std::string expected_error_message = "Font::al_font: error: guard \"al_is_ttf_addon_initialized()\" not met";
   ASSERT_THROW_WITH_MESSAGE(font.al_font(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}

TEST(Hexagon_FontTest, al_font__without_a_valid_font_bin__will_raise_an_exception)
{
   al_init();
   al_init_ttf_addon();
   Hexagon::Font font;
   std::string expected_error_message = "Font::al_font: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(font.al_font(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}

TEST(Hexagon_FontTest, al_font__without_an_initialized_font_bin__will_raise_an_exception)
{
   // delegated
}

TEST(Hexagon_FontTest, al_font__will_return_a_font)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   //font_bin.set_full_path("Users/markoates/Repos/hexagon/tests/fixtures/data/fonts");

   Hexagon::Font font(&font_bin);
   ALLEGRO_FONT *al_font = font.al_font();
   ASSERT_NE(nullptr, al_font);

   font_bin.clear();
   al_uninstall_system();
}

