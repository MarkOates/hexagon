
#include <gtest/gtest.h>

#include <Hexagon/ChatCPTIntegration/Conversation.hpp>

#include <Hexagon/ChatCPTIntegration/Messages/Text.hpp>


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

   EXPECT_EQ(1, messages[0]->get_author_id());
   EXPECT_EQ("Messages/Text", messages[0]->get_type());
   Hexagon::ChatCPTIntegration::Messages::Text* as_text_message =
      static_cast<Hexagon::ChatCPTIntegration::Messages::Text*>(messages[0]);
   EXPECT_EQ("Hey, if I tried to describe to you a theoretical programming language, do you think you might "
             "be able to write some code with it?  It's very similar to C++, but is nottated slightly differently, "
             "using a yaml file.", as_text_message->get_body());

   EXPECT_EQ(2, messages[1]->get_author_id());
   EXPECT_EQ("Messages/Text", messages[1]->get_type());
}


