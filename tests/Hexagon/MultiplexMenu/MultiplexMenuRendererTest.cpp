
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_MultiplexMenu_MultiplexMenuRendererTest : public ::testing::Test
{};

class Hexagon_MultiplexMenu_MultiplexMenuRendererTestWithAllegroRenderingFixture
   : public Testing::WithAllegroRenderingFixture
{};


#include <Hexagon/MultiplexMenu/MultiplexMenuRenderer.hpp>


TEST_F(Hexagon_MultiplexMenu_MultiplexMenuRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::MultiplexMenu::MultiplexMenuRenderer multiplex_menu_renderer;
}


TEST_F(Hexagon_MultiplexMenu_MultiplexMenuRendererTest, render__without_allegro_initialized__raises_an_error)
{
   Hexagon::MultiplexMenu::MultiplexMenuRenderer multiplex_menu_renderer;
   std::string expected_error_message =
      "MultiplexMenuRenderer::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(multiplex_menu_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_MultiplexMenu_MultiplexMenuRendererTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   Hexagon::MultiplexMenu::MultiplexMenuRenderer multiplex_menu_renderer;
   multiplex_menu_renderer.render();
   SUCCEED();
}

