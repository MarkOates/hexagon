
#include <gtest/gtest.h>

#include <Hexagon/System/Action/CheckGitSyncAndUpdatePowerbar.hpp>

TEST(Hexagon_System_Action_CheckGitSyncAndUpdatePowerbarTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::CheckGitSyncAndUpdatePowerbar check_git_sync_and_update_powerbar;
}

TEST(Hexagon_System_Action_CheckGitSyncAndUpdatePowerbarTest, run__returns_the_expected_response)
{
   Hexagon::System::Action::CheckGitSyncAndUpdatePowerbar check_git_sync_and_update_powerbar;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, check_git_sync_and_update_powerbar.run());
}
