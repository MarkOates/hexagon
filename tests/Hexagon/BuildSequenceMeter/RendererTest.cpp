
#include <gtest/gtest.h>

#include <Hexagon/BuildSequenceMeter/Renderer.hpp>

TEST(Hexagon_BuildSequenceMeter_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSequenceMeter::Renderer renderer;
}

TEST(Hexagon_BuildSequenceMeter_RendererTest, run__returns_the_expected_response)
{
   Hexagon::BuildSequenceMeter::Renderer renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, renderer.run());
}
