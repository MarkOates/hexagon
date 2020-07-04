
#include <gtest/gtest.h>

#include <Hexagon/Elements/ColorKit.hpp>

#include <AllegroFlare/Color.hpp>

static void EXPECT_COLOR_EQ(const ALLEGRO_COLOR &color1, const ALLEGRO_COLOR &color2)
{
   EXPECT_EQ(color1.r, color2.r);
   EXPECT_EQ(color1.g, color2.g);
   EXPECT_EQ(color1.b, color2.b);
   EXPECT_EQ(color1.a, color2.a);
}

TEST(Hexagon_Elements_ColorKitTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::ColorKit color_kit;
}

TEST(Hexagon_Elements_ColorKitTest, black__returns_the_expected_value)
{
   Hexagon::Elements::ColorKit color_kit;
   ALLEGRO_COLOR expected = al_color_name("black");
   EXPECT_COLOR_EQ(expected, color_kit.black());
}
