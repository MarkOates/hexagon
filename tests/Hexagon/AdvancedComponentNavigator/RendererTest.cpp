
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/AdvancedComponentNavigator/Renderer.hpp>


class Hexagon_AdvancedComponentNavigator_RendererWithFixtureTest : public ::testing::Test
{
protected:
   ALLEGRO_DISPLAY *display;
   AllegroFlare::FontBin font_bin;
   Hexagon::AdvancedComponentNavigator::Stage *stage;
   ALLEGRO_FONT *font;
   Hexagon::AdvancedComponentNavigator::Renderer *renderer;

   Hexagon_AdvancedComponentNavigator_RendererWithFixtureTest()
      : display(nullptr)
      , font_bin()
      , stage(nullptr)
      , font(nullptr)
      , renderer(nullptr)
   {
   }

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());

      al_init_font_addon();
      al_init_ttf_addon();
      al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
      ASSERT_EQ(ALLEGRO_OPENGL, al_get_new_display_flags() & ALLEGRO_OPENGL);
      ASSERT_EQ(ALLEGRO_PROGRAMMABLE_PIPELINE, al_get_new_display_flags() & ALLEGRO_PROGRAMMABLE_PIPELINE);
      display = al_create_display(1920 / 5 * 4, 1080 / 5 * 4);
      ASSERT_NE(nullptr, display);

      font = al_create_builtin_font();
      int cell_width = al_get_text_width(font, "X");
      int cell_height = al_get_font_line_height(font);
      std::string TEST_FIXTURE_FONT_FOLDER = "/Users/markoates/Repos/hexagon/tests/fixtures/data/fonts";

      font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
      ALLEGRO_COLOR base_backfill_color = al_color_name("black");
      float backfill_opacity = 0.8f;
      ALLEGRO_COLOR base_text_color = al_color_name("white");
      stage = new Hexagon::AdvancedComponentNavigator::Stage();
      renderer = new Hexagon::AdvancedComponentNavigator::Renderer(
         stage, &font_bin, true, font, cell_width, cell_height, &base_backfill_color, backfill_opacity, &base_text_color
      );

      placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
      place.size.x = al_get_display_width(display)/4;
      place.size.y = al_get_display_height(display)/4;
      place.scale.x = 2.0;
      place.scale.y = 2.0;
      stage->set_place(place);
   }

   virtual void TearDown() override
   {
      font_bin.clear();
      al_destroy_font(font);
      delete stage;
      delete renderer;

      if (al_get_current_display()) al_destroy_display(al_get_current_display());
      al_uninstall_system();
   }

   Hexagon::AdvancedComponentNavigator::Stage &get_stage_fixture()
   {
      return *stage;
   }

   Hexagon::AdvancedComponentNavigator::Renderer &get_renderer_fixture()
   {
      return *renderer;
   }
};


TEST(Hexagon_AdvancedComponentNavigator_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedComponentNavigator::Renderer renderer;
}


TEST(Hexagon_AdvancedComponentNavigator_RendererTest, render__and__render_raw__without_a_stage_throws_an_error)
{
   Hexagon::AdvancedComponentNavigator::Renderer renderer;
   std::string expected_message = "Renderer::render: error: guard \"stage\" not met";
   std::string expected_raw_message = "Renderer::render_raw: error: guard \"stage\" not met";
   EXPECT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_message);
   EXPECT_THROW_WITH_MESSAGE(renderer.render_raw(), std::runtime_error, expected_raw_message);
}


TEST(Hexagon_AdvancedComponentNavigator_RendererTest, render__and__render_raw__without_a_font_throws_an_error)
{
   Hexagon::AdvancedComponentNavigator::Stage stage;
   Hexagon::AdvancedComponentNavigator::Renderer renderer(&stage);
   std::string expected_message = "Renderer::render: error: guard \"font\" not met";
   std::string expected_raw_message = "Renderer::render_raw: error: guard \"font\" not met";
   EXPECT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_message);
   EXPECT_THROW_WITH_MESSAGE(renderer.render_raw(), std::runtime_error, expected_raw_message);
}


TEST_F(Hexagon_AdvancedComponentNavigator_RendererWithFixtureTest, render__renders_the_component_navigator)
{
   Hexagon::AdvancedComponentNavigator::Renderer &renderer = get_renderer_fixture();

   renderer.render();
   al_flip_display();

   //sleep(2);

   SUCCEED();
}


TEST_F(Hexagon_AdvancedComponentNavigator_RendererWithFixtureTest, render__renders_the_component_navigator_nodes)
{
   Hexagon::AdvancedComponentNavigator::Renderer &renderer = get_renderer_fixture();
   Hexagon::AdvancedComponentNavigator::Stage &stage = get_stage_fixture();
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator &component = stage.get_component_ref();
   using Blast::Project::Component;

   component.set_nodes({ Component("Blast/Foobar"), Component("Blast/BarBar") });

   renderer.render();
   al_flip_display();

   sleep(2);

   SUCCEED();
}


TEST_F(Hexagon_AdvancedComponentNavigator_RendererWithFixtureTest, render__renders_the_search_text)
{
   Hexagon::AdvancedComponentNavigator::Renderer &renderer = get_renderer_fixture();
   Hexagon::AdvancedComponentNavigator::Stage &stage = get_stage_fixture();
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator &component = stage.get_component_ref();
   using Blast::Project::Component;

   component.set_search_text("Blast");

   stage.process_local_event("refresh_list");
   stage.process_local_event("move_cursor_down");
   stage.process_local_event("move_cursor_down");

   renderer.render();
   al_flip_display();

   //sleep(1);

   SUCCEED();
}

