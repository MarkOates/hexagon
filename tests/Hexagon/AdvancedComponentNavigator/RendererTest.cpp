
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/AdvancedComponentNavigator/Renderer.hpp>


class Hexagon_AdvancedComponentNavigator_RendererWithFixtureTest : public ::testing::Test
{
protected:
   ALLEGRO_DISPLAY *display;
   Hexagon::AdvancedComponentNavigator::Stage *stage;
   ALLEGRO_FONT *font;
   Hexagon::AdvancedComponentNavigator::Renderer *renderer;

   Hexagon_AdvancedComponentNavigator_RendererWithFixtureTest()
      : display(nullptr)
      , stage(nullptr)
      , font(nullptr)
      , renderer(nullptr)
   {
   }

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());

      al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
      ASSERT_EQ(ALLEGRO_OPENGL, al_get_new_display_flags() & ALLEGRO_OPENGL);
      ASSERT_EQ(ALLEGRO_PROGRAMMABLE_PIPELINE, al_get_new_display_flags() & ALLEGRO_PROGRAMMABLE_PIPELINE);
      display = al_create_display(800, 600);
      ASSERT_NE(nullptr, display);

      font = al_create_builtin_font();
      int cell_width = al_get_text_width(font, "X");
      int cell_height = al_get_font_line_height(font);
      stage = new Hexagon::AdvancedComponentNavigator::Stage();
      renderer = new Hexagon::AdvancedComponentNavigator::Renderer(stage, true, font, cell_width, cell_height);

      placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
      place.size.x = al_get_display_width(display)/2;
      place.size.y = al_get_display_height(display)/2;
      stage->set_place(place);
   }

   virtual void TearDown() override
   {
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


TEST(Hexagon_AdvancedComponentNavigator_RendererTest, render__without_a_stage_throws_an_error)
{
   Hexagon::AdvancedComponentNavigator::Renderer renderer;
   std::string expected_message = "Renderer::render: error: guard \"stage\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_message);
}


TEST(Hexagon_AdvancedComponentNavigator_RendererTest, render__without_a_font_throws_an_error)
{
   Hexagon::AdvancedComponentNavigator::Stage stage;
   Hexagon::AdvancedComponentNavigator::Renderer renderer(&stage);
   std::string expected_message = "Renderer::render: error: guard \"font\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_message);
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
   using Blast::Project::Component;

   stage.set_nodes({ Component("Blast/Foobar"), Component("Blast/BarBar") });

   renderer.render();
   al_flip_display();

   sleep(2);

   SUCCEED();
}

