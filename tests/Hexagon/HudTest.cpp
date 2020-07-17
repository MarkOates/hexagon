
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Hud.hpp>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro_flare/placement3d.h>

class Hexagon_Elements_HudTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_HudTest_WithEmptyFixture() {}
};

class Hexagon_Elements_HudTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   AllegroFlare::FontBin font_bin;

public:
   Hexagon_Elements_HudTest_WithAllegroRenderingFixture()
      : display(nullptr)
      , font_bin()
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      ASSERT_EQ(true, al_init_primitives_addon());
      ASSERT_EQ(true, al_init_font_addon());
      ASSERT_EQ(true, al_init_ttf_addon());
      display = al_create_display(1280*2, 720*2);
      font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
      al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
   }

   virtual void TearDown() override
   {
      font_bin.clear();
      al_shutdown_ttf_addon(); // this is required otherwise subsequent al_init_ttf_addon will not work
                               // see https://www.allegro.cc/forums/thread/618183
      al_destroy_display(display);
      al_uninstall_system();
   }

   placement3d build_centered_placement(float width, float height)
   {
      placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0f);
      place.size = vec3d(width, height, 0);
      return place;
   }
};

TEST_F(Hexagon_Elements_HudTest_WithEmptyFixture,
   can_be_created_without_blowing_up)
{
   Hexagon::Hud hud;
}

TEST_F(Hexagon_Elements_HudTest_WithEmptyFixture,
   notifications2__has_a_getter_and_setter)
{
   Hexagon::Hud hud;
   ASSERT_EQ(true, hud.get_notifications2().empty());
}

TEST_F(Hexagon_Elements_HudTest_WithEmptyFixture,
   draw_powerbar__has_a_getter_and_is_initialized_with_the_expected_default)
{
   Hexagon::Hud hud;
   ASSERT_EQ(false, hud.get_draw_powerbar());
}

TEST_F(Hexagon_Elements_HudTest_WithEmptyFixture,
   reinitialize__before_initialization__raises_an_error)
{
   Hexagon::Hud hud;
   std::string expected_message = "Hud::reinitialize: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(hud.reinitialize(), std::runtime_error, expected_message);
}

TEST_F(Hexagon_Elements_HudTest_WithEmptyFixture,
   draw__before_initialization__raises_an_error)
{
   Hexagon::Hud hud;
   std::string expected_message = "Hud::draw: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(hud.draw(), std::runtime_error, expected_message);
}

TEST_F(Hexagon_Elements_HudTest_WithAllegroRenderingFixture,
   render__will_render_the_hud)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();

   hud.draw();

   al_flip_display();
}

TEST_F(Hexagon_Elements_HudTest_WithAllegroRenderingFixture,
   render__will_render_packets)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();

   std::vector<Hexagon::Packet> packets = {};
   hud.set_packets(packets);

   hud.draw();

   al_flip_display();

   sleep(1);
}

