
#include <gtest/gtest.h>

#include <Hexagon/Packet.hpp>

TEST(Hexagon_PacketTest, can_be_created_without_blowing_up)
{
   Hexagon::Packet packet;
}

TEST(Hexagon_PacketTest, has_the_expected_getters_with_the_expected_defaults)
{
   Hexagon::Packet packet;
   ASSERT_EQ(0, packet.get_searches_count());
   ASSERT_EQ(0, packet.get_saves_count());
}

TEST(Hexagon_PacketTest, has_the_expected_constructor_arguments)
{
   Hexagon::Packet packet(9, 7);
   ASSERT_EQ(9, packet.get_searches_count());
   ASSERT_EQ(7, packet.get_saves_count());
}

TEST(Hexagon_PacketTest, calculate_score__returns_the_expected_calculated_score)
{
   Hexagon::Packet packet(9, 7);
   ASSERT_EQ(16, packet.calculate_score());
}

