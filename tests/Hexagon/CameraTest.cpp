
#include <gtest/gtest.h>

#include <Hexagon/Camera.hpp>

TEST(Hexagon_CameraTest, can_be_created_without_blowing_up)
{
   Hexagon::Camera camera;
}

TEST(Hexagon_CameraTest, run__returns_the_expected_response)
{
   Hexagon::Camera camera;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, camera.run());
}
