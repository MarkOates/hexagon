
#include <gtest/gtest.h>

#include <Hexagon/Elements/ListMenu.hpp>

#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement3d.h>

class Hexagon_Elements_ListMenuTest_WithEventQueueFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   AllegroFlare::FontBin font_bin;

public:
   Hexagon_Elements_ListMenuTest_WithEventQueueFixture()
      : display(nullptr)
      , font_bin()
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      al_init_primitives_addon();
      al_init_font_addon();
      al_init_ttf_addon();
      al_install_keyboard();

      font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");

      display = al_create_display(1280 * 2, 720 * 2);
      al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.05f, 0.05f});
   }

   virtual void TearDown() override
   {
      font_bin.clear();
      al_destroy_display(display);
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

TEST_F(Hexagon_Elements_ListMenuTest_WithEventQueueFixture, render__does_not_blow_up)
{
   Hexagon::Elements::ListMenu list_menu(&font_bin);
   list_menu.render();
}

TEST_F(Hexagon_Elements_ListMenuTest_WithEventQueueFixture, width__has_with_the_expected_default_value)
{
   Hexagon::Elements::ListMenu list_menu(&font_bin);
   EXPECT_EQ(list_menu.get_width(), 600);
}

TEST_F(Hexagon_Elements_ListMenuTest_WithEventQueueFixture, render__draws_the_items_in_the_list)
{
   Hexagon::Elements::ListMenu list_menu(
      &font_bin,
      "Projects",
      {
         { "Hexagon", "/Users/markoates/Repos/hexagon/" },
         { "Solitare", "/Users/markoates/Repos/Solitare/" },
         { "A Project That Should Be Selected", "none" },
         { "Blast", "/Users/markoates/Repos/blast/" },
         { "AllegroFlare", "/Users/markoates/Repos/allegro_flare/" },
      }
   );
   placement3d place = centered_placement(0, 0);

   list_menu.move_cursor_down();
   list_menu.move_cursor_down();

   al_clear_to_color(ALLEGRO_COLOR{0.1,0.1,0.1,1});
   place.start_transform();
   list_menu.render();
   place.restore_transform();
   al_flip_display();

   //sleep(2);
}

TEST_F(Hexagon_Elements_ListMenuTest_WithEventQueueFixture, CAPTURE__render__draws_the_menu_as_expected_when_not_active)
{
   Hexagon::Elements::ListMenu list_menu(
      &font_bin,
      "Projects",
      {
         { "Hexagon", "/Users/markoates/Repos/hexagon/" },
         { "Solitare", "/Users/markoates/Repos/Solitare/" },
         { "A Project That Should Be Selected", "none" },
         { "Blast", "/Users/markoates/Repos/blast/" },
         { "AllegroFlare", "/Users/markoates/Repos/allegro_flare/" },
      }
   );
   float spacing = 100;
   placement3d place = centered_placement(list_menu.get_width(), -240);
   place.position.x -= (list_menu.get_width()/2 - spacing/2);

   list_menu.move_cursor_down();
   list_menu.move_cursor_down();

   al_clear_to_color(ALLEGRO_COLOR{0.1,0.1,0.1,1});
   //al_clear_to_color(ALLEGRO_COLOR{1, 1, 1, 1});
   place.start_transform();
   list_menu.render();
   place.restore_transform();

   list_menu.set_active(false);

   place.position.x += (list_menu.get_width() + spacing);
 
   place.start_transform();
   list_menu.render();
   place.restore_transform();
 
   al_flip_display();

   sleep(2);
}

TEST_F(Hexagon_Elements_ListMenuTest_WithEventQueueFixture,
   render__with_active_set_to_false__does_not_draw_the_border_or_arrow)
{
   Hexagon::Elements::ListMenu list_menu(
      &font_bin,
      "Projects",
      {
         { "Hexagon", "/Users/markoates/Repos/hexagon/" },
         { "Solitare", "/Users/markoates/Repos/Solitare/" },
         { "A Project That Should Be Selected", "none" },
         { "Blast", "/Users/markoates/Repos/blast/" },
         { "AllegroFlare", "/Users/markoates/Repos/allegro_flare/" },
      }
   );
   placement3d place = centered_placement(0, 0);
   list_menu.move_cursor_down();
   list_menu.move_cursor_down();

   list_menu.set_active(false);

   al_clear_to_color(ALLEGRO_COLOR{0.1,0.1,0.1,1});
   place.start_transform();
   list_menu.render();
   place.restore_transform();
   al_flip_display();

   //sleep(2);
}

TEST_F(Hexagon_Elements_ListMenuTest_WithEventQueueFixture, move_cursor_down__will_move_the_position_of_the_cursor)
{
   Hexagon::Elements::ListMenu list_menu(
      &font_bin,
      "Projects",
      {
         { "Hexagon", "/Users/markoates/Repos/hexagon/" },
         { "Solitare", "/Users/markoates/Repos/Solitare/" },
         { "Blast", "/Users/markoates/Repos/blast/" },
         { "AllegroFlare", "/Users/markoates/Repos/allegro_flare/" },
      }
   );

   int passes = 2;
   for (unsigned i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0,0,0,1});
      list_menu.move_cursor_down();
      list_menu.render();
      al_flip_display();
      //sleep(1);
   }
}

TEST_F(Hexagon_Elements_ListMenuTest_WithEventQueueFixture,
   move_cursor_up__with_wrap_cursor_when_moving_cursor_outsize_bounds__set_to_true__will_wrap_the_cursor)
{
   Hexagon::Elements::ListMenu list_menu(
      &font_bin,
      "Projects",
      {
         { "Hexagon", "/Users/markoates/Repos/hexagon/" },
         { "Solitare", "/Users/markoates/Repos/Solitare/" },
         { "Blast", "/Users/markoates/Repos/blast/" },
         { "AllegroFlare", "/Users/markoates/Repos/allegro_flare/" },
      }
   );

   int passes = 2;
   for (unsigned i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0,0,0,1});
      list_menu.move_cursor_up();
      list_menu.render();
      //al_flip_display();
      //sleep(1);
   }

   std::string current_list_item = list_menu.get_current_list_item_identifier();
   EXPECT_EQ(current_list_item, "/Users/markoates/Repos/blast/");
}


TEST_F(Hexagon_Elements_ListMenuTest_WithEventQueueFixture,
   render__when_the_height_of_the_list_exceeds_the_cursor_max_scroll_distance__will_offset_the_menu_during_scrolling)
{
   Hexagon::Elements::ListMenu list_menu(
      &font_bin,
      "Colors",
      {
        {"Red", "red_color"},
        {"Blue", "blue_color"},
        {"Yellow", "yellow_color"},
        {"Green", "green_color"},
        {"Purple", "purple_color"},
        {"Orange", "orange_color"},
        {"Pink", "pink_color"},
        {"Teal", "teal_color"},
        {"Lavender", "lavender_color"},
        {"Brown", "brown_color"},
        {"Crimson", "crimson_color"},
        {"Magenta", "magenta_color"},
        {"Turquoise", "turquoise_color"},
        {"Indigo", "indigo_color"},
        {"Sapphire", "sapphire_color"},
        {"Ruby", "ruby_color"},
        {"Emerald", "emerald_color"},
        {"Amber", "amber_color"},
        {"Coral", "coral_color"},
        {"Lime", "lime_color"},
        {"Slate", "slate_color"},
        {"Violet", "violet_color"},
        {"Gold", "gold_color"},
        {"Silver", "silver_color"},
        {"Bronze", "bronze_color"},
      }
   );

   int passes = 30;
   for (unsigned i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0,0,0,1});
      list_menu.move_cursor_down();
      list_menu.render();
      al_flip_display();
      al_rest(0.1);
   }

   // TODO: Capture y_offset and test
}


TEST_F(Hexagon_Elements_ListMenuTest_WithEventQueueFixture, set_list_items__will_set_the_list_items)
{
   // TODO
}


TEST_F(Hexagon_Elements_ListMenuTest_WithEventQueueFixture, set_list_items__will_reset_the_cursor_position_to_zero)
{
   // TODO
}


TEST_F(Hexagon_Elements_ListMenuTest_WithEventQueueFixture,
   move_cursor_down__with_wrap_cursor_when_moving_cursor_outsize_bounds_set_to_true__will_wrap_the_cursor)
{
   Hexagon::Elements::ListMenu list_menu(
      &font_bin,
      "Projects",
      {
         { "Hexagon", "/Users/markoates/Repos/hexagon/" },
         { "Solitare", "/Users/markoates/Repos/Solitare/" },
         { "Blast", "/Users/markoates/Repos/blast/" },
         { "AllegroFlare", "/Users/markoates/Repos/allegro_flare/" },
      }
   );

   int passes = 5;
   for (unsigned i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0,0,0,1});
      list_menu.move_cursor_down();
      list_menu.render();
      al_flip_display();
      al_rest(0.2);
   }

   std::string current_list_item = list_menu.get_current_list_item_identifier();
   EXPECT_EQ(current_list_item, "/Users/markoates/Repos/Solitare/");
}

