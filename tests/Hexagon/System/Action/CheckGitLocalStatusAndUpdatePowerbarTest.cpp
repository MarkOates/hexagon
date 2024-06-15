
#include <gtest/gtest.h>

#include <Hexagon/System/Action/CheckGitLocalStatusAndUpdatePowerbar.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <Hexagon/Powerbar/Powerbar.hpp>

TEST(Hexagon_System_Action_CheckGitLocalStatusAndUpdatePowerbarTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar action;
}

TEST(Hexagon_System_Action_CheckGitLocalStatusAndUpdatePowerbarTest,
   execute__without_a_valid_powerbar__throws_an_error)
{
   Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar action;
   ASSERT_THROW_GUARD_ERROR(
      action.execute(),
      "Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar::execute",
      "powerbar"
   );
}

TEST(Hexagon_System_Action_CheckGitLocalStatusAndUpdatePowerbarTest,
   execute__does_not_blow_up)
{
   std::string current_project_directory = "/Users/markoates/Repos/hexagon/";
   Hexagon::Powerbar::Powerbar powerbar;
   Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar action(current_project_directory, &powerbar);
   ASSERT_EQ(true, action.execute());
}

TEST(Hexagon_System_Action_CheckGitLocalStatusAndUpdatePowerbarTest,
   DISABLED_execute__updates_the_powerbar)
{
   std::string current_project_directory = "/Users/markoates/Repos/hexagon/";
   Hexagon::Powerbar::Powerbar powerbar;
   Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar action(current_project_directory, &powerbar);

   ASSERT_EQ(true, action.execute());

   ASSERT_EQ(true, powerbar.get_files_are_modified());  // (hint: modify any file)
   ASSERT_EQ(true, powerbar.get_files_are_staged());    // (hint: stage any file)
   ASSERT_EQ(true, powerbar.get_files_are_untracked()); // (hint: touch foo.txt)
}

