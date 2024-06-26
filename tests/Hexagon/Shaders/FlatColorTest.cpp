
#include <gtest/gtest.h>

#include <Hexagon/Shaders/FlatColor.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro_flare/placement2d.h>


class Hexagon_Shaders_FlatColorTest : public ::testing::Test
{
protected:
   ALLEGRO_DISPLAY *display;

   Hexagon_Shaders_FlatColorTest()
      : display(nullptr)
   {
   }

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());

      al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
      ASSERT_EQ(ALLEGRO_OPENGL, al_get_new_display_flags() & ALLEGRO_OPENGL);
      ASSERT_EQ(ALLEGRO_PROGRAMMABLE_PIPELINE, al_get_new_display_flags() & ALLEGRO_PROGRAMMABLE_PIPELINE);
      ALLEGRO_DISPLAY *display = al_create_display(800, 600);
      ASSERT_NE(nullptr, display);
   }

   virtual void TearDown() override
   {
      if (al_get_current_display()) al_destroy_display(al_get_current_display());
      al_uninstall_system();
   }

   ALLEGRO_DISPLAY *get_display()
   {
      return display;
   }
};


TEST_F(Hexagon_Shaders_FlatColorTest, can_be_created_without_blowing_up)
{
   Hexagon::Shaders::FlatColor flat_color_shader;
   SUCCEED();
}


TEST_F(Hexagon_Shaders_FlatColorTest, activate__before_being_initialized_raises_an_exception)
{
   Hexagon::Shaders::FlatColor flat_color_shader;
   //std::string expected_error_message = "FlatColor::activate: error: guard \"initialized\" not met";
   //ASSERT_THROW_WITH_MESSAGE(flat_color_shader.activate(), std::runtime_error, expected_error_message);
   EXPECT_THROW_GUARD_ERROR(
      flat_color_shader.activate(),
      "Hexagon::Shaders::FlatColor::activate",
      "initialized"
   );
}


TEST_F(Hexagon_Shaders_FlatColorTest, initialize__works_without_blowing_up)
{
   Hexagon::Shaders::FlatColor flat_color_shader;
   flat_color_shader.initialize();
   SUCCEED();
}


TEST_F(Hexagon_Shaders_FlatColorTest, activate__works_without_blowing_up)
{
   Hexagon::Shaders::FlatColor flat_color_shader;

   flat_color_shader.initialize();
   flat_color_shader.activate();
}


TEST_F(Hexagon_Shaders_FlatColorTest, when_active__renders_the_image_with_the_flat_color)
{
   Hexagon::Shaders::FlatColor flat_color_shader;

   flat_color_shader.initialize();
   flat_color_shader.activate();

   al_init_image_addon();

   ALLEGRO_BITMAP *test_image =
      al_load_bitmap("/Users/markoates/Repos/hexagon/tests/fixtures/data/bitmaps/billboarding_tester_sprite.png");
   ASSERT_NE(nullptr, test_image);


   ALLEGRO_COLOR color = al_color_name("red");

   flat_color_shader.set_flat_color(color);

   ALLEGRO_DISPLAY *current_display = al_get_current_display();
   ASSERT_NE(nullptr, current_display);

   placement2d place(
         al_get_display_width(current_display)/2,
         al_get_display_height(current_display)/2,
         al_get_bitmap_width(test_image),
         al_get_bitmap_height(test_image));
   place.scale = vec2d(4, 4);
   place.start_transform();
   al_draw_bitmap(test_image, 0, 0, 0);
   place.restore_transform();

   ALLEGRO_COLOR expected_color = color;
   ALLEGRO_COLOR actual_color = al_get_pixel(
         al_get_backbuffer(current_display),
         al_get_display_width(current_display)/2,
         al_get_display_height(current_display)/2
      );

   ASSERT_EQ(color.r, actual_color.r);
   ASSERT_EQ(color.g, actual_color.g);
   ASSERT_EQ(color.b, actual_color.b);
   ASSERT_EQ(color.a, actual_color.a);

   std::string tmp_path = "/Users/markoates/Repos/hexagon/tmp/";
   std::string output_image_full_filename = tmp_path + "when_activated__renders_bitmaps_with_a_solid_tinted_overlay.png";
   ASSERT_EQ(true, al_save_bitmap(output_image_full_filename.c_str(), al_get_backbuffer(current_display)));
}

