
#include <gtest/gtest.h>

#include <Hexagon/ChatCPTIntegration/Conversation.hpp>


TEST(Hexagon_ChatCPTIntegration_ConversationTest, can_be_created_without_blowing_up)
{
   Hexagon::ChatCPTIntegration::Conversation conversation;
}


TEST(Hexagon_ChatCPTIntegration_ConversationTest, load_from_log_text_file__will_load_the_expected_data)
{
   std::string FIXTURE_TEST_LOG_FILE = "/Users/markoates/Repos/ChatGPT/tests/fixtures/log_with_messages.txt";
   Hexagon::ChatCPTIntegration::Conversation conversation;

   conversation.load_from_log_text_file(FIXTURE_TEST_LOG_FILE);

   std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> messages = conversation.get_messages();
   ASSERT_EQ(15, messages.size());
}


