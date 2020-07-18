
#include <gtest/gtest.h>

#include <Hexagon/Git/Modified.hpp>

TEST(Hexagon_Git_ModifiedTest, can_be_created_without_blowing_up)
{
   Hexagon::Git::Modified modified;
}

TEST(Hexagon_Git_ModifiedTest, run__returns_the_expected_response)
{
   Hexagon::Git::Modified modified;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, modified.run());
}
