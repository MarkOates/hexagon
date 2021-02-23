
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/Build.hpp>

TEST(Hexagon_BuildSystem_BuildTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::Build build;
}

TEST(Hexagon_BuildSystem_BuildTest, status__has_a_getter__and_is_set_to_undefined)
{
   Hexagon::BuildSystem::Build build;
   std::string expected_string = "undefined";
   EXPECT_EQ(expected_string, build.get_status());
}
