
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/System/Renderer.hpp>

TEST(Hexagon_System_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Renderer renderer;
}

TEST(Hexagon_System_RendererTest, render__without_a_system__throws_an_error)
{
   Hexagon::System::Renderer renderer;
   std::string expected_error_message = "Renderer::render: error: guard \"system\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_RendererTest, render__without_a_display__throws_an_error)
{
   Hexagon::System::System system;
   Hexagon::System::Renderer renderer(&system);
   std::string expected_error_message = "Renderer::render: error: guard \"display\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_RendererTest, render__without_a_backfill_color__throws_an_error)
{
   al_init();

   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   Hexagon::System::System system;
   Hexagon::System::Renderer renderer(&system, display);

   std::string expected_error_message = "Renderer::render: error: guard \"backfill_color\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);

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

