
#include <gtest/gtest.h>

#include <Hexagon/Git/RemoteSyncChecker.hpp>

TEST(Hexagon_Git_RemoteSyncCheckerTest, can_be_created_without_blowing_up)
{
   Hexagon::Git::RemoteSyncChecker remote_sync_checker;
}

TEST(Hexagon_Git_RemoteSyncCheckerTest, run__returns_the_expected_response)
{
   Hexagon::Git::RemoteSyncChecker remote_sync_checker;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, remote_sync_checker.run());
}
