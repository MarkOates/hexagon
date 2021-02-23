
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/Controller.hpp>

TEST(Hexagon_BuildSystem_ControllerTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::Controller controller;
}

TEST(Hexagon_BuildSystem_ControllerTest, create__returns_the_expected_response)
{
   Hexagon::BuildSystem::Controller controller;
   std::string expected_string = "This is some text output by the fixture program.\n";
   EXPECT_EQ(expected_string, controller.create());
}
