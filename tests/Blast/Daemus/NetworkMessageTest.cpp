
#include <gtest/gtest.h>

#include <Blast/Daemus/NetworkMessage.hpp>

TEST(Blast_Daemus_NetworkMessageTest, can_be_created_without_blowing_up)
{
   Blast::Daemus::NetworkMessage network_message;
}

TEST(Blast_Daemus_NetworkMessageTest, run__returns_the_expected_response)
{
   Blast::Daemus::NetworkMessage network_message;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, network_message.run());
}
