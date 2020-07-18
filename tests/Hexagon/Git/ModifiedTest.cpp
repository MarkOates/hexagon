
#include <gtest/gtest.h>

#include <Hexagon/Git/Modified.hpp>

TEST(Hexagon_Git_ModifiedTest, can_be_created_without_blowing_up)
{
   Hexagon::Git::Modified modified;
}

TEST(Hexagon_Git_ModifiedTest, build_tracked_files_shell_command__returns_the_expected_value)
{
   Hexagon::Git::Modified modified("/A/Directory/Where/A/Project/Is/");
   std::string expected_command = "(cd /A/Directory/Where/A/Project/Is/ && git diff --name-only)";
   std::string actual_command = modified.build_tracked_files_shell_command();
   EXPECT_EQ(expected_command, actual_command);
}

TEST(Hexagon_Git_ModifiedTest, get_shell_response__will_not_output_anything_to_stdout)
{
   Hexagon::Git::Modified modified;

   testing::internal::CaptureStdout();
   modified.get_shell_response();
   std::string captured_cout_output = testing::internal::GetCapturedStdout();

   EXPECT_EQ(true, captured_cout_output.empty());
}

TEST(Hexagon_Git_ModifiedTest, DISABLED_get_shell_response__will_return_a_list_of_modified_files)
{
   Hexagon::Git::Modified modified;

   std::string expected_response = "tests/Hexagon/Git/ModifiedTest.cpp\n";
   std::string actual_response = modified.get_shell_response();

   EXPECT_EQ(expected_response, actual_response);
}

