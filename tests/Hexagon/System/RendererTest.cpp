
#include <gtest/gtest.h>

#include <Hexagon/System/Renderer.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


TEST(Hexagon_System_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Renderer renderer;
}

TEST(Hexagon_System_RendererTest, render__without_a_system__throws_an_error)
{
   Hexagon::System::Renderer renderer;
   ASSERT_THROW_GUARD_ERROR(
      renderer.render(),
      "Hexagon::System::Renderer::render",
      "system"
   );
}

TEST(Hexagon_System_RendererTest, render__without_a_display__throws_an_error)
{
   Hexagon::System::System system;
   Hexagon::System::Renderer renderer(&system);
   ASSERT_THROW_GUARD_ERROR(
      renderer.render(),
      "Hexagon::System::Renderer::render",
      "display"
   );
}

TEST(Hexagon_System_RendererTest, render__without_a_backfill_color__throws_an_error)
{
   al_init();

   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   Hexagon::System::System system;
   Hexagon::System::Renderer renderer(&system, display);

   ASSERT_THROW_GUARD_ERROR(
      renderer.render(),
      "Hexagon::System::Renderer::render",
      "backfill_color"
   );

   al_uninstall_system();
}

TEST(DISABLED_Hexagon_System_RendererTest, render__with_the_expected_dependencies__does_not_blow_up)
{
   // todo
}

TEST(Hexagon_System_RendererTest, render__renders_the_scene)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   Hexagon::System::System system(display);
   Hexagon::System::Renderer renderer(&system, display);

   SUCCEED();
}

TEST(DISABLED_Hexagon_System_RendererTest, render__will_render_stages_marked_as_render_on_hud_only_on_the_hud)
{
   // todo
}

