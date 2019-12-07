
#include <gtest/gtest.h>

#include <Hexagon/Shapes/Hexagon/Fill.hpp>

TEST(Hexagon_Shapes_Hexagon_FillTest, can_be_created_without_blowing_up)
{
   Hexagon::Shapes::Hexagon::Fill fill;
}

TEST(Hexagon_Shapes_Hexagon_FillTest, run__returns_the_expected_response)
{
   Hexagon::Shapes::Hexagon::Fill fill;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, fill.run());
}
