
#include <gtest/gtest.h>

#include <Hexagon/Git/Untracked.hpp>

TEST(Hexagon_Git_UntrackedTest, can_be_created_without_blowing_up)
{
   Hexagon::Git::Untracked untracked;
}

TEST(Hexagon_Git_UntrackedTest, build_tracked_files_shell_command__returns_the_expected_value)
{
   Hexagon::Git::Untracked untracked("/A/Directory/Where/A/Project/Is/");
   std::string expected_command = "(cd /A/Directory/Where/A/Project/Is/ && git ls-files --others --exclude-standard)";
   std::string actual_command = untracked.build_tracked_files_shell_command();
   EXPECT_EQ(expected_command, actual_command);
}

TEST(Hexagon_Git_UntrackedTest, get_shell_response__will_not_output_anything_to_stdout)
{
   Hexagon::Git::Untracked untracked;

   testing::internal::CaptureStdout();
   untracked.get_shell_response();
   std::string captured_cout_output = testing::internal::GetCapturedStdout();

   EXPECT_EQ(true, captured_cout_output.empty());
}

TEST(Hexagon_Git_UntrackedTest, DISABLED_get_shell_response__will_return_a_list_of_untracked_files)
{
   Hexagon::Git::Untracked untracked;

   std::string expected_response = "foobar.txt\n";
   std::string actual_response = untracked.get_shell_response();

   EXPECT_EQ(expected_response, actual_response);
}

