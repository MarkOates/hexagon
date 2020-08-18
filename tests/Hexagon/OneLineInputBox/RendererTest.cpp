
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

TEST(Hexagon_OneLineInputBox_RendererTest, get_lines_character_count__returns_the_number_of_characters_in_the_input)
{
   Hexagon::OneLineInputBox::Renderer renderer(
      nullptr, ALLEGRO_COLOR{0, 0, 0, 0}, ALLEGRO_COLOR{0, 0, 0, 0}, 0, 0, 0, 0,
      {
         "This is the line",
      }
   );
   ASSERT_EQ(16, renderer.get_lines_character_count());
}

