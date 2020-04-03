
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

