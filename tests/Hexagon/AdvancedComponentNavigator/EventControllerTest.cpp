
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


TEST(Hexagon_AdvancedComponentNavigator_EventControllerTest, process_local_event__processes_the_events)
{
   using Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator;
   std::map<std::string, std::function<void(AdvancedComponentNavigator&)>> event_dictionary = {
      { "move_cursor_up", &AdvancedComponentNavigator::move_cursor_up },
      { "move_cursor_down", &AdvancedComponentNavigator::move_cursor_down },
   };

   AdvancedComponentNavigator stage;
   Hexagon::AdvancedComponentNavigator::EventController event_controller(&stage, event_dictionary);

   event_controller.process_local_event("move_cursor_down");
   event_controller.process_local_event("move_cursor_down");
   event_controller.process_local_event("move_cursor_down");
   event_controller.process_local_event("move_cursor_up");

   EXPECT_EQ(2, stage.get_cursor_position());
}


TEST(Hexagon_AdvancedComponentNavigator_EventControllerTest,
   process_local_event__with_an_event_that_does_not_exist_throws_an_error)
{
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator stage;
   Hexagon::AdvancedComponentNavigator::EventController event_controller(&stage);

   std::string expected_error_message = "AdvancedComponentNavigator::EventController::process_local_event: " \
                                        "error: No local event named \"event_that_does_not_exist\" exists.";

   ASSERT_THROW_WITH_MESSAGE(event_controller.process_local_event("event_that_does_not_exist"),
                             std::runtime_error,
                             expected_error_message);
}


