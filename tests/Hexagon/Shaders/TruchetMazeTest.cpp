
#include <gtest/gtest.h>

#include <Hexagon/Shaders/TruchetMaze.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro_flare/placement2d.h>
#include <allegro_flare/placement3d.h>
#include <AllegroFlare/Timer.hpp>


class Hexagon_Shaders_TruchetMazeTest : public ::testing::Test
{
protected:
   ALLEGRO_DISPLAY *display;

   Hexagon_Shaders_TruchetMazeTest()
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


class Hexagon_Shaders_TruchetMazeTest_WithEventQueueFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   AllegroFlare::FontBin font_bin;
   AllegroFlare::Timer timer;
   ALLEGRO_EVENT_QUEUE *event_queue;
   ALLEGRO_TIMER *primary_timer;

public:
   Hexagon_Shaders_TruchetMazeTest_WithEventQueueFixture()
      : display(nullptr)
      , font_bin()
      , timer()
      , event_queue(nullptr)
      , primary_timer(nullptr)
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

      primary_timer = al_create_timer(1.0/60.0);
      al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
      al_start_timer(primary_timer);

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
      al_destroy_event_queue(event_queue);
      al_destroy_display(display);
      al_destroy_timer(primary_timer);
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


TEST_F(Hexagon_Shaders_TruchetMazeTest, can_be_created_without_blowing_up)
{
   Hexagon::Shaders::TruchetMaze shader;
   SUCCEED();
}


TEST_F(Hexagon_Shaders_TruchetMazeTest, activate__before_being_initialized_raises_an_exception)
{
   Hexagon::Shaders::TruchetMaze shader;
   EXPECT_THROW_GUARD_ERROR(
      shader.activate(),
      "Hexagon::Shaders::TruchetMaze::activate",
      "initialized"
   );
}


TEST_F(Hexagon_Shaders_TruchetMazeTest, initialize__works_without_blowing_up)
{
   Hexagon::Shaders::TruchetMaze shader;
   shader.initialize();
   SUCCEED();
}


TEST_F(Hexagon_Shaders_TruchetMazeTest, activate__works_without_blowing_up)
{
   Hexagon::Shaders::TruchetMaze shader;
   shader.initialize();

   shader.activate();

   SUCCEED();
}


TEST_F(Hexagon_Shaders_TruchetMazeTest_WithEventQueueFixture, when_active__renders_the_image_with_the_flat_color)
{
   Hexagon::Shaders::TruchetMaze shader;

   shader.initialize();
   shader.activate();

   ALLEGRO_BITMAP *test_image = al_create_bitmap(16 * 50, 9 * 50);
   ASSERT_NE(nullptr, test_image);

   ALLEGRO_COLOR color = al_color_name("red");
   ALLEGRO_FONT *font = al_create_builtin_font();

   shader.set_flat_color(color);
   shader.set_texture_width(al_get_bitmap_width(test_image));
   shader.set_texture_height(al_get_bitmap_height(test_image));
   shader.set_time(1000);

   ALLEGRO_DISPLAY *current_display = al_get_current_display();
   ASSERT_NE(nullptr, current_display);

   placement2d place(
         al_get_display_width(current_display)/2,
         al_get_display_height(current_display)/2,
         al_get_bitmap_width(test_image),
         al_get_bitmap_height(test_image));

   ALLEGRO_EVENT keyboard_key_event;
   keyboard_key_event.type = ALLEGRO_EVENT_KEY_DOWN;
   keyboard_key_event.keyboard.keycode = ALLEGRO_KEY_ESCAPE;
   al_emit_user_event(al_get_keyboard_event_source(), &keyboard_key_event, nullptr);

   ALLEGRO_EVENT e, next_event;
   bool abort = false;
   while (!abort)
   {
      al_wait_for_event(event_queue, &e);
      switch(e.type)
      {
      case ALLEGRO_EVENT_TIMER:
         al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});

         place.start_transform();
         shader.activate();
         timer.pause(); timer.reset(); timer.start();
         shader.set_time(al_get_time());
         al_draw_bitmap(test_image, 0, 0, 0);
         timer.pause();
         shader.deactivate();
         place.restore_transform();

         al_draw_textf(font, color, 10, 10, 0, "%d", timer.get_elapsed_time_microseconds());

         al_flip_display();
         while (al_peek_next_event(event_queue, &next_event)
              && next_event.type == ALLEGRO_EVENT_TIMER
              && next_event.timer.source == primary_timer)
           al_drop_next_event(event_queue);
         break;
      case ALLEGRO_EVENT_KEY_DOWN:
         if (e.keyboard.keycode == ALLEGRO_KEY_F)
         {
            FAIL();
         }
         else
         {
            abort = true;
            SUCCEED();
         }
         break;
      }
   }
}

