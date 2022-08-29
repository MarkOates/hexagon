
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/BuildStages/BuildPrograms.hpp>


TEST(Hexagon_BuildSystem_BuildStages_BuildProgramsTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::BuildStages::BuildPrograms build_programs;
}


TEST(Hexagon_BuildSystem_BuildStages_BuildProgramsTest, has_the_expected_type)
{
   Hexagon::BuildSystem::BuildStages::BuildPrograms build_programs;
   EXPECT_EQ("BuildPrograms", build_programs.get_type());
}


