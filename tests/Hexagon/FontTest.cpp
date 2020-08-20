
#include <gtest/gtest.h>

#include <Hexagon/Font.hpp>

TEST(Hexagon_FontTest, can_be_created_without_blowing_up)
{
   Hexagon::Font font;
}

TEST(Hexagon_FontTest, run__returns_the_expected_response)
{
   Hexagon::Font font;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, font.run());
}

