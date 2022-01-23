
#include <gtest/gtest.h>

#include <Hexagon/ObjectivesLog/ObjectiveRenderer.hpp>

TEST(Hexagon_ObjectivesLog_ObjectiveRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::ObjectivesLog::ObjectiveRenderer objective_renderer;
}

TEST(Hexagon_ObjectivesLog_ObjectiveRendererTest, run__returns_the_expected_response)
{
   Hexagon::ObjectivesLog::ObjectiveRenderer objective_renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, objective_renderer.run());
}
