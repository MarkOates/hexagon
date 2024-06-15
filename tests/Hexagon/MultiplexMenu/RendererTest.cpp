
#include <gtest/gtest.h>

#include <Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <Hexagon/MultiplexMenu/Renderer.hpp>


class Hexagon_MultiplexMenu_RendererTest : public ::testing::Test
{};

class Hexagon_MultiplexMenu_RendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{
protected:
   Hexagon::MultiplexMenu::MultiplexMenuPage build_menu_page_a()
   {
      return Hexagon::MultiplexMenu::MultiplexMenuPage({
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_A, true}, "Do thing"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_B},       "Do other thing"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_N},       "Some thing"),
      });
   }
   Hexagon::MultiplexMenu::MultiplexMenuPage build_menu_page_b()
   {
      return Hexagon::MultiplexMenu::MultiplexMenuPage({
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_R}, "Do R thing"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_N}, "Other thing executes"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_X}, "Some other thing"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_Z}, "Something else"),
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
      result->open_page("a-page-that-does-not-exist");
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
   ASSERT_THROW_GUARD_ERROR(
      renderer.render(),
      "Hexagon::MultiplexMenu::Renderer::render",
      "multiplex_menu"
   );
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


