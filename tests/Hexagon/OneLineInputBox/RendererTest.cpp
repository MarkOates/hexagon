
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/OneLineInputBox/Renderer.hpp>

TEST(Hexagon_OneLineInputBox_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::OneLineInputBox::Renderer renderer;
}

TEST(Hexagon_OneLineInputBox_RendererTest, render__renders_the_box)
{
   Hexagon::OneLineInputBox::Renderer renderer;
   //std::string expected_message = "foo";
   //renderer.render();
}
