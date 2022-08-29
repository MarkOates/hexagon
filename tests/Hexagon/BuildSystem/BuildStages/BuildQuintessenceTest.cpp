
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/BuildStages/BuildQuintessence.hpp>


TEST(Hexagon_BuildSystem_BuildStages_BuildQuintessenceTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::BuildStages::BuildQuintessence build_quintessence;
}


TEST(Hexagon_BuildSystem_BuildStages_BuildQuintessenceTest, has_the_expected_type)
{
   Hexagon::BuildSystem::BuildStages::BuildQuintessence build_quintessence;
   EXPECT_EQ("BuildQuintessence", build_quintessence.get_type());
}


