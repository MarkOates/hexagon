
#include <gtest/gtest.h>

#include <IntegrationTests/Integrations.hpp>

TEST(IntegrationTests_IntegrationsTest, can_be_created_without_blowing_up)
{
   IntegrationTests::Integrations integrations;
}


///////////////////////////
// ApplicationController
///////////////////////////

std::string TEST_CONFIG_FILENAME =
   "/Users/markoates/Repos/hexagon/tests/fixtures/hexagon.application_controller_test.cfg";

#include <ApplicationController.hpp>

TEST(IntegrationsTests_IntegrationsTest, ApplicationController__will_use_the_component_navigator)
   // this is an incomplete test, it does not have any assertion in it and is not reliable in some
   // circumstances (multiple keypresses do sometimes not register).
   // here, I've kept the test in place so that the technique can be examined in the future.
{
   ApplicationController application_controller(TEST_CONFIG_FILENAME);
   application_controller.initialize();

   // open component navigator
   {
      ALLEGRO_EVENT ev;
      e.type = ALLEGRO_EVENT_KEY_CHAR;
      e.keyboard.keycode = ALLEGRO_KEY_TAB;
      application_controller.emit_user_event(ev);
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
