
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/ReportRenderers/Base.hpp>


TEST(Hexagon_BuildSystem_ReportRenderers_BaseTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::ReportRenderers::Base base;
}


TEST(Hexagon_BuildSystem_ReportRenderers_BaseTest, run__returns_the_expected_response)
{
   Hexagon::BuildSystem::ReportRenderers::Base base;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, base.run());
}

