
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
   Hexagon::ChatCPTIntegration::Messages::Text* as_text_message_0 =
      static_cast<Hexagon::ChatCPTIntegration::Messages::Text*>(messages[0]);
   EXPECT_EQ("Hey, if I tried to describe to you a theoretical programming language, do you think you might "
             "be able to write some code with it?  It's very similar to C++, but is nottated slightly differently, "
             "using a yaml file.",
             as_text_message_0->get_body()
         );
   EXPECT_EQ(true, messages[0]->get_conversation_id().empty());
   EXPECT_EQ(true, messages[0]->get_parent_id().empty());

   EXPECT_EQ(2, messages[1]->get_author_id());
   EXPECT_EQ("Messages/Text", messages[1]->get_type());
   Hexagon::ChatCPTIntegration::Messages::Text* as_text_message_1 =
      static_cast<Hexagon::ChatCPTIntegration::Messages::Text*>(messages[1]);
   EXPECT_EQ("It is possible that I could write code in a theoretical programming language that is similar to C++ "
             "and uses a YAML file for notation, assuming that I am provided with enough information about the "
             "language's syntax, semantics, and any built-in functions or libraries that are available."
             "\n\n"
             "To write code in a new language, it is helpful to have access to documentation or examples of how the "
             "language works, as well as a reference manual or other resources that describe the language's features "
             "and how to use them."
             "\n\n"
             "It would also be helpful to have a compiler or interpreter for the language, so that I can test and "
             "debug the code that I write."
             "\n\n"
             "Without knowing more about your theoretical programming language, it is "
             "difficult to say for certain whether I would be able to write code in it. However, as a general rule, "
             "it is often possible to learn and adapt to new programming languages, especially if they are similar "
             "to languages that one is already familiar with.",
             as_text_message_1->get_body()
         );
   EXPECT_EQ("25370edb-6c25-42a6-81ee-76acd77be211", messages[1]->get_conversation_id());
   EXPECT_EQ("f3212bc5-dd1b-440e-83bd-61b3c9add5d3", messages[1]->get_parent_id());
}


