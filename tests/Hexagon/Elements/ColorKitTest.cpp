
#include <gtest/gtest.h>

#include <Hexagon/Elements/ColorKit.hpp>

TEST(Hexagon_Elements_ColorKitTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::ColorKit color_kit;
}

TEST(Hexagon_Elements_ColorKitTest, run__returns_the_expected_response)
{
   Hexagon::Elements::ColorKit color_kit;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, color_kit.run());
}
