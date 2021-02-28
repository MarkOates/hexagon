
#include <gtest/gtest.h>

#include <Hexagon/System/Action/SendMessageToDaemusToBuild.hpp>

TEST(Hexagon_System_Action_SendMessageToDaemusToBuildTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::SendMessageToDaemusToBuild send_message_to_daemus_to_build;
}

TEST(Hexagon_System_Action_SendMessageToDaemusToBuildTest, execute__returns_the_expected_response)
{
   Hexagon::System::Action::SendMessageToDaemusToBuild send_message_to_daemus_to_build;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, send_message_to_daemus_to_build.execute());
}
