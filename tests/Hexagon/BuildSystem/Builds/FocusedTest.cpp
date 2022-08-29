
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/Builds/Focused.hpp>


TEST(Hexagon_BuildSystem_Builds_FocusedTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::Builds::Focused focused;
}


TEST(Hexagon_BuildSystem_Builds_FocusedTest, has_the_expected_type)
{
   Hexagon::BuildSystem::Builds::Focused focused;
   EXPECT_EQ("Focused", focused.get_type());
}


