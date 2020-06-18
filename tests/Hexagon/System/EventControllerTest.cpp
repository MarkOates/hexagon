
#include <gtest/gtest.h>

#include <Hexagon/System/EventController.hpp>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

TEST(Hexagon_System_EventControllerTest, can_be_created_without_blowing_up)
{
   Hexagon::System::EventController event_controller;
}

TEST(Hexagon_System_EventControllerTest, process_local_event__without_a_valid_system_raises_an_error)
{
   Hexagon::System::EventController event_controller;
   std::string expected_error_message = "EventController::process_local_event: error: guard \"system\" not met";
   ASSERT_THROW_WITH_MESSAGE(event_controller.process_local_event(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_EventControllerTest, process_local_event__responds_to_the_expected_mappings)
{
}

