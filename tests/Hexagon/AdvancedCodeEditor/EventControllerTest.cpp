
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/EventController.hpp>

TEST(Hexagon_AdvancedCodeEditor_EventControllerTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::EventController event_controller;
}

TEST(Hexagon_AdvancedCodeEditor_EventControllerTest, run__returns_the_expected_response)
{
   Hexagon::AdvancedCodeEditor::EventController event_controller;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, event_controller.run());
}
