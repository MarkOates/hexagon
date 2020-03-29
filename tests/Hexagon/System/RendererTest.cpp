
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
   std::string expected_error_message = "[System::Renderer error:] cannot render() with a nullptr system";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_RendererTest, render__without_a_display__throws_an_error)
{
   ::System system;
   Hexagon::System::Renderer renderer(&system);
   std::string expected_error_message = "[System::Renderer error:] cannot render() with a nullptr display";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_RendererTest, render__renders_the_scene)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   ::System system(display);
   Hexagon::System::Renderer renderer(&system, display);

   SUCCEED();
}
