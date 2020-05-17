
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/AdvancedComponentNavigator/EventController.hpp>

TEST(Hexagon_AdvancedComponentNavigator_EventControllerTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedComponentNavigator::EventController event_controller;
}

TEST(Hexagon_AdvancedComponentNavigator_StageTest, process_local_event__processes_the_events)
{
   Hexagon::AdvancedComponentNavigator::Stage stage;
   Hexagon::AdvancedComponentNavigator::EventController event_controller(&stage);

   event_controller.process_local_event("move_cursor_down");
   event_controller.process_local_event("move_cursor_down");
   event_controller.process_local_event("move_cursor_down");
   event_controller.process_local_event("move_cursor_up");

   EXPECT_EQ(2, stage.get_cursor_position());
}

TEST(Hexagon_AdvancedComponentNavigator_StageTest,
   process_local_event__with_an_event_that_does_not_exist_throws_an_error)
{
   Hexagon::AdvancedComponentNavigator::Stage stage;
   Hexagon::AdvancedComponentNavigator::EventController event_controller(&stage);

   event_controller.process_local_event("event_that_does_not_exist");
}

