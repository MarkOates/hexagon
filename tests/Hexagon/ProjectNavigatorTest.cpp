
#include <gtest/gtest.h>

#include <Hexagon/ProjectNavigator.hpp>
#include <allegro5/allegro_primitives.h>


class Hexagon_ProjectNavigatorTest : public ::testing::Test
{
protected:
   ALLEGRO_DISPLAY *display;
   AllegroFlare::FontBin font_bin;

   Hexagon_ProjectNavigatorTest()
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

      font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");

      al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
      ASSERT_EQ(ALLEGRO_OPENGL, al_get_new_display_flags() & ALLEGRO_OPENGL);
      ASSERT_EQ(ALLEGRO_PROGRAMMABLE_PIPELINE, al_get_new_display_flags() & ALLEGRO_PROGRAMMABLE_PIPELINE);
      ALLEGRO_DISPLAY *display = al_create_display(1920 / 5 * 4, 1080 / 5 * 4);
      ASSERT_NE(nullptr, display);
   }

   virtual void TearDown() override
   {
      if (al_get_current_display()) al_destroy_display(al_get_current_display());
      font_bin.clear();
      al_shutdown_ttf_addon(); // needed due to bug in al_uninstall_system overlooking ttf shutdown specifically
      al_uninstall_system();
   }

   ALLEGRO_DISPLAY *get_display()
   {
      return display;
   }
};


TEST_F(Hexagon_ProjectNavigatorTest, can_be_created_without_blowing_up)
{
   Hexagon::ProjectNavigator project_navigator;
}


TEST_F(Hexagon_ProjectNavigatorTest, contains_an_empty_list_of_menu_items_by_default)
{
   Hexagon::ProjectNavigator project_navigator;
   EXPECT_EQ(0, project_navigator.get_menu_items().size());
}


TEST_F(Hexagon_ProjectNavigatorTest,
   build_placeholder_menu_items__will_create_a_set_of_menu_items_useful_for_testing_or_development)
{
   std::vector<std::tuple<std::string, std::string>> actual_placeholder_menu_items =
      Hexagon::ProjectNavigator::build_placeholder_menu_items();

   std::vector<std::tuple<std::string, std::string>> expected_placeholder_menu_items = {
      { "AllegroFlare", "/Users/markoates/Repos/allegro_flare/" },
      { "Hexagon", "/Users/markoates/Repos/hexagon/" },
      { "Blast", "/Users/markoates/Repos/blast/" },
   };

   EXPECT_EQ(expected_placeholder_menu_items, actual_placeholder_menu_items);
}


TEST_F(Hexagon_ProjectNavigatorTest, set_menu_items__will_set_the_menu_items)
{
   Hexagon::ProjectNavigator project_navigator;
   project_navigator.set_menu_items(Hexagon::ProjectNavigator::build_placeholder_menu_items());

   std::vector<std::tuple<std::string, std::string>> expected_placeholder_menu_items = {
      { "AllegroFlare", "/Users/markoates/Repos/allegro_flare/" },
      { "Hexagon", "/Users/markoates/Repos/hexagon/" },
      { "Blast", "/Users/markoates/Repos/blast/" },
   };

   EXPECT_EQ(expected_placeholder_menu_items, project_navigator.get_menu_items());
}


TEST_F(Hexagon_ProjectNavigatorTest, set_menu_items__will_reset_the_cursor_position_to_zero)
{
   // TODO
}


