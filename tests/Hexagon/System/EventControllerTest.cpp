
#include <gtest/gtest.h>

#include <Hexagon/System/EventController.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>


TEST(Hexagon_System_EventControllerTest, can_be_created_without_blowing_up)
{
   Hexagon::System::EventController event_controller;
}

TEST(Hexagon_System_EventControllerTest, process_local_event__without_a_valid_system_raises_an_error)
{
   Hexagon::System::EventController event_controller;
   ASSERT_THROW_GUARD_ERROR(
      event_controller.process_local_event(),
      "Hexagon::System::EventController::process_local_event",
      "system"
   );
}

TEST(Hexagon_System_EventControllerTest, DISABLED__process_local_event__responds_to_the_expected_mappings)
{
   // TODO
}

