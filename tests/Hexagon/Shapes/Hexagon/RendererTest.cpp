
#include <gtest/gtest.h>

#include <Hexagon/Shapes/Hexagon/Renderer.hpp>

TEST(Hexagon_Shapes_Hexagon_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::Shapes::Hexagon::Renderer renderer;
}

TEST(Hexagon_Shapes_Hexagon_RendererTest, run__returns_the_expected_response)
{
   Hexagon::Shapes::Hexagon::Renderer renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, renderer.run());
}
