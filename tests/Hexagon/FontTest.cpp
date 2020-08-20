
#include <gtest/gtest.h>

#include <Hexagon/Font.hpp>

TEST(Hexagon_FontTest, can_be_created_without_blowing_up)
{
   Hexagon::Font font;
}

TEST(Hexagon_FontTest, font_filename__has_a_getter_and_is_set_to_default_values)
{
   Hexagon::Font font;
   ASSERT_EQ("Consolas.ttf", font.get_font_filename());
}

TEST(Hexagon_FontTest, font_size__has_a_getter_and_is_set_to_default_values)
{
   Hexagon::Font font;
   ASSERT_EQ(-16, font.get_font_size());
}

