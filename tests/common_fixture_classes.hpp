#include <gtest/gtest.h>
#include <allegro5/allegro.h>
#include <allegro_flare/placement3d.h>


class WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   AllegroFlare::FontBin font_bin;

public:
   Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture()
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

