
#include <gtest/gtest.h>

#include <Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>

class Hexagon_ObjectivesLog_ObjectiveRendererTest : public ::testing::Test
{};

class Hexagon_ObjectivesLog_ObjectiveRendererTestWithAllegroRenderingFixture :
   public Testing::WithAllegroRenderingFixture
{};

#include <Hexagon/ObjectivesLog/ObjectiveRenderer.hpp>


TEST_F(Hexagon_ObjectivesLog_ObjectiveRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::ObjectivesLog::ObjectiveRenderer objective_renderer;
}


TEST_F(Hexagon_ObjectivesLog_ObjectiveRendererTest, render__without_allegro_initialized__raises_an_error)
{
   Hexagon::ObjectivesLog::ObjectiveRenderer objective_renderer;
   ASSERT_THROW_GUARD_ERROR(
      objective_renderer.render(),
      "Hexagon::ObjectivesLog::ObjectiveRenderer::render",
      "al_is_system_installed()"
   );
}


TEST_F(Hexagon_ObjectivesLog_ObjectiveRendererTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   Hexagon::ObjectivesLog::Objective objective;
   Hexagon::ObjectivesLog::ObjectiveRenderer objective_renderer(&get_font_bin_ref(), &objective);
   objective_renderer.render();
   SUCCEED();
}


TEST_F(Hexagon_ObjectivesLog_ObjectiveRendererTestWithAllegroRenderingFixture, render__will_render_the_objective)
{
   Hexagon::ObjectivesLog::Objective objective;
   Hexagon::ObjectivesLog::ObjectiveRenderer objective_renderer(&get_font_bin_ref(), &objective);
   objective_renderer.set_is_activated(true);

   al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1.0});
   objective_renderer.render();
   al_flip_display();
   sleep(2);

   SUCCEED();
}


