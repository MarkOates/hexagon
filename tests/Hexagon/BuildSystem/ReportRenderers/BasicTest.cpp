
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/ReportRenderers/Basic.hpp>


TEST(Hexagon_BuildSystem_ReportRenderers_BasicTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::ReportRenderers::Basic basic;
}


TEST(Hexagon_BuildSystem_ReportRenderers_BasicTest, run__returns_the_expected_response)
{
   Hexagon::BuildSystem::ReportRenderers::Basic basic;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, basic.run());
}

