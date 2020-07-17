
#include <gtest/gtest.h>

#include <Hexagon/PacketRenderer.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement3d.h>

class Hexagon_Elements_PacketRendererTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_PacketRendererTest_WithEmptyFixture() {}
};

class Hexagon_Elements_PacketRendererTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   ALLEGRO_FONT* font;

public:
   Hexagon_Elements_PacketRendererTest_WithAllegroRenderingFixture()
      : display(nullptr)
      , font(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      ASSERT_EQ(true, al_init_primitives_addon());
      display = al_create_display(1280*2, 720*2);
      font = al_create_builtin_font();
      al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
   }

   virtual void TearDown() override
   {
      if (font) al_destroy_font(font);
      al_destroy_display(display);
      al_uninstall_system();
   }

   placement3d centered_placement(float width, float height)
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

TEST_F(Hexagon_Elements_PacketRendererTest_WithEmptyFixture,
   can_be_created_without_blowing_up)
{
   Hexagon::PacketRenderer packet_renderer;
}


TEST_F(Hexagon_Elements_PacketRendererTest_WithAllegroRenderingFixture,
   render__will_render_the_packet)
{
   Hexagon::Packet packet;

   Hexagon::PacketRenderer packet_renderer(&packet);
   packet_renderer.render();
}

