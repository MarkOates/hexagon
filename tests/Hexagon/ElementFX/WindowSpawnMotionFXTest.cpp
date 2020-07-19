
#include <gtest/gtest.h>

#include <Hexagon/ElementFX/WindowSpawnMotionFX.hpp>

TEST(Hexagon_ElementFX_WindowSpawnMotionFXTest, can_be_created_without_blowing_up)
{
   Hexagon::ElementFX::WindowSpawnMotionFX window_spawn_motion_fx;
}

TEST(Hexagon_ElementFX_WindowSpawnMotionFXTest, construct_modified_window__does_not_blow_up)
{
   Hexagon::ElementFX::WindowSpawnMotionFX window_spawn_motion_fx;
   window_spawn_motion_fx.construct_modified_window();
   SUCCEED();
}

TEST(Hexagon_ElementFX_WindowSpawnMotionFXTest, construct_modified_window__returns_a_window)
{
   Hexagon::ElementFX::WindowSpawnMotionFX window_spawn_motion_fx;
   Hexagon::Elements::Window expected_result_window;
   Hexagon::Elements::Window actual_result_window = window_spawn_motion_fx.construct_modified_window();

   EXPECT_EQ(expected_result_window.get_width(), actual_result_window.get_width());
   EXPECT_EQ(expected_result_window.get_height(), actual_result_window.get_width());
}
