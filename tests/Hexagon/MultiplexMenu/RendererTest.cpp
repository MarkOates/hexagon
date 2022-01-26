
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_MultiplexMenu_RendererTest : public ::testing::Test
{};

class Hexagon_MultiplexMenu_RendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};


#include <Hexagon/MultiplexMenu/Renderer.hpp>


TEST_F(Hexagon_MultiplexMenu_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::MultiplexMenu::Renderer renderer;
}


TEST_F(Hexagon_MultiplexMenu_RendererTest, render__without_allegro_initialized__raises_an_error)
{
   Hexagon::MultiplexMenu::Renderer renderer;
   std::string expected_error_message =
      "Renderer::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_MultiplexMenu_RendererTestWithAllegroRenderingFixture, render__will_render_as_expected)
{
   Hexagon::MultiplexMenu::Renderer renderer(&get_font_bin_ref());
   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

   renderer.render();

   al_flip_display();
   sleep(2);
   SUCCEED();
}
