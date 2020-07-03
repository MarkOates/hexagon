
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
   //application_controller.run_program();
}

