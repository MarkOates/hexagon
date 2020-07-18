
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::MatchesRegex;

#include <Hexagon/Git/Staged.hpp>

TEST(Hexagon_Git_StagedTest, can_be_created_without_blowing_up)
{
   Hexagon::Git::Staged staged;
}

TEST(Hexagon_Git_StagedTest, build_staged_files_shell_command__returns_the_expected_value)
{
   Hexagon::Git::Staged staged("/A/Directory/Where/A/Project/Is/");
   std::string expected_command = "(cd /A/Directory/Where/A/Project/Is/ && git diff --staged --name-only)";
   std::string actual_command = staged.build_staged_files_shell_command();
   EXPECT_EQ(expected_command, actual_command);
}

TEST(Hexagon_Git_StagedTest, get_staged_response__returns_the_expected_response)
{
   Hexagon::Git::Staged staged;
   std::string a_regex_that_will_match_a_bunch_of_git_diff_staged_output = ".*";
   EXPECT_THAT(staged.get_staged_response(), MatchesRegex(a_regex_that_will_match_a_bunch_of_git_diff_staged_output));
}

TEST(Hexagon_Git_StagedTest, get_staged_response__will_not_output_anything_to_stdout)
{
   Hexagon::Git::Staged staged;

   testing::internal::CaptureStdout();
   staged.get_staged_response();
   std::string captured_cout_output = testing::internal::GetCapturedStdout();

   EXPECT_EQ(true, captured_cout_output.empty());
}

TEST(Hexagon_Git_StagedTest, DISABLED_get_staged_response__will_return_a_list_of_untracked_files)
{
   Hexagon::Git::Staged staged;

   std::string expected_response = "tests/Hexagon/Git/StagedTest.cpp\n";
   std::string actual_response = staged.get_staged_response();

   EXPECT_EQ(expected_response, actual_response);
}

