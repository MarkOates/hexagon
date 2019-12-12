
#include <gtest/gtest.h>

#include <ApplicationController.hpp>

TEST(ApplicationControllerTest, can_be_created_without_blowing_up)
{
   ApplicationController application_controller;
}

TEST(ApplicationControllerTest, run__returns_the_expected_response)
{
   ApplicationController application_controller;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, application_controller.run());
}
