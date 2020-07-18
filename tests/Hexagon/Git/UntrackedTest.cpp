
#include <gtest/gtest.h>

#include <Hexagon/Git/Untracked.hpp>

TEST(Hexagon_Git_UntrackedTest, can_be_created_without_blowing_up)
{
   Hexagon::Git::Untracked untracked;
}

TEST(Hexagon_Git_UntrackedTest, build_staged_files_shell_command__returns_the_expected_value)
{
   Hexagon::Git::Untracked untracked("/A/Directory/Where/A/Project/Is/");
   std::string expected_command = "(cd /A/Directory/Where/A/Project/Is/ && git ls-files --others --exclude-standard)";
   std::string actual_command = untracked.build_tracked_files_shell_command();
   EXPECT_EQ(expected_command, actual_command);
}

