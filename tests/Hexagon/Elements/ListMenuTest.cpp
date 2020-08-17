
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

   al_clear_to_color(ALLEGRO_COLOR{0,0,0,1});
   place.start_transform();
   list_menu.render();
   place.restore_transform();
   al_flip_display();

   sleep(3);
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

