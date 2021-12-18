
#include <gtest/gtest.h>

#include <Hexagon/Camera.hpp>


class Hexagon_CameraTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_CameraTest_WithEmptyFixture() {}
};


class Hexagon_CameraTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   //AllegroFlare::FontBin font_bin;

public:
   Hexagon_CameraTest_WithAllegroRenderingFixture()
      : display(nullptr)
      //, font_bin()
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      //ASSERT_EQ(true, al_init_primitives_addon());
      //ASSERT_EQ(true, al_init_font_addon());
      //ASSERT_EQ(true, al_init_ttf_addon());
      display = al_create_display(1280*2, 720*2);
      //display = al_create_display(1920 / 2 * 4, 1080 / 2 * 4);
      //font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
      al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
   }

   virtual void TearDown() override
   {
      //font_bin.clear();
      //al_shutdown_ttf_addon(); // this is required otherwise subsequent al_init_ttf_addon will not work
                                 // see https://www.allegro.cc/forums/thread/618183
      al_destroy_display(display);
      al_uninstall_system();
   }

   //placement3d build_centered_placement(float width, float height)
   //{
   //   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0f);
   //   place.size = vec3d(width, height, 0);
   //   return place;
   //}
};


TEST_F(Hexagon_CameraTest_WithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Camera camera;
}

TEST_F(Hexagon_CameraTest_WithAllegroRenderingFixture, setup_camera_perspective__can_be_created_without_blowing_up)
{
   ALLEGRO_BITMAP *bitmap = al_get_backbuffer(display);
   Hexagon::Camera camera;
   camera.setup_camera_perspective(bitmap);
}

