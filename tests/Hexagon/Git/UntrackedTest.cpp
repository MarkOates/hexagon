
#include <gtest/gtest.h>

#include <Hexagon/Git/Untracked.hpp>

TEST(Hexagon_Git_UntrackedTest, can_be_created_without_blowing_up)
{
   Hexagon::Git::Untracked untracked;
}

TEST(Hexagon_Git_UntrackedTest, run__returns_the_expected_response)
{
   Hexagon::Git::Untracked untracked;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, untracked.run());
}
