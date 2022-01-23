
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Testing/WithAllegroRenderingFixture.hpp>

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
   std::string expected_error_message =
      "ObjectiveRenderer::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(objective_renderer.render(), std::runtime_error, expected_error_message);
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
