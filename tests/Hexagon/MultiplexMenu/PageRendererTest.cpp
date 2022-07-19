
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Testing/WithAllegroRenderingFixture.hpp>

#include <Hexagon/MultiplexMenu/PageRenderer.hpp>


class Hexagon_MultiplexMenu_PageRendererTest : public ::testing::Test
{};

class Hexagon_MultiplexMenu_PageRendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{
protected:
   Hexagon::MultiplexMenu::MultiplexMenuPage* create_menu_page_a()
   {
      return new Hexagon::MultiplexMenu::MultiplexMenuPage({
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_A, true}, "Do thing"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_B}, "Do other thing"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_N}, "Some thing"),
      });
   }
   Hexagon::MultiplexMenu::MultiplexMenuPage* create_menu_page_b()
   {
      return new Hexagon::MultiplexMenu::MultiplexMenuPage({
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_R}, "Do R thing"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_N}, "Other thing executes"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_X}, "Some other thing"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_Z}, "Something else"),
      });
   }
};


TEST_F(Hexagon_MultiplexMenu_PageRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::MultiplexMenu::PageRenderer renderer;
}


TEST_F(Hexagon_MultiplexMenu_PageRendererTest, render__without_allegro_initialized__raises_an_error)
{
   Hexagon::MultiplexMenu::PageRenderer renderer;
   std::string expected_error_message =
      "PageRenderer::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_MultiplexMenu_PageRendererTestWithAllegroRenderingFixture,
   render__without_a_font_bin__will_throw_an_error)
{
   Hexagon::MultiplexMenu::PageRenderer renderer;
   std::string expected_error_message =
      "PageRenderer::render: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_MultiplexMenu_PageRendererTestWithAllegroRenderingFixture,
   VISUAL__render__without_a_page__will_render_a_special_empty_page)
{
   Hexagon::MultiplexMenu::PageRenderer renderer(&get_font_bin_ref());
   al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1});
   renderer.render();
   al_flip_display();
   sleep(1);
}


TEST_F(Hexagon_MultiplexMenu_PageRendererTestWithAllegroRenderingFixture, render__will_render_as_expected)
{
   Hexagon::MultiplexMenu::MultiplexMenuPage* page = create_menu_page_b();
   Hexagon::MultiplexMenu::PageRenderer renderer(&get_font_bin_ref(), page);
   al_install_keyboard();

   al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1});
   renderer.render();
   al_flip_display();
   sleep(1);

   delete page;
   al_uninstall_keyboard();
   SUCCEED();
}


TEST_F(Hexagon_MultiplexMenu_PageRendererTest,
   convert_key_input_to_string__without_allegro_initialized__will_throw_an_error)
{
   Hexagon::MultiplexMenu::PageRenderer renderer;
   std::string expected_error_message =
      "PageRenderer::convert_key_input_to_string: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.convert_key_input_to_string(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_MultiplexMenu_PageRendererTest,
   convert_key_input_to_string__without_a_keyboard_initialized__will_throw_an_error)
{
   al_init();
   Hexagon::MultiplexMenu::PageRenderer renderer;
   std::string expected_error_message =
      "PageRenderer::convert_key_input_to_string: error: guard \"al_is_keyboard_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.convert_key_input_to_string(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(Hexagon_MultiplexMenu_PageRendererTest,
   convert_key_input_to_string__will_return_a_string_representation_of_the_keyboard_input)
{
   al_init();
   al_install_keyboard();
   Hexagon::MultiplexMenu::PageRenderer renderer;

   EXPECT_EQ("Shift+N", renderer.convert_key_input_to_string(ALLEGRO_KEY_N, false, false, false, true));
   EXPECT_EQ("Ctrl+Shift+DOWN", renderer.convert_key_input_to_string(ALLEGRO_KEY_DOWN, true, false, false, true));
   EXPECT_EQ("Command+SPACE", renderer.convert_key_input_to_string(ALLEGRO_KEY_SPACE, false, false, true, false));

   al_uninstall_system();
}


