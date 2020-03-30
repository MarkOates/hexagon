
#include <gtest/gtest.h>

#include <Hexagon/Git/Staged.hpp>

TEST(Hexagon_Git_StagedTest, can_be_created_without_blowing_up)
{
   Hexagon::Git::Staged staged;
}

TEST(Hexagon_Git_StagedTest, get_commit_everything_shell_command__returns_the_expected_value)
{
   Hexagon::Git::Staged staged("/A/Directory/Where/A/Project/Is/");
   std::string expected_command = "(cd /A/Directory/Where/A/Project/Is/ && git diff --staged)";
   std::string actual_command = staged.get_commit_everything_shell_command();
   EXPECT_EQ(expected_command, actual_command);
}

TEST(Hexagon_Git_StagedTest, get_staged_response__returns_the_expected_response)
{
   Hexagon::Git::Staged staged;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, staged.get_staged_response());
}
