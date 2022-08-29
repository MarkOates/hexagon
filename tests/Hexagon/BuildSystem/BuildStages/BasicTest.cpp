
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/BuildStages/Basic.hpp>


TEST(Hexagon_BuildSystem_BuildStages_BasicTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::BuildStages::Basic basic;
}


TEST(Hexagon_BuildSystem_BuildStages_BasicTest, has_the_expected_type)
{
   Hexagon::BuildSystem::BuildStages::Basic basic;
   EXPECT_EQ("Basic", basic.get_type());
}


