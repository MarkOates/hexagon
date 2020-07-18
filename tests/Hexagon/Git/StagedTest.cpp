
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::MatchesRegex;

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
   std::string a_regex_that_will_match_a_bunch_of_git_diff_staged_output = ".*";
   EXPECT_THAT(staged.get_staged_response(), MatchesRegex(a_regex_that_will_match_a_bunch_of_git_diff_staged_output));
}
