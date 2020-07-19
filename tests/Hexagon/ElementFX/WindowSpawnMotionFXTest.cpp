
#include <gtest/gtest.h>

#include <Hexagon/ElementFX/WindowSpawnMotionFX.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement3d.h>

class Hexagon_ElementFX_WindowSpawnMotionFXTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_ElementFX_WindowSpawnMotionFXTest_WithEmptyFixture() {}
};

class Hexagon_ElementFX_WindowSpawnMotionFXTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;

public:
   Hexagon_ElementFX_WindowSpawnMotionFXTest_WithAllegroRenderingFixture()
      : display(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      ASSERT_EQ(true, al_init_primitives_addon());
      display = al_create_display(1280*2, 720*2);
      al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
   }

   virtual void TearDown() override
   {
      al_destroy_display(display);
      al_uninstall_system();
   }

   placement3d centered_placement(float width, float height)
   {
      placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0f);
      place.size = vec3d(width, height, 0);
      return place;
   }
};

TEST_F(Hexagon_ElementFX_WindowSpawnMotionFXTest_WithEmptyFixture,
   can_be_created_without_blowing_up)
{
   Hexagon::ElementFX::WindowSpawnMotionFX window_spawn_motion_fx;
}

TEST_F(Hexagon_ElementFX_WindowSpawnMotionFXTest_WithEmptyFixture,
   construct_modified_window__does_not_blow_up)
{
   Hexagon::ElementFX::WindowSpawnMotionFX window_spawn_motion_fx;
   window_spawn_motion_fx.construct_modified_window();
   SUCCEED();
}

TEST_F(Hexagon_ElementFX_WindowSpawnMotionFXTest_WithEmptyFixture,
   construct_modified_window__returns_a_window)
{
   Hexagon::ElementFX::WindowSpawnMotionFX window_spawn_motion_fx;
   Hexagon::Elements::Window expected_result_window;
   Hexagon::Elements::Window actual_result_window = window_spawn_motion_fx.construct_modified_window();

   EXPECT_EQ(expected_result_window.get_width(), actual_result_window.get_width());
   EXPECT_EQ(expected_result_window.get_height(), actual_result_window.get_width());
}
