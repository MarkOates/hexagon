
#include <gtest/gtest.h>

#include <Hexagon/ChatCPTIntegration/Conversation.hpp>


TEST(Hexagon_ChatCPTIntegration_ConversationTest, can_be_created_without_blowing_up)
{
   Hexagon::ChatCPTIntegration::Conversation conversation;
}


TEST(Hexagon_ChatCPTIntegration_ConversationTest, run__returns_the_expected_response)
{
   Hexagon::ChatCPTIntegration::Conversation conversation;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, conversation.run());
}


