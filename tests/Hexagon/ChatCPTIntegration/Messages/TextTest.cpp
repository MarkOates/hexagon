
#include <gtest/gtest.h>

#include <Hexagon/ChatCPTIntegration/Messages/Text.hpp>


TEST(Hexagon_ChatCPTIntegration_Messages_TextTest, can_be_created_without_blowing_up)
{
   Hexagon::ChatCPTIntegration::Messages::Text text;
}


TEST(Hexagon_ChatCPTIntegration_Messages_TextTest, TYPE__has_the_expected_value)
{
   Hexagon::ChatCPTIntegration::Messages::Text text;
   EXPECT_EQ("Messages/Text", text.get_type());
}


TEST(Hexagon_ChatCPTIntegration_Messages_TextTest, type__has_the_expected_value_matching_TYPE)
{
   Hexagon::ChatCPTIntegration::Messages::Text text;
   EXPECT_EQ(Hexagon::ChatCPTIntegration::Messages::Text::TYPE, text.get_type());
}


