
#include <gtest/gtest.h>

#include <Hexagon/System/Action/CheckGitSyncAndUpdatePowerbar.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

TEST(Hexagon_System_Action_CheckGitSyncAndUpdatePowerbarTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::CheckGitSyncAndUpdatePowerbar check_git_sync_and_update_powerbar;
}

TEST(Hexagon_System_Action_CheckGitSyncAndUpdatePowerbarTest,
   execute__without_a_valid_powerbar__throws_an_error)
{
   Hexagon::System::Action::CheckGitSyncAndUpdatePowerbar check_git_sync_and_update_powerbar;
   ASSERT_THROW_GUARD_ERROR(
      check_git_sync_and_update_powerbar.execute(),
      "Hexagon::System::Action::CheckGitSyncAndUpdatePowerbar::execute",
      "powerbar"
   );
}

