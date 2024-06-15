
#include <gtest/gtest.h>

#include <Hexagon/Font.hpp>
#include <Hexagon/Testing/ErrorAssertions.hpp>

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
   EXPECT_THROW_GUARD_ERROR(
      font.al_font(),
      "Hexagon::Font::al_font",
      "al_is_system_installed()"
   );
}

TEST(Hexagon_FontTest, al_font__without_the_allegro_image_addon_initialized__will_raise_an_exception)
{
   al_init();
   Hexagon::Font font;
   EXPECT_THROW_GUARD_ERROR(
      font.al_font(),
      "Hexagon::Font::al_font",
      "al_is_ttf_addon_initialized()"
   );
   al_uninstall_system();
}

TEST(Hexagon_FontTest, al_font__without_a_valid_font_bin__will_raise_an_exception)
{
   al_init();
   al_init_ttf_addon();
   Hexagon::Font font;
   EXPECT_THROW_GUARD_ERROR(
      font.al_font(),
      "Hexagon::Font::al_font",
      "font_bin"
   );
   al_shutdown_ttf_addon();
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

   Hexagon::Font font(&font_bin);
   ALLEGRO_FONT *al_font = font.al_font();
   ASSERT_NE(nullptr, al_font);

   font_bin.clear();
   al_shutdown_ttf_addon();
   al_uninstall_system();
}

TEST(Hexagon_FontTest, increase_font_size__will_increase_the_size_of_the_font)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");

   Hexagon::Font font(&font_bin);

   ALLEGRO_FONT* start_al_font = font.al_font();

   ASSERT_NE(nullptr, start_al_font);
   int start_font_width = al_get_text_width(start_al_font, "XYZ");
   int start_font_height = al_get_font_line_height(start_al_font);

   font.increase_font_size();
   font.increase_font_size();
   font.increase_font_size();

   ALLEGRO_FONT* end_al_font = font.al_font();

   ASSERT_NE(nullptr, end_al_font);
   int end_font_width = al_get_text_width(end_al_font, "XYZ");
   int end_font_height = al_get_font_line_height(end_al_font);

   EXPECT_LT(start_font_width, end_font_width);
   EXPECT_LT(start_font_height, end_font_height);

   font_bin.clear();
   al_shutdown_ttf_addon();
   al_uninstall_system();
}

TEST(Hexagon_FontTest, decrease_font_size__will_decrease_the_size_of_the_font)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");

   Hexagon::Font font(&font_bin);

   ALLEGRO_FONT* start_al_font = font.al_font();

   ASSERT_NE(nullptr, start_al_font);
   int start_font_width = al_get_text_width(start_al_font, "XYZ");
   int start_font_height = al_get_font_line_height(start_al_font);

   font.decrease_font_size();
   font.decrease_font_size();
   font.decrease_font_size();

   ALLEGRO_FONT* end_al_font = font.al_font();

   ASSERT_NE(nullptr, end_al_font);
   int end_font_width = al_get_text_width(end_al_font, "XYZ");
   int end_font_height = al_get_font_line_height(end_al_font);

   EXPECT_GT(start_font_width, end_font_width);
   EXPECT_GT(start_font_height, end_font_height);

   font_bin.clear();
   al_shutdown_ttf_addon();
   al_uninstall_system();
}

