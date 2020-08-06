
#include <gtest/gtest.h>

#include <Hexagon/Shaders/FlatColor.hpp>

TEST(Hexagon_Shaders_FlatColorTest, can_be_created_without_blowing_up)
{
   Hexagon::Shaders::FlatColor flat_color;
}

TEST(Hexagon_Shaders_FlatColorTest, run__returns_the_expected_response)
{
   Hexagon::Shaders::FlatColor flat_color;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, flat_color.run());
}
