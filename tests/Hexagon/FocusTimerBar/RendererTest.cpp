#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class Hexagon_FocusTimerBar_RendererTest : public ::testing::Test {};
class Hexagon_FocusTimerBar_RendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <Hexagon/FocusTimerBar/Renderer.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(Hexagon_FocusTimerBar_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::FocusTimerBar::Renderer renderer;
}


TEST_F(Hexagon_FocusTimerBar_RendererTest, render__without_allegro_initialized__raises_an_error)
{
   Hexagon::FocusTimerBar::Renderer renderer;
   EXPECT_THROW_GUARD_ERROR(
      renderer.render(),
      "Hexagon::FocusTimerBar::Renderer::render",
      "al_is_system_installed()"
   );
}


TEST_F(Hexagon_FocusTimerBar_RendererTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   Hexagon::FocusTimerBar::Renderer renderer;
   EXPECT_THROW_GUARD_ERROR(
      renderer.render(),
      "Hexagon::FocusTimerBar::Renderer::render",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(Hexagon_FocusTimerBar_RendererTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   Hexagon::FocusTimerBar::Renderer renderer;
   EXPECT_THROW_GUARD_ERROR(
      renderer.render(),
      "Hexagon::FocusTimerBar::Renderer::render",
      "al_is_font_addon_initialized()"
   );
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(Hexagon_FocusTimerBar_RendererTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   Hexagon::FocusTimerBar::Renderer renderer;
   EXPECT_THROW_GUARD_ERROR(
      renderer.render(),
      "Hexagon::FocusTimerBar::Renderer::render",
      "font_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(Hexagon_FocusTimerBar_RendererTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   Hexagon::FocusTimerBar::FocusTimerBar focus_timer_bar;
   Hexagon::FocusTimerBar::Renderer renderer(&get_font_bin_ref());
   renderer.set_focus_timer_bar(&focus_timer_bar);
   renderer.render();
   al_flip_display();
   sleep_for(1);
}


