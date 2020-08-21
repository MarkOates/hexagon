
#include <gtest/gtest.h>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <Hexagon/Shaders/Smiley.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro_flare/placement2d.h>
#include <allegro_flare/placement3d.h>


class Hexagon_Shaders_SmileyTest : public ::testing::Test
{
protected:
   ALLEGRO_DISPLAY *display;

   Hexagon_Shaders_SmileyTest()
      : display(nullptr)
   {}

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


class Hexagon_Shaders_SmileyTest_WithEventQueueFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   AllegroFlare::FontBin font_bin;
   ALLEGRO_EVENT_QUEUE *event_queue;

public:
   Hexagon_Shaders_SmileyTest_WithEventQueueFixture()
      : display(nullptr)
      , font_bin()
      , event_queue(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      al_init_primitives_addon();
      al_init_font_addon();
      al_init_ttf_addon();
      al_install_keyboard();

      event_queue = al_create_event_queue();
      al_register_event_source(event_queue, al_get_keyboard_event_source());

      font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");

      al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
      ASSERT_EQ(ALLEGRO_OPENGL, al_get_new_display_flags() & ALLEGRO_OPENGL);
      ASSERT_EQ(ALLEGRO_PROGRAMMABLE_PIPELINE, al_get_new_display_flags() & ALLEGRO_PROGRAMMABLE_PIPELINE);
      display = al_create_display(16 * 80, 9 * 80);
      ASSERT_NE(nullptr, display);

      al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.05f, 0.05f});
   }

   virtual void TearDown() override
   {
      font_bin.clear();
      al_destroy_display(display);
      al_destroy_event_queue(event_queue);
      al_shutdown_ttf_addon(); // this is required otherwise subsequent al_init_ttf_addon will not work
      al_uninstall_system();
   }

   placement3d centered_placement(float width, float height)
   {
      placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0f);
      place.size = vec3d(width, height, 0);
      return place;
   }
};


TEST_F(Hexagon_Shaders_SmileyTest, can_be_created_without_blowing_up)
{
   Hexagon::Shaders::Smiley smiley_shader;
   SUCCEED();
}


TEST_F(Hexagon_Shaders_SmileyTest, activate__before_being_initialized_raises__an_exception)
{
   Hexagon::Shaders::Smiley smiley_shader;
   std::string expected_error_message = "Smiley::activate: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(smiley_shader.activate(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_Shaders_SmileyTest, initialize__works_without_blowing_up)
{
   Hexagon::Shaders::Smiley smiley_shader;
   smiley_shader.initialize();
   SUCCEED();
}


TEST_F(Hexagon_Shaders_SmileyTest, activate__works_without_blowing_up)
{
   Hexagon::Shaders::Smiley smiley_shader;
   smiley_shader.initialize();

   smiley_shader.activate();

   SUCCEED();
}


TEST_F(Hexagon_Shaders_SmileyTest_WithEventQueueFixture, when_active__renders_the_image_with_the_flat_color)
{
   Hexagon::Shaders::Smiley smiley_shader;

   smiley_shader.initialize();
   smiley_shader.activate();

   ALLEGRO_BITMAP *test_image = al_create_bitmap(16 * 50, 9 * 50);
   ASSERT_NE(nullptr, test_image);

   ALLEGRO_COLOR color = al_color_name("red");

   smiley_shader.set_flat_color(color);
   smiley_shader.set_texture_width(al_get_bitmap_width(test_image));
   smiley_shader.set_texture_height(al_get_bitmap_height(test_image));

   ALLEGRO_DISPLAY *current_display = al_get_current_display();
   ASSERT_NE(nullptr, current_display);

   placement2d place(
         al_get_display_width(current_display)/2,
         al_get_display_height(current_display)/2,
         al_get_bitmap_width(test_image),
         al_get_bitmap_height(test_image));
   //place.scale = vec2d(4, 4);
   place.start_transform();
   al_draw_bitmap(test_image, 0, 0, 0);
   place.restore_transform();

   std::string tmp_path = "/Users/markoates/Repos/hexagon/tmp/";
   std::string output_image_full_filename = tmp_path + "when_activated__renders_bitmaps_with_a_solid_tinted_overlay.png";

   al_flip_display();

   ALLEGRO_EVENT keyboard_key_event;
   keyboard_key_event.type = ALLEGRO_EVENT_KEY_DOWN;
   keyboard_key_event.keyboard.keycode = ALLEGRO_KEY_ESCAPE;
   al_emit_user_event(al_get_keyboard_event_source(), &keyboard_key_event, nullptr);

   ALLEGRO_EVENT e;
   al_wait_for_event(event_queue, &e);
   if (e.type == ALLEGRO_EVENT_KEY_DOWN && e.keyboard.keycode == ALLEGRO_KEY_F) FAIL();
   else SUCCEED();
}

