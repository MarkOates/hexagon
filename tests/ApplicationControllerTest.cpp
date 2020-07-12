
#include <gtest/gtest.h>

#include <ApplicationController.hpp>

std::string TEST_CONFIG_FILENAME =
   "/Users/markoates/Repos/hexagon/tests/fixtures/hexagon.application_controller_test.cfg";


TEST(ApplicationControllerTest, can_be_created_without_blowing_up)
{
   ApplicationController application_controller;
}

TEST(ApplicationControllerTest, run_program__is_successful_and_will_shutdown_on_window_close)
{
   ApplicationController application_controller(TEST_CONFIG_FILENAME);
   application_controller.initialize();

   ALLEGRO_EVENT display_close_event;
   display_close_event.type = ALLEGRO_EVENT_DISPLAY_CLOSE;

   application_controller.emit_user_event(display_close_event);

   application_controller.run_event_loop();
   application_controller.shutdown();

   SUCCEED();
}

TEST(ApplicationControllerTest, build_allegro_version_string__will_create_the_expected_version)
{
   ApplicationController application_controller;
   std::string expected_version_string = "Allegro v5.2.7 r0";
   std::string actual_version_string = application_controller.build_allegro_version_string();
   ASSERT_EQ(expected_version_string, actual_version_string);
}

TEST(DISABLED_ApplicationControllerTest, run_program__will_open_the_component_navigator)
   // this is an incomplete test, it does not have any assertion in it and is not reliable in some
   // circumstances (multiple keypresses do sometimes not register).
   // here, I've kept the test in place so that the technique can be examined in the future.
{
   ApplicationController application_controller(TEST_CONFIG_FILENAME);
   application_controller.initialize();

   // open component navigator
   {
      ALLEGRO_EVENT e;
      e.type = ALLEGRO_EVENT_KEY_CHAR;
      e.keyboard.keycode = ALLEGRO_KEY_TAB;
      application_controller.emit_user_event(e);
   }

   // cursor down
   {
      ALLEGRO_EVENT ev;
      ev.type = ALLEGRO_EVENT_KEY_CHAR;
      ev.keyboard.keycode = ALLEGRO_KEY_J;
      application_controller.emit_user_event(ev);
   }

   // select option
   {
      ALLEGRO_EVENT ev;
      ev.type = ALLEGRO_EVENT_KEY_CHAR;
      ev.keyboard.keycode = ALLEGRO_KEY_ENTER;
      application_controller.emit_user_event(ev);
   }

   // close the window
   {
      ALLEGRO_EVENT display_close_event;
      display_close_event.type = ALLEGRO_EVENT_DISPLAY_CLOSE;
      application_controller.emit_user_event(display_close_event);
   }

   application_controller.run_event_loop();
   application_controller.shutdown();

   SUCCEED();
}

