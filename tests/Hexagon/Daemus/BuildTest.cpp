
#include <gtest/gtest.h>

#include <Hexagon/Daemus/Build.hpp>

TEST(Hexagon_Daemus_BuildTest, can_be_created_without_blowing_up)
{
   Hexagon::Daemus::Build build;
}

TEST(Hexagon_Daemus_BuildTest, run__returns_the_expected_response)
{
   Hexagon::Daemus::Build build;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, build.run());
}
