
#include <gtest/gtest.h>

#include <Hexagon/System/Action/CheckGitUntrackedModifiedStagedAndUpdatePowerbar.hpp>

TEST(Hexagon_System_Action_CheckGitUntrackedModifiedStagedAndUpdatePowerbarTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::CheckGitUntrackedModifiedStagedAndUpdatePowerbar check_git_untracked_modified_staged_and_update_powerbar;
}

TEST(Hexagon_System_Action_CheckGitUntrackedModifiedStagedAndUpdatePowerbarTest, run__returns_the_expected_response)
{
   Hexagon::System::Action::CheckGitUntrackedModifiedStagedAndUpdatePowerbar check_git_untracked_modified_staged_and_update_powerbar;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, check_git_untracked_modified_staged_and_update_powerbar.run());
}
