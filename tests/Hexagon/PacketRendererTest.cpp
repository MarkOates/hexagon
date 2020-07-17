
#include <gtest/gtest.h>

#include <Hexagon/PacketRenderer.hpp>

TEST(Hexagon_PacketRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::PacketRenderer packet_renderer;
}

TEST(Hexagon_PacketRendererTest, run__returns_the_expected_response)
{
   Hexagon::PacketRenderer packet_renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, packet_renderer.run());
}
