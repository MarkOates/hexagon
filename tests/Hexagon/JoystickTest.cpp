
#include <gtest/gtest.h>

#include <Hexagon/Joystick.hpp>

TEST(Hexagon_JoystickTest, can_be_created_without_blowing_up)
{
   Hexagon::Joystick joystick;
}

TEST(Hexagon_JoystickTest, run__returns_the_expected_response)
{
   Hexagon::Joystick joystick;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, joystick.run());
}
