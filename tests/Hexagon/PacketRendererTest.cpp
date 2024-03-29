
#include <gtest/gtest.h>

#include <Hexagon/PacketRenderer.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement3d.h>

#define FONT_FIXTURES_FOLDER "/Users/markoates/Repos/hexagon/bin/programs/data/fonts"

class Hexagon_Elements_PacketRendererTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_PacketRendererTest_WithEmptyFixture() {}
};

class Hexagon_Elements_PacketRendererTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   static std::string FONT_PATH;
   ALLEGRO_DISPLAY* display;
   ALLEGRO_FONT* font;
   AllegroFlare::FontBin font_bin;

public:
   Hexagon_Elements_PacketRendererTest_WithAllegroRenderingFixture()
      : display(nullptr)
      , font(nullptr)
      , font_bin()
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      ASSERT_EQ(true, al_init_font_addon());
      ASSERT_EQ(true, al_init_ttf_addon());
      ASSERT_EQ(true, al_init_primitives_addon());
      display = al_create_display(1280*2, 720*2);
      font = al_load_font(FONT_PATH.c_str(), -16, 0);
      font_bin.set_full_path(FONT_FIXTURES_FOLDER);
      al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
   }

   virtual void TearDown() override
   {
      if (font) al_destroy_font(font);
      font_bin.clear();
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
std::string Hexagon_Elements_PacketRendererTest_WithAllegroRenderingFixture::FONT_PATH =
   "/Users/markoates/Repos/hexagon/bin/programs/data/fonts/Exan-Regular.ttf";


TEST_F(Hexagon_Elements_PacketRendererTest_WithEmptyFixture,
   can_be_created_without_blowing_up)
{
   Hexagon::PacketRenderer packet_renderer;
}


TEST_F(Hexagon_Elements_PacketRendererTest_WithEmptyFixture, render__without_a_font_bin__raises_an_exception)
{
   //TODO
}


TEST_F(Hexagon_Elements_PacketRendererTest_WithAllegroRenderingFixture,
   render__will_render_the_packet)
{
   int width = 120;
   int height = 120;

   placement3d presentation_placement(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0f);
   presentation_placement.scale = vec3d(2.0, 2.0, 2.0);

   std::vector<Hexagon::Packet> packets_to_present = {
      Hexagon::Packet(7, 12),
      Hexagon::Packet(8, 12),
      Hexagon::Packet(8, 13)
   };

   presentation_placement.start_transform();

   int num_columns = 3;
   int presenting_packet_num = 0;
   int x_spacing = 30;
   int y_spacing = 20;
   int x_offset = ((num_columns * (width)) + (num_columns-1 * x_spacing)) * -0.5;

   for (auto &packet_to_present : packets_to_present)
   {
      int xi = presenting_packet_num % num_columns;
      int yi = presenting_packet_num / num_columns;

      placement3d box_place(xi * (width + x_spacing) + x_offset, yi * (height + y_spacing), 0);
      box_place.size = vec3d(width, height, 0);
      box_place.start_transform();
      Hexagon::PacketRenderer packet_renderer(&font_bin, &packet_to_present, font, box_place.size.x, box_place.size.y);
      packet_renderer.render();
      box_place.restore_transform();

      presenting_packet_num++;
   }

   presentation_placement.restore_transform();

   al_flip_display();

   sleep(2);
}

