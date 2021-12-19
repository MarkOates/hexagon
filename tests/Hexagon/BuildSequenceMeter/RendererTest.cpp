
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/BuildSequenceMeter/Renderer.hpp>

class Hexagon_BuildSequenceMeter_RendererTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_BuildSequenceMeter_RendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};


TEST_F(Hexagon_BuildSequenceMeter_RendererTestWithEmptyFixture,
   can_be_created_without_blowing_up)
{
   Hexagon::BuildSequenceMeter::Renderer renderer;
}


TEST_F(Hexagon_BuildSequenceMeter_RendererTestWithAllegroRenderingFixture,
   render__without_a_font_bin__raises_an_error)
{
   Hexagon::BuildSequenceMeter::Renderer renderer;
   std::string expected_error_message =
      "Renderer::render_rectangle: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_BuildSequenceMeter_RendererTestWithAllegroRenderingFixture,
   render__without_allegro_initialized__raises_an_error)
{
   // TODO
}


TEST_F(Hexagon_BuildSequenceMeter_RendererTestWithAllegroRenderingFixture,
   render__will_not_blow_up)
{
   Hexagon::BuildSequenceMeter::Renderer renderer(&get_font_bin_ref());
   renderer.render();
   al_flip_display();
   sleep(1);
   SUCCEED();
}


