
#include <gtest/gtest.h>

#include <Hexagon/Git/RemoteSyncChecker.hpp>

TEST(Hexagon_Git_RemoteSyncCheckerTest, can_be_created_without_blowing_up)
{
   Hexagon::Git::RemoteSyncChecker remote_sync_checker;
}

TEST(Hexagon_Git_RemoteSyncCheckerTest, repo_name__has_a_getter_and_the_expected_default)
{
   Hexagon::Git::RemoteSyncChecker remote_sync_checker;
   EXPECT_EQ("blast", remote_sync_checker.get_repo_name());
}

TEST(Hexagon_Git_RemoteSyncCheckerTest, repos_directory__has_a_getter_and_the_expected_default)
{
   Hexagon::Git::RemoteSyncChecker remote_sync_checker;
   EXPECT_EQ("~/Repos", remote_sync_checker.get_repos_directory());
}

//TEST(Hexagon_Git_RemoteSyncCheckerTest, is_in_sync_with_remote__returns_true_when_the_repo_is_in_sync)
//{
//   std::string repo_that_is_expected_to_be_in_sync = "blast";
//   Hexagon::Git::RemoteSyncChecker remote_sync_checker(repo_that_is_expected_to_be_in_sync);
//   EXPECT_EQ(true, remote_sync_checker.is_in_sync_with_remote());
//}

//TEST(Hexagon_Git_RemoteSyncCheckerTest, is_in_sync_with_remote__returns_false_when_the_repo_is_not_in_sync)
//{
//   std::string repo_that_is_expected_to_be_out_of_sync = "hexagon";
//   Hexagon::Git::RemoteSyncChecker remote_sync_checker(repo_that_is_expected_to_be_out_of_sync);
//   EXPECT_EQ(false, remote_sync_checker.is_in_sync_with_remote());
//}

