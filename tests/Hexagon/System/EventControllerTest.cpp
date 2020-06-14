
#include <gtest/gtest.h>

#include <Hexagon/System/EventController.hpp>

TEST(Hexagon_System_EventControllerTest, can_be_created_without_blowing_up)
{
   Hexagon::System::EventController event_controller;
}

TEST(Hexagon_System_EventControllerTest, run__returns_the_expected_response)
{
   Hexagon::System::EventController event_controller;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, event_controller.run());
}
