
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/AdvancedComponentNavigator/Renderer.hpp>

TEST(Hexagon_AdvancedComponentNavigator_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedComponentNavigator::Renderer renderer;
}

TEST(Hexagon_AdvancedComponentNavigator_RendererTest, render__without_a_stage_throws_an_error)
{
   Hexagon::AdvancedComponentNavigator::Renderer renderer;
   std::string expected_message = "Renderer::render: error: guard \"stage\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_message);
}

TEST(Hexagon_AdvancedComponentNavigator_RendererTest, render__without_a_font_throws_an_error)
{
   Hexagon::AdvancedComponentNavigator::Stage stage;
   Hexagon::AdvancedComponentNavigator::Renderer renderer(&stage);
   std::string expected_message = "Renderer::render: error: guard \"font\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_message);
}
