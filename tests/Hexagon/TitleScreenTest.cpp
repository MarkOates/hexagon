
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Hexagon/TitleScreen.hpp>
#include <allegro5/allegro_primitives.h>


class Hexagon_TitleScreenTest : public ::testing::Test
{
protected:
   ALLEGRO_DISPLAY *display;
   AllegroFlare::FontBin font_bin;

   Hexagon_TitleScreenTest()
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


TEST_F(Hexagon_TitleScreenTest, can_be_created_without_blowing_up)
{
   Hexagon::TitleScreen title_screen;
}


TEST_F(Hexagon_TitleScreenTest, DISABLED__INTERACTIVE__operates_as_expected)
{
   Hexagon::TitleScreen title_screen(&font_bin);
   title_screen.initialize();
   title_screen.draw_hexagon_logo_and_wait_for_keypress();
}


TEST_F(Hexagon_TitleScreenTest, build_allegro_version_string__will_create_a_version_string_in_the_expected_format)
{
   Hexagon::TitleScreen title_screen;
   std::string actual_version_string = title_screen.build_allegro_version_string();
   //Example format: "Allegro v5.2.9 r0";
   EXPECT_THAT(actual_version_string, ::testing::MatchesRegex("^Allegro v[0-9]+.[0-9]+.[0-9]+ r[0-9]+$"));
}


