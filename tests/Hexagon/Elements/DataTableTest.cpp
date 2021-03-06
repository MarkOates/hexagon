
#include <gtest/gtest.h>

#include <Hexagon/Elements/DataTable.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement3d.h>

class Hexagon_Elements_DataTableTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_DataTableTest_WithEmptyFixture() {}
};

class Hexagon_Elements_DataTableTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   static std::string FONT_PATH;
   ALLEGRO_DISPLAY* display;
   ALLEGRO_FONT* font;

public:
   Hexagon_Elements_DataTableTest_WithAllegroRenderingFixture()
      : display(nullptr)
      , font(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      ASSERT_EQ(true, al_init_font_addon());
      ASSERT_EQ(true, al_init_ttf_addon());
      ASSERT_EQ(true, al_init_primitives_addon());
      display = al_create_display(1280*2, 720*2);
      font = al_load_font(FONT_PATH.c_str(), -42, 0);
      al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
   }

   virtual void TearDown() override
   {
      if (font) al_destroy_font(font);
      al_shutdown_ttf_addon();
      al_destroy_display(display);
      al_uninstall_system();
   }

   placement3d build_centered_placement(float width, float height)
   {
      placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0f);
      place.size = vec3d(width, height, 0);
      return place;
   }

   void draw_current_test_name()
   {
      std::string current_test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
      ALLEGRO_COLOR color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
      al_draw_text(
         font,
         color,
         al_get_display_width(display)/2,
         al_get_display_height(display)/4,
         ALLEGRO_ALIGN_CENTER,
         current_test_name.c_str()
      );
   }
};
std::string Hexagon_Elements_DataTableTest_WithAllegroRenderingFixture::FONT_PATH =
   "/Users/markoates/Repos/hexagon/bin/programs/data/fonts/Purista Medium.otf";


TEST_F(Hexagon_Elements_DataTableTest_WithEmptyFixture,
   can_be_created_without_blowing_up)
{
   Hexagon::Elements::DataTable data_table;
}


TEST_F(Hexagon_Elements_DataTableTest_WithAllegroRenderingFixture,
   render__will_render_the_data)
{
   placement3d place = build_centered_placement(0, 0);
   place.position -= vec3d(600, 300, 0);

   place.start_transform();

   std::vector<std::vector<std::string>> data2d = {
      { "SEARCHES", "22", "DOPPER", "Active", "Running" },
      { "SAVES",    "11", "DOPPER" },
      { "SCORE",    "97", "DOPPER" },
   };

   Hexagon::Elements::DataTable data_table(font, 300, 70, data2d);
   data_table.render();

   place.restore_transform();

   al_flip_display();

   //sleep(2);
}

