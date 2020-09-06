
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
#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <Hexagon/StageInterface.hpp>

class DummyUnrenderableStageType : public StageInterface
{
public:
   DummyUnrenderableStageType()
     : StageInterface(StageInterface::NONE)
   {}
   virtual void render() override {}
   virtual void process_local_event(std::string event_name, ActionData action_data=ActionData()) override {}
   virtual void process_event(ALLEGRO_EVENT &event) override {}
};

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
   draw_packets__has_a_getter_and_is_initialized_with_the_expected_default)
{
   Hexagon::Hud hud;
   ASSERT_EQ(false, hud.get_draw_packets());
}

TEST_F(Hexagon_Elements_HudTest_WithEmptyFixture,
   draw_focus_timer_bar__has_a_getter_and_is_initialized_with_the_expected_default)
{
   Hexagon::Hud hud;
   ASSERT_EQ(true, hud.get_draw_focus_timer_bar());
}

TEST_F(Hexagon_Elements_HudTest_WithEmptyFixture,
   draw_notifications__has_a_getter_and_is_initialized_with_the_expected_default)
{
   Hexagon::Hud hud;
   ASSERT_EQ(true, hud.get_draw_notifications());
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
   render__will_render_packets_with_newest_packets_at_the_bottom)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();

   std::vector<Hexagon::Packet> packets = {
      Hexagon::Packet(1, 8),
      Hexagon::Packet(2, 3),
      Hexagon::Packet(3, 27),
   };
   hud.set_packets(packets);
   hud.set_draw_packets(true);

   hud.draw();

   al_flip_display();

   sleep(2);
}

TEST_F(Hexagon_Elements_HudTest_WithAllegroRenderingFixture,
   render__will_render_powerbar_with_the_expected_text)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();

   Hexagon::Powerbar::Powerbar &powerbar = hud.get_powerbar_ref();

   hud.set_draw_powerbar(true);
   powerbar.set_files_are_modified(true);
   powerbar.set_files_are_staged(true);
   powerbar.set_files_are_untracked(true);

   hud.draw();

   al_flip_display();

   //sleep(2);
}

TEST_F(Hexagon_Elements_HudTest_WithAllegroRenderingFixture,
   render__will_render_title)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();

   hud.set_title_text("Some/Title/Text");

   hud.draw();

   al_flip_display();

   //sleep(2);
}

TEST_F(Hexagon_Elements_HudTest_WithAllegroRenderingFixture,
   render__will_render_advanced_component_navigator_stages_that_are_marked_as_render_on_hud)
{
   Hexagon::AdvancedComponentNavigator::Stage stage;
   stage.set_render_on_hud(true);
   stage.get_place() = build_centered_placement(800, 700);
   stage.set_font(font_bin["Menlo-Regular.ttf -20"]);
   stage.process_local_event("refresh_list");

   std::vector<StageInterface *> stages = { &stage };

   Hexagon::Hud hud(display, font_bin); // TODO: font_bin is required for construction, but never used
                                        // in this use case.  Should probably be removed from the constructor
                                        // or changed to an AllegroFlare::FontBin*
   hud.initialize();
   hud.set_stages(&stages);

   hud.draw();

   al_flip_display();

   //sleep(2);
}

TEST_F(Hexagon_Elements_HudTest_WithAllegroRenderingFixture,
   render__when_given_stages_that_are_marked_as_render_on_hud__that_are_of_unknown_type__will_raise_an_error)
{
   DummyUnrenderableStageType dummy_stage;
   dummy_stage.set_render_on_hud(true);

   std::vector<StageInterface *> stages = { &dummy_stage };

   Hexagon::Hud hud(display, font_bin);
   hud.initialize();
   hud.set_stages(&stages);

   // terrible error message, please fix later :pray:
   std::string expected_error_message =
      "Hexagon/Hud::draw: error: Cannot render a stage marked as render_on_hud that is of type \"0\"";

   ASSERT_THROW_WITH_MESSAGE(hud.draw(), std::runtime_error, expected_error_message);
}

