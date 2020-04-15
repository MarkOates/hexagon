
#include <gtest/gtest.h>

#include <Hexagon/Git/CommitStagedWithMessage.hpp>

TEST(Hexagon_Git_CommitStagedWithMessageTest, can_be_created_without_blowing_up)
{
   Hexagon::Git::CommitStagedWithMessage commit_staged_with_message;
}

TEST(DISABLED_Hexagon_Git_CommitStagedWithMessageTest,
   commit__is_not_tested_because_it_is_destructive_to_the_live_environment)
{
   Hexagon::Git::CommitStagedWithMessage commit_staged_with_message;
   //EXPECT_EQ(expected_string, commit_staged_with_message.commit());
}

TEST(Hexagon_Git_CommitStagedWithMessageTest,
   build_sanitized_commit_message__returns_the_commit_message_with_double_quote_and_slash_characters_replaced_with_pound)
{
   std::string project_directory = "/Users/markoates/Repos/hexagon/";
   std::string commit_message = "Commit message with unsafe \"quotes\" and \\slashes\\";
   Hexagon::Git::CommitStagedWithMessage commit_staged_with_message(project_directory, commit_message);

   std::string expected_sanitized_message = "* Commit message with unsafe #quotes# and #slashes#";

   EXPECT_EQ(expected_sanitized_message, commit_staged_with_message.build_sanitized_commit_message());
}

TEST(Hexagon_Git_CommitStagedWithMessageTest,
   build_shell_command__returns_the_expected_shell_command)
{

   std::string project_directory = "/Users/markoates/Repos/hexagon/";
   std::string commit_message = "Commit message with unsafe \"quotes\" and \\slashes\\";
   Hexagon::Git::CommitStagedWithMessage commit_staged_with_message(project_directory, commit_message);

   std::string expected_shell_command = "(cd /Users/markoates/Repos/hexagon/ && git commit -m " \
                                        "\"* Commit message with unsafe #quotes# and #slashes#\")";

   EXPECT_EQ(expected_shell_command, commit_staged_with_message.build_shell_command());
}

