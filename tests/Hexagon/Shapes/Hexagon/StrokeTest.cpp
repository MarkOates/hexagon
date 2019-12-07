
#include <gtest/gtest.h>

#include <Hexagon/Shapes/Hexagon/Stroke.hpp>

TEST(Hexagon_Shapes_Hexagon_StrokeTest, can_be_created_without_blowing_up)
{
   Hexagon::Shapes::Hexagon::Stroke stroke;
}

TEST(Hexagon_Shapes_Hexagon_StrokeTest, run__returns_the_expected_response)
{
   Hexagon::Shapes::Hexagon::Stroke stroke;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, stroke.run());
}
