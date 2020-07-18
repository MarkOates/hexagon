
#include <gtest/gtest.h>

#include <Hexagon/System/Action/CheckGitLocalStatusAndUpdatePowerbar.hpp>

TEST(Hexagon_System_Action_CheckGitLocalStatusAndUpdatePowerbarTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar check_git_local_status_and_update_powerbar;
}

TEST(Hexagon_System_Action_CheckGitLocalStatusAndUpdatePowerbarTest, run__returns_the_expected_response)
{
   Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar check_git_local_status_and_update_powerbar;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, check_git_local_status_and_update_powerbar.run());
}
