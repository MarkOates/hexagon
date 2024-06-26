
#include <gtest/gtest.h>

#include <Hexagon/ProjectComponentNavigator/Renderer.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class Hexagon_ProjectComponentNavigator_RendererWithFixtureTest : public ::testing::Test
{
protected:
   ALLEGRO_DISPLAY *display;
   Hexagon::ProjectComponentNavigator::Stage *stage;
   ALLEGRO_FONT *font;
   Hexagon::ProjectComponentNavigator::Renderer *renderer;

   Hexagon_ProjectComponentNavigator_RendererWithFixtureTest()
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
      display = al_create_display(1920 / 5 * 4, 1080 / 5 * 4);
      ASSERT_NE(nullptr, display);

      font = al_create_builtin_font();
      int cell_width = al_get_text_width(font, "X");
      int cell_height = al_get_font_line_height(font);
      ALLEGRO_COLOR base_backfill_color = al_color_name("black");
      float backfill_opacity = 0.8f;
      ALLEGRO_COLOR base_text_color = al_color_name("white");
      stage = new Hexagon::ProjectComponentNavigator::Stage();
      renderer = new Hexagon::ProjectComponentNavigator::Renderer(
         stage, font, cell_width, cell_height, &base_backfill_color, backfill_opacity, &base_text_color
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
      al_destroy_font(font);
      delete stage;
      delete renderer;

      if (al_get_current_display()) al_destroy_display(al_get_current_display());
      al_uninstall_system();
   }

   Hexagon::ProjectComponentNavigator::Stage &get_stage_fixture()
   {
      return *stage;
   }

   Hexagon::ProjectComponentNavigator::Renderer &get_renderer_fixture()
   {
      return *renderer;
   }
};


TEST(Hexagon_ProjectComponentNavigator_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::ProjectComponentNavigator::Renderer renderer;
}


TEST(Hexagon_ProjectComponentNavigator_RendererTest, render__and__render_raw__without_a_stage_throws_an_error)
{
   Hexagon::ProjectComponentNavigator::Renderer renderer;
   ASSERT_THROW_GUARD_ERROR(
      renderer.render(),
      "Hexagon::ProjectComponentNavigator::Renderer::render",
      "stage"
   );
   ASSERT_THROW_GUARD_ERROR(
      renderer.render_raw(),
      "Hexagon::ProjectComponentNavigator::Renderer::render_raw",
      "stage"
   );
}


TEST(Hexagon_ProjectComponentNavigator_RendererTest, render__and__render_raw__without_a_font_throws_an_error)
{
   Hexagon::ProjectComponentNavigator::Stage stage;
   Hexagon::ProjectComponentNavigator::Renderer renderer(&stage);
   ASSERT_THROW_GUARD_ERROR(
      renderer.render(),
      "Hexagon::ProjectComponentNavigator::Renderer::render",
      "font"
   );
   ASSERT_THROW_GUARD_ERROR(
      renderer.render_raw(),
      "Hexagon::ProjectComponentNavigator::Renderer::render_raw",
      "font"
   );
}


TEST_F(Hexagon_ProjectComponentNavigator_RendererWithFixtureTest, render__renders_the_component_navigator)
{
   Hexagon::ProjectComponentNavigator::Renderer &renderer = get_renderer_fixture();

   al_clear_to_color(al_color_name("gray"));
   renderer.render();
   al_flip_display();

   //sleep(2);

   SUCCEED();
}


TEST_F(Hexagon_ProjectComponentNavigator_RendererWithFixtureTest, render__renders_the_component_navigator_nodes)
{
   Hexagon::ProjectComponentNavigator::Renderer &renderer = get_renderer_fixture();
   Hexagon::ProjectComponentNavigator::Stage &stage = get_stage_fixture();
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator &component = stage.get_component_ref();
   using Hexagon::Layout;

   component.set_nodes({ Layout("Blast/Foobar"), Layout("Blast/BarBar") });

   al_clear_to_color(al_color_name("gray"));
   renderer.render();
   al_flip_display();

   //sleep(2);

   SUCCEED();
}


TEST_F(Hexagon_ProjectComponentNavigator_RendererWithFixtureTest, render__renders_the_search_text)
{
   Hexagon::ProjectComponentNavigator::Renderer &renderer = get_renderer_fixture();
   Hexagon::ProjectComponentNavigator::Stage &stage = get_stage_fixture();
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator &component = stage.get_component_ref();
   using Hexagon::Layout;

   component.set_search_text("Blast");

   stage.process_local_event("refresh_list");
   stage.process_local_event("move_cursor_down");
   stage.process_local_event("move_cursor_down");

   al_clear_to_color(al_color_name("gray"));
   renderer.render();
   al_flip_display();

   //sleep(1);

   SUCCEED();
}

