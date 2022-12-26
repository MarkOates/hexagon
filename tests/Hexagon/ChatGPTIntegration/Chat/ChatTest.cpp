
#include <gtest/gtest.h>

#include <Hexagon/ChatGPTIntegration/Chat/Chat.hpp>


TEST(Hexagon_ChatGPTIntegration_Chat_ChatTest, can_be_created_without_blowing_up)
{
   Hexagon::ChatGPTIntegration::Chat::Chat chat;
}


TEST(Hexagon_ChatGPTIntegration_Chat_ChatTest, run__returns_the_expected_response)
{
   Hexagon::ChatGPTIntegration::Chat::Chat chat;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, chat.run());
}


