
#include <gtest/gtest.h>

#include <Hexagon/ChatGPTIntegration/Chat/InputBox.hpp>


TEST(Hexagon_ChatGPTIntegration_Chat_InputBoxTest, can_be_created_without_blowing_up)
{
   Hexagon::ChatGPTIntegration::Chat::InputBox input_box;
}


TEST(Hexagon_ChatGPTIntegration_Chat_InputBoxTest, run__returns_the_expected_response)
{
   Hexagon::ChatGPTIntegration::Chat::InputBox input_box;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, input_box.run());
}


