
#include <gtest/gtest.h>

#include <Hexagon/ElementFX/WindowSpawnMotionFX.hpp>

TEST(Hexagon_ElementFX_WindowSpawnMotionFXTest, can_be_created_without_blowing_up)
{
   Hexagon::ElementFX::WindowSpawnMotionFX window_spawn_motion_fx;
}

TEST(Hexagon_ElementFX_WindowSpawnMotionFXTest, run__returns_the_expected_response)
{
   Hexagon::ElementFX::WindowSpawnMotionFX window_spawn_motion_fx;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, window_spawn_motion_fx.run());
}
