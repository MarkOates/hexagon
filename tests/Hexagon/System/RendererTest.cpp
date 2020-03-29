
#include <gtest/gtest.h>

#include <Hexagon/System/Renderer.hpp>

TEST(Hexagon_System_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Renderer renderer;
}

TEST(Hexagon_System_RendererTest, run__returns_the_expected_response)
{
   Hexagon::System::Renderer renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, renderer.run());
}
