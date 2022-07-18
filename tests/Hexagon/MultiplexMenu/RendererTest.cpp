
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Testing/WithAllegroRenderingFixture.hpp>


#include <Hexagon/MultiplexMenu/Renderer.hpp>


class Hexagon_MultiplexMenu_RendererTest : public ::testing::Test
{};

class Hexagon_MultiplexMenu_RendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{
protected:
   Hexagon::MultiplexMenu::MultiplexMenuPage build_menu_page_a()
   {
      //convert_key_input_to_string(ALLEGRO_KEY_B, false, false, false, false);

      return Hexagon::MultiplexMenu::MultiplexMenuPage({
         Hexagon::MultiplexMenu::MenuItem("Shift+A", "Do thing"),
         Hexagon::MultiplexMenu::MenuItem("B", "Do other thing"),
         Hexagon::MultiplexMenu::MenuItem("N", "Some thing"),
      });
   }
   Hexagon::MultiplexMenu::MultiplexMenuPage build_menu_page_b()
   {
      return Hexagon::MultiplexMenu::MultiplexMenuPage({
         Hexagon::MultiplexMenu::MenuItem("R", "Do R thing"),
         Hexagon::MultiplexMenu::MenuItem("N", "Other thing executes"),
         Hexagon::MultiplexMenu::MenuItem("X", "Some other thing"),
      });
   }
   std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> build_dictionary_a()
   {
      return {
         { "page_a", build_menu_page_a() },
         { "page_b", build_menu_page_b() },
      };
   }
   Hexagon::MultiplexMenu::MultiplexMenu* create_multiplex_menu_a()
   {
      Hexagon::MultiplexMenu::MultiplexMenu* result;
      result = new Hexagon::MultiplexMenu::MultiplexMenu(build_dictionary_a());
      result->open_page("page_a");
      result->open_page("page_b");
      return result;
   }
};


TEST_F(Hexagon_MultiplexMenu_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::MultiplexMenu::Renderer renderer;
}


TEST_F(Hexagon_MultiplexMenu_RendererTestWithAllegroRenderingFixture, render__without_a_multiplex_menu__raises_an_error)
{
   Hexagon::MultiplexMenu::Renderer renderer;
   std::string expected_error_message =
      "Renderer::render: error: guard \"multiplex_menu\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_MultiplexMenu_RendererTestWithAllegroRenderingFixture, render__will_render_as_expected)
{
   Hexagon::MultiplexMenu::MultiplexMenu* multiplex_menu = create_multiplex_menu_a();
   al_install_keyboard();

   Hexagon::MultiplexMenu::Renderer renderer(&get_font_bin_ref(), multiplex_menu);
   al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1});

   renderer.render();

   al_flip_display();
   sleep(1);

   delete multiplex_menu;
   al_uninstall_keyboard();
   SUCCEED();
}


