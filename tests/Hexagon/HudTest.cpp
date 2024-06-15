
#include <gtest/gtest.h>

#include <Hexagon/Hud.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
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

class Hexagon_HudTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_HudTest_WithEmptyFixture() {}
};

class Hexagon_HudTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   AllegroFlare::FontBin font_bin;

public:
   Hexagon_HudTest_WithAllegroRenderingFixture()
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
      //display = al_create_display(1280*2, 720*2);
      display = al_create_display(1920 / 2 * 4, 1080 / 2 * 4);
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

   placement3d build_centered_placement(Hexagon::Hud &hud, float object_width, float object_height)
   {
      placement3d place(hud.get_surface_projection_width()/2, hud.get_surface_projection_height()/2, 0.0f);
      place.size = vec3d(object_width, object_height, 0);
      return place;
   }
};

TEST_F(Hexagon_HudTest_WithEmptyFixture,
   can_be_created_without_blowing_up)
{
   Hexagon::Hud hud;
}

TEST_F(Hexagon_HudTest_WithEmptyFixture,
   notifications2__has_a_getter_and_setter)
{
   Hexagon::Hud hud;
   ASSERT_EQ(true, hud.get_notifications2().empty());
}

TEST_F(Hexagon_HudTest_WithEmptyFixture,
   show_powerbar__has_a_getter_and_is_initialized_with_the_expected_default)
{
   Hexagon::Hud hud;
   ASSERT_EQ(false, hud.get_show_powerbar());
}

TEST_F(Hexagon_HudTest_WithEmptyFixture,
   show_packets__has_a_getter_and_is_initialized_with_the_expected_default)
{
   Hexagon::Hud hud;
   ASSERT_EQ(false, hud.get_show_packets());
}

TEST_F(Hexagon_HudTest_WithEmptyFixture,
   show_focus_timer_bar__has_a_getter_and_is_initialized_with_the_expected_default)
{
   Hexagon::Hud hud;
   ASSERT_EQ(false, hud.get_show_focus_timer_bar());
}

TEST_F(Hexagon_HudTest_WithEmptyFixture,
   show_build_sequence_meter__has_a_getter_and_is_initialized_with_the_expected_default)
{
   Hexagon::Hud hud;
   ASSERT_EQ(false, hud.get_show_build_sequence_meter());
}

TEST_F(Hexagon_HudTest_WithEmptyFixture,
   show_notifications__has_a_getter_and_is_initialized_with_the_expected_default)
{
   Hexagon::Hud hud;
   ASSERT_EQ(true, hud.get_show_notifications());
}

TEST_F(Hexagon_HudTest_WithEmptyFixture,
   reinitialize__before_initialization__raises_an_error)
{
   Hexagon::Hud hud;
   //std::string expected_message = "Hud::reinitialize: error: guard \"initialized\" not met";
   //ASSERT_THROW_WITH_MESSAGE(hud.reinitialize(), std::runtime_error, expected_message);
   EXPECT_THROW_GUARD_ERROR(
      hud.reinitialize(),
      "Hexagon::Hud::reinitialize",
      "initialized"
   );
}

TEST_F(Hexagon_HudTest_WithEmptyFixture,
   draw__before_initialization__raises_an_error)
{
   Hexagon::Hud hud;
   //std::string expected_message = "Hud::draw: error: guard \"initialized\" not met";
   //ASSERT_THROW_WITH_MESSAGE(hud.draw(), std::runtime_error, expected_message);
   EXPECT_THROW_GUARD_ERROR(
      hud.draw(),
      "Hexagon::Hud::draw",
      "initialized"
   );
}

TEST_F(Hexagon_HudTest_WithAllegroRenderingFixture,
   render__will_render_the_hud)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();

   hud.draw();

   al_flip_display();
}

TEST_F(Hexagon_HudTest_WithAllegroRenderingFixture,
   render__will_show_packets_with_newest_packets_at_the_bottom)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();
   hud.set_show_packets(true);

   std::vector<Hexagon::Packet> packets = {
      Hexagon::Packet(1, 8),
      Hexagon::Packet(2, 3),
      Hexagon::Packet(3, 27),
   };
   hud.set_packets(packets);

   hud.draw();

   al_flip_display();

   //sleep(2);
}

TEST_F(Hexagon_HudTest_WithAllegroRenderingFixture,
   render__when_there_are_more_than_9_plus_1_packets__will_render_the_most_recent_ones)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();
   hud.set_show_packets(true);

   std::vector<Hexagon::Packet> packets = {
      Hexagon::Packet(1, 1), // should not be shown
      Hexagon::Packet(2, 1), // should not be shown
      Hexagon::Packet(3, 1),
      Hexagon::Packet(4, 1),
      Hexagon::Packet(5, 1),
      Hexagon::Packet(6, 1),
      Hexagon::Packet(7, 1),
      Hexagon::Packet(8, 1),
      Hexagon::Packet(9, 1),
      Hexagon::Packet(10, 1),
      Hexagon::Packet(11, 1),
      // an additional packet is appended, one that is the "packet in progress"
   };
   hud.set_packets(packets);

   hud.draw();

   al_flip_display();

   //sleep(2);
}

TEST_F(Hexagon_HudTest_WithAllegroRenderingFixture,
   render__will_render_powerbar_with_the_expected_text)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();

   Hexagon::Powerbar::Powerbar &powerbar = hud.get_powerbar_ref();

   hud.set_show_powerbar(true);
   powerbar.set_files_are_modified(true);
   powerbar.set_files_are_staged(true);
   powerbar.set_files_are_untracked(true);

   hud.draw();

   al_flip_display();

   //sleep(2);
}

TEST_F(Hexagon_HudTest_WithAllegroRenderingFixture,
   render__will_render_the_objective_with_the_expected_text)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();

   Hexagon::Powerbar::Powerbar &powerbar = hud.get_powerbar_ref();

   hud.set_show_objective(true);
   hud.set_objective_text("Show the objective text in the hud");

   hud.draw();

   al_flip_display();

   //sleep(2);
}

TEST_F(Hexagon_HudTest_WithAllegroRenderingFixture,
   render__will_render_the_domain_with_the_expected_text)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();

   Hexagon::Powerbar::Powerbar &powerbar = hud.get_powerbar_ref();

   hud.set_show_domain(true);
   hud.set_domain_text("Hexagon/Hud");

   hud.draw();

   al_flip_display();

   //sleep(2);
}

TEST_F(Hexagon_HudTest_WithAllegroRenderingFixture,
   render__will_remove_the_domain_from_the_title_text)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();

   Hexagon::Powerbar::Powerbar &powerbar = hud.get_powerbar_ref();

   hud.set_show_domain(true);
   hud.set_domain_text("Hexagon/System/");
   hud.set_title_text("Hexagon/System/Action/CreateCodeEditorStageFromFilename");

   hud.draw();

   al_flip_display();

   //sleep(2);
}

TEST_F(Hexagon_HudTest_WithAllegroRenderingFixture,
   render__will_render_title)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();

   hud.set_title_text("Some/Title/Text");

   hud.draw();

   al_flip_display();

   //sleep(2);
}


TEST_F(Hexagon_HudTest_WithAllegroRenderingFixture,
   render__will_render_held_component)
{
   Hexagon::Hud hud(display, font_bin);
   hud.initialize();

   hud.set_held_component_text("Some/Held/Component");

   hud.draw();

   al_flip_display();

   sleep(2);
}


TEST_F(Hexagon_HudTest_WithAllegroRenderingFixture,
   render__will_render_advanced_component_navigator_stages_that_are_marked_as_render_on_hud)
{
   // TODO: use a test class for this instead of the (very heavy) AdvancedComponentNavigator

   Hexagon::Hud hud(display, font_bin); // TODO: font_bin is required for construction, but never used
                                        // in this use case.  Should probably be removed from the constructor
                                        // or changed to an AllegroFlare::FontBin*
   //hud.set_render_build_sequence_meter(false);
   hud.initialize();

   Hexagon::AdvancedComponentNavigator::Stage stage;
   stage.get_place() = build_centered_placement(hud, 800, 700);
   stage.set_render_on_hud(true);
   stage.set_font(font_bin["Menlo-Regular.ttf -20"]);
   stage.set_font_bin(&font_bin);
   stage.process_local_event("refresh_list");

   std::vector<StageInterface *> stages = { &stage };
   hud.set_stages(&stages);

   //int passes = 60 * 3;
   int passes = 1;
   for (unsigned i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      hud.draw();
      al_flip_display();
   }

   //sleep(2);
}

TEST_F(Hexagon_HudTest_WithAllegroRenderingFixture,
   render__when_given_stages_that_are_marked_as_render_on_hud__that_are_of_unknown_type__will_raise_an_error)
{
   DummyUnrenderableStageType dummy_stage;
   dummy_stage.set_render_on_hud(true);

   std::vector<StageInterface *> stages = { &dummy_stage };

   Hexagon::Hud hud(display, font_bin);
   hud.initialize();
   hud.set_stages(&stages);

   // terrible error message, please fix later
   std::string expected_error_message =
      "Hexagon/Hud::draw: error: Cannot render a stage marked as render_on_hud that is of type \"0\"";

   ASSERT_THROW_WITH_MESSAGE(hud.draw(), std::runtime_error, expected_error_message);
}


