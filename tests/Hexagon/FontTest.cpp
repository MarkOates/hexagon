
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Font.hpp>

TEST(Hexagon_FontTest, can_be_created_without_blowing_up)
{
   Hexagon::Font font;
}

TEST(Hexagon_FontTest, font_filename__has_a_getter_and_is_set_to_default_values)
{
   Hexagon::Font font;
   ASSERT_EQ("Consolas.ttf", font.get_font_filename());
}

TEST(Hexagon_FontTest, font_size__has_a_getter_and_is_set_to_default_values)
{
   Hexagon::Font font;
   ASSERT_EQ(-16, font.get_font_size());
}

TEST(Hexagon_FontTest, al_font__without_a_valid_font_bin__will_raise_an_exception)
{
   Hexagon::Font font;
   std::string expected_error_message = "Font::al_font: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(font.al_font(), std::runtime_error, expected_error_message);
}

